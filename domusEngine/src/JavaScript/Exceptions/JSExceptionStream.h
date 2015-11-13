/*
 * JSExceptionStream.h
 *
 *  Created on: 05/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSEXCEPTIONSTREAM_H_
#define SRC_JAVASCRIPT_JSEXCEPTIONSTREAM_H_

#include <sstream>

namespace v8 {
	class Isolate;
}

namespace zigbee {

class JSExceptionStream : public std::stringstream {
public:
	JSExceptionStream(v8::Isolate * isolate);
	virtual ~JSExceptionStream();
public:
	void throwException();
private:
	v8::Isolate * isolate;
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSEXCEPTIONSTREAM_H_ */
