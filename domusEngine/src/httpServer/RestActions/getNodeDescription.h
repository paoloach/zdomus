//
// Created by paolo on 31/01/18.
//

#ifndef DOMUS_ENGINE_GETNODEDESCRIPTION_H
#define DOMUS_ENGINE_GETNODEDESCRIPTION_H

#include <zigbee/messageStructure/NodeDescriptorResponse.h>
#include <zigbee/ResponseCallback.h>
#include "pistache/endpoint.h"
#include "pistache/router.h"

namespace zigbee {
    class SingletonObjects;
    class GetNodeDescription {
    public:
        GetNodeDescription(SingletonObjects *singletons) : singletons(singletons) {}

        Pistache::Rest::Route::Result operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &&response);

    private:
        SingletonObjects *singletons;
    };

    class GetNodeDescriptionCallback : public ResponseCallback<std::shared_ptr<NodeDescriptorResponse> >{
    public:
        GetNodeDescriptionCallback(Pistache::Http::ResponseWriter &&responseWriter) : responseWriter(std::move(responseWriter)) {}

        GetNodeDescriptionCallback(GetNodeDescriptionCallback &&other) : responseWriter(std::move(other.responseWriter)) {}

        ~GetNodeDescriptionCallback() {}

        GetNodeDescriptionCallback &operator=(GetNodeDescriptionCallback &&other) {
            responseWriter = std::move(other.responseWriter);
            return *this;
        }

        void response(std::shared_ptr<NodeDescriptorResponse> nodeDescriptorResponse) override;

        void timeout() override;
    private:
        Pistache::Http::ResponseWriter responseWriter;
        static std::string toString(LogicalType logicalType);
    };
}


#endif //DOMUS_ENGINE_GETNODEDESCRIPTION_H
