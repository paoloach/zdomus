/*
 * IODataBufferTest.cpp
 *
 *  Created on: 06/dic/2014
 *      Author: Paolo Achdjian
 */

#include "IODataBufferTest.h"

namespace zigbee {
namespace test {

using namespace testing;

static const std::string line1="line1";
static const std::string line2="line2";
static const std::string line1_n = line1+"\n";
static const std::string line2_n = line1+"\n"+line2+"\n";
static const std::string line2_nr = line1+"\n\r"+line2+"\n";

IODataBufferTest::IODataBufferTest() {
	ioDataBuffer=nullptr;
}

IODataBufferTest::~IODataBufferTest() {
}

void IODataBufferTest::SetUp() {
	ioDataBuffer = new IODataBuffer {};
}



void IODataBufferTest::TearDown() {
	delete ioDataBuffer;
}

TEST_F( IODataBufferTest, add1Line) {
	ioDataBuffer->put(line1_n.begin(), line1_n.end());
	ASSERT_THAT(ioDataBuffer->getLine(), Eq(line1));
}

TEST_F( IODataBufferTest, addTwoLines) {
	ioDataBuffer->put(line2_n.begin(), line2_n.end());
	ASSERT_THAT(ioDataBuffer->getLine(), Eq(line1));
	ASSERT_THAT(ioDataBuffer->getLine(), Eq(line2));
}

TEST_F( IODataBufferTest, addTwoWirh_rLines) {
	ioDataBuffer->put(line2_nr.begin(), line2_nr.end());
	ASSERT_THAT(ioDataBuffer->getLine(), Eq(line1));
	ASSERT_THAT(ioDataBuffer->getLine(), Eq(line2));
}

TEST_F( IODataBufferTest, add1Line_using_2_pieces) {
	size_t half = line1_n.size()/2;

	ioDataBuffer->put(line1_n.begin(), line1_n.begin()+half);
	ASSERT_THAT(ioDataBuffer->getLine().empty(),Eq(true));
	ioDataBuffer->put(line1_n.begin()+half, line1_n.end());
	ASSERT_THAT(ioDataBuffer->getLine(), Eq(line1));
}

} /* namespace test */
} /* namespace zigbee */
