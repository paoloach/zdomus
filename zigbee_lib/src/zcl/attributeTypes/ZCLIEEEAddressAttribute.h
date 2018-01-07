//
// Created by paolo on 04/01/18.
//

#ifndef ZIGBEE_LIB_ZCLIEEEADDRESSATTRIBUTE_H
#define ZIGBEE_LIB_ZCLIEEEADDRESSATTRIBUTE_H

#include "zcl/ZCLAttribute.h"

namespace zigbee {
    class ZCLIEEEAddressAttribute : public virtual ZCLAttribute {
    public:
        static std::string name() {
            return "IEEEAddress";
        }

        static constexpr ZCLTypeDataType type = ZCLTypeDataType::ZCLTypeIEEEaddress;
    };

}


#endif //ZIGBEE_LIB_ZCLIEEEADDRESSATTRIBUTE_H
