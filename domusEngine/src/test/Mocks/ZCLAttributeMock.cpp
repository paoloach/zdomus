/*
 * ZCLAttributeMock.cpp
 *
 *  Created on: 05/gen/2015
 *      Author: Paolo Achdjian
 */

#include "ZCLAttributeMock.h"

namespace zigbee {
namespace test {

ZCLAttributeMock::ZCLAttributeMock( ZigbeeDevice * zigbeeDevice, Cluster * parent,int identifier, ZCLTypeDataType zclType, const std::string & name, bool readOnly):
		ZCLAttribute(zigbeeDevice, parent, identifier, zclType, name, readOnly){

}

ZCLAttributeMock::~ZCLAttributeMock() {
}

} /* namespace test */
} /* namespace zigbee */
