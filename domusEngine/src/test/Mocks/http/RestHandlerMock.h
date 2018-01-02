//
// Created by paolo on 30/04/17.
//

#ifndef DOMUS_ENGINE_RESTHANDLERMOCK_H
#define DOMUS_ENGINE_RESTHANDLERMOCK_H

#include "../../../trompeloeil/src/trompeloeil/include/trompeloeil.hpp"
#include "../../../httpServer/RestHandler.h"

namespace zigbee {
    namespace test {
        namespace http {
            class RestHandlerMock : public zigbee::http::RestHandler {
            public:
                MAKE_MOCK0(start, void () );
                MAKE_MOCK2(addGetPath,  void (std::string &&path, Pistache::Rest::Route::Handler &&fn));
                MAKE_MOCK1(isGetPathExist, bool (std::string &path));
            };
        }
    }
}


#endif //DOMUS_ENGINE_RESTHANDLERMOCK_H
