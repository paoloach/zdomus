/*
 * Log.cpp
 *
 *  Created on: 18/gen/2015
 *      Author: Paolo Achdjian
 */

#include "Log.h"

namespace zigbee {

Log::Log() {
	level=DEBUG;
}

Log::~Log() {
}

Log::LogData Log::get() {
	std::lock_guard<std::mutex> lock(mutexLog);
	if (!logData.empty()){
		Log::LogData result = logData.front();
		logData.pop_front();
		return result;
	}
	return Log::LogData {};
}

} /* namespace zigbee */
