//
// Created by paolo on 04/01/18.
//

#ifndef ZIGBEE_LIB_ZCLENUM8BITATTRIBUTE_H
#define ZIGBEE_LIB_ZCLENUM8BITATTRIBUTE_H

#include "zcl/ZCLAttribute.h"

namespace zigbee {

    class ZCLEnum8bitAttribute : public virtual ZCLAttribute {
    public:
        static std::string name() {
            return "8BitEnum";
        }

        static constexpr ZCLTypeDataType type = ZCLTypeDataType::ZCLTypeenum8;
    };

}


#endif //ZIGBEE_LIB_ZCLENUM8BITATTRIBUTE_H
