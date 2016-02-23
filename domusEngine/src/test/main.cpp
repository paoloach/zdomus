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

using namespace v8;

static void initV8(int argc, char* argv[]) {
	V8::InitializeICU();
	if (argc==0) {
        V8::InitializeExternalStartupData(argv[0]);
    } else {
        V8::InitializeExternalStartupData(argv[1]);
    }
    Platform* platform = platform::CreateDefaultPlatform();
    V8::InitializePlatform(platform);
    V8::Initialize();
}

static void exitV8() {
	V8::Dispose();
	V8::ShutdownPlatform();
}

int main( int argc, char *argv[]) {
	initV8(argc, argv);
	::testing::InitGoogleMock( &argc, argv );
	int result {RUN_ALL_TESTS( )};
	exitV8();
	return result;
}



