//
// Created by paolo on 24/06/16.
//

#ifndef DOMUS_ENGINE_ATTRIBUTEWRITER_H
#define DOMUS_ENGINE_ATTRIBUTEWRITER_H

#include "../../json/json/json.h"
namespace zigbee {

    class SingletonObjects;

    namespace http {
        class AttributeWriter {
        public:
            AttributeWriter(SingletonObjects &singletons) noexcept : singletons(singletons) { };
            void write(Json::Value & value);
        private:
            SingletonObjects & singletons;
        };
    }


#endif //DOMUS_ENGINE_ATTRIBUTEWRITER_H
