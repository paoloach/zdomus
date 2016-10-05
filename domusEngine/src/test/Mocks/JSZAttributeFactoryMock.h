/*
 * JSZAttributeFactory.h
 *
 *  Created on: 10/gen/2015
 *      Author: Paolo Achdjian
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../JavaScript/JSZAttributeFactory.h"

#ifndef SRC_TEST_MOCKS_JSZATTRIBUTEFACTORYMOCK_H_
#define SRC_TEST_MOCKS_JSZATTRIBUTEFACTORYMOCK_H_

namespace zigbee {
namespace test {

class JSZAttributeFactoryMock : public JSZAttributeFactory{
public:
	JSZAttributeFactoryMock();
	virtual ~JSZAttributeFactoryMock();

	MOCK_METHOD3(init, void (ZDevices * zDevices,const std::shared_ptr<ZigbeeDevice> & zigbeeDevice,const std::shared_ptr<ClusterTypeFactory> & clusterFactory));
	MOCK_METHOD2(createAttributeInstance, v8::Local<v8::Object> (v8::Isolate* isolate, std::shared_ptr<ZCLAttribute> attribute ));
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_JSZATTRIBUTEFACTORYMOCK_H_ */
