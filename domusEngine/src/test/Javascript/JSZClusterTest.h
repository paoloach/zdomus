/*
 * JSZClusterTest.h
 *
 *  Created on: 04/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_JSZCLUSTERTEST_H_
#define SRC_TEST_JAVASCRIPT_JSZCLUSTERTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../Mocks/JSZDeviceMock.h"
#include "../Mocks/JSZAttributeMock.h"
#include "../Mocks/ZDevicesMock.h"
#include "../Mocks/ZigbeeDeviceMock.h"
#include "../Mocks/ClusterTypeFactoryMock.h"
#include "../Mocks/ClusterMock.h"
#include "../Mocks/ZCLAttributeMock.h"
#include "../Mocks/JSZAttributeFactoryMock.h"
#include "../../JavaScript/JSZCluster.h"
#include "../../JavaScript/V8Allocator.h"

namespace zigbee {
namespace test {


class JSZClusterTest : public testing::Test{
public:
	~JSZClusterTest() override =default;
protected:
	virtual void SetUp() override ;
	virtual void TearDown() override ;
	v8::Local<v8::Value> runScript(const std::string& script);
	static ExtAddress convertFromString(const std::string & strExt);
protected:
	V8Allocator v8Allocator;
	v8::Isolate::CreateParams createParams;
	std::unique_ptr<v8::Locker> locker;
	std::string	creatingZDeviceScript;
	v8::Isolate * isolate;
	std::unique_ptr<ZDevicesMock>  zDevices;
	ClusterTypeFactoryMock_P clusterTypeFactoryMock;
	std::shared_ptr<ZigbeeDeviceMock> zigbeeDeviceMock;
	std::shared_ptr<ZigbeeDevice> zigbeeDevice;
	std::unique_ptr<JSZCluster> jsZCluster;
	ExtAddress extAddress;
	std::shared_ptr<ClusterMock> defaultCluster;
	std::shared_ptr<ClusterMock> cluster;
	std::shared_ptr<ZCLAttributeMock> zclAttributeMock;
	std::shared_ptr<ZCLAttribute> zclAttribute;
	std::shared_ptr<JSZAttributeFactoryMock> jsZAttributeFactory;
	std::shared_ptr<ZCLAttributeMock> defaultZclAttribute;
	ZDevice defaultZDevice;
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSZCLUSTERTEST_H_ */
