/*
 * V8anyConverter.h
 *
 *  Created on: 22/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_V8ANYCONVERTER_H_
#define SRC_JAVASCRIPT_V8ANYCONVERTER_H_

#include <v8.h>
#include <string>
#include <any>

namespace zigbee {

class V8_any_Converter {
public:
	virtual ~V8_any_Converter();
public:
	static std::any convertToAny(const v8::Local<v8::Value>& value);
	static v8::Local<v8::Value> convertToV8(v8::Isolate * isolate, const std::any& value);
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_V8ANYCONVERTER_H_ */
