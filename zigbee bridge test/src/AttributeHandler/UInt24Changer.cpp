/*
 * uint24Changer.cpp
 *
 *  Created on: 22/ago/2014
 *      Author: Paolo Achdjian
 */

#include "UInt24Changer.h"
#include "QtGui/QIntValidator"

namespace zigbee {

UInt24Changer::UInt24Changer(std::shared_ptr<ZCL_uint24_Attribute> attribute) :parent(nullptr), attribute(attribute){

}

UInt24Changer::~UInt24Changer() {
}

void UInt24Changer::show(QDialog * dialog) {
	parent = dialog;
	changerUInt24.setupUi(dialog);
	changerUInt24.newValue->setValidator(new QIntValidator(0,0xFFFFFF));

	connect(changerUInt24.buttonBox, SIGNAL(rejected()), this, SLOT(close()));
	connect(changerUInt24.buttonBox, SIGNAL(accepted()), this, SLOT(apply()));
	if (attribute->isAvailable()){
		boost::any_cast<uint32_t>(attribute->getValue());
	}
}

void UInt24Changer::close() {
	delete parent;
}

void UInt24Changer::apply() {
	bool ok;

	int newValue = changerUInt24.newValue->text().toInt(&ok,10);
	if (ok){
		attribute->sendValue(newValue);
		attribute->requestValue();
		delete parent;
	}
}

} /* namespace zigbee */
