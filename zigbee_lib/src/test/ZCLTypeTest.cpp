/*
 * ZCLTypeTest.cpp
 *
 *  Created on: 07/gen/2015
 *      Author: Paolo Achdjian
 */
#include <sstream>


#include "ZCLTypeTest.h"
#include "../zcl/ZCLDataType.h"


namespace zigbee {

using namespace testing;

ZCLTypeTest::ZCLTypeTest() {
}

ZCLTypeTest::~ZCLTypeTest() {
}

void ZCLTypeTest::SetUp() {
}

void ZCLTypeTest::TearDown() {
}

TEST_F( ZCLTypeTest, Raw_ZCLTypeIEEEaddress_from_string) {
	std::vector<uint8_t> expected = {0x10,0x40,0x30,0x44,0xA5,0xB7,0x78,0x93};
	std::stringstream stream;
	ZCLType<ZCLTypeDataType::ZCLTypeIEEEaddress> typeIEEEAdress;

	for (int i = 0; i < 8 - 1; i++) {
		stream << std::setw(2) << std::setfill('0') << std::hex << (int)expected[i] << "-";
	}

	stream << std::setw(2) << std::setfill('0') << std::hex << (int)expected[7];

	std::vector<uint8_t> data = typeIEEEAdress.getRaw(stream.str());

	ASSERT_THAT(data, Eq(expected));
}

TEST_F( ZCLTypeTest, Raw_ZCLArrayType) {
	std::vector<std::string> arrays = {"10","20"};
	uint8_t size=2;
	std::vector<uint8_t> expected = {static_cast<uint8_t>(ZCLTypeDataType::ZCLTypeUInt16), size, 10, 0, 20, 0};
	std::stringstream stream;
	ZCLArrayType<ZCLTypeDataType::ZCLTypeUInt16> typeArray;

	std::vector<uint8_t> data = typeArray.getRaw(arrays);

	ASSERT_THAT(data, Eq(expected));
}

TEST_F( ZCLTypeTest, Raw_CmdListType) {
	std::vector<std::string> arrays = {"10","20"};
	uint8_t size=2;
	std::vector<uint8_t> expected = {10, 0, 20, 0};
	std::stringstream stream;
	ZCLCmdList<ZCLTypeDataType::ZCLTypeUInt16> typeArray;

	std::vector<uint8_t> data = typeArray.getRaw(arrays);

	ASSERT_THAT(data, Eq(expected));
}

} /* namespace zigbee */
