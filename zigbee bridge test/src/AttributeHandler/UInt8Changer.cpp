/*
 * uint8Changer.cpp
 *
 *  Created on: 22/ago/2014
 *      Author: Paolo Achdjian
 */

#include "UInt8Changer.h"
#include "QtGui/QIntValidator"

namespace zigbee {

UInt8Changer::UInt8Changer(std::shared_ptr<ZCL_uint8_Attribute> attribute) :parent(nullptr), attribute(attribute){

}

UInt8Changer::~UInt8Changer() {
}

void UInt8Changer::show(QDialog * dialog) {
	parent = dialog;
	changerUInt8.setupUi(dialog);
	changerUInt8.newValue->setValidator(new QIntValidator(0,255));

	connect(changerUInt8.buttonBox, SIGNAL(rejected()), this, SLOT(close()));
	connect(changerUInt8.buttonBox, SIGNAL(accepted()), this, SLOT(apply()));
	if (attribute->isAvailable()){
		boost::any_cast<uint8_t>(attribute->getValue());
	}
}

void UInt8Changer::close() {
	delete parent;
}

void UInt8Changer::apply() {
	bool ok;

	int newValue = changerUInt8.newValue->text().toInt(&ok,10);
	if (ok){
		attribute->sendValue(newValue);
		attribute->requestValue();
		delete parent;
	}
}

} /* namespace zigbee */
