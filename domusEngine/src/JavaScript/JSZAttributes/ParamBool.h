#include <v8.h>
#include <boost/any.hpp>
#include "../Exceptions/JSExceptionArgNoBool.h"
#include "../JSObjects.h"

namespace zigbee {

class ParamBool {
public:
	static bool fromV8(const v8::Local<v8::Value> & hValue) {
		if (!hValue->IsBoolean()){
			throw JSExceptionArgNoBool();
		}
		return hValue->BooleanValue();
	}

	static v8::Local<v8::Boolean> toV8(v8::Isolate * isolate, const boost::any & value) {
		return v8::Boolean::New(isolate, boost::any_cast<bool>(value));
	}
};

} /* namespace zigbee */
