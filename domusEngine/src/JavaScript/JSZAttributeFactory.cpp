/*
 * JSZAttributeFactory.cpp
 *
 *  Created on: 10/gen/2015
 *      Author: Paolo Achdjian
 */

#include <zigbee/ZigbeeDevice.h>
#include <zcl/ClusterTypeFactory.h>
#include <zcl/ZCLAttribute.h>

#include "JSZAttributeFactory.h"
#include "../ZigbeeData/ZDevices.h"

namespace zigbee {

    using std::make_shared;

    JSZAttributeFactory::JSZAttributeFactory() {

    }

    JSZAttributeFactory::~JSZAttributeFactory() {
    }

    void JSZAttributeFactory::init(const std::shared_ptr<ZDevices> &zDevices, const std::shared_ptr<ZigbeeDevice> &zigbeeDevice,
                                   const std::shared_ptr<ClusterTypeFactory> &clusterFactory) {
        jsZAttribute8BitBitmap = make_shared<JSZAttribute8BitBitmap>(zDevices, zigbeeDevice, clusterFactory);
        jsZAttribute16BitBitmap = make_shared<JSZAttribute16BitBitmap>(zDevices, zigbeeDevice, clusterFactory);
        jsZAttribute32BitBitmap = make_shared<JSZAttribute32BitBitmap>(zDevices, zigbeeDevice, clusterFactory);
        jsZAttributeBool = make_shared<JSZAttributeBool>(zDevices, zigbeeDevice, clusterFactory);
        jsZAttributeIEEEAddress = make_shared<JSZAttributeIEEEAddress>(zDevices, zigbeeDevice, clusterFactory);
        jsZAttributeInt8 = make_shared<JSZAttributeInt8>(zDevices, zigbeeDevice, clusterFactory);
        jsZAttributeInt16 = make_shared<JSZAttributeInt16>(zDevices, zigbeeDevice, clusterFactory);
        jsZAttributeInt24 = make_shared<JSZAttributeInt24>(zDevices, zigbeeDevice, clusterFactory);
        jsZAttributeInt32 = make_shared<JSZAttributeInt32>(zDevices, zigbeeDevice, clusterFactory);
        jsZAttributeOctectString = make_shared<JSZAttributeOctectString>(zDevices, zigbeeDevice, clusterFactory);
        jsZAttributeString = make_shared<JSZAttributeString>(zDevices, zigbeeDevice, clusterFactory);
        jsZAttribute8BitEnum = make_shared<JSZAttribute8BitEnum>(zDevices, zigbeeDevice, clusterFactory);

        jsZAttributeUInt8 = make_shared<JSZAttributeUint8>(zDevices, zigbeeDevice, clusterFactory);
        jsZAttributeUInt16 = make_shared<JSZAttributeUint16>(zDevices, zigbeeDevice, clusterFactory);
        jsZAttributeUInt24 = make_shared<JSZAttributeUint24>(zDevices, zigbeeDevice, clusterFactory);
        jsZAttributeUInt32 = make_shared<JSZAttributeUint32>(zDevices, zigbeeDevice, clusterFactory);
        jsZAttributeUInt48 = make_shared<JSZAttributeUint48>(zDevices, zigbeeDevice, clusterFactory);

    }

    void JSZAttributeFactory::initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::Object> &global) {
        jsZAttribute8BitBitmap->initJsObjectsTemplate(isolate, global);
        jsZAttribute16BitBitmap->initJsObjectsTemplate(isolate, global);
        jsZAttribute32BitBitmap->initJsObjectsTemplate(isolate, global);
        jsZAttributeBool->initJsObjectsTemplate(isolate, global);
        jsZAttributeIEEEAddress->initJsObjectsTemplate(isolate, global);
        jsZAttributeInt8->initJsObjectsTemplate(isolate, global);
        jsZAttributeInt16->initJsObjectsTemplate(isolate, global);
        jsZAttributeInt24->initJsObjectsTemplate(isolate, global);
        jsZAttributeInt32->initJsObjectsTemplate(isolate, global);
        jsZAttributeOctectString->initJsObjectsTemplate(isolate, global);
        jsZAttributeString->initJsObjectsTemplate(isolate, global);

        jsZAttribute8BitEnum->initJsObjectsTemplate(isolate, global);

        jsZAttributeUInt8->initJsObjectsTemplate(isolate, global);
        jsZAttributeUInt16->initJsObjectsTemplate(isolate, global);
        jsZAttributeUInt24->initJsObjectsTemplate(isolate, global);
        jsZAttributeUInt32->initJsObjectsTemplate(isolate, global);
        jsZAttributeUInt48->initJsObjectsTemplate(isolate, global);
    }

    v8::Local<v8::Object> JSZAttributeFactory::createAttributeInstance(v8::Isolate *isolate, std::shared_ptr<ZCLAttribute> attribute) {
        switch (attribute->getZCLType()) {
            case ZCLTypeDataType::ZCLType8bitBitmap:
                return jsZAttribute8BitBitmap->createInstance(isolate, attribute);
            case ZCLTypeDataType::ZCLTypeIEEEaddress:
                return jsZAttributeIEEEAddress->createInstance(isolate, attribute);
            case ZCLTypeDataType::ZCLTypeBool:
                return jsZAttributeBool->createInstance(isolate, attribute);
            case ZCLTypeDataType::ZCLTypeenum8:
                return jsZAttribute8BitEnum->createInstance(isolate, attribute);

            case ZCLTypeDataType::ZCLTypeSInt16:
                return jsZAttributeInt16->createInstance(isolate, attribute);
            case ZCLTypeDataType::ZCLTypeStringChar:
                return jsZAttributeString->createInstance(isolate, attribute);
            case ZCLTypeDataType::ZCLTypeUInt24:
                return jsZAttributeUInt24->createInstance(isolate, attribute);
            case ZCLTypeDataType::ZCLTypeUInt16:
                return jsZAttributeUInt16->createInstance(isolate, attribute);
            case ZCLTypeDataType::ZCLTypeUInt8:
                return jsZAttributeUInt8->createInstance(isolate, attribute);
            default:
                return v8::Object::New(isolate);
        }
    }

    void JSZAttributeFactory::resetPersistences() {
        jsZAttributeIEEEAddress->resetPersistence();
        jsZAttributeBool->resetPersistence();
        jsZAttribute8BitEnum->resetPersistence();
        jsZAttribute8BitBitmap->resetPersistence();
        jsZAttributeInt16->resetPersistence();
        jsZAttributeUInt16->resetPersistence();
        jsZAttributeUInt8->resetPersistence();
        jsZAttributeUInt24->resetPersistence();
        jsZAttributeString->resetPersistence();
    }

} /* namespace zigbee */
