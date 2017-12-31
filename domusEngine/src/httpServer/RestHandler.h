//
// Created by paolo on 25/04/17.
//

#ifndef DOMUS_ENGINE_RESTHANDLER_H
#define DOMUS_ENGINE_RESTHANDLER_H

#include <boost/fiber/unbuffered_channel.hpp>
#include <boost/fiber/fiber.hpp>
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
            enum class Cmd {
                Start,
                Shutdown
            };

            void commandHandler();
            Pistache::Rest::Router router;
            Pistache::Http::Endpoint  * server;
            boost::fibers::unbuffered_channel<RestHandler::Cmd> channel;
            boost::fibers::fiber commandFiber;
        };
    } /* namespace http */
} /* namespace zigbee */


#endif //DOMUS_ENGINE_RESTHANDLER_H
