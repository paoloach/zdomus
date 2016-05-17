/*
 * AttributeDataContainerTest.cpp
 *
 *  Created on: 01/dic/2014
 *      Author: Paolo Achdjian
 */

#include <boost/lexical_cast.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include "jsonFields.h"
#include "AttributeDataContainerTest.h"
#include "DataPropertyTreeMatcher.h"

namespace zigbee {
namespace test {

using boost::property_tree::ptree;
using namespace testing;

static  GenericMessage generticDataMsg {1};
static ReadAttributeResponseMessage message1 {generticDataMsg, 1,2,3,4,5,6 };
static ReadAttributeResponseMessage message2 {generticDataMsg, 11,12,13,14,15,16};
static ReadAttributeResponseMessage message3 {generticDataMsg, 21,22,23,24,25,26};
static ReadAttributeResponseMessage message4 {generticDataMsg, 31,32,33,34,35,36,};
static ReadAttributeResponseMessage message5 {generticDataMsg, 41,42,43,44,45,46,};


AttributeDataContainerTest::AttributeDataContainerTest() {
	container=nullptr;
}

AttributeDataContainerTest::~AttributeDataContainerTest() {
}

void AttributeDataContainerTest::SetUp() {
	const int MAX_ATTRIBUTE { 4 };
	container = new AttributeDataContainer { MAX_ATTRIBUTE };

}



void AttributeDataContainerTest::TearDown() {
	delete container;
}

//TEST_F( AttributeDataContainerTest, addAttributeRetriveToken0) {
//	container->push(message1);
//	ptree properties =  container->get(0);
//	ASSERT_THAT(properties.size(), Eq(2));
//	ASSERT_THAT(properties.get<uint64_t>(TOKEN_ATTRIBUTE_NAME), Eq(1));
//	ASSERT_THAT(properties.get_child(ATTRIBUTE_MESSAGE_NAME), isAttributeResponseMessage(message1));
//}
//
//TEST_F( AttributeDataContainerTest, add2AttributesRetriveToken0AddToken1) {
//	container->push(message1);
//	container->push(message2);
//	ptree properties =  container->get(1);
//	ASSERT_THAT(properties.size(), Eq(2));
//	ASSERT_THAT(properties.get<uint64_t>(TOKEN_ATTRIBUTE_NAME), Eq(2));
//	auto responses = properties.equal_range(ATTRIBUTE_MESSAGE_NAME);
//	ASSERT_THAT(std::distance(responses.first, responses.second),Eq(1));
//	ptree firstResponse = (*(responses.first)).second;
//	ASSERT_THAT(firstResponse, isAttributeResponseMessage(message2));
//}
//
//TEST_F( AttributeDataContainerTest, fillAttributesHistoryRetriveAll) {
//	container->push(message1);
//	container->push(message2);
//	container->push(message3);
//	container->push(message4);
//	ptree properties =  container->get(0);
//	ASSERT_THAT(properties.size(), Eq(5));
//	ASSERT_THAT(properties.get<uint64_t>(TOKEN_ATTRIBUTE_NAME), Eq(4));
//	auto responses = properties.equal_range(ATTRIBUTE_MESSAGE_NAME);
//	ASSERT_THAT(std::distance(responses.first, responses.second),Eq(4));
//	ptree firstResponse = (*(responses.first)).second;
//	responses.first++;
//	ptree secondResponse = (*(responses.first)).second;
//	responses.first++;
//	ptree thrithResponse = (*(responses.first)).second;
//	responses.first++;
//	ptree fourthResponse = (*(responses.first)).second;
//	ASSERT_THAT(firstResponse, isAttributeResponseMessage(message1));
//	ASSERT_THAT(secondResponse, isAttributeResponseMessage(message2));
//	ASSERT_THAT(thrithResponse, isAttributeResponseMessage(message3));
//	ASSERT_THAT(fourthResponse, isAttributeResponseMessage(message4));
//}
//
//TEST_F( AttributeDataContainerTest, fillPlus1AttributesHistoryRetriveAllTheFirstMessageIsLost) {
//	container->push(message1);
//	container->push(message2);
//	container->push(message3);
//	container->push(message4);
//	container->push(message5);
//	ptree properties =  container->get(1);
//	ASSERT_THAT(properties.size(), Eq(5));
//	ASSERT_THAT(properties.get<uint64_t>(TOKEN_ATTRIBUTE_NAME), Eq(5));
//	auto responses = properties.equal_range(ATTRIBUTE_MESSAGE_NAME);
//	ASSERT_THAT(std::distance(responses.first, responses.second),Eq(4));
//	ptree firstResponse = (*(responses.first)).second;
//	responses.first++;
//	ptree secondResponse = (*(responses.first)).second;
//	responses.first++;
//	ptree thrithResponse = (*(responses.first)).second;
//	responses.first++;
//	ptree fourthResponse = (*(responses.first)).second;
//	ASSERT_THAT(firstResponse, isAttributeResponseMessage(message2));
//	ASSERT_THAT(secondResponse, isAttributeResponseMessage(message3));
//	ASSERT_THAT(thrithResponse, isAttributeResponseMessage(message4));
//	ASSERT_THAT(fourthResponse, isAttributeResponseMessage(message5));
//}

}
} /* namespace zigbee */
