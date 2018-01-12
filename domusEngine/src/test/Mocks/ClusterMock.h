/*
 * ClusterMock.h
 *
 *  Created on: 04/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_CLUSTERMOCK_H_
#define SRC_TEST_MOCKS_CLUSTERMOCK_H_

#include <gtest/gtest.h>
#include "../../trompeloeil/src/trompeloeil/include/trompeloeil.hpp"

#include <zcl/Cluster.h>
#include <zigbee/EndpointID.h>

namespace zigbee {
namespace test {

class ClusterMock: public Cluster {
public:
	ClusterMock();
	virtual ~ClusterMock();

    MAKE_CONST_MOCK0(getId, ClusterID () );
    MAKE_CONST_MOCK0(getClusterName, std::string () );
    MAKE_MOCK2(createAttributes, void (const Cluster::AttributeDef * attributesDef, int size) );
    MAKE_MOCK1(createAttributes, void (const std::vector<AttributeDef> & attributesDef) ) ;
    MAKE_CONST_MOCK0(getEndpoint,const EndpointID () );
    MAKE_CONST_MOCK0(getNetworkAddress, NwkAddr () );
    MAKE_CONST_MOCK1(getAttribute, ZCLAttribute *(int id) );
    MAKE_CONST_MOCK1(getAttribute, ZCLAttribute * (std::string_view  name) );
    MAKE_MOCK2(executeCommand, void (uint32_t cmd, std::vector<uint8_t>  data));
    MAKE_CONST_MOCK0(getAttributes, std::vector<AttributeDef> ());
    MAKE_CONST_MOCK0(getCommands, const std::vector<CommandDef> & ());
    MAKE_MOCK1(getCmdParams,  std::vector<ClusterCmdParamsBase *> (uint32_t cmd));
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_CLUSTERMOCK_H_ */
