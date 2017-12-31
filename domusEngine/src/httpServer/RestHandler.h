//
// Created by paolo on 25/04/17.
//

#ifndef DOMUS_ENGINE_RESTHANDLER_H
#define DOMUS_ENGINE_RESTHANDLER_H

#include <set>
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

            virtual void addGetPath(std::string && path, Pistache::Rest::Route::Handler && fn);
            virtual bool isGetPathExist(std::string & path){return pathGetUsed.count(path) > 0;}
        private:
            enum class Cmd {
                Start, Shutdown
            };

            void commandHandler();
            void getPath(std::string && path, Pistache::Rest::Route::Handler &&fn );

            Pistache::Rest::Router router;
            Pistache::Http::Endpoint *server;
            boost::fibers::unbuffered_channel<RestHandler::Cmd> channel;
            boost::fibers::fiber commandFiber;
            std::set<std::string> pathGetUsed;
        };
    } /* namespace http */
} /* namespace zigbee */


#endif //DOMUS_ENGINE_RESTHANDLER_H
