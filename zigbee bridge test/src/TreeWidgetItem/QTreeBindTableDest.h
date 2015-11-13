/*
 * QTreeBindTableDest.h
 *
 *  Created on: 27/mar/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_QTREEBINDTABLEDEST_H_
#define SRC_QTREEBINDTABLEDEST_H_

#include <zigbee/NwkAddr.h>
#include <zigbee/EndpointID.h>
#include <zigbee/ClusterID.h>

class QTreeWidgetItem;

namespace zigbee {

class QTreeBindTableDest: public QTreeWidgetItem {
public:
	QTreeBindTableDest(QTreeWidget* parent, NwkAddr destAddr, EndpointID destEP, ClusterID destCluster);
	virtual ~QTreeBindTableDest();

	NwkAddr getAddr() const {
		return addr;
	}

	ClusterID getCluster() const {
		return cluster;
	}

	EndpointID getEndpoint() const {
		return endpoint;
	}

public:

private:
	NwkAddr addr;
	EndpointID endpoint;
	ClusterID cluster;
};

} /* namespace zigbee */

#endif /* SRC_QTREEBINDTABLEDEST_H_ */
