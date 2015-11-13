/*
 * ZCLIEEEAddressAttributeMock.cpp
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#include "ZCLIEEEAddressAttributeMock.h"

namespace zigbee {
namespace test {

ZCLIEEEAddressAttributeMock::ZCLIEEEAddressAttributeMock():
		ZCLIEEEAddressAttribute(nullptr,nullptr, 0,"",false) {

}

ZCLIEEEAddressAttributeMock::~ZCLIEEEAddressAttributeMock() {
}

} /* namespace test */
} /* namespace zigbee */
