/*
 * JSExceptionInvalidAttributeType.cpp
 *
 *  Created on: 13/gen/2015
 *      Author: Paolo Achdjian
 */


#include "JSExceptionInvalidAttributeType.h"

namespace zigbee {


JSExceptionInvalidAttributeType::JSExceptionInvalidAttributeType(const std::string& name, ZCLTypeDataType wrongType, ZCLTypeDataType rightType) {
	std::stringstream stream;
	stream << "Unable to create an instance of " << name << " because the is of type " << rightType << " but tried to construct as " << wrongType;
	message = stream.str();
}

JSExceptionInvalidAttributeType::~JSExceptionInvalidAttributeType() {
}

} /* namespace zigbee */
