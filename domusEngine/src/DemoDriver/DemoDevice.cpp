//
// Created by paolo on 27/01/17.
//

#include <boost/fiber/algo/round_robin.hpp>
#include <boost/fiber/operations.hpp>
//#include <boost/fiber/all.hpp>
#include <boost/log/trivial.hpp>
#include <boost/endian/conversion.hpp>
#include <zcl/Cluster.h>
#include <zcl/StatusEnum.h>
#include "DemoDevice.h"
#include "../Utils/SingletonObjects.h"

using boost::fibers::fiber;
using boost::fibers::mutex;
using boost::fibers::condition_variable;
using namespace std::chrono_literals;
using std::unique_lock;
using std::get;

namespace zigbee {

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

    static constexpr NwkAddr NWK_ADDR1{0x1234};
    static constexpr NwkAddr NWK_ADDR2{0x1232};
    static constexpr NwkAddr NWK_ADDR3{0x8934};

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


    DemoDevice::DemoDevice(SingletonObjects &singletonObjects) : singletonObjects(singletonObjects), stop(false), e1(rd()) {
        BOOST_LOG_TRIVIAL(info) << "-------------------------- DEMO MODE ------------------------";
        demoThread = std::thread([this] { runDemoThread(); });
    }

    void DemoDevice::runDemoThread() {
        boost::fibers::use_scheduling_algorithm<boost::fibers::algo::round_robin>();
        powerNodeQueue.startDequeFiber();

        boost::fibers::fiber fiberPowerNodeSetDeque([this]() {
            for (auto && nwkAddr: powerNodeSet) {
                boost::fibers::fiber setPowerMode([this, nwkAddr]() {
                    auto powerNodeData = std::make_shared<PowerNodeData>();
                    powerNodeData->nwkAddr = nwkAddr;
                    boost::this_fiber::sleep_for(3s);
                    BOOST_LOG_TRIVIAL(info) << "Notify power node arrived";
                    powerNodeQueue.setData(nwkAddr,powerNodeData);
                });
                fibers.push_back(std::move(setPowerMode));
            }
        });


        while (!stop) {
            boost::this_fiber::yield();
            for (auto &attribute: intValuesMap) {
                if (std::get<ClusterID>(attribute.first).getId() == ClustersId::IDENTIFY_CLUSTER) {
                    if (attribute.second > 0) {
                        attribute.second--;
                    }
                }
            }
            std::vector<std::tuple<int32_t, std::function<void()> > > remainCallbacks;
            for (auto &callback: posponedCallbacks) {
                std::get<0>(callback)--;
                if (std::get<0>(callback) <= 0) {
                    std::get<1>(callback)();
                } else {
                    remainCallbacks.push_back(callback);
                }
            }
            posponedCallbacks = remainCallbacks;
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
        auto zDevices = singletonObjects.getZDevices();
        if (nwkAddr == NWK_ADDR1) {
            SimpleDescMessage simpleDescMessage;
            simpleDescMessage.nwkAddr = NWK_ADDR1.getId();
            simpleDescMessage.endpoint = 2;
            simpleDescMessage.numInClusters = 3;
            simpleDescMessage.numOutClusters = 0;
            simpleDescMessage.appDeviceId = 0x51; // SMART PLUG
            simpleDescMessage.clustersList[0] = ClustersId::BASIC_CLUSTER;
            simpleDescMessage.clustersList[1] = ClustersId::IDENTIFY_CLUSTER;
            simpleDescMessage.clustersList[2] = ClustersId::METERING;
            simpleDescMessage.clustersList[3] = ClustersId::ON_OFF_CLUSTER;
            zDevices->put(simpleDescMessage);

            simpleDescMessage.endpoint = 4;
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

            simpleDescMessage.endpoint = 6;
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

    void DemoDevice::getIEEEAddress(zigbee::NwkAddr nwkAddr, zigbee::ZDPRequestType, uint8_t) {
        auto zDevices = singletonObjects.getZDevices();
        IEEEAddrResp message;

        if (nwkAddr == 0) {
            message.nwkAddr = NwkAddr(0);
            message.ieeeAddr = ExtAddress({0x01, 0x02, 0x03, 0x04, 0x1A, 0x1B, 0x1C, 0x1D});
            message.children.insert(NWK_ADDR1);
            message.children.insert(NWK_ADDR2);
            zDevices->addDeviceInfo(message);
        }

        if (nwkAddr == NWK_ADDR1) {
            message.nwkAddr = NwkAddr(NWK_ADDR1);
            message.ieeeAddr = ExtAddress({0x01, 0x02, 0x03, 0x04, 0x2A, 0x2B, 0x2C, 0x2D});
            zDevices->addDeviceInfo(message);
        }

        if (nwkAddr == NWK_ADDR2) {
            message.nwkAddr = NwkAddr(NWK_ADDR2);
            message.ieeeAddr = ExtAddress({0x01, 0x02, 0x03, 0x04, 0x3A, 0x3B, 0x3C, 0x3D});
            message.children.insert(NWK_ADDR3);
            zDevices->addDeviceInfo(message);
        }

        if (nwkAddr == NWK_ADDR3) {
            message.nwkAddr = NwkAddr(NWK_ADDR3);
            message.ieeeAddr = ExtAddress({0x01, 0x02, 0x03, 0x04, 0x4A, 0x4B, 0x4C, 0x4D});
            zDevices->addDeviceInfo(message);
        }
    }

    void DemoDevice::requestAttribute(zigbee::NwkAddr nwkAddrs, const zigbee::EndpointID endpoint, zigbee::ClusterID cluster, ZigbeeAttributeId attributeId) {
        ZigbeeAttributeIds ids;
        ids.push_back(attributeId);
        requestAttributes(nwkAddrs, endpoint, cluster, ids);
    }


    void DemoDevice::assignBasicCluster(std::shared_ptr<Cluster> cluster, ZigbeeAttributeIds &attributeIds, std::array<std::vector<uint8_t>, 8> &data) {
        for (auto &&attributeId : attributeIds) {
            auto attribute = cluster->getAttribute(attributeId);
            auto attr = &(*data[attributeId].begin());
            if (attributeId <= 7) {
                attribute->setValue(0, attr[0], attr + 1);
            } else {
                if (attribute != nullptr)
                    attribute->setValue(StatusEnum::UNSUPPORTED_ATTRIBUTE, 00, nullptr);
            }
        }
    }

    void
    DemoDevice::assignTemperatureMeasureCluster(std::shared_ptr<Cluster> cluster, ZigbeeAttributeIds &attributeIds, AttributeValueSignalMap &attributeValueSignalMap, int16_t temp,
                                                int delay) {
        for (auto &&attributeId : attributeIds) {
            auto attribute = cluster->getAttribute(attributeId);
            if (attributeId == 0) {
                std::normal_distribution<> normal_dist(temp, 2);
                uint16_t value = boost::endian::native_to_little(temp * 100 + normal_dist(e1));
                AttributeKey key{cluster->getNetworkAddress(), cluster->getEndpoint().getId(), cluster->getId().getId(), attributeId};
                if (delay > 0) {
                    posponedCallbacks.emplace_back(delay, [attribute, value, attributeValueSignalMap, key]() mutable {
                        BOOST_LOG_TRIVIAL(trace) << "set temperature to " << value / 100.00;
                        attribute->setValue(0, typeSINT16, (uint8_t *) &value);

                        if (attributeValueSignalMap.count(key) > 0) {
                            attributeValueSignalMap.execute(key, 0);
                        }
                    });
                } else {
                    BOOST_LOG_TRIVIAL(trace) << "set temperature to " << value / 100.00;
                    attribute->setValue(0, typeSINT16, (uint8_t *) &value);
                    if (attributeValueSignalMap.count(key) > 0) {
                        attributeValueSignalMap.execute(key, 0);
                    }
                }
            } else if (attributeId == 1) {
                uint16_t value = static_cast<uint16_t>(boost::endian::native_to_little(-2000));
                attribute->setValue(0, typeSINT16, (uint8_t *) &value);
            } else if (attributeId == 2) {
                uint16_t value = static_cast<uint16_t>(boost::endian::native_to_little(10000));
                attribute->setValue(0, typeSINT16, (uint8_t *) &value);
            } else if (attributeId == 3) {
                uint16_t value = static_cast<uint16_t>(boost::endian::native_to_little(100));
                attribute->setValue(0, typeUINT16, (uint8_t *) &value);
            } else {
                if (attribute != nullptr)
                    attribute->setValue(StatusEnum::UNSUPPORTED_ATTRIBUTE, 00, nullptr);
            }
        }
    }

    void DemoDevice::assignOnOffCluster(zigbee::NwkAddr nwkAddrs, const zigbee::EndpointID endpoint, std::shared_ptr<Cluster> cluster, ZigbeeAttributeIds &attributeIds) {
        for (auto &&attributeId : attributeIds) {
            auto attribute = cluster->getAttribute(attributeId);
            if (attributeId == 0) {
                auto key = std::make_tuple(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, attributeId);
                uint8_t val;
                if (intValuesMap.count(key) > 0) {
                    val = intValuesMap[key];
                } else {
                    val = 0;
                }
                attribute->setValue(0, typeBOOLRAN, &val);
            } else {
                if (attribute != nullptr)
                    attribute->setValue(StatusEnum::UNSUPPORTED_ATTRIBUTE, 00, nullptr);
            }
        }
    }

    void DemoDevice::requestAttributes(zigbee::NwkAddr nwkAddrs, const zigbee::EndpointID endpoint, zigbee::ClusterID clusterId, ZigbeeAttributeIds &attributeIds) {
        auto clusters = singletonObjects.getClusters();
        auto attributeValueSignalMap = singletonObjects.getAttributeValueSignalMap();
        auto cluster = clusters->getCluster(nwkAddrs, endpoint, clusterId);


        if (clusterId == ClustersId::IDENTIFY_CLUSTER) {
            for (auto &&attributeId : attributeIds) {
                if (attributeId == 0) {
                    auto key = std::make_tuple(nwkAddrs, endpoint, clusterId, attributeId);
                    int val;
                    if (intValuesMap.count(key) > 0) {
                        val = intValuesMap[key];
                    } else {
                        val = 0;
                    }
                    uint8_t data[2] = {static_cast<uint8_t >(val >> 8), static_cast<uint8_t >(val & 0xFF)};

                    auto attribute = cluster->getAttribute(attributeId);
                    attribute->setValue(0, typeUINT16, data);
                    return;
                }
            }
        } else if (nwkAddrs == NWK_ADDR1) {
            if (endpoint == 4) {
                if (clusterId == 0) {
                    assignBasicCluster(cluster, attributeIds, NKW1_4_0);
                    return;
                } else if (clusterId.getId() == ClustersId::ON_OFF_CLUSTER) {
                    assignOnOffCluster(nwkAddrs, endpoint, cluster, attributeIds);
                    return;
                }

            }

            if (endpoint == 6) {
                if (clusterId == 0) {
                    assignBasicCluster(cluster, attributeIds, NKW1_6_0);
                    return;
                } else if (clusterId.getId() == ClustersId::ON_OFF_CLUSTER) {
                    assignOnOffCluster(nwkAddrs, endpoint, cluster, attributeIds);
                    return;
                }

            }
            if (endpoint == 7) {
                if (clusterId == 0) {
                    assignBasicCluster(cluster, attributeIds, NKW1_7_0);
                    return;
                } else if (clusterId.getId() == ClustersId::ON_OFF_CLUSTER) {
                    assignOnOffCluster(nwkAddrs, endpoint, cluster, attributeIds);
                    return;
                }

            }
        } else if (nwkAddrs == NWK_ADDR2) {
            if (endpoint == 5) {
                if (clusterId == 0) {
                    assignBasicCluster(cluster, attributeIds, NKW2_5_0);
                    return;
                } else if (clusterId.getId() == ClustersId::TEMPERATURE_MEASUREMENT) {
                    BOOST_LOG_TRIVIAL(trace) << "request attribute temperature cluster for " << nwkAddrs << ":" << endpoint;
                    assignTemperatureMeasureCluster(cluster, attributeIds, attributeValueSignalMap, 23, 0);
                    return;
                }

            }

            if (endpoint == 7) {
                if (clusterId == 0) {
                    assignBasicCluster(cluster, attributeIds, NKW2_7_0);
                    return;
                } else if (clusterId.getId() == ClustersId::ON_OFF_CLUSTER) {
                    assignOnOffCluster(nwkAddrs, endpoint, cluster, attributeIds);
                    return;
                }

            }
            if (endpoint == 11) {
                if (clusterId == 0) {
                    assignBasicCluster(cluster, attributeIds, NKW2_11_0);
                    return;;
                } else if (clusterId.getId() == ClustersId::ON_OFF_CLUSTER) {
                    assignOnOffCluster(nwkAddrs, endpoint, cluster, attributeIds);
                    return;
                }

            }
        } else if (nwkAddrs == NWK_ADDR3) {
            if (endpoint == 7) {
                if (clusterId == 0) {
                    assignBasicCluster(cluster, attributeIds, NKW3_7_0);
                    return;
                } else if (clusterId.getId() == ClustersId::TEMPERATURE_MEASUREMENT) {
                    BOOST_LOG_TRIVIAL(trace) << "request attribute temperature cluster for " << nwkAddrs << ":" << endpoint;
                    assignTemperatureMeasureCluster(cluster, attributeIds, attributeValueSignalMap, 23, 4);
                    return;
                }

            }
        } else {
            for (auto &&attributeId : attributeIds) {
                auto attribute = cluster->getAttribute(attributeId);
                if (attribute != nullptr)
                    attribute->setValue(StatusEnum::UNSUPPORTED_ATTRIBUTE, 00, nullptr);
            }
        }

    }

    void DemoDevice::requestReset() {

    }

    void DemoDevice::writeAttribute(zigbee::NwkAddr, const zigbee::EndpointID, zigbee::ClusterID, ZigbeeAttributeId, ZCLTypeDataType, uint8_t, uint8_t *) {

    }

    void DemoDevice::sendCmd(zigbee::NwkAddr nwkAddrs, const zigbee::EndpointID endpoint, zigbee::ClusterID cluster, ZigbeeClusterCmdId commandId, std::vector<uint8_t>) {
        if (nwkAddrs == NWK_ADDR1) {
            if (endpoint == 4) {
                if (cluster == ClustersId::ON_OFF_CLUSTER) {
                    if (commandId == 0) {
                        auto key = std::make_tuple(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                        intValuesMap[key] = 0;
                        BOOST_LOG_TRIVIAL(info) << "Turn off " << nwkAddrs << ", " << endpoint;
                    } else if (commandId == 1) {
                        auto key = std::make_tuple(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                        intValuesMap[key] = 1;
                        BOOST_LOG_TRIVIAL(info) << "Turn on " << nwkAddrs << ", " << endpoint;
                    } else if (commandId == 2) {
                        auto key = std::make_tuple(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                        intValuesMap[key] = intValuesMap[key] > 0 ? 0 : 1;
                        BOOST_LOG_TRIVIAL(info) << "Toggle at " << intValuesMap[key] << " " << nwkAddrs << ", " << endpoint;
                    }
                }
            } else if (endpoint == 6) {
                if (cluster == ClustersId::ON_OFF_CLUSTER) {
                    if (commandId == 0) {
                        auto key = std::make_tuple(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                        intValuesMap[key] = 0;
                        BOOST_LOG_TRIVIAL(info) << "Turn off " << nwkAddrs << ", " << endpoint;
                    } else if (commandId == 1) {
                        auto key = std::make_tuple(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                        intValuesMap[key] = 1;
                        BOOST_LOG_TRIVIAL(info) << "Turn on " << nwkAddrs << ", " << endpoint;
                    } else if (commandId == 2) {
                        auto key = std::make_tuple(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                        intValuesMap[key] = intValuesMap[key] > 0 ? 0 : 1;
                        BOOST_LOG_TRIVIAL(info) << "Toggle at " << intValuesMap[key] << " " << nwkAddrs << ", " << endpoint;
                    }
                }
            } else if (endpoint == 7) {
                if (cluster == ClustersId::ON_OFF_CLUSTER) {
                    if (commandId == 0) {
                        auto key = std::make_tuple(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                        intValuesMap[key] = 0;
                        BOOST_LOG_TRIVIAL(info) << "Turn off " << nwkAddrs << ", " << endpoint;
                    } else if (commandId == 1) {
                        auto key = std::make_tuple(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                        intValuesMap[key] = 1;
                        BOOST_LOG_TRIVIAL(info) << "Turn on " << nwkAddrs << ", " << endpoint;
                    } else if (commandId == 2) {
                        auto key = std::make_tuple(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
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
                        auto key = std::make_tuple(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                        intValuesMap[key] = 0;
                        BOOST_LOG_TRIVIAL(info) << "Turn off " << nwkAddrs << ", " << endpoint;
                    } else if (commandId == 1) {
                        auto key = std::make_tuple(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                        intValuesMap[key] = 1;
                        BOOST_LOG_TRIVIAL(info) << "Turn on " << nwkAddrs << ", " << endpoint;
                    } else if (commandId == 2) {
                        auto key = std::make_tuple(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                        intValuesMap[key] = intValuesMap[key] > 0 ? 0 : 1;
                        BOOST_LOG_TRIVIAL(info) << "Toggle at " << intValuesMap[key] << " " << nwkAddrs << ", " << endpoint;
                    }
                }
            } else if (endpoint == 11) {
                if (cluster == ClustersId::ON_OFF_CLUSTER) {
                    if (commandId == 0) {
                        auto key = std::make_tuple(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                        intValuesMap[key] = 0;
                        BOOST_LOG_TRIVIAL(info) << "Turn off " << nwkAddrs << ", " << endpoint;
                    } else if (commandId == 1) {
                        auto key = std::make_tuple(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                        intValuesMap[key] = 1;
                        BOOST_LOG_TRIVIAL(info) << "Turn on " << nwkAddrs << ", " << endpoint;
                    } else if (commandId == 2) {
                        auto key = std::make_tuple(nwkAddrs, endpoint, ClusterID {ClustersId::ON_OFF_CLUSTER}, 0);
                        intValuesMap[key] = intValuesMap[key] > 0 ? 0 : 1;
                        BOOST_LOG_TRIVIAL(info) << "Toggle at " << intValuesMap[key] << " " << nwkAddrs << ", " << endpoint;
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
        auto deviceInfoDispatcher = singletonObjects.getDeviceInfoDispatcher();
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

    void
    DemoDevice::registerForAttributeValue(zigbee::NwkAddr, const zigbee::EndpointID, zigbee::ClusterID, ZigbeeAttributeId, const zigbee::ZigbeeDevice::NewAttributeValueCallback) {

    }


}