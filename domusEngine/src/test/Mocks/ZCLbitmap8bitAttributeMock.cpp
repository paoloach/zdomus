/*
 * ZCLbitmap8bitAttributeMock.cpp
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#include "ZCLbitmap8bitAttributeMock.h"

namespace zigbee {
namespace test {

ZCL_bitmap8bit_AttributeMock::ZCL_bitmap8bit_AttributeMock():
		ZCL_bitmap8bit_Attribute(nullptr,nullptr, 0,"",false) {

}

ZCL_bitmap8bit_AttributeMock::~ZCL_bitmap8bit_AttributeMock() {
}

} /* namespace test */
} /* namespace zigbee */
