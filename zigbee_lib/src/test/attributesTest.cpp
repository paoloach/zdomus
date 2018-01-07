//
// Created by developer on 11/16/15.
//

#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>
#include <src/zcl/attributeTypes/implementation/ZCLBitmap32bitAttributeImpl.h>

#include "zcl/attributeTypes/ZCLuint48Attribute.h"
#include "zcl/attributeTypes/ZCLint24Attribute.h"
#include "src/zcl/attributeTypes/implementation/ZCLUTCTimeImpl.h"
#include "src/zcl/attributeTypes/implementation/ZCLOctetStringImp.h"
#include "src/zcl/attributeTypes/implementation/ZCLBitmap32bitAttributeImpl.h"
#include "src/zcl/attributeTypes/implementation/ZCLBitmap16bitAttributeImpl.h"
#include <sstream>
#include <src/zcl/attributeTypes/implementation/ZCLuint48AttributeImpl.h>
#include <src/zcl/attributeTypes/implementation/ZCLint24AttributeImpl.h>

namespace zigbee {

    using boost::posix_time::ptime;
    using boost::posix_time::time_duration;
    using boost::gregorian::date;
    using boost::gregorian::Jan;


    TEST(attributes, 48bit_rightorder) {
        ZigbeeDevice *zigbee;
        uint8_t data[6];
        data[0] = 0x01;
        data[1] = 0x02;
        data[2] = 0x03;
        data[3] = 0x04;
        data[4] = 0x05;
        data[5] = 0x06;


        ZCLUINT48AttributeImpl attribute(zigbee, nullptr, 1, "test", false);

        attribute.setRawValue(data);
        auto value = attribute.getValue();
        auto casted = std::any_cast<uint64_t>(value);
        ASSERT_EQ(0x060504030201, casted);
    }

    TEST(attributes, S24bit_rightorder) {
        ZigbeeDevice *  zigbee;
        uint8_t data[3];
        data[0] = 0x01;
        data[1] = 0x02;
        data[2] = 0x03;


        ZCLint24AttributeImpl attribute(zigbee, nullptr, 1, "test", false);

        attribute.setRawValue(data);
        auto value = attribute.getValue();
        auto casted = std::any_cast<int32_t>(value);
        ASSERT_EQ(0x030201, casted);
    }

    TEST(attributes, S24bit_negative) {
        ZigbeeDevice *  zigbee;
        uint8_t data[3];
        data[0] = 0x01;
        data[1] = 0x02;
        data[2] = 0x83;


        ZCLint24AttributeImpl attribute(zigbee, nullptr, 1, "test", false);

        attribute.setRawValue(data);
        auto value = attribute.getValue();
        auto casted = std::any_cast<int32_t>(value);
        ASSERT_EQ(0xFF830201, casted);
    }

    TEST(attributes, UTCTime) {
        ZigbeeDevice *  zigbee;
        uint8_t data[4];
        data[0] = 0x01;
        data[1] = 0x02;
        data[2] = 0x03;
        data[4] = 0x03;

        boost::posix_time::seconds expectedSeconds(0x04030201);
        auto expectedTime = ptime(boost::gregorian::date(2000, Jan, 1), time_duration(0, 0, 0)) + expectedSeconds;


        ZCLUTCTimeImpl attribute(zigbee, nullptr, 1, "test", false);

        attribute.setRawValue(data);
        auto value = attribute.getValue();
        auto casted = std::any_cast<ptime>(value);
        ASSERT_EQ(expectedTime, casted);
    }

    TEST(attributes, stringOctect) {
        ZigbeeDevice *  zigbee;
        uint8_t data[4];
        data[0] = 0x03;
        data[1] = 0xAA;
        data[2] = 0xBB;
        data[4] = 0xCC;

        ZCLOctetStringImpl attribute(zigbee, nullptr, 1, "test", false);

        attribute.setRawValue(data);
        auto value = attribute.getValue();
        auto casted = std::any_cast<std::vector<uint8_t>>(value);
        ASSERT_EQ(3, casted.size());
        ASSERT_EQ(0xAA, casted[0]);
        ASSERT_EQ(0xBB, casted[1]);
        ASSERT_EQ(0xCC, casted[2]);
    }

    TEST(attributes, bitmap32bit) {
        ZigbeeDevice *  zigbee;
        uint8_t data[4];
        data[0] = 0x99;
        data[1] = 0xAA;
        data[2] = 0xBB;
        data[4] = 0xCC;

        ZCLBitmap32bitAttributeImpl attribute(zigbee, nullptr, 1, "test", false);

        attribute.setRawValue(data);
        auto value = attribute.getValue();
        auto casted = std::any_cast<std::bitset<32>>(value);
        std::bitset<32> expected(0xCCBBAA99);
        ASSERT_EQ(expected, casted);
        std::stringstream sstream;
        sstream << casted;
        ASSERT_EQ("11001100101110111010101010011001", sstream.str());
    }

    TEST(attributes, bitmap16bit) {
        ZigbeeDevice *  zigbee;
        uint8_t data[2];
        data[0] = 0x99;
        data[1] = 0xAA;
        ZCLBitmap16bitAttributeImpl attribute(zigbee, nullptr, 1, "test", false);

        attribute.setRawValue(data);
        auto value = attribute.getValue();
        auto casted = std::any_cast<std::bitset<16>>(value);
        std::bitset<16> expected(0xCCBBAA99);
        ASSERT_EQ(expected, casted);
        std::stringstream sstream;
        sstream << casted;
        ASSERT_EQ("1010101010011001", sstream.str());
    }

};
