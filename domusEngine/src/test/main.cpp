/*
 * main.cpp
 *
 *  Created on: 26/nov/2014
 *      Author: Paolo Achdjian
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <v8.h>
#include <v8-platform.h>
#include <libplatform/libplatform.h>
#include <memory>

static void initV8() {
	v8::V8::InitializeICU();
	v8::Platform * platform(v8::platform::CreateDefaultPlatform());
	v8::V8::InitializePlatform(platform);
	v8::V8::Initialize();
}

static void exitV8() {
	v8::V8::Dispose();
	v8::V8::ShutdownPlatform();
}

int main( int argc, char *argv[]) {
	initV8();
	::testing::InitGoogleMock( &argc, argv );
	int result {RUN_ALL_TESTS( )};
	exitV8();
	return result;
}



