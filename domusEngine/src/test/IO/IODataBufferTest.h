/*
 * IODataBufferTest.h
 *
 *  Created on: 06/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_IO_IODATABUFFERTEST_H_
#define SRC_TEST_IO_IODATABUFFERTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../IO/IODataBuffer.h"

namespace zigbee {
namespace test {

class IODataBufferTest : public ::testing::Test{
public:
	IODataBufferTest();
	virtual ~IODataBufferTest();
protected:
	IODataBuffer * ioDataBuffer;
protected:
	virtual void SetUp() ;
	virtual void TearDown() ;
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_IO_IODATABUFFERTEST_H_ */
