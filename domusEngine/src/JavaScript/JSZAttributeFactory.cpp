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

void JSZAttributeFactory::init(const std::shared_ptr<ZDevices>& zDevices, const std::shared_ptr<ZigbeeDevice>& zigbeeDevice,
		const std::shared_ptr<ClusterTypeFactory>& clusterFactory) {
	jsZAttributeIEEEAddress = make_shared<JSZAttributeIEEEAddress>(zDevices, zigbeeDevice, clusterFactory);
	jsZAttributeBool = make_shared<JSZAttributeBool>(zDevices, zigbeeDevice, clusterFactory);
	jsZAttribute8BitEnum = make_shared<JSZAttribute8BitEnum>(zDevices, zigbeeDevice, clusterFactory);
	jsZAttribute8BitBitmap = make_shared<JSZAttribute8BitBitmap>(zDevices, zigbeeDevice, clusterFactory);
	jsZAttributeInt16 = make_shared<JSZAttributeInt16>(zDevices, zigbeeDevice, clusterFactory);
	jsZAttributeUInt16 = make_shared<JSZAttributeUint16>(zDevices, zigbeeDevice, clusterFactory);
	jsZAttributeUInt8 = make_shared<JSZAttributeUint8>(zDevices, zigbeeDevice, clusterFactory);
	jsZAttributeUInt24 = make_shared<JSZAttributeUint24>(zDevices, zigbeeDevice, clusterFactory);
	jsZAttributeString = make_shared<JSZAttributeString>(zDevices, zigbeeDevice, clusterFactory);
}

void JSZAttributeFactory::initJsObjectsTemplate(v8::Isolate* isolate, v8::Handle<v8::Object>& global) {
	jsZAttributeIEEEAddress->initJsObjectsTemplate(isolate, global);
	jsZAttributeBool->initJsObjectsTemplate(isolate, global);
	jsZAttribute8BitEnum->initJsObjectsTemplate(isolate, global);
	jsZAttribute8BitBitmap->initJsObjectsTemplate(isolate, global);
	jsZAttributeInt16->initJsObjectsTemplate(isolate, global);
	jsZAttributeUInt16->initJsObjectsTemplate(isolate, global);
	jsZAttributeUInt8->initJsObjectsTemplate(isolate, global);
	jsZAttributeUInt24->initJsObjectsTemplate(isolate, global);
	jsZAttributeString->initJsObjectsTemplate(isolate, global);
}

v8::Local<v8::Object> JSZAttributeFactory::createAttributeInstance(v8::Isolate* isolate, std::shared_ptr<ZCLAttribute> attribute) {
	switch (attribute->getZCLType()) {
	case ZCLTypeDataType::ZCLTypeIEEEaddress:
		return jsZAttributeIEEEAddress->createInstance(isolate, attribute);
	case ZCLTypeDataType::ZCLTypeBool:
		return jsZAttributeBool->createInstance(isolate, attribute);
	case ZCLTypeDataType::ZCLTypeenum8:
		return jsZAttribute8BitEnum->createInstance(isolate, attribute);
	case ZCLTypeDataType::ZCLType8bitBitmap:
		return jsZAttribute8BitBitmap->createInstance(isolate, attribute);
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
