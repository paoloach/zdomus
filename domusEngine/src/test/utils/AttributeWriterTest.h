//
// Created by paolo on 24/06/16.
//

#ifndef DOMUS_ENGINE_ATTRIBUTEWRITERTEST_H
#define DOMUS_ENGINE_ATTRIBUTEWRITERTEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Mocks/SingletonObjectsMock.h"
#include "../Mocks/ClusterMock.h"
#include "../Mocks/ZCLAttributeMock.h"
#include "../Mocks/ZigbeeDeviceMock.h"
#include "../../json/json/json.h"

namespace zigbee {
    class AttributeWriter;
    namespace test {
        class AttributeWriterTest : public ::testing::Test {
        protected:
            virtual void SetUp() override;

            SingletonObjectsMock singletonObjectsMock;
            std::shared_ptr<ZigbeeDeviceMock> zigbeeDeviceMock;
            std::shared_ptr<ClusterMock> clusterMock;
            std::shared_ptr<ZCLAttributeMock> attributeMockString;
            std::shared_ptr<ZCLAttributeMock> attributeMockInt8;
            NwkAddr nwkAddr;
            EndpointID endpointID;
            std::unique_ptr<AttributeWriter> attributeWriter;
            Json::Value root;
            Json::Value attributes;
            Json::Value attributeString;
            Json::Value attributeInt8;
            Json::Value attributeUInt32;
            Json::Value attributeUInt32Raw;
        };
    }
}


#endif //DOMUS_ENGINE_ATTRIBUTEWRITERTEST_H
