#include <v8.h>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <boost/any.hpp>
#include "../Exceptions/JSExceptionArgNoIEEEAddress.h"
#include "../JSObjects.h"

namespace zigbee {



class ParamIEEEAddress {
	union Value {
		uint64_t data;
		uint8_t raw[8];
	};

public:
	static uint64_t fromV8(const v8::Local<v8::Value> & hValue) {
		char octet[3] = { 0, 0, 0 };
		if (!hValue->IsString()) {
			throw JSExceptionArgNoIEEEAddress();
		}
		v8::String::Utf8Value utfValue(hValue);
		const char * arg = *utfValue;
		size_t len = std::strlen(arg);
		if (len != 23) {
			throw JSExceptionArgNoIEEEAddress(arg);
		}
		for (int i = 6; i >= 0; i--) {
			if (arg[i * 3 + 2] != ':' && arg[i * 3 + 2] != '-') {
				throw JSExceptionArgNoIEEEAddress(arg);
			}
		}

		Value result;
		for (int i = 0; i < 8; i++) {
			octet[0] = arg[3 * i];
			octet[1] = arg[3 * i + 1];
			if (!isxdigit(octet[0]) || !isxdigit(octet[1])) {
				throw JSExceptionArgNoIEEEAddress(arg);
			}
			result.raw[7-i] = std::stoi(octet, 0, 16);
		}
		return result.data;
	}

	static v8::Local<v8::String> toV8(v8::Isolate * isolate, const std::any & value) {
		std::stringstream stream;
		Value result;
		result.data = std::any_cast<uint64_t>(value);

		for(int i=7; i > 0;i--){
			stream << std::hex << std::setw(2) << std::setfill('0') << (int)result.raw[i] << "-";
		}
		stream << std::hex << std::setw(2) << std::setfill('0') << (int)result.raw[0];

		return v8::String::NewFromUtf8(isolate, stream.str().c_str());
	}
};

} /* namespace zigbee */
