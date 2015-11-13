/*
 * CmdNull.h
 *
 *  Created on: 28/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_COMAND_CMDNULL_H_
#define SRC_COMAND_CMDNULL_H_

#include "Comand.h"

namespace zigbee {

class CmdNull  : public Comand {
public:
	CmdNull();
	virtual ~CmdNull();
protected:
	virtual bool parseData(const std::string &line) override;
	virtual void execute() override;
	virtual void getResponse(boost::property_tree::ptree & result) override;
};

} /* namespace zigbee */

#endif /* SRC_COMAND_CMDNULL_H_ */
