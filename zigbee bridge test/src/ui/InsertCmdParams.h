/*
 * InsertCmdParams.h
 *
 *  Created on: 27/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef INSERTCMDPARAMS_H_
#define INSERTCMDPARAMS_H_
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

#include <vector>
#include <memory>

#include <zcl/CmdParams/ClusterCmdParams.h>
#include "Param.h"

namespace zigbee {

class InsertCmdParams : public QDialog{
	Q_OBJECT
public:
	InsertCmdParams();
	virtual ~InsertCmdParams();
public:
	void setup(std::vector<std::shared_ptr<ClusterCmdParamsBase>> params);

	std::vector<uint8_t> getCmdData();
private slots:
	void ok();
	void cancel();
private:
	QLabel * title;
	QVBoxLayout *verticalLayout;
	QGridLayout *gridLayout;
	QDialogButtonBox *buttonBox;
	QSpacerItem * verticalSpace;
	std::vector<Param *> params;
	std::vector<QWidget *> widgets;
private:
	QWidget * createWidget(std::shared_ptr<ClusterCmdParamsBase> clusterCmdParam);
};

} /* namespace zigbee */

#endif /* INSERTCMDPARAMS_H_ */
