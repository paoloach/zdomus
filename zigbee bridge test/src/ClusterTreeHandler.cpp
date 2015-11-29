/*
 * ClusterTreeHandler.cpp
 *
 *  Created on: 28/lug/2014
 *      Author: Paolo Achdjian
 */

#include "ClusterTreeHandler.h"
#include "zcl/attributeTypes/ZCLuint8Attribute.h"
#include "zcl/attributeTypes/ZCLuint16Attribute.h"
#include "zcl/attributeTypes/ZCLuint24Attribute.h"
#include "zcl/attributeTypes/ZCLuint32Attribute.h"
#include "zcl/attributeTypes/ZCLuint48Attribute.h"
#include "zcl/attributeTypes/ZCLint8Attribute.h"
#include "zcl/attributeTypes/ZCLint16Attribute.h"
#include "zcl/attributeTypes/ZCLint24Attribute.h"
#include "zcl/attributeTypes/ZCLint32Attribute.h"
#include "zcl/attributeTypes/ZCLstringAttribute.h"
#include "zcl/attributeTypes/ZCLOctetString.h"
#include "zcl/attributeTypes/ZCLbitmap8bitAttribute.h"
#include "zcl/attributeTypes/ZCLBitmap16bitAttribute.h"
#include "zcl/attributeTypes/ZCLBitmap32bitAttribute.h"
#include "zcl/attributeTypes/ZCLbooleanAttribute.h"
#include "zcl/attributeTypes/ZCLenum8bitAttribute.h"
#include "zcl/attributeTypes/ZCLIEEEAddressAttribute.h"
#include "zcl/attributeTypes/ZCLUTCTime.h"

using std::shared_ptr;
using std::make_shared;
using std::dynamic_pointer_cast;

namespace zigbee {

    ClusterTreeHandler::ClusterTreeHandler(std::shared_ptr<Cluster> &cluster) :
            cluster(cluster), popupMenu(nullptr), widgeItem(nullptr) {

    }

    bool ClusterTreeHandler::operator==(const QTreeWidgetItem *widget) const {
        return widgeItem == widget;
    }

    template<typename _TP_attribute>
    shared_ptr<AttributeHandler> getHandler(shared_ptr<ZCLAttribute> attribute, const std::string name, QTreeWidgetItem *parentItem) {
        auto attributeChild = std::dynamic_pointer_cast<_TP_attribute>(attribute);
        auto typezedAttributeHandler = make_shared<TypezedAttributeHandler<_TP_attribute> >(attributeChild, name, parentItem);
        return dynamic_pointer_cast<AttributeHandler>(typezedAttributeHandler);
    }

    void ClusterTreeHandler::createAttributesHandler(std::shared_ptr<Cluster> cluster, QTreeWidgetItem *parentItem) {
        shared_ptr<AttributeHandler> attributeHandler;
        auto attributes = cluster->getAttributes();

        for (auto &attributeDef : attributes) {
            std::shared_ptr<ZCLAttribute> attribute = cluster->getAttribute(attributeDef.id);
            switch (attributeDef.type) {
                case ZCLTypeDataType::ZCLType8bitBitmap:
                    attributeHandler = getHandler<ZCL_bitmap8bit_Attribute>(attribute, attributeDef.name, parentItem);
                    break;
                case ZCLTypeDataType::ZCLType16bitBitmap:
                    attributeHandler = getHandler<ZCLBitmap16bitAttribute>(attribute, attributeDef.name, parentItem);
                    break;
                case ZCLTypeDataType::ZCLType32bitBitmap:
                    attributeHandler = getHandler<ZCLBitmap32bitAttribute>(attribute, attributeDef.name, parentItem);
                    break;
                case ZCLTypeDataType::ZCLTypeBool:
                    attributeHandler = getHandler<ZCL_boolean_Attribute>(attribute, attributeDef.name, parentItem);
                    break;
                case ZCLTypeDataType::ZCLTypeenum8:
                    attributeHandler = getHandler<ZCL_enum8bit_Attribute>(attribute, attributeDef.name, parentItem);
                    break;
                case ZCLTypeDataType::ZCLTypeIEEEaddress:
                    attributeHandler = getHandler<ZCLIEEEAddressAttribute>(attribute, attributeDef.name, parentItem);
                    break;
                case ZCLTypeDataType::ZCLTypeSInt8:
                    attributeHandler = getHandler<ZCLint8Attribute>(attribute, attributeDef.name, parentItem);
                    break;
                case ZCLTypeDataType::ZCLTypeSInt16:
                    attributeHandler = getHandler<ZCL_int16_Attribute>(attribute, attributeDef.name, parentItem);
                    break;
                case ZCLTypeDataType::ZCLTypeSInt24:
                    attributeHandler = getHandler<ZCLint24Attribute>(attribute, attributeDef.name, parentItem);
                    break;
                case ZCLTypeDataType::ZCLTypeSInt32:
                    attributeHandler = getHandler<ZCL_int32_Attribute>(attribute, attributeDef.name, parentItem);
                    break;
                case ZCLTypeDataType::ZCLTypeStringOctect:
                    attributeHandler = getHandler<ZCLOctetString>(attribute, attributeDef.name, parentItem);
                    break;
                case ZCLTypeDataType::ZCLTypeStringChar:
                    attributeHandler = getHandler<ZCL_string_Attribute>(attribute, attributeDef.name, parentItem);
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
                case ZCLTypeDataType::ZCLTypeUInt32:
                    attributeHandler = getHandler<ZCL_uint32_Attribute>(attribute, attributeDef.name, parentItem);
                    break;
                case ZCLTypeDataType::ZCLTypeUInt48:
                    attributeHandler = getHandler<ZCLuint48Attribute>(attribute, attributeDef.name, parentItem);
                    break;
                case ZCLTypeDataType::ZCLTypeUTCTime:
                    attributeHandler = getHandler<ZCLUTCTime>(attribute, attributeDef.name, parentItem);
                    break;
                default:
                    std::cout << __FILE__ << ":" << __LINE__ << ": Invalid attribute: " << attributeDef.type << std::endl;
                    throw std::exception();
            }
            attributesHandler.push_back(attributeHandler);
        }
    }

    void ClusterTreeHandler::insert(QTreeWidgetItem *parentItem) {
        QString clusterName = "cluster: " + QString::number(cluster->getId().getId()) + "(" + QString::fromStdString(cluster->getClusterName()) + ")";
        QTreeWidgetItem *clusterItem = new QTreeWidgetItem(parentItem);
        clusterItem->setText(0, clusterName);

        createAttributesHandler(cluster, clusterItem);
        setContextualMenuI(clusterItem);
    }

    void ClusterTreeHandler::setContextualMenuI(QTreeWidgetItem *parentItem) {
        if (!cluster->getCommands().empty()) {
            TreeItemSignalMap::getHistance().add(parentItem, [this](){this->click();});
            widgeItem = parentItem;
        }
    }

    void ClusterTreeHandler::click() {
        QTreeWidget *parent = widgeItem->treeWidget();
        QRect rect = parent->visualItemRect(widgeItem);
        QPoint pos = parent->mapToGlobal(rect.topLeft());
        if (popupMenu == nullptr) {
            std::vector<Cluster::CommandDef> commands = cluster->getCommands();
            popupMenu = new QMenu();
            for (unsigned int index = 0; index < commands.size(); index++) {
                QAction *action = popupMenu->addAction(QString::fromStdString(commands[index].name));
                action->setData(QVariant(index));
                connect(action, SIGNAL(triggered()), this, SLOT(cmd()));
            }
        }
        popupMenu->popup(pos);
    }

    void ClusterTreeHandler::cmd() {
        QAction *action = dynamic_cast<QAction *>(sender());
        if (action != nullptr) {
            std::vector<Cluster::CommandDef> commands = cluster->getCommands();
            int index = action->data().toInt();
            if (index >= 0 && (unsigned) index < commands.size()) {
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
