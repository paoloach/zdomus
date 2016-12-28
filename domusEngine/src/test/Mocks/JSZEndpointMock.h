/*
 * JSZEndpointMock.h
 *
 *  Created on: 03/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_JSZENDPOINTMOCK_H_
#define SRC_TEST_MOCKS_JSZENDPOINTMOCK_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../JavaScript/JSZEndpoint.h"
#include "shared_ptr_mock.h"

namespace zigbee {
    namespace test {

        class JSZEndpointMock : public JSZEndpoint, public sharedMockClass<JSZEndpoint, JSZEndpointMock> {
        public:
            JSZEndpointMock();

            virtual ~JSZEndpointMock();

            MOCK_METHOD2(initJsObjectsTemplate, void (v8::Isolate
                    *isolate, v8::Handle<v8::Object> & global));

            MOCK_METHOD3(createInstance, v8::Local<v8::Object>(v8::Isolate * isolate,
                    const ExtAddress &extAddress, EndpointID
                    endpointId));
        };


    } /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_JSZENDPOINTMOCK_H_ */
