/*
 * ParamUInteger.h
 *
 *  Created on: 27/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef PARAMUINTEGER_H_
#define PARAMUINTEGER_H_

#include <memory>
#include <QtGui/QLineEdit>

#include <zcl/CmdParams/ClusterCmdParams.h>

#include "Param.h"

namespace zigbee {

class ParamUInteger : public QLineEdit, public Param{
public:
	ParamUInteger(std::shared_ptr<ClusterCmdParamsBase> clusterCmdParam);
	virtual ~ParamUInteger();
public:
	virtual std::vector<uint8_t> getParamData();
private:
	std::shared_ptr<ClusterCmdParamsBase> clusterCmdParam;
};

} /* namespace zigbee */

#endif /* PARAMINTEGER_H_ */
