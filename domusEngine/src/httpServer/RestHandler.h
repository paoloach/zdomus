//
// Created by paolo on 25/04/17.
//

#ifndef DOMUS_ENGINE_RESTHANDLER_H
#define DOMUS_ENGINE_RESTHANDLER_H

#include "pistache/endpoint.h"
#include "pistache/router.h"

namespace zigbee {
    class SingletonObjects;
    namespace http {
        class RestHandler {
        public:
            RestHandler(zigbee::SingletonObjects &singletons);
            virtual ~RestHandler() = default;
            virtual void start();
            virtual void addGetPath(std::string path, Net::Rest::Route::Handler fn);

        private:
            Net::Rest::Router router;
            Net::Http::Endpoint server;
        };
    } /* namespace http */
} /* namespace zigbee */


#endif //DOMUS_ENGINE_RESTHANDLER_H
