/*
 * ZDeviceFixture.h
 *
 *  Created on: 14/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_HTTPSERVER_ZDEVICEFIXTURE_H_
#define SRC_TEST_HTTPSERVER_ZDEVICEFIXTURE_H_

#include <zcl/Cluster.h>
#include "../../ZigbeeData/ZDevice.h"
#include "../../ZigbeeData/ZEndpoint.h"
#include "../../ZigbeeData/ExtAddress.h"

namespace zigbee {
namespace http {
namespace test {

class ZDeviceFixture {
public:
	static ZEndpoint endpoint1_1;
	static ZEndpoint endpoint2_1;
	static ZEndpoint endpoint1_2;

	static ExtAddress extAddress1;
	static ExtAddress extAddress2;
	static ZDevice zDevice1;
	static ZDevice zDevice2;

	static std::string clusterName;
	static constexpr ClusterID clusterId{23};
	static zigbee::Cluster::AttributeDef attribute1;
	static zigbee::Cluster::AttributeDef attribute2;
	static zigbee::Cluster::AttributeDef attribute3;

	static std::vector<zigbee::Cluster::AttributeDef> attributes;

	static zigbee::Cluster::CommandDef command1;
	static zigbee::Cluster::CommandDef command2;
	static zigbee::Cluster::CommandDef command3;

	static std::vector<zigbee::Cluster::CommandDef> commands;
};

} /* namespace test */
} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_TEST_HTTPSERVER_ZDEVICEFIXTURE_H_ */
