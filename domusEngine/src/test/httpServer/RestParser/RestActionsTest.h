/*
 * RestActionsTest.h
 *
 *  Created on: 20/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_HTTPSERVER_RESTPARSER_RESTACTIONSTEST_H_
#define SRC_TEST_HTTPSERVER_RESTPARSER_RESTACTIONSTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace zigbee {
namespace http {
namespace test {

class RestActionsTest : public ::testing::Test{
public:
	RestActionsTest();
	virtual ~RestActionsTest();
};

} /* namespace test */
} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_TEST_HTTPSERVER_RESTPARSER_RESTACTIONSTEST_H_ */
