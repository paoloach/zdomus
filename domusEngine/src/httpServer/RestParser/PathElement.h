/*
 * PathElement.h
 *
 *  Created on: 19/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTPARSER_PATHELEMENT_H_
#define SRC_HTTPSERVER_RESTPARSER_PATHELEMENT_H_

#include <string>

namespace zigbee {
namespace http {

class PathElement {
public:
	PathElement(const std::string & value) noexcept;
public:
	std::string getValue() const noexcept {return value;}
	bool isPlaceholder() const noexcept {return placeholder;}
private:
	std::string value;
	bool placeholder;
};

} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTPARSER_PATHELEMENT_H_ */
