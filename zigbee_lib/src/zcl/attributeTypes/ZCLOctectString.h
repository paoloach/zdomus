//
// Created by paolo on 04/01/18.
//

#ifndef ZIGBEE_LIB_ZCLOCTETSTRING_H
#define ZIGBEE_LIB_ZCLOCTETSTRING_H

#include "zcl/ZCLAttribute.h"

namespace zigbee {
    class ZCLOctetString : public virtual ZCLAttribute {
    public:
        static std::string name() {
            return "OctectString";
        }

        static constexpr ZCLTypeDataType type = ZCLTypeDataType::ZCLTypeStringOctect;
    };
}


#endif //ZIGBEE_LIB_ZCLINT8ATTRIBUTE_H
