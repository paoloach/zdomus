/*
 * StringAttributeChanger.h
 *
 *  Created on: 21/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef STRINGATTRIBUTECHANGER_H_
#define STRINGATTRIBUTECHANGER_H_
#include <QtCore/qobject.h>
#include <QtGui/qdialog.h>

#include <memory>

#include <zcl/attributeTypes/ZCLstringAttribute.h>
#include "AttributeChanger.h"
#include "../../ui_changeString.h"

namespace zigbee {

class StringAttributeChanger  : public QObject , public AttributeChanger{
	Q_OBJECT
public:
	StringAttributeChanger(std::shared_ptr<ZCL_string_Attribute> attribute);
	virtual ~StringAttributeChanger();
public:
	virtual void show(QDialog * dialog);
private slots:
	void close();
	void apply();
private:
	Ui::StringChanger stringChanger;
	QDialog * parent;
	std::shared_ptr<ZCL_string_Attribute> attribute;
};

} /* namespace zigbee */

#endif /* STRINGATTRIBUTECHANGER_H_ */
