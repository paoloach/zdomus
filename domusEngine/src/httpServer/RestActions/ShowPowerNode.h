//
// Created by paolo on 12/05/17.
//

#ifndef DOMUS_ENGINE_SHOWPOWERNODE_H
#define DOMUS_ENGINE_SHOWPOWERNODE_H

#include "endpoint.h"
#include "router.h"
#include <zigbee/PowerNodeData.h>
#include <memory>
#include <zigbee/powerNode/PowerNodeResponseCallback.h>

namespace zigbee {
    class SingletonObjects;
    namespace http {
        class ShowPowerNodeCallback : public PowerNodeResponseCallback{
        public:
            ShowPowerNodeCallback(Net::Http::ResponseWriter && responseWriter):responseWriter(std::move(responseWriter)){}
            ShowPowerNodeCallback(ShowPowerNodeCallback && other):responseWriter(std::move(other.responseWriter)){}
            ~ShowPowerNodeCallback(){}
            ShowPowerNodeCallback &operator=(ShowPowerNodeCallback && other){
                responseWriter = std::move(other.responseWriter);
                return *this;
            }
            void response(std::shared_ptr<PowerNodeData>  powerNodeData) override;
            void timeout() override;

        private:
            Net::Http::ResponseWriter responseWriter;
        };

        class ShowPowerNode {
        public:
            ShowPowerNode(SingletonObjects  &singletons) noexcept :  singletons(singletons) {};

            Net::Rest::Route::Result operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter &&response);

        private:
            SingletonObjects &singletons;
        };

    } /* namespace http */
} /* namespace zigbee */


#endif //DOMUS_ENGINE_SHOWPOWERNODE_H
