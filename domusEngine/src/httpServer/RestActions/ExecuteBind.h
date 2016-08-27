//
// Created by paolo on 03/04/16.
//

#ifndef DOMUS_ENGINE_EXECUTEBIND_H
#define DOMUS_ENGINE_EXECUTEBIND_H

#include "../RestParser/RestActions.h"
#include "ClusterThrowingException.h"

namespace zigbee {

  class SingletonObjects;

  namespace http {
    class PlaceHolders;

    class ExecuteBind : public ActionHandler, public ClusterThrowingException {
    public:
        ExecuteBind(SingletonObjects &singletons, bool bind=true) noexcept : singletons(singletons),bind(bind) { };

        void operator()(const PlaceHolders &&placeHolder, ServerRequest &request, Poco::Net::HTTPServerResponse &response);

    private:
        SingletonObjects &singletons;
        bool bind;
    };
  }
}


#endif //DOMUS_ENGINE_EXECUTEBIND_H
