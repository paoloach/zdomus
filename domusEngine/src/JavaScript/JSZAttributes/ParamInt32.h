/*
 * ParamInt32.h
 *
 *  Created on: 14/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSZATTRIBUTES_PARAMINT32_H_
#define SRC_JAVASCRIPT_JSZATTRIBUTES_PARAMINT32_H_

#include <v8.h>
#include <boost/any.hpp>
#include "../Exceptions/JSExceptionArgNoInteger.h"
#include "../JSObjects.h"

namespace zigbee {

class ParamInt32 {
public:
	static int32_t fromV8(const v8::Local<v8::Value> & value) {
		if (!value->IsInt32()) {
			throw JSExceptionArgNoInteger(VALUE);
		}
		return value->Int32Value();
	}

	static v8::Local<v8::Integer> toV8(v8::Isolate * isolate, const boost::any & value) {
		return v8::Integer::New(isolate, boost::any_cast<int32_t>(value));
	}
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSZATTRIBUTES_PARAMINT32_H_ */
