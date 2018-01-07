//
// Created by paolo on 04/01/18.
//

#ifndef ZIGBEE_LIB_ZCLUINT48ATTRIBUTE_H
#define ZIGBEE_LIB_ZCLUINT48ATTRIBUTE_H

#include "zcl/ZCLAttribute.h"

namespace zigbee {
    class ZCLuint48Attribute : public virtual ZCLAttribute {
    public:
        static std::string name() {
            return "UInt48";
        }

        static constexpr ZCLTypeDataType type = ZCLTypeDataType::ZCLTypeUInt48;
    };
}


#endif //ZIGBEE_LIB_ZCLUINT48ATTRIBUTE_H
