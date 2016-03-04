/*
 * AttributeHandler.cpp
 *
 *  Created on: 19/ago/2014
 *      Author: Paolo Achdjian
 */

#include <QtGui/QPalette>
#include <QtGui/QDialog>

#include "AttributeHandler.h"
#include "AttributeHandler/BoolAttributeChanger.h"
#include "AttributeHandler/StringAttributeChanger.h"
#include "AttributeHandler/Bitmap8BitChanger.h"
#include "AttributeHandler/UInt8Changer.h"
#include "AttributeHandler/UInt16Changer.h"
#include "AttributeHandler/UInt24Changer.h"
#include "AttributeHandler/Int16Changer.h"
#include "AttributeHandler/Enum8BitChanger.h"

namespace zigbee {

AttributeHandler::AttributeHandler(std::experimental::string_view  name, QTreeWidgetItem * parent) :
		name(name), parent(parent), popupMenu(nullptr) {
	item = new QTreeWidgetItem(this->parent);
	TreeItemSignalMap::getHistance().add(item, boost::bind(&AttributeHandler::click, this));
}

std::string AttributeHandler::getValue() {
	std::stringstream stream;

	switch (getStatus()) {
	case ZCLAttribute::Available:
		stream << name << ": " << getAttributeValue();
		break;
	case ZCLAttribute::NotAvailable:
		stream << name << ": not available";
		break;
	case ZCLAttribute::Requesting:
		stream << name << ": waiting for data";
		break;
	case ZCLAttribute::NotSupported:
		stream << name << ": Not supported";
		break;
	default:
		stream << name << ": undefined status";
	}
	return stream.str();
}

void AttributeHandler::click() {
	if (isReadOnly()) {
		requestValue();
		item->setText(0, QString::fromStdString(getValue()));
	} else {
		QTreeWidget * parent = item->treeWidget();
		QRect rect = parent->visualItemRect(item);
		QPoint pos = parent->mapToGlobal(rect.topLeft());
		if (popupMenu == nullptr) {
			popupMenu = new QMenu();

			QAction * actionChange = popupMenu->addAction("Change value");
			connect(actionChange, SIGNAL(triggered ( )), this, SLOT(changeValue()));
			QAction * actionUpdate = popupMenu->addAction("update value");
			connect(actionUpdate, SIGNAL(triggered ( )), this, SLOT(updateValue()));
		}
		popupMenu->popup(pos);
	}
}

void AttributeHandler::changeValue() {
	typedChangeValue();
}

void AttributeHandler::updateValue() {
	requestValue();
}

void AttributeHandler::update() {
	item->setText(0, QString::fromStdString(getValue()));
}

template<>
AttributeChanger *  TypezedAttributeHandler<ZCL_boolean_Attribute>::attributeChangeFactory() {
	return new BoolAttributeChanger(attribute);
}

template<>
AttributeChanger *  TypezedAttributeHandler<ZCL_string_Attribute>::attributeChangeFactory() {
	return new StringAttributeChanger(attribute);
}

template<>
AttributeChanger *  TypezedAttributeHandler<ZCL_bitmap8bit_Attribute>::attributeChangeFactory() {
	return new Bitmap8BitChanger(attribute);
}

template<>
AttributeChanger *  TypezedAttributeHandler<ZCL_uint8_Attribute>::attributeChangeFactory() {
	return new UInt8Changer(attribute);
}

template<>
AttributeChanger *  TypezedAttributeHandler<ZCL_uint16_Attribute>::attributeChangeFactory() {
	return new UInt16Changer(attribute);
}

template<>
AttributeChanger *  TypezedAttributeHandler<ZCL_enum8bit_Attribute>::attributeChangeFactory() {
	return new Enum8BitChanger(attribute);
}

template<>
AttributeChanger *  TypezedAttributeHandler<ZCL_int16_Attribute>::attributeChangeFactory() {
	return new Int16Changer(attribute);
}

template<>
AttributeChanger *  TypezedAttributeHandler<ZCL_uint24_Attribute>::attributeChangeFactory() {
	return new UInt24Changer(attribute);
}

}
