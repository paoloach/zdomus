/*
 * RestPathTest.h
 *
 *  Created on: 19/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_HTTPSERVER_RESTPARSER_RESTPATHTEST_H_
#define SRC_TEST_HTTPSERVER_RESTPARSER_RESTPATHTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace zigbee {
namespace http {
namespace test {

class RestPathTest : public ::testing::Test{
public:
	virtual ~RestPathTest();
};

} /* namespace test */
} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_TEST_HTTPSERVER_RESTPARSER_RESTPATHTEST_H_ */
