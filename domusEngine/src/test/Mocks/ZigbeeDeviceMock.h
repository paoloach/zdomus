/*
 * ZigbeeDeviceMock.h
 *
 *  Created on: 12/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_ZIGBEEDEVICEMOCK_H_
#define SRC_TEST_MOCKS_ZIGBEEDEVICEMOCK_H_

#include <gtest/gtest.h>
#include "../../trompeloeil/src/trompeloeil/include/trompeloeil.hpp"

#include "zigbee/ZigbeeDevice.h"

namespace zigbee {
    namespace test {

        class ZigbeeDeviceMock : public ZigbeeDevice {
        public:
            ZigbeeDeviceMock();

            virtual ~ZigbeeDeviceMock();

        public:
            MAKE_MOCK0(isPresent, bool());


            MAKE_MOCK0(requestDevices, bool());
            MAKE_MOCK1(requestNodePower, void (zigbee::NwkAddr));
            MAKE_MOCK1(removeDevice, void (zigbee::NwkAddr));
            MAKE_MOCK1(getNodeDescriptor, void (zigbee::NwkAddr));
            MAKE_MOCK0(getUsbMessage, void());
            MAKE_MOCK1(requestAttribute, void(const AttributeKey &key));
            MAKE_MOCK1(requestAttributes, void(AttributesKey &key));
            MAKE_MOCK0(requestReset, void());
            MAKE_MOCK7(writeAttribute, void (NwkAddr
                    nwkAddrs,
                    const EndpointID endpoint, ClusterID
                    cluster, ZigbeeAttributeId
                    commandId, ZCLTypeDataType
                    dataType, uint8_t
                    dataValueLen, uint8_t * dataValue));

            MAKE_MOCK5(sendCmd, void (NwkAddr
                    nwkAddrs,
                    const EndpointID endpoint, ClusterID
                    cluster, ZigbeeClusterCmdId
                    commandId, std::vector<uint8_t>
                    data ));

            MAKE_MOCK1(registerForAnnunceMessage, void (AnnunceCallback));

            MAKE_MOCK1(registerForSimpleDescMessage, void (SimpleDescCallback));

            MAKE_MOCK5(registerForAttributeCmd, void (NwkAddr
                    nwkAddrs,
                    const EndpointID endpoint, ClusterID
                    cluster, ZigbeeAttributeCmdId
                    cmdId,
                    const std::function<void()>));
            MAKE_MOCK5(registerForAttributeValue, void (NwkAddr
                    nwkAddrs,
                    const EndpointID endpoint, ClusterID
                    cluster, ZigbeeAttributeId
                    attributeId,
                    const NewAttributeValueCallback subscriber));

            MAKE_MOCK1(requestBindTable, void (NwkAddr
                    nwkAddrs));

            MAKE_MOCK1(registerForBindTableMessage, void (BindTableResponseCallback));
            MAKE_MOCK4(requestAttributes, void (NwkAddr
                    nwkAddrs,
                    const EndpointID endpoint, ClusterID
                    cluster, std::vector<ZigbeeAttributeId> & attributeIds));

            MAKE_MOCK6(sendReqBind, void(zigbee::NwkAddr,
                    const uint8_t*, zigbee::EndpointID, zigbee::ClusterID, const uint8_t*, zigbee::EndpointID));

            MAKE_MOCK1(sendReqDeviceInfo, void(zigbee::NwkAddr));

            MAKE_MOCK0(enableLog, bool());

            MAKE_MOCK6(sendReqUnbind, void(zigbee::NwkAddr,
                    const uint8_t*, zigbee::EndpointID, zigbee::ClusterID, const uint8_t*, zigbee::EndpointID));
            MAKE_MOCK4(requestAttributes, void(NwkAddr
                    nwkAddrs,
                    const EndpointID endpoint, ClusterID
                    cluster, ZigbeeAttributeIds & attributeIds));

            MAKE_MOCK1(requestActiveEndpoints, void(NwkAddr));

            MAKE_MOCK3(getIEEEAddress, void(NwkAddr, ZDPRequestType, uint8_t));
        };

    }
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_ZIGBEEDEVICEMOCK_H_ */
