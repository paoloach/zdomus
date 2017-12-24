/*
 * ParamUInt32.h
 *
 *  Created on: 14/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSZATTRIBUTES_PARAMUINT32_H_
#define SRC_JAVASCRIPT_JSZATTRIBUTES_PARAMUINT32_H_

#include <v8.h>
#include <boost/any.hpp>
#include "../Exceptions/JSExceptionArgNoUInteger.h"
#include "../Exceptions/JSExceptionOutOfRange.h"
#include "../JSObjects.h"

namespace zigbee {

template <unsigned int min=0, unsigned int max = INT_MAX>
class ParamUInt32 {
public:
	static uint32_t fromV8(const v8::Local<v8::Value> & hValue) {
		if (!hValue->IsUint32()) {
			throw JSExceptionArgNoUInteger(VALUE);
		}
		uint32_t value =  hValue->Uint32Value();
		if (value < min || value > max){
			throw JSExceptionOutOfRange(value, min,max);
		}
		return value;
	}

	static v8::Local<v8::Integer> toV8(v8::Isolate * isolate, const std::any & value) {
		auto val = std::any_cast<uint32_t>(value);
		return v8::Integer::NewFromUnsigned(isolate, val);
	}
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSZATTRIBUTES_PARAMCUINT32_H_ */
