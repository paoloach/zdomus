//
// Created by paolo on 10/05/16.
//

#include "ShowAttributeFactory.h"
#include "ShowAttribute.h"

Net::Rest::Route::Result zigbee::http::ShowAttributeFactory::operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter && response) {
    ShowAttribute  showAttribute{singletons};
    showAttribute(request, std::move(response));
    return Net::Rest::Route::Result::Ok;;
}
