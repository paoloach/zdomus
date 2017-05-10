//
// Created by paolo on 10/05/16.
//

#include <memory>
#include "ShowAttributeFactory.h"
#include "ShowAttribute.h"
#include "../../Utils/SingletonObjects.h"


Net::Rest::Route::Result zigbee::http::ShowAttributeFactory::operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter && response) {
    std::unique_ptr<HttpResponseEvent::Event> showAttribute (new ShowAttribute(singletons, request, std::move(response)));
    singletons.getHttpResponseEvent()->addEvent(std::move(showAttribute));

    return Net::Rest::Route::Result::Ok;;
}
