//
// Created by paolo on 23/12/17.
//

#include <ios>
#include <iomanip>
#include <boost/log/trivial.hpp>
#include <zigbee/NwkAddr.h>
#include <zigbee/EndpointID.h>
#include <zcl/Cluster.h>
#include <zcl/ZCLAttribute.h>
#include <zigbee/AttributeKey.h>
#include <zigbee/ZigbeeDevice.h>
#include <zcl/StatusEnum.h>
#include "../Utils/Clusters.h"
#include "ReadAttributeResponseSerial2.h"

namespace zigbee {
    void ReadAttributeResponseSerial2::operator()(Packet &&packet) {
        BOOST_LOG_TRIVIAL(info) << "Packet: " << packet;

        NwkAddr nwkAddr{packet.getUint16(1)};
        EndpointID endpointID{packet.getUint8(3)};
        ClusterID clusterId{packet.getUint16(4)};
        int totalAttr = packet.getUint8(6);
        BOOST_LOG_TRIVIAL(info) << "Arrived " << totalAttr << " attributes";
        int index=7;
        for (int attrIndex=0; attrIndex < totalAttr; attrIndex++) {
            ZigbeeAttributeId attributeId{ packet.getUint16(index)};
            AttributeKey key{nwkAddr, endpointID, clusterId, attributeId};
            index+=2;
            int status = packet.getUint8(index);
            index++;
            Clusters *clusters = singletons->getClusters();
            auto cluster = clusters->getCluster(nwkAddr, endpointID, clusterId);
            auto attribute = cluster->getAttribute(attributeId);
            if (status == 0) {
                std::stringstream ss;
                uint8_t attributeType{packet.getUint8(index)};
                index++;
                uint8_t attributeLen{packet.getUint8(index)};
                index++;

                if (attribute != nullptr) {
                    uint8_t data[256];
                    for (int i = 0; i < attributeLen; i++) {
                        data[i] = packet.getUint8(index);
                        index++;
                        ss << std::setw(2) << std::setfill('0') << std::hex << (uint32_t) data[i] << " ";
                    }

                    attribute->setValue(status, attributeType, data);

                    BOOST_LOG_TRIVIAL(info) << "arrived attribute from  network id=" << nwkAddr << ", endpoint=" << endpointID << ", cluster=" << clusterId << ", attribute="
                                            << attributeId << " : " << ss.str();


                    singletons->getZigbeeDevice()->setAttribute(key, attribute);
                } else {
                    BOOST_LOG_TRIVIAL(error) << "Invalid attribute " << key;
                }
            } else {
                std::string strCause="unknonw";
                if (status == 0x86){
                    strCause = "Unsupported Attribute";
                }
                BOOST_LOG_TRIVIAL(error) << "Error on requesting attribute value from  network id=" << nwkAddr << ", endpoint=" << endpointID << ", cluster=" << clusterId
                                         << ", attribute=" << attributeId << ", cause: " << strCause << "(" << status << ")";
                auto attribute = cluster->getAttribute(attributeId);
                if (attribute != nullptr) {
                    attribute->setStatus(status);
                    singletons->getZigbeeDevice()->setAttribute(key, attribute);
                }
            }
        }
    }
}
