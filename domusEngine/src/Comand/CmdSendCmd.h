/*
 * CmdSendCmd.h
 *
 *  Created on: 12/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_COMAND_CMDSENDCMD_H_
#define SRC_COMAND_CMDSENDCMD_H_

#include <string>
#include <vector>
#include <zigbee/ZigbeeDevice.h>
#include <boost/property_tree/ptree.hpp>
#include <zigbee/EndpointID.h>
#include <zigbee/ClusterID.h>

#include "Comand.h"

namespace zigbee {

class ZDevices;

class CmdSendCmd: public Comand {
public:
	CmdSendCmd(ZigbeeDevice & zigbeeDevice);
	CmdSendCmd(ZigbeeDevice & zigbeeDevice, boost::property_tree::ptree & request);
	virtual ~CmdSendCmd();
public:
	virtual bool parseData(const std::string &line) override;
	virtual void execute() override;
	virtual void getResponse(boost::property_tree::ptree & result) override;
private:
	NwkAddr nwkAddress;
	EndpointID endpoint;
	ClusterID cluster;
	int cmdId;
	std::vector<uint8_t> data;
	ZigbeeDevice & zigbeeDevice;
	std::string response;
};

} /* namespace zigbee */

#endif /* SRC_COMAND_CMDSENDCMD_H_ */
