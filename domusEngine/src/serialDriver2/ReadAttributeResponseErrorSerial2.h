//
// Created by paolo on 03/01/17.
//

#ifndef DOMUS_ENGINE_READATTRIBUTERESPONSEERRORSERIAL2_H
#define DOMUS_ENGINE_READATTRIBUTERESPONSEERRORSERIAL2_H

#include <boost/log/trivial.hpp>
#include <zigbee/NwkAddr.h>
#include <zigbee/EndpointID.h>
#include <zcl/Cluster.h>
#include "Serial2Executor.h"
#include "../Utils/SingletonObjectsImpl.h"

namespace zigbee {
    class ReadAttributeResponseErrorSerial2 : public Serial2Executor {
    public:
        ReadAttributeResponseErrorSerial2(SingletonObjectsImpl &singletons) : singletons(singletons) {}

        virtual void operator()(Packet &&packet) override {
            NwkAddr nwkAddr{packet.getUint16(1)};
            int endpointID{packet.getUint8(3)};
            ZigbeeClusterId clusterId{packet.getUint16(4)};
            ZigbeeAttributeId attribute{packet.getUint16(6)};
            int status = packet.getUint8(8);
            BOOST_LOG_TRIVIAL(error) << "Error on requesting attribute value from  network id=" << nwkAddr << ", endpoint=" << endpointID << ", cluster=" << clusterId
                                     << ", attribute=" << attribute << ", cause: " << status;
            AttributeKey key(nwkAddr, EndpointID(endpointID), ClusterID(clusterId), attribute);
            auto cluster = singletons.getClusters()->getCluster(key.networkAddress, key.endpoint, key.clusterId);
            cluster->getAttribute(key.attributeId);
            singletons.getZigbeeDevice()->setAttribute(key, cluster->getAttribute(key.attributeId));
        }

    private:
        SingletonObjectsImpl &singletons;
    };
}
#endif //DOMUS_ENGINE_READATTRIBUTERESPONSEERRORSERIAL_H
