/*
 * ZCLbitmap8bitAttribute.h
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLBITMAP8BITATTRIBUTE_H_
#define ZCLBITMAP8BITATTRIBUTE_H_

#include "zcl/ZCLAttribute.h"

namespace zigbee {
    class ZCLBitmap8bitAttribute : public virtual ZCLAttribute {
    public:
        static std::string name() {
            return "8bitBitmap";
        }

        static constexpr ZCLTypeDataType type = ZCLTypeDataType::ZCLType8bitBitmap;
    };

} /* namespace zigbee */

#endif /* ZCLBITMAP8BITATTRIBUTE_H_ */
