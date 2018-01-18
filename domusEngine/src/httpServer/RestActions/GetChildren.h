//
// Created by paolo on 16/01/18.
//

#ifndef DOMUS_ENGINE_GETCHILDREN_H
#define DOMUS_ENGINE_GETCHILDREN_H

#include "endpoint.h"
#include "router.h"

namespace zigbee {
    class SingletonObjects;
    class IEEEAddressResponse;

    class GetChildren {
    public:
        GetChildren(SingletonObjects * singletons): singletons(singletons){}
        Pistache::Rest::Route::Result operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &&response);
    private:
        SingletonObjects *singletons;
    };

    class GetChildrenCallback : public ResponseCallback<std::shared_ptr<IEEEAddressResponse> >{
    public:
        GetChildrenCallback(Pistache::Http::ResponseWriter &&responseWriter) : responseWriter(std::move(responseWriter)) {}

        GetChildrenCallback(GetChildrenCallback &&other) : responseWriter(std::move(other.responseWriter)) {}

        ~GetChildrenCallback() {}

        GetChildrenCallback &operator=(GetChildrenCallback &&other) {
            responseWriter = std::move(other.responseWriter);
            return *this;
        }

        void response(std::shared_ptr<IEEEAddressResponse> ieeeAddressResponse) override;

        void timeout() override;
    private:
        Pistache::Http::ResponseWriter responseWriter;
    };
}


#endif //DOMUS_ENGINE_GETCHILDREN_H
