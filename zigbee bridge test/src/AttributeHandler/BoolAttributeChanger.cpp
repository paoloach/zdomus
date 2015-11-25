/*
 * BoolAttributeChanger.cpp
 *
 *  Created on: 20/ago/2014
 *      Author: Paolo Achdjian
 */

#include "BoolAttributeChanger.h"


namespace zigbee {

BoolAttributeChanger::BoolAttributeChanger(std::shared_ptr<ZCL_boolean_Attribute> attribute) :parent(nullptr), attribute(attribute){

}

BoolAttributeChanger::~BoolAttributeChanger() {
}

void BoolAttributeChanger::show(QDialog * dialog) {
	parent = dialog;
	changeBool.setupUi(dialog);

	connect(changeBool.buttonBox, SIGNAL(rejected()), this, SLOT(close()));
	connect(changeBool.buttonBox, SIGNAL(accepted()), this, SLOT(apply()));
	if (attribute->isAvailable()){
		if (boost::any_cast<bool>(attribute->getValue())){
			changeBool.trueButton->setChecked(true);
		} else {
			changeBool.falseButton->setChecked(true);
		}
	}
}

void BoolAttributeChanger::close() {
	delete parent;
}

void BoolAttributeChanger::apply() {
	attribute->sendValue(changeBool.trueButton->isChecked());
	attribute->requestValue();
	delete parent;
}


} /* namespace zigbee */
