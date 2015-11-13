/*
 * AttributeDataContainerTest.h
 *
 *  Created on: 01/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_IO_ATTRIBUTEDATACONTAINERTEST_H_
#define SRC_TEST_IO_ATTRIBUTEDATACONTAINERTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../IO/AttributeDataContainer.h"

namespace zigbee {
namespace test{

class AttributeDataContainerTest : public ::testing::Test{
public:
	AttributeDataContainerTest();
	virtual ~AttributeDataContainerTest();
protected:
	AttributeDataContainer * container;
protected:
	virtual void SetUp() ;
	virtual void TearDown() ;
};

}
} /* namespace zigbee */

#endif /* SRC_TEST_IO_ATTRIBUTEDATACONTAINERTEST_H_ */
