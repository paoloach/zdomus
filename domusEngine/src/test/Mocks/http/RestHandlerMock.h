//
// Created by paolo on 30/04/17.
//

#ifndef DOMUS_ENGINE_RESTHANDLERMOCK_H
#define DOMUS_ENGINE_RESTHANDLERMOCK_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../../httpServer/RestHandler.h"

namespace zigbee {
    namespace test {
        namespace http {
            class RestHandlerMock : public zigbee::http::RestHandler {
            public:
                RestHandlerMock(SingletonObjects &singletons);
                virtual ~RestHandlerMock();
                MOCK_METHOD0(start, void () );
                MOCK_METHOD2(addGetPath,  void (std::string path, Net::Rest::Route::Handler fn));
            };
        }
    }
}


#endif //DOMUS_ENGINE_RESTHANDLERMOCK_H
