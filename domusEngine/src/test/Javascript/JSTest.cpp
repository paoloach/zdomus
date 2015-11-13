/*
 * JSTest.cpp
 *
 *  Created on: 09/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSTest.h"

#include "../Mocks/ClusterMock.h"
#include "../Mocks/ZCLAttributeMock.h"
#include "../Mocks/ZigbeeDeviceMock.h"

namespace zigbee {
namespace test {

using std::make_shared;
using namespace v8;
using namespace testing;

constexpr NwkAddr JSTest::NWK_ADDRESS;
constexpr EndpointID JSTest::ENDPOINT_ID;
constexpr ClusterID JSTest::CLUSTER_ID;
constexpr uint32_t JSTest::PROFILE_ID;
constexpr uint32_t JSTest::DEVICE_ID;
constexpr uint32_t JSTest::DEVICE_VER;
constexpr uint32_t JSTest::ATTRIBUTE0_ID;
constexpr uint32_t JSTest::ATTRIBUTE1_ID;

const std::string JSTest::EXTENDED_ADDRESS = "00-01-02-03-04-05-06-07";
const std::vector<ClusterID> JSTest::IN_CLUSTERS { ClusterID { 1 }, ClusterID { 2 } };
const std::vector<ClusterID> JSTest::OUT_CLUSTERS { ClusterID { 3 }, ClusterID { 4 } };

JSTest::~JSTest() {
}

void JSTest::SetUp() {
	isolate = v8::Isolate::New();
	isolate->Enter();
	locker.reset(new Locker { isolate });

	extAddress = convertFromString(EXTENDED_ADDRESS);

	zigbeeDeviceMock = make_shared<ZigbeeDeviceMock>();
	zigbeeDevice = std::dynamic_pointer_cast<ZigbeeDevice>(zigbeeDeviceMock);

	defaultCluster = make_shared<ClusterMock>();
	defaultZclAttribute = make_shared<ZCLAttributeMock>(zigbeeDevice, defaultCluster.get(), -1, ZCLTypeDataType::ZCLTypeInvalid, "", true);
	cluster = make_shared<ClusterMock>();
	jsLog = std::make_shared<JSLog>(log);

	ON_CALL(*clusterTypeFactoryMock, getCluster(_,_,_,_)).WillByDefault(Return(defaultCluster));
	ON_CALL(*zDevices, getDevice(extAddress)).WillByDefault(ReturnRef(defaultZDevice));
	ON_CALL(*zDevices, exists(_)).WillByDefault(Return(false));
	ON_CALL(*cluster, getAttribute(ATTRIBUTE0_ID)).WillByDefault(Return(zclAttributeMock));
}

void JSTest::TearDown() {
	clusterTypeFactoryMock.reset();
	locker.reset();
	jsLog->resetPersistences();
	isolate->Exit();
	isolate->Dispose();
	defaultZclAttribute.reset();
	defaultCluster.reset();
}

v8::Local<v8::Value> JSTest::runScript(const std::string& script) {
	Local<String> source = String::NewFromUtf8(isolate, script.c_str());
	Local<Script> jsScript = Script::Compile(source);
	return jsScript->Run();
}

ExtAddress JSTest::convertFromString(const std::string& strExt) {
	ExtAddress extAddress { };
	std::stringstream stream { strExt };
	stream >> extAddress;
	return extAddress;
}

} /* namespace test */
} /* namespace zigbee */
