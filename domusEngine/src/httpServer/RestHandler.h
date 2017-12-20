//
// Created by paolo on 25/04/17.
//

#ifndef DOMUS_ENGINE_RESTHANDLER_H
#define DOMUS_ENGINE_RESTHANDLER_H

#include "endpoint.h"
#include "router.h"

namespace zigbee {
    class SingletonObjects;
    namespace http {
        class RestHandler {
        public:
            RestHandler(zigbee::SingletonObjects &singletons);
            virtual ~RestHandler() = default;
            virtual void start();
            virtual void addGetPath(std::string path, Pistache::Rest::Route::Handler fn);

        private:
            Pistache::Rest::Router router;
            Pistache::Http::Endpoint server;
        };
    } /* namespace http */
} /* namespace zigbee */


#endif //DOMUS_ENGINE_RESTHANDLER_H
