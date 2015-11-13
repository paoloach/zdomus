/*
 * CmdGetUpdateTest.h
 *
 *  Created on: 04/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_COMAND_CMDGETUPDATETEST_H_
#define SRC_TEST_COMAND_CMDGETUPDATETEST_H_

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../ZigbeeData/ZDevices.h"
#include "../../Comand/CmdGetUpdate.h"
#include "../Mocks/ZDevicesMock.h"

namespace zigbee {
namespace test {

class CmdGetUpdateTest: public ::testing::Test {
public:
	CmdGetUpdateTest();
	virtual ~CmdGetUpdateTest();
protected:
	virtual void SetUp();
	virtual void TearDown();
protected:
	ZDevicesMock  * zDevices;
	CmdGetUpdate * cmdGetUpdate;
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_COMAND_CMDGETUPDATETEST_H_ */
