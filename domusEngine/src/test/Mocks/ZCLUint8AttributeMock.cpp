/*
 * ZCLUint8AttributeMock.cpp
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#include "ZCLUint8AttributeMock.h"

namespace zigbee {
namespace test {

ZCLUint8AttributeMock::ZCLUint8AttributeMock() :
				ZCL_uint8_Attribute(nullptr,nullptr, 0,"",false){

}

ZCLUint8AttributeMock::~ZCLUint8AttributeMock() {
}

} /* namespace test */
} /* namespace zigbee */
