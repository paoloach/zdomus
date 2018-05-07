//
// Created by paolo on 26/09/16.
//


#include <chrono>
#include <iomanip>
#include <zigbee/ZigbeeDevice.h>
#include <boost/log/trivial.hpp>
#include "TopologyCreation.h"
#include "../Utils/SingletonObjects.h"
#include "ZDevices.h"
#include "ZDevice.h"
#include "TopologyParent.h"

using std::thread;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

namespace zigbee {

    TopologyCreation::~TopologyCreation() {
        stop = true;
        topologyFiber.join();
    }

    void TopologyCreation::start() {
        stop  = false;
        topologyFiber = boost::fibers::fiber([this]() {
            auto coordinator = TopologyParent(NwkAddr{0}, this, singletonObjects);
            coordinator.requestChildren();
            for (auto &&data: channel) {
                if (this->stop)
                    return;
                data->requestChildren();
                boost::this_fiber::yield();
            }
        });
    }
}
