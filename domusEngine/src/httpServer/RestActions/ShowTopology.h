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
#include "../../Utils/SingletonObjects.h"

namespace zigbee::http {
    class ShowTopology {
    public:
        ShowTopology(SingletonObjects *singletons) noexcept : singletons(singletons) {};

        Pistache::Rest::Route::Result operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &&response);

    private:
        Json::Value createChildren(std::set<NwkAddr> &);

        Json::Value createNode(NwkAddr &);

        SingletonObjects *singletons;
    };
}


#endif //DOMUS_ENGINE_SHOWTOPOLGY_H
