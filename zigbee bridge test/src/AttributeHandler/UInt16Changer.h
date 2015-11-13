/*
 * uint16Changer.h
 *
 *  Created on: 22/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef UINT16CHANGER_H_
#define UINT16CHANGER_H_

#include <QtCore/qobject.h>
#include <QtGui/qdialog.h>

#include <memory>

#include <zcl/attributeTypes/ZCLuint16Attribute.h>
#include "AttributeChanger.h"
#include "../../ui_changeUInt8.h"

namespace zigbee {

class UInt16Changer: public QObject , public AttributeChanger{
	Q_OBJECT
public:
	UInt16Changer(std::shared_ptr<ZCL_uint16_Attribute> attribute);
	virtual ~UInt16Changer();
public:
	virtual void show(QDialog * dialog);
private slots:
	void close();
	void apply();
private:
	Ui::UInt8Changer changerUInt16;
	QDialog * parent;
	std::shared_ptr<ZCL_uint16_Attribute> attribute;
};

} /* namespace zigbee */

#endif /* UINT16CHANGER_H_ */
