//
// Created by paolo on 12/05/17.
//

#ifndef DOMUS_ENGINE_SHOWPOWERNODE_H
#define DOMUS_ENGINE_SHOWPOWERNODE_H

#include "endpoint.h"
#include "router.h"
#include <zigbee/PowerNodeData.h>
#include <memory>
#include <zigbee/ResponseCallback.h>

namespace zigbee {
    class SingletonObjects;
    namespace http {
        class ShowPowerNodeCallback : public ResponseCallback<std::shared_ptr<PowerNodeData>>{
        public:
            ShowPowerNodeCallback(Pistache::Http::ResponseWriter && responseWriter):responseWriter(std::move(responseWriter)){}
            ShowPowerNodeCallback(ShowPowerNodeCallback && other):responseWriter(std::move(other.responseWriter)){}
            ~ShowPowerNodeCallback(){}
            ShowPowerNodeCallback &operator=(ShowPowerNodeCallback && other){
                responseWriter = std::move(other.responseWriter);
                return *this;
            }
            void response(std::shared_ptr<PowerNodeData>  powerNodeData) override;
            void timeout() override;

        private:
            Pistache::Http::ResponseWriter responseWriter;
        };

        class ShowPowerNode {
        public:
            ShowPowerNode(SingletonObjects  &singletons) noexcept :  singletons(singletons) {};

            Pistache::Rest::Route::Result operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &&response);

        private:
            SingletonObjects &singletons;
        };

    } /* namespace http */
} /* namespace zigbee */


#endif //DOMUS_ENGINE_SHOWPOWERNODE_H
