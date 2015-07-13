/*
 * QTreeBindTableSrc.h
 *
 *  Created on: 30/mar/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_QTREEBINDTABLESRC_H_
#define SRC_QTREEBINDTABLESRC_H_

#include <zigbee/EndpointID.h>
#include <QtGui/qtreewidget.h>
#include "../ExtAddress.h"

namespace zigbee {

class QTreeBindTableSrc : public QTreeWidgetItem{
public:
	QTreeBindTableSrc( QTreeWidgetItem* parent, uint8_t * srcAddr, int srcDP);
	virtual ~QTreeBindTableSrc();

	const ExtAddress& getAddr() const {
		return addr;
	}

	EndpointID getEndpoint() const {
		return endpoint;
	}

public:

private:
	ExtAddress addr;
	EndpointID endpoint;
};

} /* namespace zigbee */

#endif /* SRC_QTREEBINDTABLESRC_H_ */
