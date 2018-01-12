/*
 * ClusterTypeFactoryMock.h
 *
 *  Created on: 04/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_CLUSTERTYPEFACTORYMOCK_H_
#define SRC_TEST_MOCKS_CLUSTERTYPEFACTORYMOCK_H_

#include <gtest/gtest.h>
#include "../../trompeloeil/src/trompeloeil/include/trompeloeil.hpp"

#include <zcl/ClusterTypeFactory.h>

namespace zigbee {
namespace test {

class ClusterTypeFactoryMock : public ClusterTypeFactory{
public:
	ClusterTypeFactoryMock();
	virtual ~ClusterTypeFactoryMock();

	MAKE_MOCK4(getCluster, std::unique_ptr<Cluster> (ClusterID clusterId, ZigbeeDevice * zigbeeDevice, EndpointID endpoint, NwkAddr networkAddress));
};


} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_CLUSTERTYPEFACTORYMOCK_H_ */
