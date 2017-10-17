/*
 * CmdRequestAttribute.h
 *
 *  Created on: 13/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_COMAND_CMDREQUESTATTRIBUTE_H_
#define SRC_COMAND_CMDREQUESTATTRIBUTE_H_

#include <string>
#include <vector>
#include <zigbee/ZigbeeDevice.h>
#include <boost/property_tree/ptree.hpp>
#include <zigbee/EndpointID.h>

#include "Comand.h"

namespace zigbee {

class CmdRequestAttribute : public Comand {
public:
	CmdRequestAttribute(ZigbeeDevice &);
	CmdRequestAttribute(ZigbeeDevice & zigbeeDevice, boost::property_tree::ptree & request);
	virtual ~CmdRequestAttribute() =default;
public:
	virtual bool parseData(const std::string &line) override;
	virtual void execute() override;
	virtual void getResponse(boost::property_tree::ptree & result) override;
private:
	void init( boost::property_tree::ptree & request);
private:
	NwkAddr nwkAddress;
	EndpointID endpoint;
	ClusterID cluster;
	ZigbeeDevice & zigbeeDevice;
    ZigbeeAttributeId attributeId;
	std::string response;
};

} /* namespace zigbee */

#endif /* SRC_COMAND_CMDREQUESTATTRIBUTE_H_ */
