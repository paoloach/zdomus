/*
 * ExtAddressTest.cpp
 *
 *  Created on: 30/nov/2014
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "ExtAddressTest.h"

namespace zigbee {
namespace test {

using namespace ::testing;

static constexpr std::array<uint8_t, Z_EXTADDR_LEN>  data {1,2,3,4,100,101,102,10};


ExtAddressTest::ExtAddressTest() {
	extAddress=nullptr;
}

ExtAddressTest::~ExtAddressTest() {
}

void ExtAddressTest::SetUp() {
	extAddress = new ExtAddress {};
}

void ExtAddressTest::TearDown() {
	delete extAddress;
}


TEST_F( ExtAddressTest, convertToString) {
	std::stringstream stream {};

	*extAddress = data;
	stream << (*extAddress);

	ASSERT_THAT(stream.str(), Eq("01-02-03-04-64-65-66-0a"));
}

TEST_F( ExtAddressTest, convertFromString) {
	std::stringstream stream {};

	stream << "01-02-03-04-64-65-66-0a";

	stream >> (*extAddress);

	ASSERT_THAT(*extAddress, Eq(ExtAddress(data)));
}


}
} /* namespace zigbee */
