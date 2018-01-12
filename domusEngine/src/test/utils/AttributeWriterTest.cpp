//
// Created by paolo on 24/06/16.
//
#include <gtest/gtest.h>

#include "AttributeWriterTest.h"
#include "../../Utils/AttributeWriter.h"

namespace zigbee {
    namespace test {
        using namespace testing;
        using namespace Json;

        constexpr  int NETWORKID=12;
        constexpr  int ENDPOINT_ID=34;
        constexpr  int CLUSTER_ID=45;
        constexpr int ATTRIBUTE_STRING_ID=11;
        constexpr int ATTRIBUTE_INT_ID=13;
        constexpr int ATTRIBUTE_UINT32_ID=15;
        constexpr ClusterID clusterID{CLUSTER_ID};

        void AttributeWriterTest::SetUp() {
            Test::SetUp();

            nwkAddr.setId(NETWORKID);
            endpointID.setId(ENDPOINT_ID);

            attributeWriter = std::make_unique<AttributeWriter>(singletonObjectsMock);
            zigbeeDeviceMock = std::make_shared<ZigbeeDeviceMock>();
            clusterMock = std::make_shared<ClusterMock>();
            attributeMockString = std::make_shared<ZCLAttributeMock>(zigbeeDeviceMock, clusterMock.get(),ATTRIBUTE_STRING_ID, ZCLTypeDataType::ZCLTypeInvalid, "mock", false);
            attributeMockInt8 = std::make_shared<ZCLAttributeMock>(zigbeeDeviceMock, clusterMock.get(),ATTRIBUTE_INT_ID, ZCLTypeDataType::ZCLTypeInvalid, "mock", false);
            root = Json::Value{ValueType::objectValue};
            attributes = Json::Value{ValueType::arrayValue};
            attributeString = Json::Value{ValueType::objectValue};
            attributeString["id"]=ATTRIBUTE_STRING_ID;
            attributeString["type"]="string";
            attributeString["data"]="test string";

            attributeInt8 = Json::Value{ValueType::objectValue};
            attributeInt8["id"]=ATTRIBUTE_INT_ID;
            attributeInt8["type"]="int";
            attributeInt8["data"]=123;

            attributeUInt32 = Json::Value{ValueType::objectValue};
            attributeUInt32["id"]=ATTRIBUTE_UINT32_ID;
            attributeUInt32["type"]="int";
            attributeUInt32["data"]=0x12345678;

            attributeUInt32Raw = Json::Value{ValueType::objectValue};
            attributeUInt32Raw["id"]=ATTRIBUTE_UINT32_ID;
            attributeUInt32Raw["type"]="raw";
            auto attributeRawData = Json::Value{ValueType::arrayValue};
            attributeRawData[0u] = (int8_t) 0x12;
            attributeRawData[1u] = (int8_t)0x34;
            attributeRawData[2u] = (int8_t)0x56;
            attributeRawData[3u] = -120;
            attributeUInt32Raw["data"]=attributeRawData;


            EXPECT_CALL(singletonObjectsMock, getZigbeeDevice()).WillRepeatedly(Return(zigbeeDeviceMock));
            EXPECT_CALL(*clusterMock, getId()).WillRepeatedly(Return(clusterID));
        }

        TEST_F(AttributeWriterTest, OneElementTypeInt) {
            attributes[0u] = attributeString;
            root["attributes"]=attributes;
            ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeStringChar> attributeRawValue;

            EXPECT_CALL(*clusterMock, getAttribute(ATTRIBUTE_STRING_ID)).WillOnce(Return(attributeMockString));
            EXPECT_CALL(*attributeMockString, getAttributeRawValue()).WillOnce(ReturnRef(attributeRawValue));
            auto expectedData = [](uint8_t * p){return p[0] == 11 && memcmp(p+1, "test string",11 ) == 0;};
            EXPECT_CALL(*zigbeeDeviceMock, writeAttribute(nwkAddr, endpointID, clusterID, ATTRIBUTE_STRING_ID, ZCLTypeDataType::ZCLTypeStringChar, 12,  Truly(expectedData) ));

            auto results = attributeWriter->write(nwkAddr,endpointID, clusterMock, root);
            ASSERT_THAT(results.size(), 1);
            ASSERT_THAT(results.hasId(ATTRIBUTE_STRING_ID), true);
        }

        TEST_F(AttributeWriterTest, OneElementTypeInt8) {
            attributes[0u] = attributeInt8;
            root["attributes"]=attributes;
            ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeSInt8> attributeRawValue;

            EXPECT_CALL(*clusterMock, getAttribute(ATTRIBUTE_INT_ID)).WillOnce(Return(attributeMockInt8));
            EXPECT_CALL(*attributeMockInt8, getAttributeRawValue()).WillOnce(ReturnRef(attributeRawValue));
            EXPECT_CALL(*zigbeeDeviceMock, writeAttribute(nwkAddr, endpointID, clusterID, ATTRIBUTE_INT_ID, ZCLTypeDataType::ZCLTypeSInt8, 1, Truly([](uint8_t * p){return p[0] == 123;}) ));

            auto results = attributeWriter->write(nwkAddr,endpointID, clusterMock, root);
            ASSERT_THAT(results.size(), 1);
            ASSERT_THAT(results.hasId(ATTRIBUTE_INT_ID), true);
        }



        TEST_F(AttributeWriterTest, OneElementTypeUInt32) {
            attributes[0u] = attributeUInt32;
            root["attributes"]=attributes;
            ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeUInt32> attributeRawValue;

            EXPECT_CALL(*clusterMock, getAttribute(ATTRIBUTE_UINT32_ID)).WillOnce(Return(attributeMockInt8));
            EXPECT_CALL(*attributeMockInt8, getAttributeRawValue()).WillOnce(ReturnRef(attributeRawValue));
            auto expectedData = [](uint8_t * p){return p[3] == 0x12 && p[2] == 0x34 && p[1] == 0x56 && p[0] == 0x78;};
            EXPECT_CALL(*zigbeeDeviceMock, writeAttribute(nwkAddr, endpointID, clusterID, ATTRIBUTE_UINT32_ID, ZCLTypeDataType::ZCLTypeUInt32, 4, Truly( expectedData)));

            auto results = attributeWriter->write(nwkAddr,endpointID, clusterMock, root);
            ASSERT_THAT(results.size(), 1);
            ASSERT_THAT(results.hasId(ATTRIBUTE_UINT32_ID), true);

        }



        TEST_F(AttributeWriterTest, OneElementTypeUInt32_raw) {
            attributes[0u] = attributeUInt32Raw;
            root["attributes"]=attributes;
            ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeUInt32> attributeRawValue;

            EXPECT_CALL(*clusterMock, getAttribute(ATTRIBUTE_UINT32_ID)).WillOnce(Return(attributeMockInt8));
            EXPECT_CALL(*attributeMockInt8, getAttributeRawValue()).WillOnce(ReturnRef(attributeRawValue));
            auto expectedData = [](uint8_t * p){
                std::cout << (int)p[3] << " " << (int)p[2] << " " << (int)p[1] << " " << (int)p[0] << std::endl;
                return p[0] == 0x12 && p[1] == 0x34 && p[2] == 0x56 && p[3] == 136;
            };
            EXPECT_CALL(*zigbeeDeviceMock, writeAttribute(nwkAddr, endpointID, clusterID, ATTRIBUTE_UINT32_ID, ZCLTypeDataType::ZCLTypeUInt32, 4, Truly( expectedData)));

            auto results = attributeWriter->write(nwkAddr,endpointID, clusterMock, root);
            ASSERT_THAT(results.size(), 1);
            ASSERT_THAT(results.hasId(ATTRIBUTE_UINT32_ID), true);
        }

        TEST_F(AttributeWriterTest, MultipleElement) {
            attributes[0u] = attributeUInt32;
            attributes[1u] = attributeString;
            root["attributes"]=attributes;
            ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeUInt32> attributeRawValue0;
            ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeStringChar> attributeRawValue1;
            EXPECT_CALL(*clusterMock, getAttribute(ATTRIBUTE_UINT32_ID)).WillOnce(Return(attributeMockInt8));
            EXPECT_CALL(*clusterMock, getAttribute(ATTRIBUTE_STRING_ID)).WillOnce(Return(attributeMockString));
            EXPECT_CALL(*attributeMockString, getAttributeRawValue()).WillOnce(ReturnRef(attributeRawValue1));
            EXPECT_CALL(*attributeMockInt8, getAttributeRawValue()).WillOnce(ReturnRef(attributeRawValue0));
            auto expectedData1 = [](uint8_t * p){return p[0] == 11 && memcmp(p+1, "test string",11 ) == 0;};
            auto expectedData0 = [](uint8_t * p){return p[3] == 0x12 && p[2] == 0x34 && p[1] == 0x56 && p[0] == 0x78;};
            EXPECT_CALL(*zigbeeDeviceMock, writeAttribute(nwkAddr, endpointID, clusterID, ATTRIBUTE_UINT32_ID, ZCLTypeDataType::ZCLTypeUInt32, 4, Truly( expectedData0)));
            EXPECT_CALL(*zigbeeDeviceMock, writeAttribute(nwkAddr, endpointID, clusterID, ATTRIBUTE_STRING_ID, ZCLTypeDataType::ZCLTypeStringChar, 12,  Truly(expectedData1) ));

            auto results = attributeWriter->write(nwkAddr,endpointID, clusterMock, root);
            ASSERT_THAT(results.size(), 2);
            ASSERT_THAT(results.hasId(ATTRIBUTE_UINT32_ID), true);
            ASSERT_THAT(results.hasId(ATTRIBUTE_STRING_ID), true);
        }

    }
}



