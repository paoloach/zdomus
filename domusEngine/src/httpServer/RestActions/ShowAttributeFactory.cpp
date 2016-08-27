//
// Created by paolo on 10/05/16.
//

#include "ShowAttributeFactory.h"
#include "ShowAttribute.h"

void zigbee::http::ShowAttributeFactory::operator()(const zigbee::http::PlaceHolders &&placeHolder, ServerRequest &request,
                                                    Poco::Net::HTTPServerResponse &response) {
    ShowAttribute  showAttribute{singletons};
    showAttribute(std::move(placeHolder), request, response);
}

