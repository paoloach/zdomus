/*
 * V8anyConverter.cpp
 *
 *  Created on: 22/gen/2015
 *      Author: Paolo Achdjian
 */

#include "V8anyConverter.h"
#include <boost/date_time.hpp>

namespace zigbee {

using namespace v8;
using namespace boost::gregorian;
using namespace boost::posix_time;
using std::string;

V8_any_Converter::~V8_any_Converter() {
}


boost::any V8_any_Converter::convertToAny(const Local<Value>& value) {
	if (value->IsString()) {
		String::Utf8Value utf8(value);
		return string(*utf8);
	} else if (value->IsBoolean()) {
		return value->BooleanValue();
	} else if (value->IsInt32()) {
		return value->Int32Value();
	} else if (value->IsUint32()) {
		return value->Uint32Value();
	} else if (value->IsDate()){
		Date * date = Date::Cast(*value);
		double dateValue = date->ValueOf();
		time_t seconds = dateValue / 1000;
		uint32_t mils = (dateValue - seconds*1000);
		milliseconds millisec {mils};
		ptime timestamp = from_time_t(seconds);
		timestamp += millisec;
		return timestamp;
	} else {
		String::Utf8Value utf8(value);
		return string(*utf8);
	}
}

Local<v8::Value> V8_any_Converter::convertToV8(Isolate * isolate, const boost::any& value) {
	if (value.type() == typeid(uint32_t)) {
		return Uint32::New(isolate, boost::any_cast<uint32_t>(value));
	} else if (value.type() == typeid(std::string)) {
		std::string strValue = boost::any_cast<std::string>(value);
		return String::NewFromUtf8(isolate, strValue.c_str());
	} else if (value.type() == typeid(int32_t)) {
		return Int32::New(isolate, boost::any_cast<int32_t>(value));
	} else if (value.type() == typeid(boost::posix_time::ptime)){
		ptime epoch(date(1970,Jan,1));
		ptime timestamp = boost::any_cast<ptime>(value);
		time_duration elapsed = timestamp-epoch;
		uint64_t millisecond = elapsed.total_milliseconds();
		timestamp.date();
		return Date::New(isolate, millisecond);
	}

	std::string strValue = boost::any_cast<std::string>(value);
	return String::NewFromUtf8(isolate, strValue.c_str());
}

} /* namespace zigbee */
