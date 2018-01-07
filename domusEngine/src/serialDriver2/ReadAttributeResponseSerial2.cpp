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
        std::stringstream ss;
        NwkAddr nwkAddr{packet.getUint16(1)};
        EndpointID endpointID{packet.getUint8(3)};
        ClusterID clusterId{packet.getUint16(4)};
        ZigbeeAttributeId attributeId{packet.getUint16(6)};
        AttributeKey key{nwkAddr, endpointID, clusterId, attributeId};
        int status = packet.getUint8(8);
        if (status == 0) {
            uint8_t attributeType{packet.getUint8(9)};
            uint8_t attributeLen{packet.getUint8(10)};
            Clusters *clusters = singletons->getClusters();
            auto cluster = clusters->getCluster(nwkAddr, endpointID, clusterId);
            Cluster *pCluster = cluster.get();
            auto attribute = pCluster->getAttribute(attributeId);
            if (attribute != nullptr) {
                uint8_t data[256];
                for (int i = 0; i < attributeLen; i++) {
                    data[i] = packet.getUint8(i + 11);
                    ss << std::setw(2) << std::setfill('0') << std::hex << (uint32_t)data[i] << " ";
                }

                attribute->setValue(status, attributeType, data);

                BOOST_LOG_TRIVIAL(info) << "arrived attribute from  network id=" << nwkAddr << ", endpoint=" << endpointID << ", cluster=" << clusterId << ", attribute="
                                        << attributeId << " : " << ss.str();


                singletons->getZigbeeDevice()->setAttribute(key, attribute);
            } else {
                BOOST_LOG_TRIVIAL(error) << "Invalid attribute " << key;
            }
        } else {
            BOOST_LOG_TRIVIAL(error) << "Error on requesting attribute value from  network id=" << nwkAddr << ", endpoint=" << endpointID << ", cluster=" << clusterId
                                     << ", attribute=" << attributeId << ", cause: " << status;
        }
    }
}
