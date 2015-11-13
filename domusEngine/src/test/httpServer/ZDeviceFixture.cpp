/*
 * ZDeviceFixture.cpp
 *
 *  Created on: 14/apr/2015
 *      Author: Paolo Achdjian
 */

#include "ZDeviceFixture.h"

namespace zigbee {
namespace http {
namespace test {

static void dummyFunction(std::vector<uint8_t>) {
}

ExtAddress ZDeviceFixture::extAddress1 { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 };
ExtAddress ZDeviceFixture::extAddress2 { 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27 };

ZEndpoint ZDeviceFixture::endpoint1_1 = { NwkAddr { 10 }, EndpointID(11), 12, 13, 14, { ClusterID { 1 }, ClusterID { 2 }, ClusterID { 3 } }, { ClusterID { 4 }, ClusterID { 5 },
		ClusterID { 6 } } };
ZEndpoint ZDeviceFixture::endpoint2_1 = { NwkAddr { 20 }, EndpointID(21), 22, 23, 24, { ClusterID { 7 }, ClusterID { 8 }, ClusterID { 9 } }, { ClusterID { 10 }, ClusterID { 11 },
		ClusterID { 12 } } };
ZEndpoint ZDeviceFixture::endpoint1_2 = { NwkAddr { 30 }, EndpointID(31), 12, 33, 34, { ClusterID { 1 }, ClusterID { 2 } }, { ClusterID { 4 }, ClusterID { 5 }, ClusterID { 6 } } };

ZDevice ZDeviceFixture::zDevice1 { extAddress1, NwkAddr { 1 }, 2, { endpoint1_1, endpoint2_1 } };
ZDevice ZDeviceFixture::zDevice2 { extAddress2, NwkAddr { 11 }, 12, { endpoint1_2 } };

std::string ZDeviceFixture::clusterName { "clusterName" };
constexpr ClusterID ZDeviceFixture::clusterId;
zigbee::Cluster::AttributeDef ZDeviceFixture::attribute1 { ZCLTypeDataType::ZCLTypeUInt16, 1, "attribute1_uint16", false };
zigbee::Cluster::AttributeDef ZDeviceFixture::attribute2 { ZCLTypeDataType::ZCLType16bitBitmap, 2, "attribute1_16bitBitmap", false };
zigbee::Cluster::AttributeDef ZDeviceFixture::attribute3 { ZCLTypeDataType::ZCLType16bit, 12, "attribute1_16bit", false };

std::vector<zigbee::Cluster::AttributeDef> ZDeviceFixture::attributes { ZDeviceFixture::attribute1, ZDeviceFixture::attribute2, ZDeviceFixture::attribute3 };

zigbee::Cluster::CommandDef ZDeviceFixture::command1 { dummyFunction, 2, "command1" };
zigbee::Cluster::CommandDef ZDeviceFixture::command2 { dummyFunction, 20, "command2" };
zigbee::Cluster::CommandDef ZDeviceFixture::command3 { dummyFunction, 32, "command3" };

std::vector<zigbee::Cluster::CommandDef> ZDeviceFixture::commands { ZDeviceFixture::command1, ZDeviceFixture::command2, ZDeviceFixture::command3 };

} /* namespace test */
} /* namespace http */
} /* namespace zigbee */
