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

    using std::make_unique;


    void JSZAttributeFactory::init(SingletonObjects * singletonObjects, JSCallbackFifo & jsCallbackFifo) {

        std::array<std::unique_ptr<JSZAttribute>, 17> data = {{make_unique<JSZAttribute8BitBitmap>(singletonObjects,jsCallbackFifo),
                              make_unique<JSZAttribute16BitBitmap>(singletonObjects,jsCallbackFifo),
                              make_unique<JSZAttribute32BitBitmap>(singletonObjects,jsCallbackFifo),
                              make_unique<JSZAttributeBool>(singletonObjects,jsCallbackFifo),
                              make_unique<JSZAttributeIEEEAddress>(singletonObjects,jsCallbackFifo),
                              make_unique<JSZAttributeInt8>(singletonObjects,jsCallbackFifo),
                              make_unique<JSZAttributeInt16>(singletonObjects,jsCallbackFifo),
                              make_unique<JSZAttributeInt24>(singletonObjects,jsCallbackFifo),
                              make_unique<JSZAttributeInt32>(singletonObjects,jsCallbackFifo),
                              make_unique<JSZAttributeOctectString>(singletonObjects,jsCallbackFifo),
                              make_unique<JSZAttributeString>(singletonObjects,jsCallbackFifo),
                              make_unique<JSZAttribute8BitEnum>(singletonObjects,jsCallbackFifo),
                              make_unique<JSZAttributeUint8>(singletonObjects,jsCallbackFifo),
                              make_unique<JSZAttributeUint16>(singletonObjects,jsCallbackFifo),
                              make_unique<JSZAttributeUint24>(singletonObjects,jsCallbackFifo),
                              make_unique<JSZAttributeUint32>(singletonObjects,jsCallbackFifo),
                              make_unique<JSZAttributeUint48>(singletonObjects,jsCallbackFifo)
                      }
        };

        attributes = std::move(data);

    }

    void JSZAttributeFactory::initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::Object> &global) {
        for (auto &attribute: attributes) {
            attribute->initJsObjectsTemplate(isolate, global);
        }
    }

    v8::Local<v8::Object> JSZAttributeFactory::createAttributeInstance(v8::Isolate *isolate, ZCLAttribute * attribute) {
        for (auto &jszlAttribute: attributes) {
            if (jszlAttribute->getZCLType() == attribute->getZCLType()) {
                return jszlAttribute->createInstance(isolate, attribute);
            }
        }
        return v8::Object::New(isolate);
    }

    void JSZAttributeFactory::resetPersistences() {
        for (auto &attribute: attributes) {
            attribute->resetPersistence();
        }
    }

} /* namespace zigbee */
