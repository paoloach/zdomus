/*
 * JSZDeviceMock.h
 *
 *  Created on: 31/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_JSZDEVICEMOCK_H_
#define SRC_TEST_MOCKS_JSZDEVICEMOCK_H_

#include <gtest/gtest.h>
#include "../../trompeloeil/src/trompeloeil/include/trompeloeil.hpp"
#include "../../JavaScript/JSZDevice.h"

namespace zigbee {
namespace test {

class JSZDeviceMock :public JSZDevice {
public:
	JSZDeviceMock();
	virtual ~JSZDeviceMock();

	MAKE_MOCK2(initJsObjectsTemplate, void (v8::Isolate * isolate ,v8::Handle<v8::Object> & global));
    MAKE_MOCK2(createInstance, v8::Local<v8::Object> (v8::Isolate* isolate, const ExtAddress & extAddress));

};


} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_JSZDEVICEMOCK_H_ */
