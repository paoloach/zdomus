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
	MOCK_METHOD4(requestAttribute, void (NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId));
	MOCK_METHOD7(writeAttribute, void (NwkAddr , const EndpointID , ClusterID , ZigbeeAttributeId , ZCLTypeDataType , uint8_t , uint8_t * ));

	MOCK_METHOD5(sendCmd, void (NwkAddr nwkAddrs, EndpointID endpoint, ClusterID cluster, ZigbeeClusterCmdId commandId, std::vector<uint8_t> data ) );
	MOCK_METHOD1(registerForAnnunceMessage, boost::signals2::connection (const AnnunceSignal::slot_type &subscriber));
	MOCK_METHOD1(registerForSimpleDescMessage, boost::signals2::connection (const SimpleDescSignal::slot_type &subscriber));

	MOCK_METHOD5(registerForAttributeCmd, boost::signals2::connection (NwkAddr nwkAddrs, EndpointID endpoint, ClusterID cluster, ZigbeeAttributeCmdId cmdId,const AttributeCmdSignal::slot_type & subsriber ));
	MOCK_METHOD5(registerForAttributeValue, boost::signals2::connection (NwkAddr nwkAddrs, EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId,
					const AttributeValueSignal::slot_type &subscriber));

	MOCK_METHOD6(sendReqBind, void (NwkAddr destAddr, uint8_t outClusterAddr[Z_EXTADDR_LEN],EndpointID outClusterEP,ClusterID clusterID, uint8_t inClusterAddr[Z_EXTADDR_LEN],EndpointID inClusterEp));
	MOCK_METHOD1(requesBindTable, void (NwkAddr nwkAddrs) );
	MOCK_METHOD1(registerForBindTableMessage, boost::signals2::connection (const BindTableResponseSignal::slot_type &subscriber) );
};

}
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_ZIGBEEDEVICEMOCK_H_ */
