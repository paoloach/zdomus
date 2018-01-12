/*
 * JSZEndpointMock.h
 *
 *  Created on: 03/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_JSZENDPOINTMOCK_H_
#define SRC_TEST_MOCKS_JSZENDPOINTMOCK_H_

#include <gtest/gtest.h>
#include "../../trompeloeil/src/trompeloeil/include/trompeloeil.hpp"
#include "../../JavaScript/JSZEndpoint.h"

namespace zigbee {
    namespace test {

        class JSZEndpointMock : public JSZEndpoint{
        public:
            JSZEndpointMock();

            virtual ~JSZEndpointMock();

            MAKE_MOCK2(initJsObjectsTemplate, void (v8::Isolate*isolate, v8::Handle<v8::Object> & global));

            MAKE_MOCK3(createInstance, v8::Local<v8::Object>(v8::Isolate * isolate,const ExtAddress &extAddress, EndpointID endpointId));
        };


    } /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_JSZENDPOINTMOCK_H_ */
