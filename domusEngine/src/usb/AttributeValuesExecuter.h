//
// Created by paolo on 10/05/16.
//

#ifndef DOMUS_ENGINE_ATTRIBUTEVALUESEXECUTER_H
#define DOMUS_ENGINE_ATTRIBUTEVALUESEXECUTER_H

#include <boost/log/trivial.hpp>

namespace zigbee {
    class AttributeValuesExecuter : public Executor {
    private:
        AttributeDataContainer &attributeDataContainer;
    public:
        AttributeValuesExecuter(AttributeDataContainer &attributeDataContainer) : attributeDataContainer(attributeDataContainer) { }

        virtual void operator()(unsigned char *data, int) override {
            BOOST_LOG_TRIVIAL(info) << "Read response attribute value";
            ReadAttributeResponseMessage *readAttributeResponseMessage = reinterpret_cast<ReadAttributeResponseMessage *>(data);
            attributeDataContainer.push(*readAttributeResponseMessage);
        }
    };
}

#endif //DOMUS_ENGINE_ATTRIBUTEVALUESEXECUTER_H
