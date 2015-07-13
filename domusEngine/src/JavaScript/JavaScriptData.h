/*
 * JavaScriptData.h
 *
 *  Created on: 22/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPTDATA_H_
#define SRC_JAVASCRIPTDATA_H_

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/date_time.hpp>

namespace zigbee {

class JavaScriptData {
public:
	JavaScriptData(boost::property_tree::ptree & properties);
public:
	std::string getCode() const {return code;}
	boost::posix_time::time_duration  getPeriod() const {return period;}
	std::string getName() const {return name;}
private:
	std::string name;
	std::string code;
	boost::posix_time::time_duration period;
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPTDATA_H_ */
