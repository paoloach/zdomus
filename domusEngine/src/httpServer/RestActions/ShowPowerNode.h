//
// Created by paolo on 12/05/17.
//

#ifndef DOMUS_ENGINE_SHOWPOWERNODE_H
#define DOMUS_ENGINE_SHOWPOWERNODE_H

#include "endpoint.h"
#include "router.h"
#include <zigbee/PowerNodeData.h>
#include <memory>

namespace zigbee {
    class SingletonObjects;
    namespace http {
        class ShowPowerNodeCallback {
        public:
            ShowPowerNodeCallback(Net::Http::ResponseWriter && response):response(std::move(response)){}
            ShowPowerNodeCallback(ShowPowerNodeCallback && other):response(std::move(other.response)){}
            ~ShowPowerNodeCallback(){}
            ShowPowerNodeCallback &operator=(ShowPowerNodeCallback && other){
                response = std::move(other.response);
                return *this;
            }
            void apply(std::shared_ptr<PowerNodeData>  powerNodeData);
        private:
            Net::Http::ResponseWriter response;
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
