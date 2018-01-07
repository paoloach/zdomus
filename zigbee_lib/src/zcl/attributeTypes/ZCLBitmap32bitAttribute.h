//
// Created by paolo on 04/01/18.
//

#ifndef ZIGBEE_LIB_ZCLBITMAP32BITATTRIBUTE_H
#define ZIGBEE_LIB_ZCLBITMAP32BITATTRIBUTE_H

#include "zcl/ZCLAttribute.h"

namespace zigbee {
    class ZCLBitmap32bitAttribute : public virtual ZCLAttribute {
    public:
        static std::string name() {
            return "32bitBitmap";
        }

        static constexpr ZCLTypeDataType type = ZCLTypeDataType::ZCLType32bitBitmap;
    };
}


#endif //ZIGBEE_LIB_ZCLBITMAP32BITATTRIBUTE_H
