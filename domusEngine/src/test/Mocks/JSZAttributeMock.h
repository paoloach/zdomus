/*
 * JSZAttributeMock.h
 *
 *  Created on: 05/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_JSZATTRIBUTEMOCK_H_
#define SRC_TEST_MOCKS_JSZATTRIBUTEMOCK_H_

#include <gtest/gtest.h>
#include "../../JavaScript/JSZAttribute.h"
#include "../../trompeloeil/src/trompeloeil/include/trompeloeil.hpp"

namespace zigbee {
namespace test {

class JSZAttributeMock : public JSZAttribute {
public:
	JSZAttributeMock();
	virtual ~JSZAttributeMock();
	MAKE_MOCK2(initJsObjectsTemplate, void (v8::Isolate * isolate ,v8::Handle<v8::Object> & global));
    MAKE_MOCK2(createInstance, v8::Local<v8::Object> (v8::Isolate* isolate, const ZCLAttribute * zclAttribute));
};


} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_JSZATTRIBUTEMOCK_H_ */
