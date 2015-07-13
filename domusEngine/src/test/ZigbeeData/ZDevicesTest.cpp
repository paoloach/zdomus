/*
 * ZDevicesTest.cpp
 *
 *  Created on: 29/nov/2014
 *      Author: Paolo Achdjian
 */

#include <boost/property_tree/json_parser.hpp>
#include <sstream>
#include "../../ZigbeeData/ExtAddress.h"
#include "ZDevicesTest.h"
#include "jsonFields.h"

using boost::property_tree::ptree;
using boost::property_tree::json_parser::write_json;
using namespace ::testing;
using std::cout;
using std::endl;

namespace zigbee {


ZDevicesTest::~ZDevicesTest() {
}

static  GenericMessage annunceMsg1 {1};
static  GenericMessage simpleeMsg {2};
static  AnnunceMessage annunce1 {annunceMsg1,2,{3,4,5,6,7,8,9,10},11};
static   AnnunceMessage annunce2 {annunceMsg1,102,{11,12,13,14,15,16,17,18},111};
static   SimpleDescMessage simpleDesc1 {simpleeMsg, 2, 101, 102,103,104,105,106,2};

void ZDevicesTest::SetUp() {
	std::stringstream stream;
	std::stringstream stream2;
	zDevices = new ZDevices { };
	ExtAddress extAddress(annunce1.extAddr);
	stream << extAddress;
	extAddr1 = stream.str();

	ExtAddress extAddress2(annunce2.extAddr);
	stream2 << extAddress2;
	extAddr2 = stream2.str();
}

void ZDevicesTest::TearDown() {
	delete zDevices;
}

TEST_F( ZDevicesTest, at_begin_return_empty) {
	ptree properties = zDevices->getDifferences(0);
	ASSERT_THAT(properties.size(), Eq(0));
}

TEST_F( ZDevicesTest, with_a_device) {

	zDevices->put(annunce1);
	ptree properties = zDevices->getDifferences(0);
	ASSERT_THAT(properties.size(), Eq(2));
	ASSERT_THAT(properties.get<int>(TOKEN_NAME), Eq(1));
	ptree zDevice = properties.get_child(DEVICE);
	ASSERT_THAT(zDevice.empty(),Eq(false));

	ASSERT_THAT(zDevice.get<int>(SHORT_ADDR_NAME), Eq(annunce1.nwkAddr));
	ASSERT_THAT(zDevice.get<int>(CAPABILITY_NAME), Eq(annunce1.capabilities));
	ASSERT_THAT(zDevice.get<std::string>(EXT_ADDR_NAME), Eq(extAddr1));
}

TEST_F( ZDevicesTest, diff_with_2_devices) {
	zDevices->put(annunce1);
	zDevices->put(annunce2);
	ptree properties = zDevices->getDifferences(0);
	ASSERT_THAT(properties.size(), Eq(3));
	ASSERT_THAT(properties.get<int>(TOKEN_NAME), Ne(0));

	ASSERT_THAT(properties.count(DEVICE),2);
	auto devices = properties.equal_range(DEVICE);
	ptree firstDevice = (*(devices.first)).second;
	devices.first++;
	ptree secondDevice = (*(devices.first)).second;

	ASSERT_THAT(firstDevice.get<int>(SHORT_ADDR_NAME), Eq(annunce1.nwkAddr));
	ASSERT_THAT(firstDevice.get<int>(CAPABILITY_NAME), Eq(annunce1.capabilities));
	ASSERT_THAT(firstDevice.get<std::string>(EXT_ADDR_NAME), Eq(extAddr1));
	ASSERT_THAT(secondDevice.get<int>(SHORT_ADDR_NAME), Eq(annunce2.nwkAddr));
	ASSERT_THAT(secondDevice.get<int>(CAPABILITY_NAME), Eq(annunce2.capabilities));
	ASSERT_THAT(secondDevice.get<std::string>(EXT_ADDR_NAME), Eq(extAddr2));
}

TEST_F(ZDevicesTest, annunce_and_simpleDesc){
	zDevices->put(annunce1);
	ptree properties = zDevices->getDifferences(0);
	zDevices->put(simpleDesc1);
	properties = zDevices->getDifferences(1);
	ASSERT_THAT(properties.get<int>(TOKEN_NAME), Eq(2));
	ptree zDevice = properties.get_child(DEVICE);

}

TEST_F( ZDevicesTest, json_diff_with_2_devices) {
	std::stringstream jsonOut {};

	zDevices->put(annunce1);
	zDevices->put(annunce2);
	ptree properties = zDevices->getDifferences(0);
	write_json(jsonOut, properties,false);
	ASSERT_THAT(jsonOut.str(), Eq("{\"token\":\"2\",\"zDevice\":{\"short_address\":\"2\",\"capability\":\"11\",\"extend_address\":\"03-04-05-06-07-08-09-0a\"},\"zDevice\":{\"short_address\":\"102\",\"capability\":\"111\",\"extend_address\":\"0b-0c-0d-0e-0f-10-11-12\"}}\n"));
}

} /* namespace zigbee */
