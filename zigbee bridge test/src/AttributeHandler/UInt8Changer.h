/*
 * uint8Changer.h
 *
 *  Created on: 22/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef UINT8CHANGER_H_
#define UINT8CHANGER_H_

#include <QtCore/qobject.h>
#include <QtGui/qdialog.h>

#include <memory>

#include <zcl/attributeTypes/ZCLuint8Attribute.h>
#include "AttributeChanger.h"
#include "../../ui_changeUInt8.h"

namespace zigbee {

class UInt8Changer: public QObject , public AttributeChanger{
	Q_OBJECT
public:
	UInt8Changer(std::shared_ptr<ZCL_uint8_Attribute> attribute);
	virtual ~UInt8Changer();
public:
	virtual void show(QDialog * dialog);
private slots:
	void close();
	void apply();
private:
	Ui::UInt8Changer changerUInt8;
	QDialog * parent;
	std::shared_ptr<ZCL_uint8_Attribute> attribute;
};

} /* namespace zigbee */

#endif /* UINT8CHANGER_H_ */
