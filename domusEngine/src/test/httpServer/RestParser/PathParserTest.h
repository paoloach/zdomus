/*
 * PathParserTest.h
 *
 *  Created on: 19/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_HTTPSERVER_RESTPARSER_PATHPARSERTEST_H_
#define SRC_TEST_HTTPSERVER_RESTPARSER_PATHPARSERTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace zigbee {
namespace http {
namespace test {

class PathParserTest : public ::testing::Test{
public:
	PathParserTest();
	virtual ~PathParserTest();
protected:
	virtual void SetUp() ;
	virtual void TearDown() ;
};

}
}
} /* namespace zigbee */

#endif /* SRC_TEST_HTTPSERVER_RESTPARSER_PATHPARSERTEST_H_ */
