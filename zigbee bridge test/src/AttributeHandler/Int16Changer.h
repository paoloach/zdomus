/*
 * int16Changer.h
 *
 *  Created on: 22/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef INT16CHANGER_H_
#define INT16CHANGER_H_

#include <QtCore/qobject.h>
#include <QtGui/qdialog.h>

#include <memory>

#include <zcl/attributeTypes/ZCLint16Attribute.h>
#include "AttributeChanger.h"
#include "../../ui_changeUInt8.h"

namespace zigbee {

class Int16Changer: public QObject , public AttributeChanger{
	Q_OBJECT
public:
	Int16Changer(std::shared_ptr<ZCL_int16_Attribute> attribute);
	virtual ~Int16Changer();
public:
	virtual void show(QDialog * dialog);
private slots:
	void close();
	void apply();
private:
	Ui::UInt8Changer changerInt16;
	QDialog * parent;
	std::shared_ptr<ZCL_int16_Attribute> attribute;
};

} /* namespace zigbee */

#endif /* UINT16CHANGER_H_ */
