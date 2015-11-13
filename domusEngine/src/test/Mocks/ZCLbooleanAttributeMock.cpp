/*
 * ZCLbooleanAttributeMock.cpp
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#include "ZCLbooleanAttributeMock.h"

namespace zigbee {
namespace test {

ZCL_boolean_AttributeMock::ZCL_boolean_AttributeMock() :
		ZCL_boolean_Attribute(nullptr,nullptr, 0,"",false){

}

ZCL_boolean_AttributeMock::~ZCL_boolean_AttributeMock() {
}

} /* namespace test */
} /* namespace zigbee */
