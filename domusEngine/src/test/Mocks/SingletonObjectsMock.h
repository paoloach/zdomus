/*
 * SingletonObjectsMock.h
 *
 *  Created on: 20/giu/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_SINGLETONOBJECTSMOCK_H_
#define SRC_TEST_MOCKS_SINGLETONOBJECTSMOCK_H_

#include <gtest/gtest.h>
#include "../../trompeloeil/src/trompeloeil/include/trompeloeil.hpp"
#include "../../Utils/SingletonObjects.h"


namespace zigbee {

    class SingletonObjectsMock : public SingletonObjects {
    public:
        SingletonObjectsMock();

        virtual ~SingletonObjectsMock();

        MAKE_MOCK0(getZigbeeDevice, ZigbeeDevice *());

        MAKE_MOCK0(getZDevices, ZDevices * ());

        MAKE_MOCK0(getConfiguration, Configuration * ());

        MAKE_MOCK0(getJSManager, JSManager * ());

        MAKE_MOCK0(getBindTable, BindTable *  ());

        MAKE_MOCK0(getClusters, Clusters *());

        MAKE_MOCK0(getAttributeWriter, AttributeWriter * ());

        MAKE_MOCK0(getDeviceInfoDispatcher, DeviceInfoDispatcher *());

        MAKE_MOCK0(getConstant, Constant * ());

        MAKE_MOCK0(getTopology, TopologyCreation * ());

        MAKE_MOCK0(getRestHandler, http::RestHandler * ());
    };

} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_SINGLETONOBJECTSMOCK_H_ */
