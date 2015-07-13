/*
 * ExtAddressTest.h
 *
 *  Created on: 30/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_ZIGBEEDATA_EXTADDRESSTEST_H_
#define SRC_TEST_ZIGBEEDATA_EXTADDRESSTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../ZigbeeData/ExtAddress.h"


namespace zigbee {
namespace test {

class ExtAddressTest : public ::testing::Test{
public:
	ExtAddressTest();
	virtual ~ExtAddressTest();
protected:
	ExtAddress * extAddress;
protected:
	virtual void SetUp() ;
	virtual void TearDown() ;
};

}
} /* namespace zigbee */

#endif /* SRC_TEST_ZIGBEEDATA_EXTADDRESSTEST_H_ */
