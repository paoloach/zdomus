/*
 * MeteringCluster.cpp
 *
 *  Created on: 07/ago/2015
 *      Author: Paolo Achdjian
 */

#include "../attributeTypes/ZCLuint8Attribute.h"
#include "MeteringCluster.h"

namespace zigbee {

static std::vector<Cluster::AttributeDef> attributesDef{
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0, "Current Summation Delivered", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 1, "Current Summation Received", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 2, "Current Max Demand Deliverd", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 3, "Current Max Demand Received", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 4, "DFT Summation", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 5, "Daily Freeze Time", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt8, 6, "Power Factor", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUTCTime, 7, "Reading Snap Shot Time", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUTCTime, 8, "Current Max Demand Delivery Time", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUTCTime, 9, "Current Max Demand Received time", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x0A, "Default Update Period", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0B, "Fast Poll Update Period", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0C, "Current Block Period Consumptio Delivered", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x0D, "Daily Consumption Targe", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 0x0E, "Current Block", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 0x0F, "Profile Interval Period", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x10, "Interval Read Report Period", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x11, "Preset Reading Time", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x12, "Volume Per Report", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x13, "FlowR estriction", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x14, "Supply Status", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x15, "Current Inlet Energy Carrier Summation", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x16, "Current Outet Energy Carrier Summation", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x17, " Inlet Temperature", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x18, "Outlet Temperature", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x19, "Control Temperature", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt24, 0x1A, "Current Inlet Energy Carrier Demand", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt24, 0x1B, "Current Outlet Energy Carrier Demand", true)

};

MeteringCluster::MeteringCluster(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
        Cluster(zigbeeDevice, endpoint, networkAddress) {
    createAttributes(attributesDef);

}

ClusterID MeteringCluster::getId() {
    return Metering;
}

std::string MeteringCluster::getClusterName() {
    return "Metering";
}

} /* namespace zigbee */
