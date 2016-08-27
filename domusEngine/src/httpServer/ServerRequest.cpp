//
// Created by paolo on 15/07/16.
//
#include <iostream>
#include "ServerRequest.h"

namespace zigbee {
    namespace http {

        std::experimental::string_view ServerRequest::JSON_TYPE="application/json";

        bool ServerRequest::isApplicationJSon() {
            std::string contentType = request.getContentType();
            return (contentType.size() >=JSON_TYPE.length()) && (contentType.substr(0, JSON_TYPE.length()) == JSON_TYPE);
        }
    }
}

