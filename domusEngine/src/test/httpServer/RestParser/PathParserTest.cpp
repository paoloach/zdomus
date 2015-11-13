/*
 * PathParserTest.cpp
 *
 *  Created on: 19/mag/2015
 *      Author: Paolo Achdjian
 */

#include "PathParserTest.h"

#include "../../../httpServer/RestParser/PathReceived.h"

namespace zigbee {
namespace http {
namespace test {

using namespace testing;

PathParserTest::PathParserTest() {

}

PathParserTest::~PathParserTest() {
}

void PathParserTest::SetUp() {
}

void PathParserTest::TearDown() {
}

TEST_F( PathParserTest, parsePath) {
	PathReceived pathParser("/p1/p2/p3");

	ASSERT_THAT(pathParser.getSize(), Eq(3u));
	auto element =  pathParser.begin();
	ASSERT_THAT(*element++, Eq("p1"));
	ASSERT_THAT(*element++, Eq("p2"));
	ASSERT_THAT(*element++, Eq("p3"));
}

TEST_F( PathParserTest, parsePathWithQueryParams) {
	PathReceived pathParser("/p1/p2/p3?p4=5&p6=7");

	ASSERT_THAT(pathParser.getSize(), Eq(3u));
	auto element =  pathParser.begin();
	ASSERT_THAT(*element++, Eq("p1"));
	ASSERT_THAT(*element++, Eq("p2"));
	ASSERT_THAT(*element++, Eq("p3"));

	auto queryParams = pathParser.getQueryParams();
	ASSERT_THAT(queryParams.size(), 2);
	ASSERT_THAT(queryParams["p4"], Eq("5"));
	ASSERT_THAT(queryParams["p6"], Eq("7"));
}

TEST_F( PathParserTest, parsePathWithQueryParamsInvalid) {
	PathReceived pathParser("/p1/p2/p3?p4=5&p6&p8=9");

	ASSERT_THAT(pathParser.getSize(), Eq(3u));
	auto element =  pathParser.begin();
	ASSERT_THAT(*element++, Eq("p1"));
	ASSERT_THAT(*element++, Eq("p2"));
	ASSERT_THAT(*element++, Eq("p3"));

	auto queryParams = pathParser.getQueryParams();
	ASSERT_THAT(queryParams.size(), 3);
	ASSERT_THAT(queryParams["p4"], Eq("5"));
	ASSERT_THAT(queryParams["p6"], Eq(""));
	ASSERT_THAT(queryParams["p8"], Eq("9"));
}


}
}
} /* namespace zigbee */
