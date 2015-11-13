/*
 * ZDevices.h
 *
 *  Created on: 28/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEEDATA_ZDEVICES_H_
#define SRC_ZIGBEEDATA_ZDEVICES_H_

#include <boost/property_tree/ptree.hpp>
#include <map>
#include <memory>
#include <zigbee/messageStructure/AnnunceMessage.h>
#include <zigbee/messageStructure/SimpleDescMessage.h>
#include "ZDevice.h"

namespace zigbee {


class ZDevices {
public:
	ZDevices();
	virtual ~ZDevices() = default;
public:
	virtual void put(const AnnunceMessage & message );
	virtual void put(const SimpleDescMessage & message);
	virtual boost::property_tree::ptree getDifferences(uint32_t token);
	virtual int getNumDevices() const {return devices.size();}
	virtual std::vector<ZDevice> getDevices();
	virtual const ZDevice & getDevice(const ExtAddress & extAddress) const;
	virtual const ZDevice & getDevice(NwkAddr nwkAddress) const ;
	virtual bool exists(const ExtAddress & extAddress) const;
private:
	boost::property_tree::ptree createPTree(ZDevice & zDevice);
	boost::property_tree::ptree createPTree(ZEndpoint & zEndpoint);

private:
	std::map<ExtAddress, ZDevice> devices;
	uint32_t tokenUpdate;
};

typedef std::shared_ptr<ZDevices> ZDevices_P;

} /* namespace zigbee */

#endif /* SRC_ZIGBEEDATA_ZDEVICES_H_ */
