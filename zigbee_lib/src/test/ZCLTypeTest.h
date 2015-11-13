/*
 * ZCLTypeTest.h
 *
 *  Created on: 07/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_ZCLTYPETEST_H_
#define SRC_TEST_ZCLTYPETEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace zigbee {

class ZCLTypeTest: public testing::Test {
public:
	ZCLTypeTest();
	virtual ~ZCLTypeTest();
protected:
	virtual void SetUp() override ;
	virtual void TearDown() override ;
};

} /* namespace zigbee */

#endif /* SRC_TEST_ZCLTYPETEST_H_ */
