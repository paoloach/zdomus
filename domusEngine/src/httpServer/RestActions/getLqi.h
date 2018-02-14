//
// Created by paolo on 13/02/18.
//

#ifndef DOMUS_ENGINE_GETLQI_H
#define DOMUS_ENGINE_GETLQI_H

#include <zigbee/messageStructure/LqiResponse.h>
#include <zigbee/ResponseCallback.h>
#include "pistache/endpoint.h"
#include "pistache/router.h"

namespace zigbee {
    class SingletonObjects;
    class GetLqi {
    public:
        GetLqi(SingletonObjects *singletons) : singletons(singletons) {}

        Pistache::Rest::Route::Result operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &&response);

    private:
        SingletonObjects *singletons;
    };


    class GetLqiCallback : public ResponseCallback<std::shared_ptr<LqiResponse> >{
    public:
        GetLqiCallback(Pistache::Http::ResponseWriter &&responseWriter) : responseWriter(std::move(responseWriter)) {}

        GetLqiCallback(GetLqiCallback &&other) : responseWriter(std::move(other.responseWriter)) {}

        ~GetLqiCallback() {}

        GetLqiCallback &operator=(GetLqiCallback &&other) {
            responseWriter = std::move(other.responseWriter);
            return *this;
        }

        void response(std::shared_ptr<LqiResponse> lqiResponse) override;

        void timeout() override;
    private:
        Pistache::Http::ResponseWriter responseWriter;
        static std::string toString(LogicalType logicalType);
        static std::string toString(Relationship relationship);
    };
}


#endif //DOMUS_ENGINE_GETLQI_H
