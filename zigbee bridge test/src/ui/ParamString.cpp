/*
 * ParamString.cpp
 *
 *  Created on: 27/ago/2014
 *      Author: Paolo Achdjian
 */

#include "ParamString.h"

namespace zigbee {

ParamString::ParamString(std::shared_ptr<ClusterCmdParamsBase> clusterCmdParam) : param(clusterCmdParam){

}

ParamString::~ParamString() {
}

std::vector<uint8_t> ParamString::getParamData() {
	std::vector<uint8_t> result;

	QString value = text();

	return param->getType().getRaw(value.toStdString());
}

} /* namespace zigbee */
