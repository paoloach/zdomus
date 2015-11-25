/*
 * ParamUInteger.cpp
 *
 *  Created on: 27/ago/2014
 *      Author: Paolo Achdjian
 */

#include <QtGui/QIntValidator>

#include "ParamUInteger.h"

namespace zigbee {

    ParamUInteger::ParamUInteger(std::shared_ptr<ClusterCmdParamsBase> clusterCmdParam) :
            clusterCmdParam(clusterCmdParam) {
        QValidator *validator = nullptr;
        validator = new QIntValidator(0, 0xFFFF);
        setValidator(validator);
    }

    ParamUInteger::~ParamUInteger() {
    }

    std::vector<uint8_t> ParamUInteger::getParamData() {
        std::vector<uint8_t> result;

        uint64_t data = text().toULongLong();

        return clusterCmdParam->getType().getRaw(data);
    }

} /* namespace zigbee */
