/*
 * ClusterMock.h
 *
 *  Created on: 04/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_CLUSTERMOCK_H_
#define SRC_TEST_MOCKS_CLUSTERMOCK_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <zcl/Cluster.h>
#include <zigbee/EndpointID.h>

namespace zigbee {
namespace test {

class ClusterMock: public Cluster {
public:
	ClusterMock(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, EndpointID endpoint, NwkAddr networkAddress);
	ClusterMock();
	virtual ~ClusterMock();

	MOCK_CONST_METHOD0(getId, ClusterID () );
	MOCK_CONST_METHOD0(getClusterName, std::string () );
	MOCK_METHOD2(createAttributes, void (const Cluster::AttributeDef * attributesDef, int size) );
	MOCK_METHOD1(createAttributes, void (const std::vector<AttributeDef> & attributesDef) ) ;
	MOCK_CONST_METHOD1(getAttribute, std::shared_ptr<ZCLAttribute> (int id) );
	MOCK_CONST_METHOD1(getAttribute, std::shared_ptr<ZCLAttribute> (const std::string & name) );
	MOCK_METHOD2(executeComand, void (uint32_t cmd, std::vector<uint8_t>  data));
	MOCK_CONST_METHOD0(getAttributes, std::vector<AttributeDef> ());
	MOCK_CONST_METHOD0(getCommands, std::vector<CommandDef> ());
	MOCK_METHOD1(getCmdParams,  std::vector<std::shared_ptr<ClusterCmdParamsBase>> (uint32_t cmd));
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_CLUSTERMOCK_H_ */
