//
// Created by paolo on 04/06/16.
//

#ifndef DOMUS_ENGINE_EXECUTERESET_H
#define DOMUS_ENGINE_EXECUTERESET_H

#include "endpoint.h"
#include "router.h"
#include "../../Utils/SingletonObjects.h"

namespace zigbee::http {
    class ExecuteReset {
    public:
        ExecuteReset(SingletonObjects *singletons) noexcept : singletons(singletons) {};

        Pistache::Rest::Route::Result operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &&response);

    private:
        SingletonObjects * singletons;
    };
}


#endif //DOMUS_ENGINE_EXECUTERESET_H
