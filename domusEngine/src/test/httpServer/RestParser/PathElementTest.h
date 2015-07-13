/*
 * PathElementTest.h
 *
 *  Created on: 19/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_HTTPSERVER_RESTPARSER_PATHELEMENTTEST_H_
#define SRC_TEST_HTTPSERVER_RESTPARSER_PATHELEMENTTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace zigbee {
namespace http {
namespace test {

class PathElementTest : public ::testing::Test{
public:
	PathElementTest();
	virtual ~PathElementTest();
protected:
};

}
} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_TEST_HTTPSERVER_RESTPARSER_PATHELEMENTTEST_H_ */
