//
// Created by paolo on 30/01/18.
//

#include "../Utils/SingletonObjectsImpl.h"
#include "NodeDescriptionResponse2.h"
namespace zigbee {

    void NodeDescriptionResponse2::operator()(Packet &&packet) {
        auto nodeDescriptor = std::make_shared<NodeDescriptorResponse>();
        nodeDescriptor->nwkAddr = NwkAddr{packet.getUint16(1)};
        nodeDescriptor->logicalType = toLogicalType(packet.getUint8(3));
        nodeDescriptor->bandFrequency = packet.getUint8(4);
        nodeDescriptor->macCapability = packet.getUint8(5);
        nodeDescriptor->manufactorerCode = packet.getUint16(6);
        nodeDescriptor->maximumBufferSize = packet.getUint8(8);
        nodeDescriptor->maximumIncomingTransferSize = packet.getUint16(9);
        nodeDescriptor->serverMask = packet.getUint16(11);
        nodeDescriptor->maximumOutcomingTransferSize = packet.getUint16(13);
        nodeDescriptor->descriptorCapability = packet.getUint8(15);

        singletons->getZigbeeDevice()->setNodeDescriptor(nodeDescriptor);
    }
}


