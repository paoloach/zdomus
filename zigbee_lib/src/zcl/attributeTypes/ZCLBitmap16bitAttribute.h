//
// Created by paolo on 04/01/18.
//

#ifndef ZIGBEE_LIB_ZCLBITMAP16BITATTRIBUTE_H
#define ZIGBEE_LIB_ZCLBITMAP16BITATTRIBUTE_H

#include "zcl/ZCLAttribute.h"

namespace zigbee {
    class ZCLBitmap16bitAttribute : public virtual ZCLAttribute{
    public:
        static std::string name() {
            return "16bitBitmap";
        }

        static constexpr ZCLTypeDataType type = ZCLTypeDataType::ZCLType16bitBitmap;
    };
}


#endif //ZIGBEE_LIB_ZCLBITMAP16BITATTRIBUTE_H
