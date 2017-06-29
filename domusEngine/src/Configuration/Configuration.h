/*
 * Configuration.h
 *
 *  Created on: 22/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_CONFIGURATION_H_
#define SRC_CONFIGURATION_H_

#include <istream>
#include <boost/property_tree/ptree.hpp>
#include <array>
#include <map>

#include "../JavaScript/JavaScriptData.h"

namespace zigbee {

class Configuration {
public:
	Configuration(std::istream & config);
public:
	const std::multimap< std::string,JavaScriptData> & getJavascriptData() const{
		return jsDatas;
	}

    std::chrono::seconds getRestTimeout() const  {return timeout;}
private:
	boost::property_tree::ptree configuration;
	std::multimap< std::string, JavaScriptData > jsDatas;
    std::chrono::seconds timeout;
};

} /* namespace zigbee */

#endif /* SRC_CONFIGURATION_H_ */
