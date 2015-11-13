/*
 * ZEndpoint.h
 *
 *  Created on: 28/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEEDATA_ZENDPOINT_H_
#define SRC_ZIGBEEDATA_ZENDPOINT_H_

#include <vector>
#include <zigbee/messageStructure/SimpleDescMessage.h>
#include <zigbee/EndpointID.h>
#include <zigbee/ClusterID.h>
#include <zigbee/NwkAddr.h>

namespace zigbee {

class ZEndpoint {
public:
	ZEndpoint():endpoint{0},appProfId{0}, appDeviceId{0},appDevVer{0}{}
	ZEndpoint(const SimpleDescMessage & simpleDescMessage);
	ZEndpoint(NwkAddr nwkAddress, EndpointID endpointId, uint32_t profileId, uint32_t deviceId, uint32_t deviceVer, const std::vector<ClusterID> &  inClusters, const std::vector<ClusterID> & outClusters) :
			nwkAddr(nwkAddress), endpoint(endpointId), appProfId(profileId), appDeviceId(deviceId), appDevVer(deviceVer) ,inCluster(inClusters), outCluster(outClusters){
	}
	virtual ~ZEndpoint() = default;
public:

public:
	bool operator==(const ZEndpoint &);

	uint16_t getAppDeviceId() const {
		return appDeviceId;
	}

	uint8_t getAppDevVer() const {
		return appDevVer;
	}

	uint16_t getAppProfId() const {
		return appProfId;
	}

	EndpointID getEndpoint() const {
		return endpoint;
	}

	bool hasInCluster(ClusterID clusterId) const noexcept;

	const std::vector<ClusterID>& getInCluster() const {
		return inCluster;
	}

	NwkAddr getNwkAddr() const {
		return nwkAddr;
	}

	const std::vector<ClusterID>& getOutCluster() const {
		return outCluster;
	}

	bool isInCluster(ClusterID clusterId) const noexcept;
	bool isOutCluster(ClusterID) const noexcept;

private:
	NwkAddr nwkAddr;
	EndpointID endpoint;
	uint16_t appProfId;
	uint16_t appDeviceId;
	uint8_t appDevVer;
	std::vector<ClusterID> inCluster;
	std::vector<ClusterID> outCluster;
};

} /* namespace zigbee */

#endif /* SRC_ZIGBEEDATA_ZENDPOINT_H_ */
