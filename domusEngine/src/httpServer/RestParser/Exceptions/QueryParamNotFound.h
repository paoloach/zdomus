/*
 * QueryParamNotFound.h
 *
 *  Created on: 05/giu/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTPARSER_EXCEPTIONS_QUERYPARAMNOTFOUND_H_
#define SRC_HTTPSERVER_RESTPARSER_EXCEPTIONS_QUERYPARAMNOTFOUND_H_

#include <exception>

namespace zigbee {
namespace http {

class QueryParamNotFound : std::exception{
};

} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTPARSER_EXCEPTIONS_QUERYPARAMNOTFOUND_H_ */
