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
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeSInt24, 0x1B, "Current Outlet Energy Carrier Demand", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0100, "Current Tier1 Summation Delivered", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0101, "Current Tier1 Summation Received", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0102, "Current Tier2 Summation Delivered", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0103, "Current Tier2 Summation Received", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0104, "Current Tier3 Summation Delivered", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0105, "Current Tier3 Summation Received", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0106, "Current Tier4 Summation Delivered", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0107, "Current Tier4 Summation Received", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0108, "Current Tier5 Summation Delivered", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0109, "Current Tier5 Summation Received", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x010a, "Current Tier6 Summation Delivered", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x010b, "Current Tier6 Summation Received", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x010c, "Current Tier7 Summation Delivered", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x010d, "Current Tier7 Summation Received", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x010e, "Current Tier8 Summation Delivered", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x010f, "Current Tier8 Summation Received", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0110, "Current Tier9 Summation Delivered", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0111, "Current Tier9 Summation Received", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0112, "Current Tier10 Summation Delivered", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0113, "Current Tier10 Summation Received", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0114, "Current Tier11 Summation Delivered", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0115, "Current Tier11 Summation Received", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0116, "Current Tier12 Summation Delivered", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0117, "Current Tier12 Summation Received", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0118, "Current Tier13 Summation Delivered", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0119, "Current Tier13 Summation Received", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x011a, "Current Tier14 Summation Delivered", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x011b, "Current Tier14 Summation Received", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x011c, "Current Tier15 Summation Delivered", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x011d, "Current Tier15 Summation Received", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x0200, " Status", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x0201, "Remaining Battery Life", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x0202, "Hours In Operation", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x0203, "Hours In Fault", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 0x0300, "Unit Of Measure", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x0301, "Multiplier", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x0302, "Divisor", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x0303, "Summation Formatting", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x0304, "Demand Formatting", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x0305, "Historical Consumption Formatting", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x0306, "Metering Device Type", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeStringOctect, 0x0307, "SiteID", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeStringOctect, 0x0308, "MeterSerialNumber", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 0x0309, "Energy Carrier Unit Of Measure", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x030a, "Energy Carrier Summation Formatting", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x030b, "Energy Carrier Demand Formatting", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 0x030c, "Temperature Unit Of Measure", true),
        Cluster::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x030d, "Temperature Formatting", true),
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
