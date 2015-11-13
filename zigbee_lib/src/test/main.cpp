/*
 * main.cpp
 *
 *  Created on: 26/nov/2014
 *      Author: Paolo Achdjian
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

int main( int argc, char *argv[]) {
	::testing::InitGoogleMock( &argc, argv );
	int result {RUN_ALL_TESTS( )};
	return result;
}



