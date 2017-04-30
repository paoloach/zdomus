//
// Created by paolo on 30/04/17.
//

#include "RestHandlerMock.h"
namespace zigbee {
    namespace test {
        namespace http {
            RestHandlerMock::RestHandlerMock(SingletonObjects  &singletons):
            RestHandler(singletons){}

            RestHandlerMock::~RestHandlerMock() {

            }
        }
    }
}