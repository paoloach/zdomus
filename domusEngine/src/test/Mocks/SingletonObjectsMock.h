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

#include "../../Utils/SingletonObjects.h"


namespace zigbee {

    class SingletonObjectsMock : public SingletonObjects {
    public:
        SingletonObjectsMock();

        virtual ~SingletonObjectsMock();

        MOCK_METHOD0(getZigbeeDevice, ZigbeeDevice *());

        MOCK_METHOD0(getZDevices, ZDevices * ());

        MOCK_METHOD0(getConfiguration, Configuration * ());

        MOCK_METHOD0(getJSManager, JSManager * ());

        MOCK_METHOD0(getBindTable, BindTable *  ());

        MOCK_METHOD0(getClusters, Clusters *());

        MOCK_METHOD0(getAttributeWriter, AttributeWriter * ());

        MOCK_METHOD0(getDeviceInfoDispatcher, DeviceInfoDispatcher *());

        MOCK_METHOD0(getConstant, Constant * ());

        MOCK_METHOD0(getTopology, TopologyCreation * ());

        MOCK_METHOD0(getRestHandler, http::RestHandler * ());
    };

} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_SINGLETONOBJECTSMOCK_H_ */
