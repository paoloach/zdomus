/*
 * ZigbeeDeviceMock.h
 *
 *  Created on: 12/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_ZIGBEEDEVICEMOCK_H_
#define SRC_TEST_MOCKS_ZIGBEEDEVICEMOCK_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "zigbee/ZigbeeDevice.h"

namespace zigbee {
namespace test {

class ZigbeeDeviceMock: public ZigbeeDevice {
public:
	ZigbeeDeviceMock();
	virtual ~ZigbeeDeviceMock();
public:
	MOCK_METHOD0(isPresent, bool ());
	MOCK_METHOD0(requestDevices, bool ());
	MOCK_METHOD0(getUsbMessage, void ());
    MOCK_METHOD4(requestAttribute,  void (NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId));
	MOCK_METHOD7(writeAttribute, void (NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId commandId, ZCLTypeDataType dataType,
			uint8_t dataValueLen, uint8_t *dataValue));

	MOCK_METHOD5(sendCmd, void (NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeClusterCmdId commandId,
			std::vector<uint8_t> data ) );
	MOCK_METHOD1(registerForAnnunceMessage, void (AnnunceCallback));
	MOCK_METHOD1(registerForSimpleDescMessage, void (SimpleDescCallback));

	MOCK_METHOD5(registerForAttributeCmd, void (NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeCmdId cmdId, const std::function<void()>));
	MOCK_METHOD5(registerForAttributeValue, void (NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId,
            const NewAttributeValueCallback subscriber));

	MOCK_METHOD1(requestBindTable, void (NwkAddr nwkAddrs) );
	MOCK_METHOD1(registerForBindTableMessage, void (BindTableResponseCallback) );
	MOCK_METHOD4(requestAttributes, void (NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, std::vector<ZigbeeAttributeId> & attributeIds) );
    MOCK_METHOD6(sendReqBind,  void (zigbee::NwkAddr, const uint8_t*, zigbee::EndpointID, zigbee::ClusterID, const uint8_t*, zigbee::EndpointID));
    MOCK_METHOD6(sendReqUnbind,  void (zigbee::NwkAddr, const uint8_t*, zigbee::EndpointID, zigbee::ClusterID, const uint8_t*, zigbee::EndpointID));
	MOCK_METHOD4(requestAttributes, void(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeIds & attributeIds));
};

}
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_ZIGBEEDEVICEMOCK_H_ */
