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

extern unsigned char natives_blob_bin[];
extern unsigned int natives_blob_bin_len;
extern unsigned char snapshot_blob_bin[];
extern unsigned int snapshot_blob_bin_len;

static void initV8(int argc, char* argv[]) {
	V8::InitializeICU();

	StartupData nativeBlob;
	nativeBlob.data = (char *)natives_blob_bin;
	nativeBlob.raw_size = natives_blob_bin_len;
	V8::SetNativesDataBlob(&nativeBlob);

	StartupData snapshotBlob;
	snapshotBlob.data = (char *)snapshot_blob_bin;
	snapshotBlob.raw_size = snapshot_blob_bin_len;
	V8::SetSnapshotDataBlob(&snapshotBlob);

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



