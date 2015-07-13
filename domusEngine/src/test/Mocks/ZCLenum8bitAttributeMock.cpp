/*
 * ZCLenum8bitAttributeMock.cpp
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#include "ZCLenum8bitAttributeMock.h"

namespace zigbee {
namespace test {

ZCL_enum8bit_AttributeMock::ZCL_enum8bit_AttributeMock() :
		ZCL_enum8bit_Attribute(nullptr,nullptr, 0,"",false){

}

ZCL_enum8bit_AttributeMock::~ZCL_enum8bit_AttributeMock() {
}

} /* namespace test */
} /* namespace zigbee */
