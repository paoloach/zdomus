/*
 * uint8Changer.h
 *
 *  Created on: 22/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef ENUM8BITCHANGER_H_
#define ENUM8BITCHANGER_H_

#include <QtCore/qobject.h>
#include <QtGui/qdialog.h>

#include <memory>

#include <zcl/attributeTypes/ZCLenum8bitAttribute.h>
#include "AttributeChanger.h"
#include "../../ui_changeUInt8.h"

namespace zigbee {

class Enum8BitChanger: public QObject , public AttributeChanger{
	Q_OBJECT
public:
	Enum8BitChanger(std::shared_ptr<ZCL_enum8bit_Attribute> attribute);
	virtual ~Enum8BitChanger();
public:
	virtual void show(QDialog * dialog);
private slots:
	void close();
	void apply();
private:
	Ui::UInt8Changer changerEnum8Bit;
	QDialog * parent;
	std::shared_ptr<ZCL_uint8_Attribute> attribute;
};

} /* namespace zigbee */

#endif /* ENUM8BITCHANGER_H_ */
