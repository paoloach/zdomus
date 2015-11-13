/*
 * uint24Changer.h
 *
 *  Created on: 22/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef UINT24CHANGER_H_
#define UINT24CHANGER_H_

#include <QtCore/qobject.h>
#include <QtGui/qdialog.h>

#include <memory>

#include <zcl/attributeTypes/ZCLuint24Attribute.h>
#include "AttributeChanger.h"
#include "../../ui_changeUInt8.h"

namespace zigbee {

class UInt24Changer: public QObject , public AttributeChanger{
	Q_OBJECT
public:
	UInt24Changer(std::shared_ptr<ZCL_uint24_Attribute> attribute);
	virtual ~UInt24Changer();
public:
	virtual void show(QDialog * dialog);
private slots:
	void close();
	void apply();
private:
	Ui::UInt8Changer changerUInt24;
	QDialog * parent;
	std::shared_ptr<ZCL_uint24_Attribute> attribute;
};

} /* namespace zigbee */

#endif /* UINT16CHANGER_H_ */
