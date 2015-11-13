/*
 * ParamIEEEAddress.cpp
 *
 *  Created on: 11/set/2014
 *      Author: Paolo Achdjian
 */

#include "ParamIEEEAddress.h"

namespace zigbee {

ParamIEEEAddress::ParamIEEEAddress(std::shared_ptr<ClusterCmdParamsBase> clusterCmdParam) : param(clusterCmdParam){
	ui.setupUi(this);
}

ParamIEEEAddress::~ParamIEEEAddress() {
}

std::vector<uint8_t> ParamIEEEAddress::getParamData() {
	std::vector<uint8_t> result;
	std::vector<std::string> octects;

	octects.push_back(ui.octect1->text().toStdString());
	octects.push_back(ui.octect2->text().toStdString());
	octects.push_back(ui.octect3->text().toStdString());
	octects.push_back(ui.octect4->text().toStdString());
	octects.push_back(ui.octect5->text().toStdString());
	octects.push_back(ui.octect6->text().toStdString());
	octects.push_back(ui.octect7->text().toStdString());
	octects.push_back(ui.octect8->text().toStdString());

	return param->getType().getRaw(octects);
}

} /* namespace zigbee */
