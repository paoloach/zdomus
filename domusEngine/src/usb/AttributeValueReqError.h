//
// Created by paolo on 10/05/16.
//

#ifndef DOMUS_ENGINE_ATTRIBUTEVALUEREQERROR_H
#define DOMUS_ENGINE_ATTRIBUTEVALUEREQERROR_H

#include "AttributeValuesSignalMap.h"
#include "Executor.h"

namespace zigbee {

    class AttributeValueReqError : public Executor {
        AttributeValueSignalMap &attributeValueSignalMap;
    public:
        AttributeValueReqError(AttributeValueSignalMap &attributeValueSignalMap) : attributeValueSignalMap(attributeValueSignalMap) {

        }

        virtual void operator()(unsigned char *data, int length) override;
    };
}

#endif //DOMUS_ENGINE_ATTRIBUTEVALUEREQERROR_H
