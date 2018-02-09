//
// Created by paolo on 02/01/18.
//

#ifndef DOMUS_ENGINE_RESTHANDLER_H
#define DOMUS_ENGINE_RESTHANDLER_H

#include <string>
#include "pistache/router.h"

namespace zigbee {
    namespace http {
        class RestHandler {
        public:
            virtual ~RestHandler() = default;

            virtual void start()=0;

            virtual void addGetPath(std::string &&path, Pistache::Rest::Route::Handler &&fn)=0;

            virtual bool isGetPathExist(std::string &path)=0;
        };
    }
}

#endif //DOMUS_ENGINE_RESTHANDLER_H
