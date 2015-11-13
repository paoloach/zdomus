/*
 * ParamIEEEAddress.h
 *
 *  Created on: 11/set/2014
 *      Author: Paolo Achdjian
 */

#ifndef PARAMIEEEADDRESS_H_
#define PARAMIEEEADDRESS_H_

#include <memory>
#include <QtGui/QLineEdit>

#include <zcl/CmdParams/ClusterCmdParams.h>
#include "../../ui_IEEEAdressWidget.h"
#include "Param.h"

namespace zigbee {

class ParamIEEEAddress : public QWidget,  public Param{
public:
	ParamIEEEAddress(std::shared_ptr<ClusterCmdParamsBase> clusterCmdParam);
	virtual ~ParamIEEEAddress();
protected:
	virtual std::vector<uint8_t> getParamData();
private:
	std::shared_ptr<ClusterCmdParamsBase> param;
	Ui::IEEEAddress ui;
};

} /* namespace zigbee */

#endif /* PARAMIEEEADDRESS_H_ */
