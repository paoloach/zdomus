/*
 * CmdUpdateAttribute.h
 *
 *  Created on: 13/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_COMAND_CMDUPDATEATTRIBUTE_H_
#define SRC_COMAND_CMDUPDATEATTRIBUTE_H_

#include <string>

#include "Comand.h"


namespace zigbee {

class AttributeDataContainer;

class CmdUpdateAttribute : public Comand {
public:
	static const std::string INVALID_TOKEN_MSG;
public:
	CmdUpdateAttribute(AttributeDataContainer & attributes);
	CmdUpdateAttribute(AttributeDataContainer & attributes, uint64_t token);
	virtual ~CmdUpdateAttribute();
public:
	virtual bool parseData(const std::string &line) override;
	virtual void execute() override;
	virtual void getResponse(boost::property_tree::ptree & result) override;
private:
	AttributeDataContainer & attributes;
	std::string strToken;
	uint64_t token;
	bool badToken;
};

} /* namespace zigbee */

#endif /* SRC_COMAND_CMDUPDATEATTRIBUTE_H_ */
