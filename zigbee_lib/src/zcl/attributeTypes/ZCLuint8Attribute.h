//
// Created by paolo on 04/01/18.
//

#ifndef ZIGBEE_LIB_ZCLUINT8ATTRIBUTE_H
#define ZIGBEE_LIB_ZCLUINT8ATTRIBUTE_H

#include "zcl/ZCLAttribute.h"

namespace zigbee {
    class ZCLuint8Attribute : public virtual ZCLAttribute {
    public:
        static std::string name() {
            return "UInt8";
        }

        static constexpr ZCLTypeDataType type = ZCLTypeDataType::ZCLTypeUInt8;
    };
}


#endif //ZIGBEE_LIB_ZCLINT8ATTRIBUTE_H
