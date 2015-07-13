/*
 * ZigbeeDevice.h
 *
 *  Created on: 29/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZIGBEEDEVICE_H_
#define ZIGBEEDEVICE_H_

#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include <memory>

#include "ZigbeeTypes.h"
#include "zigbee/messageStructure/AnnunceMessage.h"
#include "messageStructure/SimpleDescMessage.h"
#include "messageStructure/ReadAttributeResponseMessage.h"
#include "messageStructure/ReqActiveEndpointsMessage.h"
#include "messageStructure/BindTableResponseMessage.h"
#include "AttributeStatusRecord.h"
#include <zigbee/EndpointID.h>
#include <zigbee/ClusterID.h>
#include <zigbee/NwkAddr.h>
#include "../zcl/ZCLDataType.h"

namespace zigbee {

class ZigbeeDevice {
public:

	typedef boost::signals2::signal<void(AnnunceMessage *)> AnnunceSignal;
	typedef boost::signals2::signal<void(SimpleDescMessage *)> SimpleDescSignal;
	typedef boost::signals2::signal<void(std::shared_ptr< AttributeStatusRecord> rawData)> AttributeValueSignal;
	typedef boost::signals2::signal<void(std::shared_ptr< BindTableResponseMessage> bindTable)> BindTableResponseSignal;
	typedef boost::signals2::signal<void()> AttributeCmdSignal;
public:
	ZigbeeDevice();
	virtual ~ZigbeeDevice();
public:
	virtual bool isPresent()=0;
	virtual bool requestDevices()=0;
	virtual void getUsbMessage()=0;
	virtual void requestAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId)=0;
	virtual void writeAttribute(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId commandId, ZCLTypeDataType dataType, uint8_t dataValueLen, uint8_t * dataValue)=0;
	virtual void sendCmd(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeClusterCmdId commandId, std::vector<uint8_t>  data = std::vector<uint8_t>())=0;
	virtual void sendReqBind(NwkAddr destAddr, uint8_t outClusterAddr[Z_EXTADDR_LEN],EndpointID outClusterEP,ClusterID clusterID, uint8_t inClusterAddr[Z_EXTADDR_LEN],EndpointID inClusterEp)=0;
	virtual void requesBindTable(NwkAddr nwkAddrs)=0;

	virtual boost::signals2::connection registerForAnnunceMessage(const AnnunceSignal::slot_type &subscriber)=0;
	virtual boost::signals2::connection registerForSimpleDescMessage(const SimpleDescSignal::slot_type &subscriber)=0;
	virtual boost::signals2::connection registerForBindTableMessage(const BindTableResponseSignal::slot_type &subscriber)=0;
	virtual boost::signals2::connection registerForAttributeCmd(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeCmdId cmdId,const AttributeCmdSignal::slot_type & subsriber )=0;
	virtual boost::signals2::connection registerForAttributeValue(NwkAddr nwkAddrs, const EndpointID endpoint, ClusterID cluster, ZigbeeAttributeId attributeId,
			const AttributeValueSignal::slot_type &subscriber)=0;
};

} /* namespace zigbee */

#endif /* ZIGBEEDEVICE_H_ */
