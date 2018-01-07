//
// Created by paolo on 04/01/18.
//

#ifndef ZIGBEE_LIB_ZCLUINT16ATTRIBUTE_H
#define ZIGBEE_LIB_ZCLUINT16ATTRIBUTE_H

#include "zcl/ZCLAttribute.h"

namespace zigbee {
    class ZCLuint16Attribute : public virtual ZCLAttribute {
    public:
        static std::string name() {
            return "UInt16";
        }

        static constexpr ZCLTypeDataType type = ZCLTypeDataType::ZCLTypeUInt16;
    };
}


#endif //ZIGBEE_LIB_ZCLINT16ATTRIBUTE_H
