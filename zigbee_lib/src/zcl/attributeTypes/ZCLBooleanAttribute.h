//
// Created by paolo on 04/01/18.
//

#ifndef ZIGBEE_LIB_ZCLBOOLEANATTRIBUTE_H
#define ZIGBEE_LIB_ZCLBOOLEANATTRIBUTE_H

#include "zcl/ZCLAttribute.h"

namespace zigbee {
    class ZCLBooleanAttribute : public virtual ZCLAttribute {
    public:
        static std::string name() {
            return "Boolean";
        }

        static constexpr ZCLTypeDataType type = ZCLTypeDataType::ZCLTypeBool;
    };
}


#endif //ZIGBEE_LIB_ZCLBOOLEANATTRIBUTE_H
