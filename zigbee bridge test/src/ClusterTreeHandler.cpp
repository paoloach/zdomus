/*
 * ClusterTreeHandler.cpp
 *
 *  Created on: 28/lug/2014
 *      Author: Paolo Achdjian
 */

#include "ClusterTreeHandler.h"
#include "zcl/Cluster.h"
#include "zcl/attributeTypes/ZCLuint8Attribute.h"
#include "zcl/attributeTypes/ZCLuint16Attribute.h"
#include "zcl/attributeTypes/ZCLuint24Attribute.h"
#include "zcl/attributeTypes/ZCLint16Attribute.h"
#include "zcl/attributeTypes/ZCLstringAttribute.h"
#include "zcl/attributeTypes/ZCLbitmap8bitAttribute.h"
#include "zcl/attributeTypes/ZCLbooleanAttribute.h"
#include "zcl/attributeTypes/ZCLenum8bitAttribute.h"
#include "zcl/attributeTypes/ZCLIEEEAddressAttribute.h"

#include <iostream>

namespace zigbee {

ClusterTreeHandler::ClusterTreeHandler(std::shared_ptr<Cluster> cluster) :
		cluster(cluster), popupMenu(nullptr), widgeItem(nullptr) {

}

ClusterTreeHandler::~ClusterTreeHandler() {
}

bool ClusterTreeHandler::operator==(const QTreeWidgetItem * widget) const{
	return widgeItem == widget;
}

template<typename _TP_attribute>
std::shared_ptr<AttributeHandler> getHandler(std::shared_ptr<ZCLAttribute> attribute, const std::string name, QTreeWidgetItem * parentItem) {
	std::shared_ptr<_TP_attribute> attributeChild = std::dynamic_pointer_cast<_TP_attribute>(attribute);

	std::shared_ptr<TypezedAttributeHandler<_TP_attribute> > typezedAttributeHandler = std::make_shared<TypezedAttributeHandler<_TP_attribute> >(attributeChild, name, parentItem);
	return std::dynamic_pointer_cast<AttributeHandler>(typezedAttributeHandler);
}

void ClusterTreeHandler::createAttributesHandler(std::shared_ptr<Cluster> cluster, QTreeWidgetItem * parentItem) {
	std::shared_ptr<AttributeHandler> attributeHandler;
	auto attributes = cluster->getAttributes();

	for (auto attributeDef : attributes) {
		std::shared_ptr<ZCLAttribute> attribute = cluster->getAttribute(attributeDef.id);
		switch (attributeDef.type) {
		case ZCLTypeDataType::ZCLTypeenum8:
			attributeHandler = getHandler<ZCL_enum8bit_Attribute>(attribute, attributeDef.name, parentItem);
			break;
		case ZCLTypeDataType::ZCLTypeUInt8:
			attributeHandler = getHandler<ZCL_uint8_Attribute>(attribute, attributeDef.name, parentItem);
			break;
		case ZCLTypeDataType::ZCLTypeUInt16:
			attributeHandler = getHandler<ZCL_uint16_Attribute>(attribute, attributeDef.name, parentItem);
			break;
		case ZCLTypeDataType::ZCLTypeUInt24:
			attributeHandler = getHandler<ZCL_uint24_Attribute>(attribute, attributeDef.name, parentItem);
			break;
		case ZCLTypeDataType::ZCLTypeSInt16:
			attributeHandler = getHandler<ZCL_int16_Attribute>(attribute, attributeDef.name, parentItem);
			break;
		case ZCLTypeDataType::ZCLType8bitBitmap:
			attributeHandler = getHandler<ZCL_bitmap8bit_Attribute>(attribute, attributeDef.name, parentItem);
			break;
		case ZCLTypeDataType::ZCLTypeStringChar:
			attributeHandler = getHandler<ZCL_string_Attribute>(attribute, attributeDef.name, parentItem);
			break;
		case ZCLTypeDataType::ZCLTypeBool:
			attributeHandler = getHandler<ZCL_boolean_Attribute>(attribute, attributeDef.name, parentItem);
			break;
		case ZCLTypeDataType::ZCLTypeIEEEaddress:
			attributeHandler = getHandler<ZCLIEEEAddressAttribute>(attribute, attributeDef.name, parentItem);
			break;
		default:
			std::cout << __FILE__ << ":" << __LINE__ << ": Invalid attribute: " << attributeDef.type << std::endl;
			throw std::exception();
		}
		attributesHandler.push_back(attributeHandler);
	}
}

void ClusterTreeHandler::insert(QTreeWidgetItem * parentItem) {
	QString clusterName = "cluster: " + QString::number(cluster->getId().getId()) + "(" + QString::fromStdString(cluster->getClusterName()) + ")";
	QTreeWidgetItem * clusterItem = new QTreeWidgetItem(parentItem);
	clusterItem->setText(0, clusterName);

	createAttributesHandler(cluster, clusterItem);
	setContextualMenuI(clusterItem);
}

void ClusterTreeHandler::setContextualMenuI(QTreeWidgetItem * parentItem) {
	if (cluster->getCommands().empty() == false) {
		TreeItemSignalMap::getHistance().add(parentItem, boost::bind(&ClusterTreeHandler::click, this));
		widgeItem = parentItem;
	}
}

void ClusterTreeHandler::click() {
	QTreeWidget * parent = widgeItem->treeWidget();
	QRect rect = parent->visualItemRect(widgeItem);
	QPoint pos = parent->mapToGlobal(rect.topLeft());
	if (popupMenu == nullptr) {
		std::vector<Cluster::CommandDef> commands = cluster->getCommands();
		popupMenu = new QMenu();
		for (int index = 0; index < commands.size(); index++) {
			QAction * action = popupMenu->addAction(QString::fromStdString(commands[index].name));
			action->setData(QVariant(index));
			connect(action, SIGNAL(triggered ( )), this, SLOT(cmd()));
		}
	}
	popupMenu->popup(pos);
}

void ClusterTreeHandler::cmd() {
	QAction * action = dynamic_cast<QAction *>(sender());
	if (action != nullptr) {
		std::vector<Cluster::CommandDef> commands = cluster->getCommands();
		int index = action->data().toInt();
		if (index >= 0 && index < commands.size()) {
			auto command = commands[index];
			if (command.params.empty()) {
				command.cmd(std::vector<uint8_t>());
			} else {
				insertCmdParams.setup(command.params);
				insertCmdParams.exec();
				if (insertCmdParams.result() == QDialog::Accepted) {
					command.cmd(insertCmdParams.getCmdData());
				}
			}
		}
	}

}

} /* namespace zigbee */
