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

    template<int min = INT_MIN, int max = INT_MAX>
    class ParamInt32 {
    public:
        static int32_t fromV8(const v8::Local<v8::Value> &jsValue) {
            if (!jsValue->IsInt32()) {
                throw JSExceptionArgNoInteger(VALUE);
            }
            int32_t value =  jsValue->Int32Value();
            if (value < min || value > max){
                throw JSExceptionOutOfRange(value, min,max);
            }
            return value;
        }

        static v8::Local<v8::Integer> toV8(v8::Isolate *isolate, const std::any &value) {
            return v8::Integer::New(isolate, std::any_cast<int32_t>(value));
        }
    };

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSZATTRIBUTES_PARAMINT32_H_ */
