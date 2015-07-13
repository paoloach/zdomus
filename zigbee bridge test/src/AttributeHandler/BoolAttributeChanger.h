/*
 * BoolAttributeChanger.h
 *
 *  Created on: 20/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef BOOLATTRIBUTECHANGER_H_
#define BOOLATTRIBUTECHANGER_H_

#include <QtCore/qobject.h>
#include <QtGui/qdialog.h>

#include <memory>

#include <zcl/attributeTypes/ZCLbooleanAttribute.h>
#include "AttributeChanger.h"
#include "../../ui_changeBool.h"


namespace zigbee {

class BoolAttributeChanger : public QObject , public AttributeChanger{
	Q_OBJECT
public:
	BoolAttributeChanger(std::shared_ptr<ZCL_boolean_Attribute> attribute);
	virtual ~BoolAttributeChanger();
public:
	virtual void show(QDialog * dialog);
private slots:
	void close();
	void apply();
private:
	Ui::ChangeBool changeBool;
	QDialog * parent;
	std::shared_ptr<ZCL_boolean_Attribute> attribute;
};

} /* namespace zigbee */

#endif /* BOOLATTRIBUTECHANGER_H_ */
