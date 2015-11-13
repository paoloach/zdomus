/*
 * ParamList.cpp
 *
 *  Created on: 09/set/2014
 *      Author: Paolo Achdjian
 */

#include "ParamList.h"

namespace zigbee {

ParamList::ParamList(std::shared_ptr<ClusterCmdParamsBase> clusterCmdParam) : param(clusterCmdParam){
	setToolTip("Insert the value separated by comma");
}

ParamList::~ParamList() {
}

std::vector<uint8_t> ParamList::getParamData() {
	std::vector<uint8_t> result;

	QString qValue = text();
	QStringList qValues = qValue.split(",", QString::SkipEmptyParts);
	std::vector<std::string> values;
	for(auto value: qValues){
		values.push_back(value.toStdString());
	}

	return param->getType().getRaw(values);
}

} /* namespace zigbee */
