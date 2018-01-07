//
// Created by paolo on 04/01/18.
//

#ifndef ZIGBEE_LIB_ZCL_UTCTIME_ATTRIBUTE_H
#define ZIGBEE_LIB_ZCL_UTCTIME_ATTRIBUTE_H

#include "zcl/ZCLAttribute.h"

namespace zigbee {
    class ZCLUTCTime : public virtual ZCLAttribute {
    public:
        static std::string name() {
            return "UTCTime";
        }

        static constexpr ZCLTypeDataType type = ZCLTypeDataType::ZCLTypeUTCTime;
    };
}


#endif //ZIGBEE_LIB_ZCLINT8ATTRIBUTE_H
