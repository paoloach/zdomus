//
// Created by paolo on 02/01/17.
//

#ifndef DOMUS_ENGINE_IEEEADDRESSRESPONSESERIALEXECUTORTEST_H
#define DOMUS_ENGINE_IEEEADDRESSRESPONSESERIALEXECUTORTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Mocks/SingletonObjectsMock.h"
#include "../Mocks/ZDevicesMock.h"
#include "../../serialDriver/IEEEAddressResponseSerialExecutor.h"

namespace zigbee {
    namespace test {
        class IEEEAddressResponseSerialExecutorTest : public ::testing::Test{
        protected:
            virtual void SetUp() override;
            virtual void TearDown() override;

            SingletonObjectsMock singletonObjectsMock;
            ZDevicesMock zDevicesMock;
            std::unique_ptr<IEEEAddressResponseSerialExecutor> executor;


        };
    }
}


#endif //DOMUS_ENGINE_IEEEADDRESSRESPONSESERIALEXECUTORTEST_H
