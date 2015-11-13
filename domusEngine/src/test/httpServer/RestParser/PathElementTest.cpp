/*
 * PathElementTest.cpp
 *
 *  Created on: 19/mag/2015
 *      Author: Paolo Achdjian
 */

#include "PathElementTest.h"
#include "../../../httpServer/RestParser/PathElement.h"

namespace zigbee {
namespace http {
namespace test {


using namespace testing;

PathElementTest::PathElementTest() {
}

PathElementTest::~PathElementTest() {
}


TEST_F( PathElementTest, pathString) {
	std::string path="path";

	PathElement pathElement(path);

	ASSERT_THAT(pathElement.isPlaceholder(), Eq(false));
	ASSERT_THAT(pathElement.getValue(), Eq(path));
}

TEST_F( PathElementTest, isPlaceholder) {
	std::string placeHolder="{path}";

	PathElement pathElement(placeHolder);

	ASSERT_THAT(pathElement.isPlaceholder(), Eq(true));
	ASSERT_THAT(pathElement.getValue(), Eq("path"));
}

}
} /* namespace http */
} /* namespace zigbee */
