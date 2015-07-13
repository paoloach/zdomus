/*
 * ComandFactoryTest.cpp
 *
 *  Created on: 16/dic/2014
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include <array>
#include <typeinfo>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../../Comand/CmdGetUpdate.h"
#include "../../Comand/CmdUpdateAttribute.h"
#include "../../Comand/CmdRequestAttribute.h"
#include "../../Comand/CmdSendCmd.h"

#include "ComandFactoryTest.h"
#include "Comands.h"
#include "jsonFields.h"

namespace zigbee {
namespace test {

using namespace testing;
using std::string;
using std::stringstream;
using boost::property_tree::ptree;
using namespace boost::property_tree::json_parser;

static constexpr uint64_t TOKEN_DEVICES_ID = 345;
static constexpr uint64_t TOKEN_PROPERTIES_ID = 679;

struct RequestAttribute {
	int nwkAddr;
	int endpoint;
	int cluster;
	int attributeId;
};


struct CmdSend {
	int nwkAddr;
	int endpoint;
	int cluster;
	int cmdId;
	std::vector<uint8_t> data;
};


static constexpr RequestAttribute REQUEST_ATTRIBUTE_1 = {1,2,3,4};
static constexpr RequestAttribute REQUEST_ATTRIBUTE_2 = {5,6,7,8};
static const CmdSend CMD_SEND_1 = {1,2,3,4,{10,11,12,13} };

ComandFactoryTest::~ComandFactoryTest() {
}

void ComandFactoryTest::SetUp() {

}

void ComandFactoryTest::TearDown() {
}

static std::string createDeviceUpdateCmdRequest(uint64_t tokenId) {
	ptree comandProperty {};
	stringstream outStream {};

	comandProperty.put(UPDATE_CMD, tokenId);
	write_json(outStream, comandProperty);
	return outStream.str();
}

static std::string createProperiesUpdateCmdRequest(uint64_t tokenId) {
	ptree comandProperty {};
	stringstream outStream {};

	comandProperty.put(UPDATE_ATTRIBUTE_CMD, tokenId);
	write_json(outStream, comandProperty);
	return outStream.str();
}

static ptree  createProperiesRequestAttribute(const RequestAttribute & requestAttribute) {
	ptree properties {};

	properties.put(SHORT_ADDR_NAME, requestAttribute.nwkAddr);
	properties.put(ENDPOINT_ID_NAME, requestAttribute.endpoint);
	properties.put(CLUSTER_ID_NAME, requestAttribute.cluster);
	properties.put(ATTR_ID_NAME, requestAttribute.attributeId);

	return properties;
}

static ptree  createPropertiesCmdSend(const CmdSend & requestAttribute) {
	ptree properties {};

	properties.put(SHORT_ADDR_NAME, requestAttribute.nwkAddr);
	properties.put(ENDPOINT_ID_NAME, requestAttribute.endpoint);
	properties.put(CLUSTER_ID_NAME, requestAttribute.cluster);
	properties.put(COMMAND_ID_NAME, requestAttribute.cmdId);

	return properties;
}

static std::string createStringProperyUpdateCmdRequest(const RequestAttribute & requestAttribute) {
	ptree comandProperty {};
	stringstream outStream {};

	comandProperty.add_child(PROPERTIES_REQUEST_NAME, createProperiesRequestAttribute(requestAttribute));

	write_json(outStream, comandProperty);
	return outStream.str();
}

static std::string createStringPropertiesUpdateCmdRequest(const RequestAttribute & requestAttribute1, const RequestAttribute & requestAttribute2) {
	ptree comandProperty {};
	stringstream outStream {};

	comandProperty.add_child(PROPERTIES_REQUEST_NAME, createProperiesRequestAttribute(requestAttribute1));
	comandProperty.add_child(PROPERTIES_REQUEST_NAME, createProperiesRequestAttribute(requestAttribute2));

	write_json(outStream, comandProperty);
	return outStream.str();
}

static std::string createStringCmdSend(const CmdSend & requestAttribute) {
	ptree comandProperty {};
	stringstream outStream {};

	comandProperty.add_child(SEND_COMMAND_CMD, createPropertiesCmdSend(requestAttribute));

	write_json(outStream, comandProperty);
	return outStream.str();
}

TEST_F( ComandFactoryTest, parserError) {

	std::vector<Comand_P>  comands = ComandFactory::createComands("NO JSON", zDevices, zigbeeDevice, attributeData);
	ASSERT_THAT(comands.size(), 0);
}

TEST_F( ComandFactoryTest, DeviceUpdateCmd) {
	std::string comand = createDeviceUpdateCmdRequest(TOKEN_DEVICES_ID);

	std::vector<Comand_P>  comands = ComandFactory::createComands(comand, zDevices, zigbeeDevice, attributeData);
	ASSERT_THAT(comands.size(), 1);
	ASSERT_THAT(typeid( *comands[0].get()).name(), StrEq(typeid( CmdGetUpdate).name()));
}

TEST_F( ComandFactoryTest, PropertiesUpdateCmd) {
	std::string comand = createProperiesUpdateCmdRequest(TOKEN_PROPERTIES_ID);

	std::vector<Comand_P>  comands = ComandFactory::createComands(comand, zDevices, zigbeeDevice, attributeData);
	ASSERT_THAT(comands.size(), 1);
	ASSERT_THAT(typeid( *comands[0].get()).name(), StrEq(typeid( CmdUpdateAttribute).name()));
}

TEST_F( ComandFactoryTest, RequestAttributeCmd) {
	std::string comand = createStringProperyUpdateCmdRequest(REQUEST_ATTRIBUTE_1);

	std::vector<Comand_P>  comands = ComandFactory::createComands(comand, zDevices, zigbeeDevice, attributeData);
	ASSERT_THAT(comands.size(), 1);
	ASSERT_THAT(typeid( *comands[0].get()).name(), StrEq(typeid( CmdRequestAttribute).name()));
}

TEST_F( ComandFactoryTest, MultipleRequestAttributeCmd) {
	std::string comand = createStringPropertiesUpdateCmdRequest(REQUEST_ATTRIBUTE_1, REQUEST_ATTRIBUTE_2);

	std::vector<Comand_P>  comands = ComandFactory::createComands(comand, zDevices, zigbeeDevice, attributeData);
	ASSERT_THAT(comands.size(), 2);
	ASSERT_THAT(typeid( *comands[0].get()).name(), StrEq(typeid( CmdRequestAttribute).name()));
	ASSERT_THAT(typeid( *comands[1].get()).name(), StrEq(typeid( CmdRequestAttribute).name()));
}

TEST_F( ComandFactoryTest, RequestSendCmd) {
	std::string comand = createStringCmdSend(CMD_SEND_1);

	std::vector<Comand_P>  comands = ComandFactory::createComands(comand, zDevices, zigbeeDevice, attributeData);
	ASSERT_THAT(comands.size(), 1);
	ASSERT_THAT(typeid( *comands[0].get()).name(), StrEq(typeid( CmdSendCmd).name()));
}


} /* namespace test */
} /* namespace zigbee */
