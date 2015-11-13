/*
 * ParamList.h
 *
 *  Created on: 09/set/2014
 *      Author: Paolo Achdjian
 */

#ifndef PARAMLIST_H_
#define PARAMLIST_H_

#include <memory>
#include <QtGui/QLineEdit>

#include <zcl/CmdParams/ClusterCmdParams.h>
#include "Param.h"

namespace zigbee {

class ParamList : public QLineEdit , public Param {
public:
	ParamList(std::shared_ptr<ClusterCmdParamsBase> clusterCmdParam);
	virtual ~ParamList();
public:
	virtual std::vector<uint8_t> getParamData();
private:
	std::shared_ptr<ClusterCmdParamsBase> param;
};

} /* namespace zigbee */

#endif /* PARAMLIST_H_ */
