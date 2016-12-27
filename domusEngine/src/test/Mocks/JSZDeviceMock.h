/*
 * JSZDeviceMock.h
 *
 *  Created on: 31/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_JSZDEVICEMOCK_H_
#define SRC_TEST_MOCKS_JSZDEVICEMOCK_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../JavaScript/JSZDevice.h"
#include "shared_ptr_mock.h"

namespace zigbee {
namespace test {

class JSZDeviceMock :public JSZDevice, public sharedMockClass<JSZDevice, JSZDeviceMock>{
public:
	JSZDeviceMock();
	virtual ~JSZDeviceMock();

	MOCK_METHOD2(initJsObjectsTemplate, void (v8::Isolate * isolate ,v8::Handle<v8::Object> & global));
	MOCK_METHOD2(createInstance, v8::Local<v8::Object> (v8::Isolate* isolate, const ExtAddress & extAddress));

};


} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_JSZDEVICEMOCK_H_ */
