/*
 * ParamCheckUString.h
 *
 *  Created on: 14/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSZATTRIBUTES_PARAMSTRING_H_
#define SRC_JAVASCRIPT_JSZATTRIBUTES_PARAMSTRING_H_

#include <v8.h>
#include <boost/any.hpp>
#include "../Exceptions/JSExceptionArgNoString.h"
#include "../JSObjects.h"

namespace zigbee {

class ParamString {
public:
	static std::string fromV8(const v8::Local<v8::Value> & value) {
		if (!value->IsString()) {
			throw JSExceptionArgNoString(VALUE);
		}
		v8::String::Utf8Value utfValue(value);
		return *utfValue;
	}

	static v8::Local<v8::String> toV8(v8::Isolate * isolate, const std::any & value) {
		return v8::String::NewFromUtf8(isolate, std::any_cast<std::string>(value).c_str());
	}
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSZATTRIBUTES_PARAMSTRING_H_ */
