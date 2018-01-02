//
// Created by paolo on 10/05/16.
//

#include <memory>
#include <zigbee/ZigbeeDevice.h>
#include "ShowAttributeFactory.h"
#include "ShowAttribute.h"

Pistache::Rest::Route::Result zigbee::http::ShowAttributeFactory::operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &&response) {

    auto showAttribute = std::make_unique<ShowAttribute>(singletons, request, std::move(response));
    if (!showAttribute->key.attributesId.empty()) {
        AttributesKey key(showAttribute->key);
        singletons->getZigbeeDevice()->registerForAttributesValue(key, std::move(showAttribute));
    }

    return Pistache::Rest::Route::Result::Ok;
}
