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


    void JSZAttributeFactory::init(ZDevices *zDevices, ZigbeeDevice *zigbeeDevice,
                                   ClusterTypeFactory *clusterFactory) {

        std::array<std::unique_ptr<JSZAttribute>, 17> data = {{make_unique<JSZAttribute8BitBitmap>(zDevices, zigbeeDevice, clusterFactory),
                              make_unique<JSZAttribute16BitBitmap>(zDevices, zigbeeDevice, clusterFactory),
                              make_unique<JSZAttribute32BitBitmap>(zDevices, zigbeeDevice, clusterFactory),
                              make_unique<JSZAttributeBool>(zDevices, zigbeeDevice, clusterFactory),
                              make_unique<JSZAttributeIEEEAddress>(zDevices, zigbeeDevice, clusterFactory),
                              make_unique<JSZAttributeInt8>(zDevices, zigbeeDevice, clusterFactory),
                              make_unique<JSZAttributeInt16>(zDevices, zigbeeDevice, clusterFactory),
                              make_unique<JSZAttributeInt24>(zDevices, zigbeeDevice, clusterFactory),
                              make_unique<JSZAttributeInt32>(zDevices, zigbeeDevice, clusterFactory),
                              make_unique<JSZAttributeOctectString>(zDevices, zigbeeDevice, clusterFactory),
                              make_unique<JSZAttributeString>(zDevices, zigbeeDevice, clusterFactory),
                              make_unique<JSZAttribute8BitEnum>(zDevices, zigbeeDevice, clusterFactory),
                              make_unique<JSZAttributeUint8>(zDevices, zigbeeDevice, clusterFactory),
                              make_unique<JSZAttributeUint16>(zDevices, zigbeeDevice, clusterFactory),
                              make_unique<JSZAttributeUint24>(zDevices, zigbeeDevice, clusterFactory),
                              make_unique<JSZAttributeUint32>(zDevices, zigbeeDevice, clusterFactory),
                              make_unique<JSZAttributeUint48>(zDevices, zigbeeDevice, clusterFactory)
                      }
        };

        attributes = std::move(data);

    }

    void JSZAttributeFactory::initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::Object> &global) {
        for (auto &attribute: attributes) {
            attribute->initJsObjectsTemplate(isolate, global);
        }
    }

    v8::Local<v8::Object> JSZAttributeFactory::createAttributeInstance(v8::Isolate *isolate, std::shared_ptr<ZCLAttribute> attribute) {
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
