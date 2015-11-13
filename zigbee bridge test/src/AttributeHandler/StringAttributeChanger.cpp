/*
 * StringAttributeChanger.cpp
 *
 *  Created on: 21/ago/2014
 *      Author: Paolo Achdjian
 */

#include "StringAttributeChanger.h"

namespace zigbee {

StringAttributeChanger::StringAttributeChanger(std::shared_ptr<ZCL_string_Attribute> attribute) :parent(nullptr), attribute(attribute) {

}

StringAttributeChanger::~StringAttributeChanger() {
}

void StringAttributeChanger::show(QDialog * dialog) {
	parent = dialog;
	stringChanger.setupUi(dialog);

	connect(stringChanger.buttonBox, SIGNAL(rejected()), this, SLOT(close()));
	connect(stringChanger.buttonBox, SIGNAL(accepted()), this, SLOT(apply()));
	if (attribute->isAvailable()){
		std::string  value = boost::any_cast<std::string>(attribute->getValue());
		stringChanger.line->setText(QString::fromStdString(value));
	}
}

void StringAttributeChanger::close() {
	delete parent;
}

void StringAttributeChanger::apply() {
	std::string newValue = stringChanger.line->text().toStdString();
	attribute->sendValue(newValue);
	attribute->requestValue();
	delete parent;
}


} /* namespace zigbee */
