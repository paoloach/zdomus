//
// Created by paolo on 10/05/16.
//

#include <memory>
#include "ShowAttributeFactory.h"
#include "ShowAttribute.h"
#include "../../Utils/SingletonObjects.h"


Net::Rest::Route::Result zigbee::http::ShowAttributeFactory::operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter && response) {

    auto showAttribute = std::make_unique<ShowAttribute> (singletons, request, std::move(response));
    if (!showAttribute->key.attributesId.empty()) {
        AttributesKey key(showAttribute->key);
        singletons.getZigbeeDevice()->registerForAttributesValue(key, std::move(showAttribute));
    }

    return Net::Rest::Route::Result::Ok;
}
