/*
 * ZCLint16AttributeMock.cpp
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#include "ZCLint16AttributeMock.h"

namespace zigbee {
namespace test {

ZCL_int16_AttributeMock::ZCL_int16_AttributeMock():
				ZCL_int16_Attribute(nullptr,nullptr, 0,"",false) {

}

ZCL_int16_AttributeMock::~ZCL_int16_AttributeMock() {
}

} /* namespace test */
} /* namespace zigbee */
