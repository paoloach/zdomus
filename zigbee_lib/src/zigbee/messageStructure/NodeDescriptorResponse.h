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

    enum class BandFrequency {
        Mhz868,
        Mhz900,
        Mhz2400
    };

    inline BandFrequency toBandFrequency(uint value) {
        switch (value) {
            case 0:
                return BandFrequency::Mhz868;
            case 2:
                return BandFrequency::Mhz900;
            case 3:
                return BandFrequency::Mhz2400;
            default:
                throw NoValidBandFrequencyException(value);
        }
    }

    inline std::ostream &operator<<(std::ostream &out, const BandFrequency bandFrequency) {
        switch (bandFrequency) {
            case BandFrequency::Mhz868:
                out << "Frequency from 868 to 868.6 Mhz";
                break;
            case BandFrequency::Mhz900:
                out << "Frequency from 902 to 928 Mhz";
                break;
            case BandFrequency::Mhz2400:
                out << "Frequency from 2400 to 2483.5 Mhz";
                break;
        }
        return out;
    }

    struct NodeDescriptorResponse {
        NwkAddr nwkAddr;
        LogicalType logicalType;
        BandFrequency bandFrequency;
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
