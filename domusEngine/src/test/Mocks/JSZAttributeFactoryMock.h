/*
 * JSZAttributeFactory.h
 *
 *  Created on: 10/gen/2015
 *      Author: Paolo Achdjian
 */

#include <gtest/gtest.h>
#include "../../trompeloeil/src/trompeloeil/include/trompeloeil.hpp"
#include "../../JavaScript/JSZAttributeFactory.h"

#ifndef SRC_TEST_MOCKS_JSZATTRIBUTEFACTORYMOCK_H_
#define SRC_TEST_MOCKS_JSZATTRIBUTEFACTORYMOCK_H_

namespace zigbee {
namespace test {

class JSZAttributeFactoryMock : public JSZAttributeFactory{
public:
	JSZAttributeFactoryMock();
	virtual ~JSZAttributeFactoryMock();

	MAKE_MOCK3(init, void (ZDevices * zDevices, ZigbeeDevice * zigbeeDevice,const std::shared_ptr<ClusterTypeFactory> & clusterFactory));
    MAKE_MOCK2(createAttributeInstance, v8::Local<v8::Object> (v8::Isolate* isolate, ZCLAttribute * attribute ));
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_JSZATTRIBUTEFACTORYMOCK_H_ */
