/*
 * PlaceHoldersTest.h
 *
 *  Created on: 20/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_HTTPSERVER_RESTPARSER_PLACEHOLDERSTEST_H_
#define SRC_TEST_HTTPSERVER_RESTPARSER_PLACEHOLDERSTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace zigbee {
namespace http {
namespace test {

class PlaceHoldersTest : public ::testing::Test{
public:
	PlaceHoldersTest();
	virtual ~PlaceHoldersTest();
};

} /* namespace test */
} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_TEST_HTTPSERVER_RESTPARSER_PLACEHOLDERSTEST_H_ */
