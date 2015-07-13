/*
 * PlaceholderNotFound.h
 *
 *  Created on: 20/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTPARSER_EXCEPTIONS_PLACEHOLDERNOTFOUND_H_
#define SRC_HTTPSERVER_RESTPARSER_EXCEPTIONS_PLACEHOLDERNOTFOUND_H_

#include <exception>

namespace zigbee {
namespace http {

class PlaceholderNotFound : std::exception{
};

} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTPARSER_EXCEPTIONS_PLACEHOLDERNOTFOUND_H_ */
