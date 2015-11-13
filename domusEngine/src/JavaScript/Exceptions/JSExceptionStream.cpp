/*
 * JSExceptionStream.cpp
 *
 *  Created on: 05/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSExceptionStream.h"

#include <v8.h>

namespace zigbee {

JSExceptionStream::JSExceptionStream(v8::Isolate * isolate):isolate(isolate) {

}

JSExceptionStream::~JSExceptionStream() {
}

void JSExceptionStream::throwException() {
	v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, str().c_str());
	isolate->ThrowException(errorMsg);
}

} /* namespace zigbee */
