//
// Created by paolo on 03/04/16.
//

#ifndef DOMUS_ENGINE_EXECUTEBIND_H
#define DOMUS_ENGINE_EXECUTEBIND_H

#include "ClusterThrowingException.h"
#include "../../Utils/SingletonObjects.h"

namespace zigbee::http {
    class ExecuteBind : public ClusterThrowingException {
    public:
        ExecuteBind(SingletonObjects * singletons, bool bind=true) noexcept : singletons(singletons),bind(bind) { };

        Pistache::Rest::Route::Result operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter  && response);

    private:
        SingletonObjects * singletons;
        bool bind;
    };
}


#endif //DOMUS_ENGINE_EXECUTEBIND_H
