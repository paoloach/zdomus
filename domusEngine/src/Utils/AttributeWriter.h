//
// Created by paolo on 24/06/16.
//

#ifndef DOMUS_ENGINE_ATTRIBUTEWRITER_H
#define DOMUS_ENGINE_ATTRIBUTEWRITER_H

#include <zigbee/EndpointID.h>
#include <boost/asio/detail/shared_ptr.hpp>
#include "../json/json/json.h"
#include "AttributeWriterResult.h"
#include "../Utils/SingletonObjects.h"

namespace zigbee {
    class AttributeWriter {
    public:
        AttributeWriter(SingletonObjects *singletons) noexcept : singletons(singletons) {};

        AttributeWriterResult write(NwkAddr nwkAddr, EndpointID endpointID, std::shared_ptr<Cluster> cluster, Json::Value value);

    private:
        void addElement(NwkAddr nwkAddr, EndpointID endpointID, std::shared_ptr<zigbee::Cluster> cluster, Json::Value &&value, AttributeWriterResult &results);

        SingletonObjects *&singletons;
    };
}


#endif //DOMUS_ENGINE_ATTRIBUTEWRITER_H
