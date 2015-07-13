/*
 * CmdGetUpdate.h
 *
 *  Created on: 28/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_COMAND_CMDGETUPDATE_H_
#define SRC_COMAND_CMDGETUPDATE_H_

#include <string>

#include "Comand.h"

namespace zigbee {
class ZDevices;

/**
 * Accept an integer as string
 *
 */
class CmdGetUpdate : public Comand{
public:
	static const std::string INVALID_TOKEN_MSG;
public:
	CmdGetUpdate(ZDevices & zDevices);
	virtual ~CmdGetUpdate();
public:
	virtual bool parseData(const std::string &line) override;
	virtual void execute() override;
	virtual void getResponse(boost::property_tree::ptree & result) override;
	virtual void setTokenId(uint64_t token);
private:
	ZDevices & zDevices;
	std::string strToken;
	uint64_t token;
	bool badToken;
};

} /* namespace zigbee */

#endif /* SRC_COMAND_CMDGETUPDATE_H_ */
