//
// Created by paolo on 03/04/16.
//

#ifndef DOMUS_ENGINE_EXECUTEBIND_H
#define DOMUS_ENGINE_EXECUTEBIND_H

#include "ClusterThrowingException.h"

namespace zigbee {

  class SingletonObjects;

  namespace http {

    class ExecuteBind : public ClusterThrowingException {
    public:
        ExecuteBind(SingletonObjects &singletons, bool bind=true) noexcept : singletons(singletons),bind(bind) { };

        Net::Rest::Route::Result operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter  && response);

    private:
        SingletonObjects &singletons;
        bool bind;
    };
  }
}


#endif //DOMUS_ENGINE_EXECUTEBIND_H
