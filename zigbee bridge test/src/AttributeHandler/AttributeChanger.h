/*
 * AttributeChanger.h
 *
 *  Created on: 20/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef ATTRIBUTECHANGER_H_
#define ATTRIBUTECHANGER_H_

#include <QtGui/QDialog>

namespace zigbee {

class AttributeChanger {
public:
	AttributeChanger();
	virtual ~AttributeChanger();

public:
	virtual void show(QDialog * dialog)=0;
};

} /* namespace zigbee */

#endif /* ATTRIBUTECHANGER_H_ */
