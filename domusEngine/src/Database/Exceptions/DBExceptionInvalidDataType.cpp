/*
 * DBExceptionInvalidDataType.cpp
 *
 *  Created on: 24/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "DBExceptionInvalidDataType.h"

namespace zigbee {

DBExceptionInvalidDataType::DBExceptionInvalidDataType(uint dataType) {
	std::stringstream stream;
	stream << "Postgres data type " << dataType << " is not recognized";
	message = stream.str();
}

DBExceptionInvalidDataType::~DBExceptionInvalidDataType() {
}

} /* namespace zigbee */
