/*
 * JSZAttributeMock.h
 *
 *  Created on: 05/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_JSZATTRIBUTEMOCK_H_
#define SRC_TEST_MOCKS_JSZATTRIBUTEMOCK_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../JavaScript/JSZAttribute.h"
#include "shared_ptr_mock.h"

namespace zigbee {
namespace test {

class JSZAttributeMock : public JSZAttribute, public sharedMockClass<JSZAttribute, JSZAttributeMock> {
public:
	JSZAttributeMock();
	virtual ~JSZAttributeMock();
	MOCK_METHOD2(initJsObjectsTemplate, void (v8::Isolate * isolate ,v8::Handle<v8::Object> & global));
	MOCK_METHOD2(createInstance, v8::Local<v8::Object> (v8::Isolate* isolate, const std::shared_ptr<ZCLAttribute> & zclAttribute));
};

typedef shared_ptr_mock<JSZAttribute,JSZAttributeMock> JSZAttributeMock_P;

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_JSZATTRIBUTEMOCK_H_ */
