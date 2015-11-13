/*
 * InsertCmdParams.cpp
 *
 *  Created on: 27/ago/2014
 *      Author: Paolo Achdjian
 */

#include "InsertCmdParams.h"
#include "ParamUInteger.h"
#include "ParamString.h"
#include "ParamList.h"
#include "ParamIEEEAddress.h"

namespace zigbee {

InsertCmdParams::InsertCmdParams() {
	title = new QLabel(this);
	title->setAlignment(Qt::AlignCenter);
	title->setText("Insert Params");

	gridLayout = new QGridLayout();
	gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

	buttonBox = new QDialogButtonBox(this);
	buttonBox->setOrientation(Qt::Horizontal);
	buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
	buttonBox->setCenterButtons(true);

	verticalSpace = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

	verticalLayout = new QVBoxLayout(this);
	verticalLayout->addWidget(title);
	verticalLayout->addLayout(gridLayout);
	verticalLayout->addItem(verticalSpace);
	verticalLayout->addWidget(buttonBox);
}

InsertCmdParams::~InsertCmdParams() {
}

void InsertCmdParams::setup(std::vector<std::shared_ptr<ClusterCmdParamsBase>> clusterCmdParams) {
	int i=0;
	for (QWidget * widget: widgets){
		gridLayout->removeWidget(widget);
		delete widget;
	}
	widgets.clear();
	params.clear();
	for (std::shared_ptr<ClusterCmdParamsBase> clusterCmdParam: clusterCmdParams){
		QLabel * paramName = new QLabel(this);
		paramName->setText(QString::fromStdString(clusterCmdParam->getName()));
		gridLayout->addWidget(paramName, i, 0, 1, 1);
		widgets.push_back(paramName);

		QWidget * widget = createWidget(clusterCmdParam);
		Param * param = dynamic_cast<Param *>(widget);
		params.push_back(param);
		gridLayout->addWidget(widget, i, 1, 1, 1);
		widgets.push_back(widget);
		i++;
	}

	connect(buttonBox, SIGNAL(rejected()), this, SLOT(cancel()));
	connect(buttonBox, SIGNAL(accepted()), this, SLOT(ok()));
}

QWidget * InsertCmdParams::createWidget(std::shared_ptr<ClusterCmdParamsBase> clusterCmdParam) {
	switch(clusterCmdParam->getZCLDataType()){
	case ZCLTypeDataType::ZCLTypeUInt8:
	case ZCLTypeDataType::ZCLTypeUInt16:
	case ZCLTypeDataType::ZCLTypeUInt24:
		return new ParamUInteger(clusterCmdParam);
	case ZCLTypeDataType::ZCLTypeStringChar:
		return new ParamString(clusterCmdParam);
	case ZCLTypeDataType::ZCLTypeArray:
		return new ParamList(clusterCmdParam);
	case ZCLTypeDataType::ZCLTypeIEEEaddress:
		return new ParamIEEEAddress(clusterCmdParam);
	}
	return nullptr;
}

std::vector<uint8_t> InsertCmdParams::getCmdData() {
	std::vector<uint8_t> result;
	for(Param * param: params){
		if (param != nullptr){
			for (uint8_t data: param->getParamData()){
				result.push_back(data);
			}
		}
	}

	return result;
}

void InsertCmdParams::ok() {
	accept();
}

void InsertCmdParams::cancel() {
	reject();
}

} /* namespace zigbee */
