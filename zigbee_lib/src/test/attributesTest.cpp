//
// Created by developer on 11/16/15.
//

#include <gtest/gtest.h>

#include "zcl/attributeTypes/ZCLuint48Attribute.h"
#include "zcl/attributeTypes/ZCLint24Attribute.h"

namespace zigbee {
TEST(attributes, 48bit_rightorder) {
    std::shared_ptr<ZigbeeDevice> zigbee;
    auto attributeStatusRecord = std::make_shared<AttributeStatusRecord>();
    attributeStatusRecord->attributeId = 1;
    attributeStatusRecord->attributeDataType = (ZigbeeAttributeDataType) ZCLTypeDataType::ZCLTypeUInt48;
    attributeStatusRecord->dataLen = 6;
    attributeStatusRecord->data[0] = 0x01;
    attributeStatusRecord->data[1] = 0x02;
    attributeStatusRecord->data[2] = 0x03;
    attributeStatusRecord->data[3] = 0x04;
    attributeStatusRecord->data[4] = 0x05;
    attributeStatusRecord->data[5] = 0x06;


    ZCLuint48Attribute attribute(zigbee, nullptr, 1, "test", false);

    attribute.setValue(attributeStatusRecord);
    auto value = attribute.getValue();
    auto casted = boost::any_cast<uint64_t>(value);
    ASSERT_EQ(0x060504030201, casted);
}

TEST(attributes, S24bit_rightorder) {
    std::shared_ptr<ZigbeeDevice> zigbee;
    auto attributeStatusRecord = std::make_shared<AttributeStatusRecord>();
    attributeStatusRecord->attributeId = 1;
    attributeStatusRecord->attributeDataType = (ZigbeeAttributeDataType) ZCLTypeDataType::ZCLTypeSInt24;
    attributeStatusRecord->dataLen = 3;
    attributeStatusRecord->data[0] = 0x01;
    attributeStatusRecord->data[1] = 0x02;
    attributeStatusRecord->data[2] = 0x03;


    ZCLint24Attribute attribute(zigbee, nullptr, 1, "test", false);

    attribute.setValue(attributeStatusRecord);
    auto value = attribute.getValue();
    auto casted = boost::any_cast<int32_t>(value);
    ASSERT_EQ(0x030201, casted);
}

TEST(attributes, S24bit_negative) {
    std::shared_ptr<ZigbeeDevice> zigbee;
    auto attributeStatusRecord = std::make_shared<AttributeStatusRecord>();
    attributeStatusRecord->attributeId = 1;
    attributeStatusRecord->attributeDataType = (ZigbeeAttributeDataType) ZCLTypeDataType::ZCLTypeSInt24;
    attributeStatusRecord->dataLen = 3;
    attributeStatusRecord->data[0] = 0x01;
    attributeStatusRecord->data[1] = 0x02;
    attributeStatusRecord->data[2] = 0x83;


    ZCLint24Attribute attribute(zigbee, nullptr, 1, "test", false);

    attribute.setValue(attributeStatusRecord);
    auto value = attribute.getValue();
    auto casted = boost::any_cast<int32_t>(value);
    ASSERT_EQ(0xFF830201, casted);
}

};
