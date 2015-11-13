/*
 * AttributeNotFoundException.h
 *
 *  Created on: 15/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZCL_EXCEPTIONS_ATTRIBUTENOTFOUNDEXCEPTION_H_
#define SRC_ZCL_EXCEPTIONS_ATTRIBUTENOTFOUNDEXCEPTION_H_

namespace zigbee {

class AttributeNotFoundException {
public:
	AttributeNotFoundException() noexcept {};
	virtual ~AttributeNotFoundException() noexcept{};
};

} /* namespace zigbee */

#endif /* SRC_ZCL_EXCEPTIONS_ATTRIBUTENOTFOUNDEXCEPTION_H_ */
