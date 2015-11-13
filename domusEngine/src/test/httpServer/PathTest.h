/*
 * PathTest.h
 *
 *  Created on: 08/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_HTTPSERVER_PATHTEST_H_
#define SRC_TEST_HTTPSERVER_PATHTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace zigbee {
namespace test {
namespace http {

class PathTest : public ::testing::Test {
public:
	virtual ~PathTest();
protected:
	virtual void SetUp() ;
	virtual void TearDown() ;
};

} /* namespace http */
} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_HTTPSERVER_PATHTEST_H_ */
