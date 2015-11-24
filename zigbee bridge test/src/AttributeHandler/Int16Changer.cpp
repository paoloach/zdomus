/*
 * uint16Changer.cpp
 *
 *  Created on: 22/ago/2014
 *      Author: Paolo Achdjian
 */

#include "Int16Changer.h"
#include "QtGui/QIntValidator"

namespace zigbee {

Int16Changer::Int16Changer(std::shared_ptr<ZCL_int16_Attribute> attribute) :parent(nullptr), attribute(attribute){

}

Int16Changer::~Int16Changer() {
}

void Int16Changer::show(QDialog * dialog) {
	parent = dialog;
	changerInt16.setupUi(dialog);
	changerInt16.newValue->setValidator(new QIntValidator(-0x7FFF,0x7FFF));

	connect(changerInt16.buttonBox, SIGNAL(rejected()), this, SLOT(close()));
	connect(changerInt16.buttonBox, SIGNAL(accepted()), this, SLOT(apply()));
	if (attribute->isAvailable()){
		boost::any_cast<uint16_t>(attribute->getValue());
	}
}

void Int16Changer::close() {
	delete parent;
}

void Int16Changer::apply() {
	bool ok;

	int newValue = changerInt16.newValue->text().toInt(&ok,10);
	if (ok){
		attribute->sendValue(newValue);
		attribute->requestValue();
		delete parent;
	}
}

} /* namespace zigbee */
