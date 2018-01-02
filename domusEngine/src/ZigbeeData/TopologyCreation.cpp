//
// Created by paolo on 26/09/16.
//

#include <chrono>
#include <iomanip>
#include <zigbee/ZigbeeDevice.h>
#include <boost/log/trivial.hpp>
#include "TopologyCreation.h"
#include "ZDevices.h"
#include "ZDevice.h"

using std::thread;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

namespace zigbee {

    TopologyCreation::~TopologyCreation() {
        stop = true;
        auto zDevices = singletonObjects->getZDevices();
        if (zDevices != nullptr) {
            zDevices->removeObserver(observerCallback);
            if (requestThread.joinable())
                requestThread.join();
        }
    }

    void TopologyCreation::create() {
        auto zDevices = singletonObjects->getZDevices();
        observerCallback = [this](ZDevice *device) { this->addDevice(device); };
        zDevices->addObserver(observerCallback);
        toDo.insert(NwkAddr(0));
        stop = false;
        requestThread = std::thread([this]() { this->manageRequest(); });
    }

    void TopologyCreation::addDevice(ZDevice *device) {
        BOOST_LOG_TRIVIAL(info) << "add device " << device->getNwkAddr();
        std::unique_lock<std::mutex> lock(mutex);
        doing.erase(device->getNwkAddr());
        done.insert(device->getNwkAddr());
        BOOST_LOG_TRIVIAL(info) << "removed device " << device->getNwkAddr();
        for (auto &child: device->getChildren()) {
            if (done.count(child) == 0) {
                toDo.insert(child);
            }
        }
    }

    void TopologyCreation::manageRequest() {
        seconds requestTimeout(30);
        milliseconds sleepTime(100);
        auto zigbeeDevice = singletonObjects->getZigbeeDevice();
        while (!stop && (!toDo.empty() || !doing.empty())) {
            while (!stop && ((doing.size() < 3 && !toDo.empty()) || (doing.empty() && toDo.empty()))) {
                auto iter = toDo.begin();
                auto nwkAddr = *iter;
                {
                    std::unique_lock<std::mutex> lock(mutex);
                    toDo.erase(iter);
                    doing.insert(std::make_pair(nwkAddr, system_clock::now()));
                }
                zigbeeDevice->getIEEEAddress(nwkAddr, Extended, 0);

                if (!stop) {
                    sleep(sleepTime);
                }

            }
            if (!stop)
                sleep(sleepTime);
            auto now = system_clock::now();
            std::set<NwkAddr> timeout;
            for (auto &inDoing: doing) {
                if (now - inDoing.second > requestTimeout) {
                    timeout.insert(inDoing.first);
                    BOOST_LOG_TRIVIAL(warning) << "device " << std::hex<<inDoing.first << " does not respond";
                    toDo.insert(inDoing.first);
                }
            }
            for (const auto & key: timeout)
                doing.erase(key);
        }
        BOOST_LOG_TRIVIAL(info) << "calling topology observer";
        for (auto &observer: observers) {
            observer();
        }
    }

    void TopologyCreation::addObserver(const std::function<void()> &observer) {
        observers.push_back(observer);
    }


}
