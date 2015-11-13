/*
 * BasicCluster.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include "../attributeTypes/ZCLuint8Attribute.h"
#include "BasicCluster.h"

namespace zigbee {

static std::vector<Cluster::AttributeDef> attributesDef {
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0, "ZCL Version",true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 1, "Application Version",true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 2, "Stack Version", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 3,  "Hardware version",true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeStringChar, 4, "Name",true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeStringChar, 5, "Model",true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeStringChar, 6, "Date Code",true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 7, "Power Source", true),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeStringChar, 0x10, "Location"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 0x11, "Physical Environment"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeBool, 0x12, "Device Enable"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x13, "Alarm Mask"),
		Cluster::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x14, "Disable Local Config")
};

BasicCluster::BasicCluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
		Cluster(zigbeeDevice, endpoint, networkAddress) {
	createAttributes(attributesDef);

}

ClusterID BasicCluster::getId() {
	return BasicClusterID;
}

std::string BasicCluster::getClusterName() {
	return "basic";
}

} /* namespace zigbee */
