/*
 * ClusterTypeFactoryMock.h
 *
 *  Created on: 04/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_CLUSTERTYPEFACTORYMOCK_H_
#define SRC_TEST_MOCKS_CLUSTERTYPEFACTORYMOCK_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <zcl/ClusterTypeFactory.h>

#include "shared_ptr_mock.h"

namespace zigbee {
namespace test {

class ClusterTypeFactoryMock : public ClusterTypeFactory{
public:
	ClusterTypeFactoryMock();
	virtual ~ClusterTypeFactoryMock();

	MOCK_METHOD4(getCluster, std::shared_ptr<Cluster> (ClusterID clusterId,const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, EndpointID endpoint, NwkAddr networkAddress));
};

typedef shared_ptr_mock<ClusterTypeFactory,ClusterTypeFactoryMock> ClusterTypeFactoryMock_P;

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_CLUSTERTYPEFACTORYMOCK_H_ */
