//
// Created by paolo on 13/05/16.
//

#ifndef ZIGBEE_LIB_ZCLATTRIBUTEUTILS_H
#define ZIGBEE_LIB_ZCLATTRIBUTEUTILS_H


#include <cstdlib>
#include <cstdint>

#include "ZCLDataType.h"

namespace zigbee {

    class ZclAttributeUtils {
    public:
        static size_t zclGetAttrDataLength(uint8_t dataType, uint8_t *pData);
        static size_t zclGetDataTypeLength( ZCLTypeDataType dataType );
    };
}


#endif //ZIGBEE_LIB_ZCLATTRIBUTEUTILS_H
