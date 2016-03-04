/*
 * AttributeHandler.h
 *
 *  Created on: 08/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef ATTRIBUTEHANDLER_H_
#define ATTRIBUTEHANDLER_H_

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>

#include <QtGui/QTreeWidgetItem>
#include <QtGui/QMenu>

#include "zcl/ZCLAttribute.h"
#include "TreeItemSignalMap.h"
#include "AttributeHandler/AttributeChanger.h"

namespace zigbee {

class AttributeHandler: public QObject {
Q_OBJECT
public:
	AttributeHandler(std::experimental::string_view  name, QTreeWidgetItem * parent);
	virtual ~AttributeHandler() {
		delete popupMenu;
	}
public:
	std::string getValue();
	void click();
	void update();

protected:
	virtual std::string getAttributeValue() = 0;
	virtual ZCLAttribute::Status getStatus() = 0;
	virtual void requestValue() = 0;
	virtual bool isReadOnly() = 0;
	virtual void typedChangeValue()=0;
private slots:
	void changeValue();
	void updateValue();

protected:
	std::experimental::string_view  name;
	QTreeWidgetItem * parent;
	QTreeWidgetItem * item;
	QMenu * popupMenu;
};

template<typename _Tp>
class TypezedAttributeHandler: public AttributeHandler {
public:
	TypezedAttributeHandler(std::shared_ptr<_Tp> attribute, std::experimental::string_view name, QTreeWidgetItem * parent) :
			AttributeHandler(name, parent), attribute(attribute) {
        if (!attribute){
            std::cerr << "undefined " << std::endl;
        } else {
            item->setText(0, attribute->getName().data());
        }

		this->attribute->onChange([this]{update();});
		attributeChanger = nullptr;
	}

	virtual ~TypezedAttributeHandler() {
		delete attributeChanger;
	}
private:
	std::string getAttributeValue() {
		return boost::lexical_cast<std::string>(attribute);
	}

	virtual ZCLAttribute::Status getStatus() {
		return attribute->getStatus();
	}

	virtual void requestValue() {
		attribute->requestValue();
	}

	virtual bool isReadOnly() {
		return attribute->isReadOnly();
	}

	virtual void typedChangeValue() {
		if (attributeChanger == nullptr) {
			attributeChanger = attributeChangeFactory();
		}
		if (attributeChanger != nullptr) {
			QTreeWidget * parent = item->treeWidget();
			QRect rect = parent->visualItemRect(item);
			QPoint pos = parent->mapToGlobal(rect.topLeft());
			QDialog * frame = new QDialog(parent);
			attributeChanger->show(frame);
			frame->move(pos);
			frame->show();
		}
	}

	AttributeChanger * attributeChangeFactory() {
		return nullptr;
	}
protected:
	std::shared_ptr<_Tp> attribute;
	AttributeChanger * attributeChanger;
};

} /* namespace zigbee */

#endif /* ATTRIBUTEHANDLER_H_ */
