/*
 * Bitmap8BitChanger.cpp
 *
 *  Created on: 22/ago/2014
 *      Author: Paolo Achdjian
 */

#include "Bitmap8BitChanger.h"

namespace zigbee {

Bitmap8BitChanger::Bitmap8BitChanger(std::shared_ptr<ZCL_bitmap8bit_Attribute> attribute) :parent(nullptr), attribute(attribute){

}

Bitmap8BitChanger::~Bitmap8BitChanger() {
}

void Bitmap8BitChanger::show(QDialog * dialog) {
	parent = dialog;
	bitmap8BitChanger.setupUi(dialog);

	connect(bitmap8BitChanger.buttonBox, SIGNAL(rejected()), this, SLOT(close()));
	connect(bitmap8BitChanger.buttonBox, SIGNAL(accepted()), this, SLOT(apply()));
	if (attribute->isAvailable()){
		uint8_t value = boost::any_cast<uint8_t>( attribute->getValue());
		if (value & 1){
			bitmap8BitChanger.bit1->setChecked(true);
		} else {
			bitmap8BitChanger.bit1->setChecked(false);
		}
		if (value & 2){
			bitmap8BitChanger.bit2->setChecked(true);
		} else {
			bitmap8BitChanger.bit2->setChecked(false);
		}
		if (value & 4){
			bitmap8BitChanger.bit3->setChecked(true);
		} else {
			bitmap8BitChanger.bit3->setChecked(false);
		}
		if (value & 8){
			bitmap8BitChanger.bit4->setChecked(true);
		} else {
			bitmap8BitChanger.bit4->setChecked(false);
		}
		if (value & 0x10){
			bitmap8BitChanger.bit5->setChecked(true);
		} else {
			bitmap8BitChanger.bit5->setChecked(false);
		}
		if (value & 0x20){
			bitmap8BitChanger.bit6->setChecked(true);
		} else {
			bitmap8BitChanger.bit6->setChecked(false);
		}
		if (value & 0x40){
			bitmap8BitChanger.bit7->setChecked(true);
		} else {
			bitmap8BitChanger.bit7->setChecked(false);
		}
		if (value & 0x80){
			bitmap8BitChanger.bit8->setChecked(true);
		} else {
			bitmap8BitChanger.bit8->setChecked(false);
		}
	}
}

void Bitmap8BitChanger::close() {
	delete parent;
}

void Bitmap8BitChanger::apply() {
	uint8_t newValue = 0;
	if (bitmap8BitChanger.bit1->isChecked()){
		newValue |= 0x01;
	}
	if (bitmap8BitChanger.bit2->isChecked()){
		newValue |= 0x02;
	}
	if (bitmap8BitChanger.bit3->isChecked()){
		newValue |= 0x04;
	}
	if (bitmap8BitChanger.bit4->isChecked()){
		newValue |= 0x08;
	}
	if (bitmap8BitChanger.bit5->isChecked()){
		newValue |= 0x10;
	}
	if (bitmap8BitChanger.bit6->isChecked()){
		newValue |= 0x20;
	}
	if (bitmap8BitChanger.bit7->isChecked()){
		newValue |= 0x40;
	}
	if (bitmap8BitChanger.bit8->isChecked()){
		newValue |= 0x80;
	}

	attribute->sendValue(newValue);
	attribute->requestValue();
	delete parent;
}

} /* namespace zigbee */
