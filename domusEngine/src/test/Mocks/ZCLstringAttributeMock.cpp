/*
 * ZCLstringAttributeMock.cpp
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#include "ZCLstringAttributeMock.h"

namespace zigbee {
namespace test {

ZCL_string_AttributeMock::ZCL_string_AttributeMock():
		ZCL_string_Attribute(nullptr,nullptr, 0,"",false) {

}

ZCL_string_AttributeMock::~ZCL_string_AttributeMock() {
}

} /* namespace test */
} /* namespace zigbee */
