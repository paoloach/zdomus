/*
 * JSException.h
 *
 *  Created on: 06/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSEXCEPTION_H_
#define SRC_JAVASCRIPT_JSEXCEPTION_H_

#include <exception>
#include <string>

namespace zigbee {

class JSException :  public std::exception{
public:
	JSException(){}
	JSException(const std::string & message);
	virtual ~JSException();
	virtual const char* what() const _GLIBCXX_USE_NOEXCEPT;
protected:
	std::string message;
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSEXCEPTION_H_ */
