//
// Created by paolo on 04/01/18.
//

#ifndef ZIGBEE_LIB_ZCLINT32ATTRIBUTE_H
#define ZIGBEE_LIB_ZCLINT32ATTRIBUTE_H

#include "zcl/ZCLAttribute.h"

namespace zigbee {
    class ZCLint32Attribute : public virtual ZCLAttribute {
    public:
        static std::string name() {
            return "Int32";
        }

        static constexpr ZCLTypeDataType type = ZCLTypeDataType::ZCLTypeSInt32;
    };
}


#endif //ZIGBEE_LIB_ZCLINT8ATTRIBUTE_H
