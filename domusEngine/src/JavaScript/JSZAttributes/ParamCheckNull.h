/*
 * ParamCheckNull.h
 *
 *  Created on: 14/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSZATTRIBUTES_PARAMCHECKNULL_H_
#define SRC_JAVASCRIPT_JSZATTRIBUTES_PARAMCHECKNULL_H_

#include <v8.h>

namespace zigbee {

class ParamCheckNull {
public:
	static void check(const v8::Local<v8::Value> & ){}
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSZATTRIBUTES_PARAMCHECKNULL_H_ */
