/*
 * BasicCluster.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include "src/zcl/attributeTypes/implementation/ZCLuint8AttributeImpl.h"
#include "BasicCluster.h"

namespace zigbee {

static std::vector<ClusterImpl::AttributeDef> attributesDef {
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0, "ZCL Version",true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 1, "Application Version",true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 2, "Stack Version", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 3,  "Hardware version",true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeStringChar, 4, "Name",true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeStringChar, 5, "Model",true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeStringChar, 6, "Date Code",true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 7, "Power Source", true),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeStringChar, 0x10, "Location"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 0x11, "Physical Environment"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeBool, 0x12, "Device Enable"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x13, "Alarm Mask"),
		ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x14, "Disable Local Config")
};

BasicCluster::BasicCluster(ZigbeeDevice *  zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
		ClusterImpl(zigbeeDevice, endpoint, networkAddress) {
	createAttributes(attributesDef);

}

ClusterID BasicCluster::getId() const {
	return BasicClusterID;
}

std::string BasicCluster::getClusterName() const {
	return "basic";
}

} /* namespace zigbee */
