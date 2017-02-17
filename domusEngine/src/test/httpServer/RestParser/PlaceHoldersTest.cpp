/*
 * PlaceHoldersTest.cpp
 *
 *  Created on: 20/mag/2015
 *      Author: Paolo Achdjian
 */

#include "PlaceHoldersTest.h"

#include "../../../httpServer/RestParser/PathReceived.h"
#include "../../../httpServer/RestParser/RestPath.h"
#include "../../../httpServer/RestParser/PlaceHolders.h"
#include "../../../httpServer/RestParser/Exceptions/PlaceholderNotFound.h"

namespace zigbee {
namespace http {
namespace test {

using namespace testing;

PlaceHoldersTest::PlaceHoldersTest() {
}

PlaceHoldersTest::~PlaceHoldersTest() {
}

TEST_F( PlaceHoldersTest, getPlaceholdersValue) {

	PathReceived pathReceived { "/p1/p2/p3/p4" };
	RestPath restPath { "/p1/{pl1}/p3/{pl2}" };

	PlaceHolders placeHolders(restPath, pathReceived);

	ASSERT_THAT(placeHolders.get<std::string>("pl1"), Eq("p2"));
	ASSERT_THAT(placeHolders.get<std::string>("pl2"), Eq("p4"));
}

TEST_F( PlaceHoldersTest, placeholdersNotFound) {

	PathReceived pathReceived { "/p1/p2/p3/p4" };
	RestPath restPath { "/p1/{pl1}/p3/{pl2}" };

	PlaceHolders placeHolders(restPath, pathReceived);

	ASSERT_THROW(placeHolders.get<std::string>("pl3"), PlaceholderNotFound );
}

} /* namespace test */
} /* namespace http */
} /* namespace zigbee */
