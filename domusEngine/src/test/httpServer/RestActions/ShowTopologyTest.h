//
// Created by paolo on 06/10/16.
//

#ifndef DOMUS_ENGINE_SHOWTOPOLOGYTEST_H
#define DOMUS_ENGINE_SHOWTOPOLOGYTEST_H
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "../../Mocks/SingletonObjectsMock.h"
#include "../../Mocks/ZDevicesMock.h"
#include "../../Mocks/http/HTTPServerResponseMock.h"
#include "../../Mocks/http/HTTPServerRequestMock.h"

namespace zigbee {
    namespace http {
        class ShowTopology;
        namespace test {

            class ShowTopologyTest : public ::testing::Test {
            protected:
                void SetUp() override;

                void TearDown() override;
            protected:
                std::unique_ptr<SingletonObjectsMock> singletonObject;
                std::unique_ptr<ShowTopology> showTopology;
                std::unique_ptr<zigbee::test::ZDevicesMock> zDevices;
                HTTPServerResponseMock response;
                HTTPServerRequestMock request;
            };
        }
    }
}


#endif //DOMUS_ENGINE_SHOWTOPOLOGYTEST_H
