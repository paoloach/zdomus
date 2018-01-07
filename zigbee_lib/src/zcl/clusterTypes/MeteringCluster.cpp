/*
 * MeteringCluster.cpp
 *
 *  Created on: 07/ago/2015
 *      Author: Paolo Achdjian
 */

#include "src/zcl/attributeTypes/implementation/ZCLuint8AttributeImpl.h"
#include "MeteringCluster.h"

namespace zigbee {

static std::vector<ClusterImpl::AttributeDef> attributesDef{
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0, "Current Summation Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 1, "Current Summation Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 2, "Current Max Demand Deliverd", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 3, "Current Max Demand Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 4, "DFT Summation", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt16, 5, "Daily Freeze Time", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt8, 6, "Power Factor", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUTCTime, 7, "Reading Snap Shot Time", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUTCTime, 8, "Current Max Demand Delivery Time", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUTCTime, 9, "Current Max Demand Received time", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x0A, "Default Update Period", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0B, "Fast Poll Update Period", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0C, "Current Block Period Consumptio Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x0D, "Daily Consumption Targe", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 0x0E, "Current Block", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 0x0F, "Profile Interval Period", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x10, "Interval Read Report Period", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x11, "Preset Reading Time", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x12, "Volume Per Report", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x13, "FlowR estriction", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x14, "Supply Status", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x15, "Current Inlet Energy Carrier Summation", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x16, "Current Outet Energy Carrier Summation", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x17, " Inlet Temperature", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x18, "Outlet Temperature", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt16, 0x19, "Control Temperature", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt24, 0x1A, "Current Inlet Energy Carrier Demand", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt24, 0x1B, "Current Outlet Energy Carrier Demand", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0100, "Current Tier1 Summation Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0101, "Current Tier1 Summation Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0102, "Current Tier2 Summation Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0103, "Current Tier2 Summation Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0104, "Current Tier3 Summation Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0105, "Current Tier3 Summation Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0106, "Current Tier4 Summation Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0107, "Current Tier4 Summation Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0108, "Current Tier5 Summation Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0109, "Current Tier5 Summation Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x010a, "Current Tier6 Summation Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x010b, "Current Tier6 Summation Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x010c, "Current Tier7 Summation Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x010d, "Current Tier7 Summation Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x010e, "Current Tier8 Summation Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x010f, "Current Tier8 Summation Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0110, "Current Tier9 Summation Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0111, "Current Tier9 Summation Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0112, "Current Tier10 Summation Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0113, "Current Tier10 Summation Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0114, "Current Tier11 Summation Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0115, "Current Tier11 Summation Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0116, "Current Tier12 Summation Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0117, "Current Tier12 Summation Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0118, "Current Tier13 Summation Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0119, "Current Tier13 Summation Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x011a, "Current Tier14 Summation Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x011b, "Current Tier14 Summation Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x011c, "Current Tier15 Summation Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x011d, "Current Tier15 Summation Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x0200, " Status", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x0201, "Remaining Battery Life", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x0202, "Hours In Operation", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x0203, "Hours In Fault", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 0x0300, "Unit Of Measure", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x0301, "Multiplier", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x0302, "Divisor", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x0303, "Summation Formatting", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x0304, "Demand Formatting", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x0305, "Historical Consumption Formatting", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x0306, "Metering Device Type", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeStringOctect, 0x0307, "SiteID", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeStringOctect, 0x0308, "MeterSerialNumber", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 0x0309, "Energy Carrier Unit Of Measure", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x030a, "Energy Carrier Summation Formatting", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x030b, "Energy Carrier Demand Formatting", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeenum8, 0x030c, "Temperature Unit Of Measure", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLType8bitBitmap, 0x030d, "Temperature Formatting", true),

        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt24, 0x0400, "Instantaneous Demand", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x0401, "Current Day Consumption Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x0402, "Current Day Consumption Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x0403, "Previous Day Consumption Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x0404, "Previous Day Consumption Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUTCTime, 0x0405, "Current Partial Profile Interval Start Time Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUTCTime, 0x0406, "Current Partial Profile Interval Start Time Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x0407, "Current Partial Profile Interval Value Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x0408, "Current Partial Profile Interval Value Received", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x0409, "Current Day Max Pressure", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x040a, "Current Day Min Pressure", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x040b, "Previous Day Max Pressure", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt48, 0x040c, "Previous Day Min Pressure", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt24, 0x040d, "Current Day Max Demand", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt24, 0x040e, "Previous Day Max Demand", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt24, 0x040f, "Current Month Max Demand", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt24, 0x0410, "Current Year Max Demand", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt24, 0x0411, "Current Day Max Energy Carry Demand", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt24, 0x0412, "Previous Day Max Energy Carry Demand", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt24, 0x0413, "Current Month Max Energy Carry Demand", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt24, 0x0414, "Current Month Min Energy Carry Demand", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt24, 0x0415, "Current Year Max Energy Carry Demand", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeSInt24, 0x0416, "Current Year Min Energy Carry Demand", true),

        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x0500, "Max Number Of Periods Delerived", true),

        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x0600, "Current Demand Delivered", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt24, 0x0601, "Demand Limit", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x0602, "Demand Integration Period", true),
        ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt8, 0x0603, "Number Of Demand Subintervals", true)

};

MeteringCluster::MeteringCluster(ZigbeeDevice * zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
        ClusterImpl(zigbeeDevice, endpoint, networkAddress) {
    createAttributes(attributesDef);

}

ClusterID MeteringCluster::getId()  const {
    return Metering;
}

std::string MeteringCluster::getClusterName()  const {
    return "Metering";
}

} /* namespace zigbee */
