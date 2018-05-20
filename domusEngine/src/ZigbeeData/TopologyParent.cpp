//
// Created by paolo on 09/04/18.
//
#include <algorithm>
#include <zigbee/ZigbeeDevice.h>
#include <boost/log/trivial.hpp>
#include "../ZigbeeData/ZDevices.h"
#include "../Utils/SingletonObjects.h"
#include "TopologyParent.h"
#include "TopologyCreation.h"

constexpr uint32_t MAX_RETRY = 3;

namespace zigbee {

    TopologyParent::TopologyParent(NwkAddr addr, TopologyCreation *owner, SingletonObjects *singletonObjects) : singletonObjects(singletonObjects), owner(owner), addr(addr),
                                                                                                                pendingFor(0), totalTables(-1) {}

    void TopologyParent::requestChildren() {
        BOOST_LOG_TRIVIAL(info) << "starting worker for " << addr;
        if (worker.joinable())
            worker.join();
        worker = boost::fibers::fiber([this]() {
            auto response = std::make_unique<TopologyParentResponse>(this);
            auto zigbeeDevice = singletonObjects->getZigbeeDevice();


            if (totalTables == -1) {
                pendingFor = 0;
                BOOST_LOG_TRIVIAL(info) << "starting request LQI for device " << addr;
                zigbeeDevice->registerForLQIResponse(addr, std::move(response));
                zigbeeDevice->getLqiResponse(addr, pendingFor);
            } else {
                BOOST_LOG_TRIVIAL(info) << "Requesting children of " << addr;
                for (uint32_t index = 0; index < responded.size(); index++) {
                    if (responded[index] < MAX_RETRY) {
                        pendingFor = index;
                        responded[index]++;
                        BOOST_LOG_TRIVIAL(info) << "request LQI for device " << addr << ", index " << pendingFor;
                        zigbeeDevice->registerForLQIResponse(addr, std::move(response));
                        zigbeeDevice->getLqiResponse(addr, pendingFor);
                        break;
                    }
                }
                for (TopologyParent *child: routesChildren) {
                    BOOST_LOG_TRIVIAL(info) << "Insert request for " << child->addr;
                    owner->channel.push(child);
                    BOOST_LOG_TRIVIAL(info) << "Inserted request for " << child->addr;
                }
            }
            BOOST_LOG_TRIVIAL(info) << "end worker for " << addr;
        });

    }

    void TopologyParent::response(std::shared_ptr<LqiResponse> lqiResponse) {
        BOOST_LOG_TRIVIAL(info) << "Arrive LQI response " << *(lqiResponse);
        if (responded.empty()) {
            responded.resize(lqiResponse->totalTables, 0);
        }
        totalTables = lqiResponse->totalTables;
        ZDevices *zDevices = singletonObjects->getZDevices();
        for (auto &table: lqiResponse->tables) {
            if (table.relationship == Relationship::NeighborIsChild) {
                zDevices->put(table.ieeeAddr, table.nwkAddr);
                singletonObjects->getZigbeeDevice()->requestActiveEndpoints(table.nwkAddr);
                if (owner->devices.count(table.ieeeAddr) == 0) {
                    owner->devices.insert(std::make_pair(table.ieeeAddr, std::make_unique<TopologyParent>(table.nwkAddr, owner, singletonObjects)));
                }
                if (table.logicalType == LogicalType::ZigbeeRouter)
                    routesChildren.push_back(owner->devices[table.ieeeAddr].get());
            }
            BOOST_LOG_TRIVIAL(info) << "table.index=" << table.index;
            responded[table.index] = UINT32_MAX;
        }
        owner->channel.push(this);
    }

    void TopologyParent::timeout() {
        BOOST_LOG_TRIVIAL(info) << "Timeout LQI response of the device " << addr;
        if (responded.size() > pendingFor)
            responded[pendingFor]++;
        owner->channel.push(this);
    }
}