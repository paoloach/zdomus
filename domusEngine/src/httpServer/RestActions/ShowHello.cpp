/*
 * ShowHello.cpp
 *
 *  Created on: 27/giu/2015
 *      Author: Paolo Achdjian
 */

#include <pistache/http_header.h>

#include "ShowHello.h"


namespace zigbee {
    namespace http {
        using namespace Net::Rest;
        using namespace Net::Http;
        using namespace Net::Http::Header;


        Net::Rest::Route::Result ShowHello::operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter response) {
            response.send(Code::Ok, "Hello\n",MIME(Text, Plain));
            return Net::Rest::Route::Result::Ok;
        }
    } /* namespace http */
} /* namespace zigbee */

