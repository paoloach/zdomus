//
// Created by paolo on 13/05/16.
//
#include <boost/endian/conversion.hpp>

#include "ZclAttributeUtils.h"


using namespace boost::endian;

namespace zigbee {
    size_t ZclAttributeUtils::zclGetAttrDataLength(uint8_t dataType, const uint8_t *pData) {
        size_t dataLen = 0;

        ZCLTypeDataType zclTypeDataType = static_cast<ZCLTypeDataType>(dataType);

        if (zclTypeDataType == ZCLTypeDataType::ZCLTypeStringLongChar || zclTypeDataType == ZCLTypeDataType::ZCLTypeStringLongOctect) {
            dataLen = little_to_native(*(const uint16_t *) pData) + 2; // long string length + 2 for length field
        }
        else if (zclTypeDataType == ZCLTypeDataType::ZCLTypeStringOctect || zclTypeDataType == ZCLTypeDataType::ZCLTypeStringChar) {
            dataLen = *pData + 1; // string length + 1 for length field
        }
        else {
            dataLen = zclGetDataTypeLength(zclTypeDataType);
        }

        return dataLen;
    }

    size_t ZclAttributeUtils::zclGetDataTypeLength(ZCLTypeDataType dataType) {
        switch (dataType) {
            case ZCLTypeDataType::ZCLType8bit:
            case ZCLTypeDataType::ZCLTypeBool:
            case ZCLTypeDataType::ZCLType8bitBitmap:
            case ZCLTypeDataType::ZCLTypeUInt8:
            case ZCLTypeDataType::ZCLTypeSInt8:
            case ZCLTypeDataType::ZCLTypeenum8:
                return 1;
            case ZCLTypeDataType::ZCLType16bit:
            case ZCLTypeDataType::ZCLType16bitBitmap:
            case ZCLTypeDataType::ZCLTypeUInt16:
            case ZCLTypeDataType::ZCLTypeSInt16:
            case ZCLTypeDataType::ZCLTypeenum16:
            case ZCLTypeDataType::ZCLTypeFloatSemiPrecision:
            case ZCLTypeDataType::ZCLTypeClusterID:
            case ZCLTypeDataType::ZCLTypeAttributeId:
                return 2;
            case ZCLTypeDataType::ZCLType24bit:
            case ZCLTypeDataType::ZCLType24bitBitmap:
            case ZCLTypeDataType::ZCLTypeUInt24:
            case ZCLTypeDataType::ZCLTypeSInt24:
                return 3;
            case ZCLTypeDataType::ZCLType32bit:
            case ZCLTypeDataType::ZCLType32bitBitmap:
            case ZCLTypeDataType::ZCLTypeUInt32:
            case ZCLTypeDataType::ZCLTypeSInt32:
            case ZCLTypeDataType::ZCLTypeFloatSinglePrecision:
            case ZCLTypeDataType::ZCLTypeTimeOfDay:
            case ZCLTypeDataType::ZCLTypeDate:
            case ZCLTypeDataType::ZCLTypeUTCTime:
            case ZCLTypeDataType::ZCLTypeBACnetOID:
                return 4;
            case ZCLTypeDataType::ZCLTypeUInt40:
            case ZCLTypeDataType::ZCLTypeSInt40:
                return 5;
            case ZCLTypeDataType::ZCLTypeUInt48:
            case ZCLTypeDataType::ZCLTypeSInt48:
                return 6;
            case ZCLTypeDataType::ZCLTypeUInt56:
            case ZCLTypeDataType::ZCLTypeSInt56:
                return 7;
            case ZCLTypeDataType::ZCLTypeFloatDoublePrecision:
            case ZCLTypeDataType::ZCLTypeIEEEaddress:
            case ZCLTypeDataType::ZCLTypeUInt64:
            case ZCLTypeDataType::ZCLTypeSInt64:
                return 8;
            case ZCLTypeDataType::ZCLType128BitSecuryKey:
                return 16;
        }

        return 0;
    }

}

