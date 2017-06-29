//
// Created by paolo on 08/06/17.
//

#ifndef ZIGBEE_LIB_ATTRIBUTESRESPONSECALLBACK_H
#define ZIGBEE_LIB_ATTRIBUTESRESPONSECALLBACK_H

#include <vector>
#include "../zcl/ZCLAttribute.h"

namespace zigbee {
    class AttributesResponseCallback {
    public:
        virtual ~AttributesResponseCallback() = default;

        virtual void response(std::vector<ZCLAttribute *> && attributes )=0;
    };
}
#endif //ZIGBEE_LIB_ATTRIBUTESRESPONSECALLBACK_H
