//
// Created by paolo on 25/04/17.
//

#ifndef DOMUS_ENGINE_RESTHANDLER_IMPL_H
#define DOMUS_ENGINE_RESTHANDLER_IMPL_H

#include <set>
#include <boost/fiber/unbuffered_channel.hpp>
#include <boost/fiber/fiber.hpp>
#include "pistache/endpoint.h"
#include "RestHandler.h"
#include "../Utils/SingletonObjects.h"

namespace zigbee {
    namespace http {
        class RestHandlerImpl : public RestHandler{
        public:
            RestHandlerImpl(SingletonObjects *singletons);

            virtual ~RestHandlerImpl() = default;

            virtual void start() override ;
            virtual void addGetPath(std::string && path, Pistache::Rest::Route::Handler && fn) override ;
            virtual bool isGetPathExist(std::string & path) override {return pathGetUsed.count(path) > 0;}
        private:
            enum class Cmd {
                Start, Shutdown
            };

            void commandHandler();
            void getPath(std::string && path, Pistache::Rest::Route::Handler &&fn );

            Pistache::Rest::Router router;
            Pistache::Http::Endpoint *server;
            boost::fibers::unbuffered_channel<RestHandlerImpl::Cmd> channel;
            boost::fibers::fiber commandFiber;
            std::set<std::string> pathGetUsed;
        };
    } /* namespace http */
} /* namespace zigbee */


#endif //DOMUS_ENGINE_RESTHANDLER_H
