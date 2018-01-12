//
// Created by paolo on 27/12/16.
//

#ifndef DOMUS_ENGINE_JSENDPOINTSTEST_H
#define DOMUS_ENGINE_JSENDPOINTSTEST_H

#include <gtest/gtest.h>

#include "../../JavaScript/JSZEndpoints.h"
#include "../../JavaScript/JSZEndpoint.h"
#include "../../JavaScript/V8Allocator.h"
#include "../Mocks/JSZEndpointMock.h"
#include "../Mocks/SingletonObjectsMock.h"
#include "../Mocks/ZDevicesMock.h"

namespace zigbee {
    namespace test {
        class JSEndpointsTest : public testing::Test {
        protected:
            virtual void SetUp() override;

            virtual void TearDown() override;
            v8::Local<v8::Value> runScript(const std::string &script);
        protected:
            V8Allocator v8Allocator;
            v8::Isolate::CreateParams createParams;
            v8::Isolate * isolate;
            std::unique_ptr<v8::Locker> locker;
            std::unique_ptr<JSZEndpoints> jsEndpoints;
            JSZEndpointMock jszEndpointMock;
            SingletonObjectsMock singletonObjectsMock;
            ZDevicesMock zDevicesMock;
            std::unique_ptr<trompeloeil::expectation> getZDevices;
            std::unique_ptr<trompeloeil::expectation> getDevices;
        };

    } /* namespace test */
} /* namespace zigbee */


#endif //DOMUS_ENGINE_JSENDPOINTSTEST_H
