/*
 * ZCLUint16AttributeMock.cpp
 *
 *  Created on: 09/gen/2015
 *      Author: Paolo Achdjian
 */

#include "ZCLUint16AttributeMock.h"

namespace zigbee {
namespace test {

ZCLUint16AttributeMock::ZCLUint16AttributeMock() :
		ZCL_uint16_Attribute(nullptr,nullptr, 0,"",false){

}

ZCLUint16AttributeMock::~ZCLUint16AttributeMock() {
}

} /* namespace test */
} /* namespace zigbee */
