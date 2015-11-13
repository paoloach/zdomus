/*
 * uint8Changer.cpp
 *
 *  Created on: 22/ago/2014
 *      Author: Paolo Achdjian
 */

#include "Enum8BitChanger.h"
#include "QtGui/QIntValidator"

namespace zigbee {

Enum8BitChanger::Enum8BitChanger(std::shared_ptr<ZCL_enum8bit_Attribute> attribute) :parent(nullptr), attribute(attribute){

}

Enum8BitChanger::~Enum8BitChanger() {
}

void Enum8BitChanger::show(QDialog * dialog) {
	parent = dialog;
	changerEnum8Bit.setupUi(dialog);
	changerEnum8Bit.newValue->setValidator(new QIntValidator(0,255));

	connect(changerEnum8Bit.buttonBox, SIGNAL(rejected()), this, SLOT(close()));
	connect(changerEnum8Bit.buttonBox, SIGNAL(accepted()), this, SLOT(apply()));
	if (attribute->isAvailable()){
		uint8_t value = boost::any_cast<uint8_t>(attribute->getValue());
	}
}

void Enum8BitChanger::close() {
	delete parent;
}

void Enum8BitChanger::apply() {
	bool ok;

	int newValue = changerEnum8Bit.newValue->text().toInt(&ok,10);
	if (ok){
		attribute->sendValue(newValue);
		attribute->requestValue();
		delete parent;
	}
}

} /* namespace zigbee */
