/*
 * DeviceBrowserHandlerTest.h
 *
 *  Created on: 14/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_HTTPSERVER_DEVICEBROWSERHANDLERTEST_H_
#define SRC_TEST_HTTPSERVER_DEVICEBROWSERHANDLERTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "../Mocks/ZDevicesMock.h"
#include "../Mocks/ClusterTypeFactoryMock.h"
#include "../Mocks/ZigbeeDeviceMock.h"
#include "../Mocks/ClusterMock.h"
#include "../Mocks/ZCLAttributeMock.h"
#include "../Mocks/SingletonObjectsMock.h"
#include "../Mocks/http/HTTPServerResponseMock.h"
#include "../Mocks/http/HTTPServerRequestMock.h"
#include "ZDeviceFixture.h"

namespace zigbee {
namespace http {
namespace test {

class DeviceBrowserHandlerTest  : public ::testing::Test {
public:
	virtual ~DeviceBrowserHandlerTest();
	DeviceBrowserHandlerTest();
protected:
	virtual void SetUp();
	virtual void TearDown();
protected:
	std::shared_ptr<zigbee::test::ClusterMock> clusterMock;
	std::shared_ptr<zigbee::test::ZCLAttributeMock> attributeMock;
	zigbee::test::ZDevicesMock_P zDevicesMock;
	std::shared_ptr<zigbee::test::ClusterTypeFactoryMock> clusterTypeFactoryMock;
	SingletonObjectsMock singletonObjects;
	std::shared_ptr<zigbee::test::ZigbeeDeviceMock> zigbeeDeviceMock;
	std::shared_ptr<zigbee::ZigbeeDevice> zigbeeDevice;
	std::stringstream outStream;
	HTTPServerResponseMock response;
	HTTPServerRequestMock request;
	static ClusterID clusterInId ;
	static ClusterID clusterOutId ;
	bool attributeAvailable;
	static constexpr int attributeId = 43;
	static constexpr auto attributeName = "name";
	static constexpr auto attributeReadOnly = false;
	static constexpr auto attributeDataType = ZCLTypeDataType::ZCLType24bit;
	static constexpr auto attributeUnsupported = true;
	ZCLAttribute::Status attributeStatus;

	void setExpectedCallForAttribute();
	template <typename T>
	std::string getRestForAttribute(T && t){
		std::stringstream restPath;
		restPath << "/devices/" << ZDeviceFixture::zDevice1.getNwkAddr() << "/endpoint/" << ZDeviceFixture::endpoint2_1.getEndpoint() << "/cluster/in/" << clusterInId << "/attribute/" << t;
		return restPath.str();
	}
	std::string getRestForCmd(int cmd);
};

} /* namespace test */
} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_TEST_HTTPSERVER_DEVICEBROWSERHANDLERTEST_H_ */
