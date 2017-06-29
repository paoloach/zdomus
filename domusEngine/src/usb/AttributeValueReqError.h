//
// Created by paolo on 10/05/16.
//

#ifndef DOMUS_ENGINE_ATTRIBUTEVALUEREQERROR_H
#define DOMUS_ENGINE_ATTRIBUTEVALUEREQERROR_H

#include <zigbee/ZigbeeDevice.h>
#include "Executor.h"

namespace zigbee {

    class AttributeValueReqError : public Executor {
    public:
        AttributeValueReqError(ZigbeeDevice *zigbeeDevice) : zigbeeDevice(zigbeeDevice){
        }

        virtual void operator()(unsigned char *data, int length) override;
    private:
        ZigbeeDevice * zigbeeDevice;
    };
}

#endif //DOMUS_ENGINE_ATTRIBUTEVALUEREQERROR_H
