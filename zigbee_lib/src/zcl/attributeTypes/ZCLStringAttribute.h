//
// Created by paolo on 04/01/18.
//

#ifndef ZIGBEE_LIB_ZCL_STRING_ATTRIBUTE_H
#define ZIGBEE_LIB_ZCL_STRING_ATTRIBUTE_H

#include "zcl/ZCLAttribute.h"

namespace zigbee {
    class ZCLStringAttribute : public virtual ZCLAttribute {
    public:
        static std::string name() {
            return "String";
        }

        static constexpr ZCLTypeDataType type = ZCLTypeDataType::ZCLTypeStringChar;
    };
}


#endif //ZIGBEE_LIB_ZCLINT8ATTRIBUTE_H
