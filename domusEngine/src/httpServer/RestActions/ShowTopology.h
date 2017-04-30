//
// Created by paolo on 04/10/16.
//

#ifndef DOMUS_ENGINE_SHOWTOPOLGY_H
#define DOMUS_ENGINE_SHOWTOPOLGY_H

#include <set>
#include <zigbee/NwkAddr.h>

#include "endpoint.h"
#include "router.h"
#include "../../json/json/json.h"

namespace zigbee {
    class SingletonObjects;
    namespace http {
        class ShowTopology  {
        public:
            ShowTopology(SingletonObjects &singletons) noexcept : singletons(singletons) {};

            Net::Rest::Route::Result  operator()(const Net::Rest::Request& request, Net::Http::ResponseWriter response);

        private:
            Json::Value createChildren(std::set<NwkAddr> &);
            Json::Value createNode(NwkAddr &);
            SingletonObjects &singletons;
        };

    }
}


#endif //DOMUS_ENGINE_SHOWTOPOLGY_H
