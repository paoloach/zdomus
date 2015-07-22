/*
 * PathReceived.h
 *
 *  Created on: 19/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTPARSER_PATHRECEIVED_
#define SRC_HTTPSERVER_RESTPARSER_PATHRECEIVED_

#include <string>
#include <vector>
#include <map>
#include <boost/filesystem/path.hpp>

namespace zigbee {
namespace http {

class PathReceived {
private:
	std::vector<std::string> elements;
	std::map<std::string, std::string> queryParams;
public:
	PathReceived(std::string && uri) noexcept;

	auto begin()const noexcept -> decltype(elements.begin())   {return elements.begin();}
	auto end() const noexcept -> decltype(elements.end()) {return elements.end();}

	auto getSize() const noexcept-> decltype(elements.size())  {return elements.size();}

	auto getQueryParams() const noexcept -> decltype(queryParams) {return queryParams;}
private:
	void createElements(std::string && uri);

};

}  // end http
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTPARSER_PATHRECEIVED_ */