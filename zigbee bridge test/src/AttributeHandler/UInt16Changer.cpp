/*
 * uint16Changer.cpp
 *
 *  Created on: 22/ago/2014
 *      Author: Paolo Achdjian
 */

#include "UInt16Changer.h"
#include "QtGui/QIntValidator"

namespace zigbee {

UInt16Changer::UInt16Changer(std::shared_ptr<ZCL_uint16_Attribute> attribute) :parent(nullptr), attribute(attribute){

}

UInt16Changer::~UInt16Changer() {
}

void UInt16Changer::show(QDialog * dialog) {
	parent = dialog;
	changerUInt16.setupUi(dialog);
	changerUInt16.newValue->setValidator(new QIntValidator(0,0xFFFF));

	connect(changerUInt16.buttonBox, SIGNAL(rejected()), this, SLOT(close()));
	connect(changerUInt16.buttonBox, SIGNAL(accepted()), this, SLOT(apply()));
	if (attribute->isAvailable()){
		boost::any_cast<uint16_t>(attribute->getValue());
	}
}

void UInt16Changer::close() {
	delete parent;
}

void UInt16Changer::apply() {
	bool ok;

	int newValue = changerUInt16.newValue->text().toInt(&ok,10);
	if (ok){
		attribute->sendValue(newValue);
		attribute->requestValue();
		delete parent;
	}
}

} /* namespace zigbee */
