/*
 * CmdGetUpdateTest.cpp
 *
 *  Created on: 04/dic/2014
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include <array>
#include <boost/property_tree/json_parser.hpp>

#include "CmdGetUpdateTest.h"
#include "PTreeContainMatcher.h"

namespace zigbee {
namespace test {

using namespace testing;
static boost::property_tree::ptree difference {};
static std::string differenceExpected { };

static uint64_t TOKEN_DEVICES_ID = 345;

CmdGetUpdateTest::CmdGetUpdateTest() {
	cmdGetUpdate = nullptr;
	zDevices = nullptr;
}

CmdGetUpdateTest::~CmdGetUpdateTest() {
}

void CmdGetUpdateTest::SetUp() {
	zDevices = new ZDevicesMock { };
	cmdGetUpdate = new CmdGetUpdate { *zDevices };
	difference.put("Test", 20);

	std::stringstream jsonOut { };
	boost::property_tree::json_parser::write_json(jsonOut, difference, false);

	differenceExpected = jsonOut.str();
}

void CmdGetUpdateTest::TearDown() {
	delete cmdGetUpdate;
	delete zDevices;
}

TEST_F( CmdGetUpdateTest, response_add_the_differences) {
	boost::property_tree::ptree result {};

	cmdGetUpdate->setTokenId(TOKEN_DEVICES_ID);

	EXPECT_CALL(*zDevices, getDifferences(TOKEN_DEVICES_ID)).WillRepeatedly(Return(difference));
	cmdGetUpdate->getResponse(result);
	ASSERT_THAT(result, contains(difference));
}



} /* namespace test */
} /* namespace zigbee */
