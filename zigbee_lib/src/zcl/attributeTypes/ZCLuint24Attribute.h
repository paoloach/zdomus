//
// Created by paolo on 04/01/18.
//

#ifndef ZIGBEE_LIB_ZCLUINT24ATTRIBUTE_H
#define ZIGBEE_LIB_ZCLUINT24ATTRIBUTE_H

#include "zcl/ZCLAttribute.h"

namespace zigbee {
    class ZCLuint24Attribute : public virtual ZCLAttribute {
    public:
        static std::string name() {
            return "UInt24";
        }

        static constexpr ZCLTypeDataType type = ZCLTypeDataType::ZCLTypeUInt24;
    };
}


#endif //ZIGBEE_LIB_ZCLINT8ATTRIBUTE_H
