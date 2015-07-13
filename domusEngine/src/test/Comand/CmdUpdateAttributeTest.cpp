/*
 * CmdUpdateAttribute.cpp
 *
 *  Created on: 13/dic/2014
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include <array>
#include <boost/property_tree/json_parser.hpp>

#include "CmdUpdateAttributeTest.h"
#include "../Mocks/AttributeDataContainerMock.h"
#include "../../Comand/CmdUpdateAttribute.h"
#include "jsonFields.h"
#include "PTreeContainMatcher.h"

namespace zigbee {
namespace test {

using namespace testing;

static constexpr uint64_t TOKEN_ID {345};
static constexpr int A_VALUE {5454};
static const std::string  A_PROPERTY="a property";



CmdUpdateAttributeTest::~CmdUpdateAttributeTest() {
}

void CmdUpdateAttributeTest::SetUp() {
	attributeDataContainer = std::make_shared< AttributeDataContainerMock>();

	newProperties.put(PROPERTIES_NAME,"test");
}

void CmdUpdateAttributeTest::TearDown() {
}

TEST_F( CmdUpdateAttributeTest, response_add_new_properties_of_attributeDataContainer) {
	boost::property_tree::ptree properties {};
	properties.put(A_PROPERTY, A_VALUE);

	cmdUpdateAttribute = std::make_shared< CmdUpdateAttribute >( *(attributeDataContainer.get()), TOKEN_ID );

	EXPECT_CALL(*attributeDataContainer, get(TOKEN_ID)).WillRepeatedly(Return(newProperties));

	cmdUpdateAttribute->getResponse(properties);

	ASSERT_THAT(properties, contains(newProperties));
	ASSERT_THAT(properties.get<int>(A_PROPERTY), Eq(A_VALUE));
}




} /* namespace test */
} /* namespace zigbee */
