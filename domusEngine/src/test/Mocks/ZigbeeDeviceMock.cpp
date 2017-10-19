/*
 * ZigbeeDeviceMock.cpp
 *
 *  Created on: 12/dic/2014
 *      Author: Paolo Achdjian
 */

#include "ZigbeeDeviceMock.h"

namespace zigbee {
namespace test {

using namespace std::chrono_literals;

ZigbeeDeviceMock::ZigbeeDeviceMock():ZigbeeDevice(std::chrono::seconds(1)) {
}

ZigbeeDeviceMock::~ZigbeeDeviceMock() {

}
}
} /* namespace zigbee */
