/*
 * ParamString.h
 *
 *  Created on: 27/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef PARAMSTRING_H_
#define PARAMSTRING_H_

#include <memory>
#include <QtGui/QLineEdit>

#include <zcl/CmdParams/ClusterCmdParams.h>
#include "Param.h"

namespace zigbee {

class ParamString: public QLineEdit , public Param {
public:
	ParamString(std::shared_ptr<ClusterCmdParamsBase> clusterCmdParam);
	virtual ~ParamString();
public:
	virtual std::vector<uint8_t> getParamData();
private:
	std::shared_ptr<ClusterCmdParamsBase> param;
};

} /* namespace zigbee */

#endif /* PARAMSTRING_H_ */
