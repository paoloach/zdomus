//
// Created by paolo on 30/01/18.
//

#ifndef ZIGBEE_LIB_NODEDESCRIPTORRESPONSE_H
#define ZIGBEE_LIB_NODEDESCRIPTORRESPONSE_H

#include <cstdint>
#include <iostream>
#include "zcl/exceptions/NoValidBandFrequencyException.h"
#include "../NwkAddr.h"
#include "zcl/exceptions/NoValidLogicalTypeException.h"

namespace zigbee {
    enum class LogicalType {
        ZigbeeCordinator,
        ZigbeeRouter,
        ZigbeeEnddevice
    };

    inline LogicalType toLogicalType(uint value) {
        switch (value) {
            case 0:
                return LogicalType::ZigbeeCordinator;
            case 1:
                return LogicalType::ZigbeeRouter;
            case 2:
                return LogicalType::ZigbeeEnddevice;
            default:
                throw NoValidLogicalTypeException(value);
        }
    }

    inline std::ostream &operator<<(std::ostream &out, const LogicalType logicalType) {
        switch (logicalType) {
            case LogicalType::ZigbeeCordinator:
                out << "Zigbee coordinator";
                break;
            case LogicalType::ZigbeeRouter:
                out << "Zigbee router";
                break;
            case LogicalType::ZigbeeEnddevice:
                out << "Zigbee End Device";
                break;
            default:
                out << "Invalid Logical Type";
        }
        return out;
    }



    struct NodeDescriptorResponse {
        NwkAddr nwkAddr;
        LogicalType logicalType;
        uint bandFrequency;
        uint macCapability;
        uint manufactorerCode;
        uint maximumBufferSize;
        uint maximumIncomingTransferSize;
        uint serverMask;
        uint maximumOutcomingTransferSize;
        uint descriptorCapability;

    };
}

#endif //ZIGBEE_LIB_NODEDESCRIPTORRESPONSE_H
