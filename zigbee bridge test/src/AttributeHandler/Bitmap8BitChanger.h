/*
 * Bitmap8BitChanger.h
 *
 *  Created on: 22/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef BITMAP8BITCHANGER_H_
#define BITMAP8BITCHANGER_H_

#include <QtCore/qobject.h>
#include <QtGui/qdialog.h>

#include <memory>

#include <zcl/attributeTypes/ZCLbitmap8bitAttribute.h>
#include "AttributeChanger.h"
#include "../../ui_changeBitmap8Bit.h"

namespace zigbee {

class Bitmap8BitChanger : public QObject , public AttributeChanger{
	Q_OBJECT
public:
	Bitmap8BitChanger(std::shared_ptr<ZCL_bitmap8bit_Attribute> attribute);
	virtual ~Bitmap8BitChanger();
public:
	virtual void show(QDialog * dialog);
private slots:
	void close();
	void apply();
private:
	Ui::Bitmap8BitChanger bitmap8BitChanger;
	QDialog * parent;
	std::shared_ptr<ZCL_bitmap8bit_Attribute> attribute;
};

} /* namespace zigbee */

#endif /* BITMAP8BITCHANGER_H_ */
