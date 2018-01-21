//
// Created by paolo on 27/01/17.
//

#include <boost/fiber/algo/round_robin.hpp>
#include <boost/fiber/operations.hpp>
#include <boost/log/trivial.hpp>
#include <boost/endian/conversion.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <zcl/Cluster.h>
#include <zcl/StatusEnum.h>
#include <zigbee/ZigbeeDevice.h>
#include <zigbee/messageStructure/DeviceInfoMessage.h>
#include "../Utils/Clusters.h"
#include "../Utils/SingletonObjects.h"
#include "../Utils/DeviceInfoDispatcher.h"
#include "../Database/DBTableFactory.h"
#include "../Database/DBRow.h"
#include "../Database/DBTable.h"
#include "DemoDevice.h"

using boost::fibers::fiber;
using boost::fibers::mutex;
using boost::fibers::condition_variable;
using namespace std::chrono_literals;
using std::chrono::system_clock;
using std::unique_lock;
using std::get;

namespace zigbee {
    using namespace std::chrono_literals;
    constexpr uint8_t typeBOOLRAN = 0x10;
    constexpr uint8_t typeUINT8 = 0x20;
    constexpr uint8_t typeUINT16 = 0x21;
    constexpr uint8_t typeUINT24 = 0x22;
    constexpr uint8_t typeUINT32 = 0x23;
    constexpr uint8_t typeUINT64 = 0x27;
    constexpr uint8_t typeSINT8 = 0x28;
    constexpr uint8_t typeSINT16 = 0x29;
    constexpr uint8_t typeSINT24 = 0x2A;
    constexpr uint8_t typeSINT32 = 0x2B;
    constexpr uint8_t typeSINT64 = 0x2F;


    constexpr uint8_t typeCHAR_STRING = 0x42;
    constexpr uint8_t type8BIT_ENUM = 0x30;
    constexpr uint8_t type16BIT_ENUM = 0x31;

    static ExtAddress extAddress0({0x01, 0x02, 0x03, 0x04, 0x1A, 0x1B, 0x1C, 0x1D});
    static constexpr NwkAddr NWK_ADDR1{0x1234};
    static ExtAddress extAddress1({0x01, 0x02, 0x03, 0x04, 0x2A, 0x2B, 0x2C, 0x2D});
    static constexpr NwkAddr NWK_ADDR2{0x1232};
    static ExtAddress extAddress2({0x01, 0x02, 0x03, 0x04, 0x3A, 0x3B, 0x3C, 0x3D});
    static constexpr NwkAddr NWK_ADDR3{0x8935};
    static ExtAddress extAddress3({0x01, 0x02, 0x03, 0x04, 0x4A, 0x4B, 0x4C, 0x4E});

    static std::vector<uint8_t> cluster0_0 = {typeUINT8, 0x01};
    static std::vector<uint8_t> cluster0_1 = {typeUINT8, 0x10};
    static std::vector<uint8_t> cluster0_2 = {typeUINT8, 0x01};
    static std::vector<uint8_t> cluster0_3 = {typeUINT8, 0x01};
    static std::vector<uint8_t> cluster0_4 = {typeCHAR_STRING, 0x08, 'a', 'c', 'h', 'd', 'j', 'i', 'a', 'n'};
    static std::vector<uint8_t> cluster0_5_switch = {typeCHAR_STRING, 0x07, 's', 'w', 'i', 't', 'c', 'h', '1'};
    static std::vector<uint8_t> cluster0_5_light_switch = {typeCHAR_STRING, 12, 'l', 'i', 'g', 'h', 't', ' ', 's', 'w', 'i', 't', 'c', 'h'};
    static std::vector<uint8_t> cluster0_5_ztemp = {typeCHAR_STRING, 5, 'z', 't', 'e', 'm', 'p'};
    static std::vector<uint8_t> cluster0_5_on_off_light = {typeCHAR_STRING, 12, 'o', 'n', '/', 'o', 'f', 'f', ' ', 'l', 'i', 'g', 't', 'h'};
    static std::vector<uint8_t> cluster0_5_on_off = {typeCHAR_STRING, 12, 'o', 'n', '/', 'o', 'f', 'f'};
    static std::vector<uint8_t> cluster0_6 = {typeCHAR_STRING, 8, '2', '0', '1', '6', '0', '4', '1', '2'};
    static std::vector<uint8_t> cluster0_7_battery = {type8BIT_ENUM, 8};
    static std::vector<uint8_t> cluster0_7_DC = {type8BIT_ENUM, 0x10};

    static std::array<std::vector<uint8_t>, 8> NKW1_4_0 = {cluster0_0, cluster0_1, cluster0_2, cluster0_3, cluster0_4, cluster0_5_switch, cluster0_6, cluster0_7_battery,};
    static std::array<std::vector<uint8_t>, 8> NKW1_6_0 = {cluster0_0, cluster0_1, cluster0_2, cluster0_3, cluster0_4, cluster0_5_light_switch, cluster0_6, cluster0_7_battery,};
    static std::array<std::vector<uint8_t>, 8> NKW1_7_0 = {cluster0_0, cluster0_1, cluster0_2, cluster0_3, cluster0_4, cluster0_5_light_switch, cluster0_6, cluster0_7_DC,};
    static std::array<std::vector<uint8_t>, 8> NKW2_5_0 = {cluster0_0, cluster0_1, cluster0_2, cluster0_3, cluster0_4, cluster0_5_ztemp, cluster0_6, cluster0_7_battery,};
    static std::array<std::vector<uint8_t>, 8> NKW2_7_0 = {cluster0_0, cluster0_1, cluster0_2, cluster0_3, cluster0_4, cluster0_5_on_off, cluster0_6, cluster0_7_battery,};
    static std::array<std::vector<uint8_t>, 8> NKW2_11_0 = {cluster0_0, cluster0_1, cluster0_2, cluster0_3, cluster0_4, cluster0_5_on_off_light, cluster0_6, cluster0_7_battery,};
    static std::array<std::vector<uint8_t>, 8> NKW3_7_0 = {cluster0_0, cluster0_1, cluster0_2, cluster0_3, cluster0_4, cluster0_5_ztemp, cluster0_6, cluster0_7_battery,};

    static std::string toStr(std::chrono::system_clock::time_point & timePoint );


    std::string toStr(std::chrono::system_clock::time_point & timePoint ){
        std::time_t epoch = system_clock::to_time_t(timePoint);
        std::tm * localTime = std::localtime(&epoch);
        std::stringstream stream;
        stream << "'"<< (localTime->tm_year+1900) << "-" << (localTime->tm_mon+1) << "-" << localTime->tm_mday << " " ;
        stream << localTime->tm_hour << ":" <<localTime->tm_min << ":" << localTime->tm_sec << "'";
        return stream.str();
    }



    DemoDevice::DemoDevice(SingletonObjects * singletonObjects, std::chrono::seconds seconds) : ZigbeeDevice(seconds), singletonObjects(singletonObjects), stop(false), e1(rd()) {
        BOOST_LOG_TRIVIAL(info) << "-------------------------- DEMO MODE ------------------------";
        demoThread = std::thread([this] { runDemoThread(); });

        DBTableFactory tableFactory;

        auto table = tableFactory.getTable("Temperatures");
        auto now = std::chrono::system_clock::now();
        auto date = now - 24h;
        double value= 1800;
        while (date < now){
            DBRow row1;
            DBRow row2;
            auto nextDate = date + 5min;
            auto result = table->find(" time between " + toStr(date) + " AND " + toStr(nextDate));
            if (result.numberOfRow()==0) {
                row1.setValue("time", toStr(date));
                row1.setValue("value", (int)value);
                row1.setValue("network_id", (int) NWK_ADDR2.getId());
                table->insert(&row1);

                row2.setValue("time", toStr(date));
                row2.setValue("value", (int)value);
                row2.setValue("network_id", (int) NWK_ADDR3.getId());
                table->insert(&row2);
            }
            date  = nextDate;
            value += 2.0833333;
        }

    }

    void DemoDevice::runDemoThread() {
        boost::fibers::use_scheduling_algorithm<boost::fibers::algo::round_robin>();
        powerNodeQueue.startDequeFiber();
        attributeQueue.startDequeFiber();
        ieeeAddressResponseQueue.startDequeFiber();
        BOOST_LOG_NAMED_SCOPE("demo_driver");
        BOOST_LOG_TRIVIAL(info) << "Demo attribute service thread started";
        boost::fibers::fiber fiberPowerNodeSetDeque([this]() {
            for (auto &&nwkAddr: powerNodeSet) {
                boost::fibers::fiber setPowerMode([this, nwkAddr]() {
                    auto powerNodeData = std::make_shared<PowerNodeData>();
                    powerNodeData->nwkAddr = nwkAddr;
                    boost::this_fiber::sleep_for(3s);
                    BOOST_LOG_TRIVIAL(info) << "Notify power node arrived";
                    switch (nwkAddr.getId()) {
                        case NWK_ADDR1.getId():
                            powerNodeData->error = false;
                            powerNodeData->currentPowerSource = PowerSource(4);
                            powerNodeData->availablePowerSource = PowerSource(4);
                            powerNodeData->powerMode = PowerMode::RECV_AUTO;
                            powerNodeData->currentPowerSourceLevel = PowerLevel::CRITICAL;
                            break;
                        case NWK_ADDR2.getId():
                            powerNodeData->error = false;
                            powerNodeData->currentPowerSource = PowerSource(4);
                            powerNodeData->availablePowerSource = PowerSource(4);
                            powerNodeData->powerMode = PowerMode::RECV_AUTO;
                            powerNodeData->currentPowerSourceLevel = PowerLevel::LEVEL_33;
                            break;
                        case NWK_ADDR3.getId():
                            powerNodeData->error = false;
                            powerNodeData->currentPowerSource = PowerSource(4);
                            powerNodeData->availablePowerSource = PowerSource(4);
                            powerNodeData->powerMode = PowerMode::ALWAYS_ON;
                            powerNodeData->currentPowerSourceLevel = PowerLevel::LEVEL_100;
                            break;
                        default:
                            powerNodeData->error = true;
                            break;

                    }
                    powerNodeQueue.setData(nwkAddr, powerNodeData);
                });
                fibers.push_back(std::move(setPowerMode));
            }
        });


        boost::fibers::fiber fiberInitSendIEEEAddress([this]() {
            boost::this_fiber::sleep_for(2s);
            this->init();
        });


        while (!stop) {
            std::this_thread::__sleep_for(0s, 10us);
            boost::this_fiber::yield();
            for (auto &attribute: intValuesMap) {
                BOOST_LOG_TRIVIAL(info) << "new attribute request: " << attribute.first;
                if (attribute.first.clusterId == ClustersId::IDENTIFY_CLUSTER) {
                    if (attribute.second > 0) {
                        attribute.second--;
                    }
                }
            }
            auto now = std::chrono::system_clock::now();
            auto list_iterator = posponedCallbacks.begin();
            while (list_iterator != posponedCallbacks.end()) {
                if (std::get<0>(*list_iterator) <= now) {
                    std::get<1>(*list_iterator)();
                    list_iterator = posponedCallbacks.erase(list_iterator);
                } else {
                    ++list_iterator;
                }

            }
        }
    }


    bool DemoDevice::isPresent() {
        return true;
    }

    bool DemoDevice::enableLog() {
        return false;
    }

    void DemoDevice::requestNodePower(zigbee::NwkAddr nwkAddr) {
        powerNodeSet.push(nwkAddr);
    }

    void DemoDevice::requestActiveEndpoints(zigbee::NwkAddr nwkAddr) {
        auto zDevices = singletonObjects->getZDevices();
        if (nwkAddr == NWK_ADDR1) {
            SimpleDescMessage simpleDescMessage;
            simpleDescMessage.nwkAddr = NWK_ADDR1.getId();
            simpleDescMessage.endpoint = 4;
            simpleDescMessage.numInClusters = 3;
            simpleDescMessage.numOutClusters = 0;
            simpleDescMessage.appDeviceId = 0x51; // SMART PLUG
            simpleDescMessage.clustersList[0] = ClustersId::BASIC_CLUSTER;
            simpleDescMessage.clustersList[1] = ClustersId::IDENTIFY_CLUSTER;
            simpleDescMessage.clustersList[2] = ClustersId::METERING;
            simpleDescMessage.clustersList[3] = ClustersId::ON_OFF_CLUSTER;
            zDevices->put(simpleDescMessage);

            simpleDescMessage.endpoint = 6;
            simpleDescMessage.numInClusters = 2;
            simpleDescMessage.numOutClusters = 4;
            simpleDescMessage.appDeviceId = 0; // ON OFF SWITCH
            simpleDescMessage.clustersList[0] = ClustersId::BASIC_CLUSTER;
            simpleDescMessage.clustersList[1] = ClustersId::IDENTIFY_CLUSTER;
            simpleDescMessage.clustersList[2] = ClustersId::ON_OFF_CLUSTER;
            simpleDescMessage.clustersList[3] = ClustersId::IDENTIFY_CLUSTER;
            simpleDescMessage.clustersList[4] = ClustersId::SCENE_CLUSTER;
            simpleDescMessage.clustersList[5] = ClustersId::GROUPS_CLUSTER;
            zDevices->put(simpleDescMessage);

            simpleDescMessage.endpoint = 7;
            simpleDescMessage.numInClusters = 2;
            simpleDescMessage.numOutClusters = 4;
            simpleDescMessage.appDeviceId = 0x103; // ON OFF LIGHT SWITCH
            simpleDescMessage.clustersList[0] = ClustersId::BASIC_CLUSTER;
            simpleDescMessage.clustersList[1] = ClustersId::IDENTIFY_CLUSTER;
            simpleDescMessage.clustersList[2] = ClustersId::ON_OFF_CLUSTER;
            simpleDescMessage.clustersList[3] = ClustersId::IDENTIFY_CLUSTER;
            simpleDescMessage.clustersList[4] = ClustersId::SCENE_CLUSTER;
            simpleDescMessage.clustersList[5] = ClustersId::GROUPS_CLUSTER;
            zDevices->put(simpleDescMessage);
        }

        if (nwkAddr == NWK_ADDR2) {
            SimpleDescMessage simpleDescMessage;
            simpleDescMessage.nwkAddr = NWK_ADDR2.getId();
            simpleDescMessage.endpoint = 5;
            simpleDescMessage.numInClusters = 3;
            simpleDescMessage.numOutClusters = 0;
            simpleDescMessage.appDeviceId = 0x302; // Temp sensor
            simpleDescMessage.clustersList[0] = ClustersId::BASIC_CLUSTER;
            simpleDescMessage.clustersList[1] = ClustersId::IDENTIFY_CLUSTER;
            simpleDescMessage.clustersList[2] = ClustersId::TEMPERATURE_MEASUREMENT;
            zDevices->put(simpleDescMessage);


            simpleDescMessage.endpoint = 7;
            simpleDescMessage.numInClusters = 5;
            simpleDescMessage.numOutClusters = 0;
            simpleDescMessage.appDeviceId = 0x02; // On off output
            simpleDescMessage.clustersList[0] = ClustersId::BASIC_CLUSTER;
            simpleDescMessage.clustersList[1] = ClustersId::IDENTIFY_CLUSTER;
            simpleDescMessage.clustersList[2] = ClustersId::ON_OFF_CLUSTER;
            simpleDescMessage.clustersList[3] = ClustersId::SCENE_CLUSTER;
            simpleDescMessage.clustersList[4] = ClustersId::GROUPS_CLUSTER;
            zDevices->put(simpleDescMessage);

            simpleDescMessage.endpoint = 11;
            simpleDescMessage.numInClusters = 5;
            simpleDescMessage.numOutClusters = 0;
            simpleDescMessage.appDeviceId = 0x100; // On off light
            simpleDescMessage.clustersList[0] = ClustersId::BASIC_CLUSTER;
            simpleDescMessage.clustersList[1] = ClustersId::IDENTIFY_CLUSTER;
            simpleDescMessage.clustersList[2] = ClustersId::ON_OFF_CLUSTER;
            simpleDescMessage.clustersList[3] = ClustersId::SCENE_CLUSTER;
            simpleDescMessage.clustersList[4] = ClustersId::GROUPS_CLUSTER;
            zDevices->put(simpleDescMessage);
        }

        if (nwkAddr == NWK_ADDR3) {
            SimpleDescMessage simpleDescMessage;
            simpleDescMessage.nwkAddr = NWK_ADDR3.getId();
            simpleDescMessage.endpoint = 7;
            simpleDescMessage.numInClusters = 3;
            simpleDescMessage.numOutClusters = 0;
            simpleDescMessage.appDeviceId = 0x302; // Temp sensor
            simpleDescMessage.clustersList[0] = ClustersId::BASIC_CLUSTER;
            simpleDescMessage.clustersList[1] = ClustersId::IDENTIFY_CLUSTER;
            simpleDescMessage.clustersList[2] = ClustersId::TEMPERATURE_MEASUREMENT;
            zDevices->put(simpleDescMessage);
        }

    }


    void DemoDevice::init() {
        auto zDevices = singletonObjects->getZDevices();
        auto message = std::make_shared<IEEEAddressResponse>();
        message->nwkAddr = NwkAddr(NWK_ADDR1);
        message->ieeeAddr = extAddress1;
        zDevices->addDeviceInfo(message.get());
        boost::this_fiber::sleep_for(2s);
        message->nwkAddr = NwkAddr(NWK_ADDR2);
        message->ieeeAddr = extAddress2;
        zDevices->addDeviceInfo(message.get());
        boost::this_fiber::sleep_for(2s);
        message->nwkAddr = NwkAddr(NWK_ADDR3);
        message->ieeeAddr = extAddress3;
        zDevices->addDeviceInfo(message.get());

        requestActiveEndpoints(NWK_ADDR1);
        boost::this_fiber::sleep_for(2s);
        requestActiveEndpoints(NWK_ADDR2);
        boost::this_fiber::sleep_for(2s);
        requestActiveEndpoints(NWK_ADDR3);
        boost::this_fiber::sleep_for(2s);
    }


    void DemoDevice::removeDevice(NwkAddr networkId) {
        BOOST_LOG_TRIVIAL(info) << "TO BE IMPLEMENTED";

    }

    void DemoDevice::getIEEEAddress(zigbee::NwkAddr nwkAddr, zigbee::ZDPRequestType, uint8_t) {
        auto zDevices = singletonObjects->getZDevices();
        auto message = std::make_shared<IEEEAddressResponse>();

        if (nwkAddr == 0) {
            message->nwkAddr = NwkAddr(0);
            message->ieeeAddr = extAddress0;
            message->totalDevice=2;
            message->startIndex=0;
            message->children.insert(NWK_ADDR1);
            message->children.insert(NWK_ADDR2);
            usleep(1000);
            zDevices->addDeviceInfo(message.get());
            ieeeAddressResponseQueue.setData(nwkAddr, message);
        }

        if (nwkAddr == NWK_ADDR1) {
            message->nwkAddr = NwkAddr(NWK_ADDR1);
            message->ieeeAddr = extAddress1;
            message->totalDevice=0;
            message->startIndex=0;
            usleep(1000);
            zDevices->addDeviceInfo(message.get());
            ieeeAddressResponseQueue.setData(nwkAddr, message);
        }

        if (nwkAddr == NWK_ADDR2) {
            message->nwkAddr = NwkAddr(NWK_ADDR2);
            message->ieeeAddr = extAddress2;
            message->children.insert(NWK_ADDR3);
            message->totalDevice=1;
            message->startIndex=0;
            usleep(1000);
            zDevices->addDeviceInfo(message.get());
            ieeeAddressResponseQueue.setData(nwkAddr, message);
        }

        if (nwkAddr == NWK_ADDR3) {
            message->nwkAddr = NwkAddr(NWK_ADDR3);
            message->ieeeAddr = extAddress3;
            message->totalDevice=0;
            message->startIndex=0;
            usleep(1000);
            zDevices->addDeviceInfo(message.get());
            ieeeAddressResponseQueue.setData(nwkAddr, message);
        }
    }

    void DemoDevice::requestAttribute(const AttributeKey &key) {
        ZigbeeAttributeIds ids;
        ids.push_back(key.attributeId);
        AttributesKey attributesKey(key.networkAddress, key.endpoint, key.clusterId, ids);
        requestAttributes(attributesKey);
    }


    void DemoDevice::assignBasicCluster(Cluster* cluster, std::vector<ZigbeeAttributeId> &attributeIds, std::array<std::vector<uint8_t>, 8> &data) {
        for (auto attributeId : attributeIds) {
            auto attribute = cluster->getAttribute(attributeId);
            auto attr = &(*data[attributeId].begin());
            if (attributeId <= 7) {
                AttributeKey key(cluster->getNetworkAddress(), cluster->getEndpoint(), cluster->getId(), attributeId);
                posponedCallbacks.emplace_back(system_clock::now() + 500ms, [attribute, attr, this, key]() mutable {
                    attribute->setValue(0, attr[0], attr + 1);
                    attributeQueue.setData(key, attribute);
                });
            } else {
                if (attribute != nullptr) {
                    AttributeKey key(cluster->getNetworkAddress(), cluster->getEndpoint(), cluster->getId(), attributeId);
                    posponedCallbacks.emplace_back(system_clock::now() + 500ms, [attribute, this, key]() mutable {
                        attribute->setValue(StatusEnum::UNSUPPORTED_ATTRIBUTE, 00, nullptr);
                        attributeQueue.setData(key, attribute);
                    });
                }
            }
        }
    }

    void DemoDevice::assignTemperatureMeasureCluster(Cluster * cluster, std::vector<ZigbeeAttributeId> &attributeIds, int16_t temp, std::chrono::seconds delay) {
        for (auto &&attributeId : attributeIds) {
            AttributeKey key{cluster->getNetworkAddress(), cluster->getEndpoint(), cluster->getId(), attributeId};
            auto attribute = cluster->getAttribute(attributeId);
            if (attributeId == 0) {
                std::normal_distribution<> normal_dist(temp, 2);
                uint16_t value = boost::endian::native_to_little(temp * 100 + normal_dist(e1));

                if (delay > 0s) {
                    posponedCallbacks.emplace_back(system_clock::now() + delay, [attribute, value, this, key]() mutable {
                        BOOST_LOG_TRIVIAL(trace) << "set temperature to " << value / 100.00;
                        attribute->setValue(0, typeSINT16, (uint8_t *) &value);
                        setAttribute(key, attribute);
                    });
                } else {
                    posponedCallbacks.emplace_back(system_clock::now() + 500ms, [attribute, value, this, key]() mutable {
                        BOOST_LOG_TRIVIAL(trace) << "set temperature to " << value / 100.00;
                        attribute->setValue(0, typeSINT16, (uint8_t *) &value);
                        setAttribute(key, attribute);
                    });

                }
            } else if (attributeId == 1) {
                posponedCallbacks.emplace_back(system_clock::now() + 500ms, [attribute, this, key]() mutable {
                    uint16_t value = static_cast<uint16_t>(boost::endian::native_to_little(-2000));
                    attribute->setValue(0, typeSINT16, (uint8_t *) &value);
                    setAttribute(key, attribute);
                });

            } else if (attributeId == 2) {
                posponedCallbacks.emplace_back(system_clock::now() + 500ms, [attribute, this, key]() mutable {
                    uint16_t value = static_cast<uint16_t>(boost::endian::native_to_little(10000));
                    attribute->setValue(0, typeSINT16, (uint8_t *) &value);
                    setAttribute(key, attribute);
                });
            } else if (attributeId == 3) {
                posponedCallbacks.emplace_back(system_clock::now() + 500ms, [attribute, this, key]() mutable {
                    uint16_t value = static_cast<uint16_t>(boost::endian::native_to_little(100));
                    attribute->setValue(0, typeUINT16, (uint8_t *) &value);
                    setAttribute(key, attribute);
                });
            } else {
                if (attribute != nullptr) {
                    posponedCallbacks.emplace_back(system_clock::now() + 500ms, [attribute, this, key]() mutable {
                        attribute->setValue(StatusEnum::UNSUPPORTED_ATTRIBUTE, 00, nullptr);
                        setAttribute(key, attribute);
                    });

                }
            }
        }
    }

    void
    DemoDevice::assignOnOffCluster(zigbee::NwkAddr nwkAddrs, const zigbee::EndpointID endpoint, Cluster * cluster, std::vector<ZigbeeAttributeId> &attributeIds) {
        for (auto &&attributeId : attributeIds) {
            auto attribute = cluster->getAttribute(attributeId);
            auto key = AttributeKey(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, attributeId);
            if (attributeId == 0) {
                uint8_t val;
                if (intValuesMap.count(key) > 0) {
                    val = intValuesMap[key];
                } else {
                    val = 0;
                }

                posponedCallbacks.emplace_back(system_clock::now() + 500ms, [attribute, val, this, key]() mutable {
                    attribute->setValue(0, typeBOOLRAN, &val);
                    setAttribute(key, attribute);
                });
            } else {
                if (attribute != nullptr) {
                    posponedCallbacks.emplace_back(system_clock::now() + 500ms, [attribute, this, key]() mutable {
                        attribute->setValue(StatusEnum::UNSUPPORTED_ATTRIBUTE, 00, nullptr);
                        setAttribute(key, attribute);
                    });

                }
            }
        }
    }

    void DemoDevice::requestAttributes(AttributesKey &key) {
        auto clusters = singletonObjects->getClusters();
        auto cluster = clusters->getCluster(key.networkAddress, key.endpoint, key.clusterId);


        if (key.clusterId == ClustersId::IDENTIFY_CLUSTER) {
            for (auto &&attributeId : key.attributesId) {
                if (attributeId == 0) {
                    auto attributeKey = AttributeKey(key.networkAddress, key.endpoint, key.clusterId, attributeId);
                    int val;
                    if (intValuesMap.count(attributeKey) > 0) {
                        val = intValuesMap[attributeKey];
                    } else {
                        val = 0;
                    }
                    uint8_t data[2] = {static_cast<uint8_t >(val >> 8), static_cast<uint8_t >(val & 0xFF)};

                    auto attribute = cluster->getAttribute(attributeId);
                    auto aKey = AttributeKey(key.networkAddress, key.endpoint, key.clusterId, attributeId);
                    posponedCallbacks.emplace_back(system_clock::now() + 500ms, [attribute, this, data, aKey]() mutable {
                        attribute->setValue(0, typeUINT16, data);
                        setAttribute(aKey, attribute);
                    });

                    return;
                }
            }
        } else if (key.networkAddress == NWK_ADDR1) {
            if (key.endpoint == 4) {
                if (key.clusterId == 0) {
                    assignBasicCluster(cluster, key.attributesId, NKW1_4_0);
                    return;
                } else if (key.clusterId.getId() == ClustersId::ON_OFF_CLUSTER) {
                    assignOnOffCluster(key.networkAddress, key.endpoint, cluster, key.attributesId);
                    return;
                }

            }

            if (key.endpoint == 6) {
                if (key.clusterId == 0) {
                    assignBasicCluster(cluster, key.attributesId, NKW1_6_0);
                    return;
                } else if (key.clusterId.getId() == ClustersId::ON_OFF_CLUSTER) {
                    assignOnOffCluster(key.networkAddress, key.endpoint, cluster, key.attributesId);
                    return;
                }

            }
            if (key.endpoint == 7) {
                if (key.clusterId == 0) {
                    assignBasicCluster(cluster, key.attributesId, NKW1_7_0);
                    return;
                } else if (key.clusterId.getId() == ClustersId::ON_OFF_CLUSTER) {
                    assignOnOffCluster(key.networkAddress, key.endpoint, cluster, key.attributesId);
                    return;
                }

            }
        } else if (key.networkAddress == NWK_ADDR2) {
            if (key.endpoint == 5) {
                if (key.clusterId == 0) {
                    assignBasicCluster(cluster, key.attributesId, NKW2_5_0);
                    return;
                } else if (key.clusterId.getId() == ClustersId::TEMPERATURE_MEASUREMENT) {
                    BOOST_LOG_TRIVIAL(trace) << "request attribute temperature cluster for " << key.networkAddress << ":" << key.endpoint;
                    assignTemperatureMeasureCluster(cluster, key.attributesId, 23, 0s);
                    return;
                }

            }

            if (key.endpoint == 7) {
                if (key.clusterId == 0) {
                    assignBasicCluster(cluster, key.attributesId, NKW2_7_0);
                    return;
                } else if (key.clusterId.getId() == ClustersId::ON_OFF_CLUSTER) {
                    assignOnOffCluster(key.networkAddress, key.endpoint, cluster, key.attributesId);
                    return;
                }

            }
            if (key.endpoint == 11) {
                if (key.clusterId == 0) {
                    assignBasicCluster(cluster, key.attributesId, NKW2_11_0);
                    return;;
                } else if (key.clusterId.getId() == ClustersId::ON_OFF_CLUSTER) {
                    assignOnOffCluster(key.networkAddress, key.endpoint, cluster, key.attributesId);
                    return;
                }

            }
        } else if (key.networkAddress == NWK_ADDR3) {
            if (key.endpoint == 7) {
                if (key.clusterId == 0) {
                    assignBasicCluster(cluster, key.attributesId, NKW3_7_0);
                    return;
                } else if (key.clusterId.getId() == ClustersId::TEMPERATURE_MEASUREMENT) {
                    BOOST_LOG_TRIVIAL(trace) << "request attribute temperature cluster for " << key.networkAddress << ":" << key.endpoint;
                    assignTemperatureMeasureCluster(cluster, key.attributesId, 23, 4s);
                    return;
                }

            }
        } else {
            for (auto &&attributeId : key.attributesId) {
                auto attribute = cluster->getAttribute(attributeId);
                if (attribute != nullptr) {
                    auto aKey = AttributeKey(key.networkAddress, key.endpoint, key.clusterId, attributeId);
                    posponedCallbacks.emplace_back(system_clock::now() + 500ms, [attribute, this, aKey]() mutable {
                        attribute->setValue(StatusEnum::UNSUPPORTED_ATTRIBUTE, 00, nullptr);
                        setAttribute(aKey, attribute);
                    });

                }
            }
        }

    }

    void DemoDevice::requestReset() {

    }


    void DemoDevice::writeAttribute(zigbee::NwkAddr, const zigbee::EndpointID, zigbee::ClusterID, ZigbeeAttributeId, ZCLTypeDataType, uint8_t, uint8_t *) {

    }

    void DemoDevice::sendCmd(zigbee::NwkAddr nwkAddrs, const zigbee::EndpointID endpoint, zigbee::ClusterID cluster, ZigbeeClusterCmdId commandId, std::vector<uint8_t>) {
        BOOST_LOG_NAMED_SCOPE("demo_driver");
        BOOST_LOG_TRIVIAL(info) << "Executing cmd: {" << nwkAddrs << "," << endpoint << "," << cluster << "," << commandId << "}";
        if (cluster == 3) {
            BOOST_LOG_TRIVIAL(info) << "Executing cmd identify: {" << nwkAddrs << "," << endpoint << "," << cluster << "}";
        } else {
            BOOST_LOG_TRIVIAL(info) << "Executing cmd: {" << nwkAddrs << "," << endpoint << "," << cluster << "," << commandId << "}";
            if (nwkAddrs == NWK_ADDR1) {
                if (endpoint == 4) {
                    if (cluster == ClustersId::ON_OFF_CLUSTER) {
                        if (commandId == 0) {
                            auto key = AttributeKey(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                            intValuesMap[key] = 0;
                            BOOST_LOG_TRIVIAL(info) << "Turn off " << nwkAddrs << ", " << endpoint;
                        } else if (commandId == 1) {
                            auto key = AttributeKey(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                            intValuesMap[key] = 1;
                            BOOST_LOG_TRIVIAL(info) << "Turn on " << nwkAddrs << ", " << endpoint;
                        } else if (commandId == 2) {
                            auto key = AttributeKey(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                            intValuesMap[key] = intValuesMap[key] > 0 ? 0 : 1;
                            BOOST_LOG_TRIVIAL(info) << "Toggle at " << intValuesMap[key] << " " << nwkAddrs << ", " << endpoint;
                        }
                    }
                } else if (endpoint == 6) {
                    if (cluster == ClustersId::ON_OFF_CLUSTER) {
                        if (commandId == 0) {
                            auto key = AttributeKey(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                            intValuesMap[key] = 0;
                            BOOST_LOG_TRIVIAL(info) << "Turn off " << nwkAddrs << ", " << endpoint;
                        } else if (commandId == 1) {
                            auto key = AttributeKey(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                            intValuesMap[key] = 1;
                            BOOST_LOG_TRIVIAL(info) << "Turn on " << nwkAddrs << ", " << endpoint;
                        } else if (commandId == 2) {
                            auto key = AttributeKey(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                            intValuesMap[key] = intValuesMap[key] > 0 ? 0 : 1;
                            BOOST_LOG_TRIVIAL(info) << "Toggle at " << intValuesMap[key] << " " << nwkAddrs << ", " << endpoint;
                        }
                    }
                } else if (endpoint == 7) {
                    if (cluster == ClustersId::ON_OFF_CLUSTER) {
                        if (commandId == 0) {
                            auto key = AttributeKey(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                            intValuesMap[key] = 0;
                            BOOST_LOG_TRIVIAL(info) << "Turn off " << nwkAddrs << ", " << endpoint;
                        } else if (commandId == 1) {
                            auto key = AttributeKey(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                            intValuesMap[key] = 1;
                            BOOST_LOG_TRIVIAL(info) << "Turn on " << nwkAddrs << ", " << endpoint;
                        } else if (commandId == 2) {
                            auto key = AttributeKey(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                            intValuesMap[key] = intValuesMap[key] > 0 ? 0 : 1;
                            BOOST_LOG_TRIVIAL(info) << "Toggle at " << intValuesMap[key] << " " << nwkAddrs << ", " << endpoint;
                        }
                    }
                }

            }

            if (nwkAddrs == NWK_ADDR2) {
                if (endpoint == 7) {
                    if (cluster == ClustersId::ON_OFF_CLUSTER) {
                        if (commandId == 0) {
                            auto key = AttributeKey(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                            intValuesMap[key] = 0;
                            BOOST_LOG_TRIVIAL(info) << "Turn off " << nwkAddrs << ", " << endpoint;
                        } else if (commandId == 1) {
                            auto key = AttributeKey(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                            intValuesMap[key] = 1;
                            BOOST_LOG_TRIVIAL(info) << "Turn on " << nwkAddrs << ", " << endpoint;
                        } else if (commandId == 2) {
                            auto key = AttributeKey(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                            intValuesMap[key] = intValuesMap[key] > 0 ? 0 : 1;
                            BOOST_LOG_TRIVIAL(info) << "Toggle at " << intValuesMap[key] << " " << nwkAddrs << ", " << endpoint;
                        }
                    }
                } else if (endpoint == 11) {
                    if (cluster == ClustersId::ON_OFF_CLUSTER) {
                        if (commandId == 0) {
                            auto key = AttributeKey(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                            intValuesMap[key] = 0;
                            BOOST_LOG_TRIVIAL(info) << "Turn off " << nwkAddrs << ", " << endpoint;
                        } else if (commandId == 1) {
                            auto key = AttributeKey(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                            intValuesMap[key] = 1;
                            BOOST_LOG_TRIVIAL(info) << "Turn on " << nwkAddrs << ", " << endpoint;
                        } else if (commandId == 2) {
                            auto key = AttributeKey(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                            intValuesMap[key] = intValuesMap[key] > 0 ? 0 : 1;
                            BOOST_LOG_TRIVIAL(info) << "Toggle at " << intValuesMap[key] << " " << nwkAddrs << ", " << endpoint;
                        }
                    }
                }

            }
        }
    }


    void DemoDevice::sendReqBind(zigbee::NwkAddr, const uint8_t *, zigbee::EndpointID, zigbee::ClusterID, const uint8_t *, zigbee::EndpointID) {

    }

    void DemoDevice::sendReqUnbind(zigbee::NwkAddr, const uint8_t *, zigbee::EndpointID, zigbee::ClusterID, const uint8_t *, zigbee::EndpointID) {

    }

    void DemoDevice::sendReqDeviceInfo(zigbee::NwkAddr networkId) {
        auto deviceInfoDispatcher = singletonObjects->getDeviceInfoDispatcher();
        DeviceInfoMessage deviceInfoMessage;
        deviceInfoMessage.nwkAddr = networkId.getId();
        if (networkId == NWK_ADDR1) {
            deviceInfoMessage.rxLqi = 50;
            deviceInfoMessage.txCounter = 3;
            deviceInfoMessage.txCounter = 5;
            deviceInfoDispatcher->dispatch(&deviceInfoMessage);
        }

        if (networkId == NWK_ADDR2) {
            deviceInfoMessage.rxLqi = 60;
            deviceInfoMessage.txCounter = 32;
            deviceInfoMessage.txCounter = 6;
            deviceInfoDispatcher->dispatch(&deviceInfoMessage);
        }


        if (networkId == NWK_ADDR3) {
            deviceInfoMessage.rxLqi = 20;
            deviceInfoMessage.txCounter = 2;
            deviceInfoMessage.txCounter = 2;
            deviceInfoDispatcher->dispatch(&deviceInfoMessage);
        }

    }

    void DemoDevice::requestBindTable(zigbee::NwkAddr) {

    }

    void DemoDevice::registerForAnnunceMessage(zigbee::ZigbeeDevice::AnnunceCallback) {

    }

    void DemoDevice::registerForSimpleDescMessage(zigbee::ZigbeeDevice::SimpleDescCallback) {

    }

    void DemoDevice::registerForBindTableMessage(zigbee::ZigbeeDevice::BindTableResponseCallback) {

    }

    void DemoDevice::registerForAttributeCmd(zigbee::NwkAddr, const zigbee::EndpointID, zigbee::ClusterID, ZigbeeAttributeCmdId, const std::function<void()>) {

    }


}