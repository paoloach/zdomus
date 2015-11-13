/*
 * CmdUpdateAttribute.h
 *
 *  Created on: 13/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_COMAND_CMDUPDATEATTRIBUTETEST_H_
#define SRC_TEST_COMAND_CMDUPDATEATTRIBUTETEST_H_

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../ZigbeeData/ZDevices.h"
#include "../../Comand/CmdGetUpdate.h"
#include "../Mocks/ZDevicesMock.h"

namespace zigbee {
class CmdUpdateAttribute;

namespace test {
class AttributeDataContainerMock;

class CmdUpdateAttributeTest : public ::testing::Test{
public:
	virtual ~CmdUpdateAttributeTest();
protected:
	virtual void SetUp();
	virtual void TearDown();
protected:
	std::shared_ptr<AttributeDataContainerMock> attributeDataContainer;
	std::shared_ptr<CmdUpdateAttribute> cmdUpdateAttribute;

	boost::property_tree::ptree newProperties;
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_COMAND_CMDUPDATEATTRIBUTETEST_H_ */
