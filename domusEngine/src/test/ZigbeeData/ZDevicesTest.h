/*
 * ZDevicesTest.h
 *
 *  Created on: 29/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_ZIGBEEDATA_ZDEVICESTEST_H_
#define SRC_TEST_ZIGBEEDATA_ZDEVICESTEST_H_

#include <iostream>
#include <memory>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../ZigbeeData/ZDevices.h"

namespace zigbee {

class ZDevicesTest: public ::testing::Test {
public:
	virtual ~ZDevicesTest();
protected:
	ZDevices * zDevices;
	std::string extAddr1;
	std::string extAddr2;
protected:
	virtual void SetUp() ;
	virtual void TearDown() ;
};



} /* namespace zigbee */

#endif /* SRC_TEST_ZIGBEEDATA_ZDEVICESTEST_H_ */
