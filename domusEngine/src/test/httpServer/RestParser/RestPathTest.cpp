/*
 * RestPathTest.cpp
 *
 *  Created on: 19/mag/2015
 *      Author: Paolo Achdjian
 */

#include "RestPathTest.h"

#include "../../../httpServer/RestParser/PathReceived.h"
#include "../../../httpServer/RestParser/RestPath.h"

namespace zigbee {
namespace http {
namespace test {

using namespace testing;


RestPathTest::~RestPathTest() {
}

TEST_F( RestPathTest, pathWithPlaceHolderMatch) {

	PathReceived pathReceived {"/p1/p2/p3/p4"};
	RestPath restPath {"/p1/{pl1}/p3/{pl2}"};

	ASSERT_THAT(restPath, Eq(pathReceived));

}

TEST_F( RestPathTest, pathWithPlaceHolderNotMatchTooShort) {

	PathReceived pathReceived {"/p1/p2/p3"};
	RestPath restPath {"/p1/{pl1}/p3/{pl2}"};

	ASSERT_THAT(restPath, Not(Eq(pathReceived)));

}

TEST_F( RestPathTest, pathWithPlaceHolderNotMatch) {

	PathReceived pathReceived {"/p1/p2/p2/p4"};
	RestPath restPath {"/p1/{pl1}/p3/{pl2}"};

	ASSERT_THAT(restPath, Not(Eq(pathReceived)));

}

} /* namespace test */
} /* namespace http */
} /* namespace zigbee */