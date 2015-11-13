/*
 * Log.h
 *
 *  Created on: 18/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_UTILS_LOG_H_
#define SRC_UTILS_LOG_H_

#include <mutex>
#include <boost/date_time.hpp>
#include <deque>

namespace zigbee {

class Log {
public:
	enum Level {
		DEBUG = 0, INFO, WARNING, ERROR
	};

	class LogData {
	public:
		std::string msg;
		Log::Level level;
		boost::posix_time::ptime timestamp;
	};
public:
	Log();
	virtual ~Log();
public:
	void debug(const std::string & msg) {
		if (level <= DEBUG) {
			std::lock_guard<std::mutex> lock(mutexLog);
			logData.push_back( { msg, DEBUG, boost::posix_time::second_clock::local_time() });
		}
	}
	void info(const std::string & msg) {
		if (level <= INFO) {
			std::lock_guard<std::mutex> lock(mutexLog);
			logData.push_back( { msg, INFO, boost::posix_time::second_clock::local_time() });
		}
	}
	void warning(const std::string & msg) {
		if (level <= INFO) {
			std::lock_guard<std::mutex> lock(mutexLog);
			logData.push_back( { msg, WARNING, boost::posix_time::second_clock::local_time() });
		}
	}
	void error(const std::string & msg) {
		std::lock_guard<std::mutex> lock(mutexLog);
		logData.push_back( { msg, ERROR, boost::posix_time::second_clock::local_time() });
	}

	LogData get();

	bool empty(){
		std::lock_guard<std::mutex> lock(mutexLog);
		return logData.empty();
	}
private:
	Level level;
	std::deque<LogData> logData;
	std::mutex mutexLog;
};

} /* namespace zigbee */

#endif /* SRC_UTILS_LOG_H_ */
