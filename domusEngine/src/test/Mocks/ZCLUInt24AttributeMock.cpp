/*
 * ZCLUInt24AttributeMock.cpp
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#include "ZCLUInt24AttributeMock.h"

namespace zigbee {
namespace test {

ZCLUInt24AttributeMock::ZCLUInt24AttributeMock():
		ZCL_uint24_Attribute(nullptr,nullptr, 0,"",false) {

}

ZCLUInt24AttributeMock::~ZCLUInt24AttributeMock() {
}

} /* namespace test */
} /* namespace zigbee */
