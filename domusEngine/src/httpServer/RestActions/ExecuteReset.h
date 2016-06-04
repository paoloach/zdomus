//
// Created by paolo on 04/06/16.
//

#ifndef DOMUS_ENGINE_EXECUTERESET_H
#define DOMUS_ENGINE_EXECUTERESET_H

#include "../RestParser/RestActions.h"
#include "ClusterThrowingException.h"

namespace zigbee {

    class SingletonObjects;

    namespace http {
        class ExecuteReset  : public ActionHandler{
        public:
            ExecuteReset(SingletonObjects &singletons) noexcept : singletons(singletons) { };

            void operator()(const PlaceHolders &&placeHolder, Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

        private:
            SingletonObjects &singletons;
        };
    }
}


#endif //DOMUS_ENGINE_EXECUTERESET_H
