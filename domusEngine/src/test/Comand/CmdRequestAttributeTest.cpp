/*
 * CmdRequestAttributeTest.cpp
 *
 *  Created on: 13/dic/2014
 *      Author: Paolo Achdjian
 */

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>

#include "jsonFields.h"
#include "CmdRequestAttributeTest.h"
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
static constexpr int ATTRIBUTE_STRING_ID { 4 };

CmdRequestAttributeTest::~CmdRequestAttributeTest() {
}

void CmdRequestAttributeTest::SetUp() {
	inputJson = createInputJSON(NWKADDR, ENDPOINT, CLUSTER, ATTRIBUTE_STRING_ID);

	cmdReqAttribute = new CmdRequestAttribute { zigbeeDevice };
}

void CmdRequestAttributeTest::TearDown() {
	delete cmdReqAttribute;
}

TEST_F( CmdRequestAttributeTest, parse_data) {
	ASSERT_THAT(cmdReqAttribute->parseData(inputJson), Eq(true));
}

TEST_F( CmdRequestAttributeTest, execute) {
	cmdReqAttribute->parseData(inputJson);

	EXPECT_CALL(zigbeeDevice, requestAttribute(NWKADDR, ENDPOINT, CLUSTER, ATTRIBUTE_STRING_ID));

	cmdReqAttribute->execute();
}

TEST_F( CmdRequestAttributeTest, responso_add_any_properties) {
	boost::property_tree::ptree result { };

	cmdReqAttribute->parseData(inputJson);
	cmdReqAttribute->execute();
	cmdReqAttribute->getResponse(result);

	ASSERT_THAT(result.empty(), Eq(true));
}

std::string CmdRequestAttributeTest::createInputJSON(NwkAddr nwkAddr, EndpointID endpoint, ClusterID cluster, int attributeId) {
	stringstream stream { };
	ptree properties { };

	properties.put(SHORT_ADDR_NAME, nwkAddr);
	properties.put(ENDPOINT_ID_NAME, endpoint);
	properties.put(CLUSTER_ID_NAME, cluster);
	properties.put(ATTR_ID_NAME, attributeId);

	write_json(stream, properties);

	return stream.str();
}

} /* namespace test */
} /* namespace zigbee */
