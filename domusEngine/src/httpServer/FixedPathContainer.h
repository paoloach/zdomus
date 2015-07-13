/*
 * FixedPathContainer.h
 *
 *  Created on: 09/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_FIXEDPATHCONTAINER_H_
#define SRC_HTTPSERVER_FIXEDPATHCONTAINER_H_

#include <boost/filesystem/path.hpp>
#include <map>
#include <mutex>
#include "RestValue.h"

namespace zigbee {
namespace http {

class FixedPathContainer {
public:
	void addRestValue(const RestValue & restValue);
	std::string getValue(const boost::filesystem::path & path);
private:
	std::map<boost::filesystem::path, std::string> mapRestValue;
	std::mutex mutexRestValue;
};

} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_FIXEDPATHCONTAINER_H_ */
