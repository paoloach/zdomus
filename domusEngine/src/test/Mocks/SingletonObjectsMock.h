/*
 * SingletonObjectsMock.h
 *
 *  Created on: 20/giu/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_SINGLETONOBJECTSMOCK_H_
#define SRC_TEST_MOCKS_SINGLETONOBJECTSMOCK_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../../src/ZigbeeData/ZDevices.h"


#include "../../Utils/SingletonObjects.h"


namespace zigbee {

    class SingletonObjectsMock : public SingletonObjects {
    public:
        SingletonObjectsMock();

        virtual ~SingletonObjectsMock();

        MOCK_METHOD0(getZigbeeDevice, std::shared_ptr<ZigbeeDevice>());

        MOCK_METHOD0(getZDevices, ZDevices * ());

        MOCK_METHOD0(getConfiguration, std::shared_ptr<Configuration>());

        MOCK_METHOD0(getJSManage, std::shared_ptr<JSManager>());

        MOCK_METHOD0(getClusterTypeFactory, std::shared_ptr<ClusterTypeFactory>());

        MOCK_METHOD0(getFixedPathContainer, std::shared_ptr<http::FixedPathContainer>());

        MOCK_METHOD0(getIO, boost::asio::io_service & ());

        MOCK_METHOD0(getAttributeDataContainer, AttributeDataContainer & ());

        MOCK_METHOD0(getClusters,  Clusters *());
    };

} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_SINGLETONOBJECTSMOCK_H_ */
