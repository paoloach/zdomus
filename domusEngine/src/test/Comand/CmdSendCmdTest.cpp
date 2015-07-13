/*
 * CmdSendCmdTest.cpp
 *
 *  Created on: 12/dic/2014
 *      Author: Paolo Achdjian
 */

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>

#include "jsonFields.h"
#include "CmdSendCmdTest.h"
#include "../../IO/ProperyTreeUtils.h"

namespace zigbee {
namespace test {

using namespace testing;
using boost::property_tree::ptree;
using namespace boost::property_tree::json_parser;
using std::stringstream;

static constexpr NwkAddr NWKADDR { 1 };
static constexpr EndpointID ENDPOINT { 2 };
static constexpr ClusterID CLUSTER { 3 };
static constexpr int CMD_ID { 4 };
static const std::vector<uint8_t> DATA { 10, 11, 12, 13 };

CmdSendCmdTest::~CmdSendCmdTest() {
}

void CmdSendCmdTest::SetUp() {
	inputJson = createInputJSON(NWKADDR, ENDPOINT, CLUSTER, CMD_ID, DATA);

	cmdSendCmd = new CmdSendCmd { zigbeeDevice };
}

void CmdSendCmdTest::TearDown() {
	delete cmdSendCmd;
}

TEST_F( CmdSendCmdTest, parse_data) {
	ASSERT_THAT(cmdSendCmd->parseData(inputJson), Eq(true));
}

TEST_F( CmdSendCmdTest, execute) {
	cmdSendCmd->parseData(inputJson);

	EXPECT_CALL(zigbeeDevice, sendCmd(NWKADDR, ENDPOINT, CLUSTER, CMD_ID, DATA));

	cmdSendCmd->execute();
}

TEST_F( CmdSendCmdTest, response_not_add_any_properties) {
	ptree properties { };

	cmdSendCmd->parseData(inputJson);
	cmdSendCmd->execute();
	cmdSendCmd->getResponse(properties);
	ASSERT_THAT(properties.empty(), Eq(true));
}

std::string CmdSendCmdTest::createInputJSON(NwkAddr nwkAddr, EndpointID endpoint, ClusterID cluster, int commandId, const std::vector<uint8_t> & data) {
	stringstream stream { };
	ptree properties { };

	properties.put(SHORT_ADDR_NAME, nwkAddr);
	properties.put(ENDPOINT_ID_NAME, endpoint);
	properties.put(CLUSTER_ID_NAME, cluster);
	properties.put(COMMAND_ID_NAME, commandId);
	ProperyTreeUtils::write(properties, data);

	write_json(stream, properties);

	return stream.str();
}

} /* namespace test */
} /* namespace zigbee */
