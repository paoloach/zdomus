/*
 * ComandFactoryTest.h
 *
 *  Created on: 16/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_COMAND_COMANDFACTORYTEST_H_
#define SRC_TEST_COMAND_COMANDFACTORYTEST_H_

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../Comand/ComandFactory.h"
#include "../Mocks/ZDevicesMock.h"
#include "../Mocks/ZigbeeDeviceMock.h"
#include "../Mocks/AttributeDataContainerMock.h"

namespace zigbee {
namespace test {

class ComandFactoryTest: public ::testing::Test {
public:
	virtual ~ComandFactoryTest();
protected:
	virtual void SetUp();
	virtual void TearDown();
protected:
	ZDevicesMock zDevices;
	ZigbeeDeviceMock zigbeeDevice;
	AttributeDataContainerMock attributeData;
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_COMAND_COMANDFACTORYTEST_H_ */
