/*
 * ShowWhoAreYou.cpp
 *
 *  Created on: 18/lug/2015
 *      Author: Paolo Achdjian
 */

#include "ShowWhoAreYou.h"

namespace zigbee {
    namespace http {
        using namespace Net::Rest;
        using namespace Net::Http;
        using namespace Net::Http::Header;

        Net::Rest::Route::Result ShowWhoAreYou::operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter response) {
            response.send(Code::Ok, "I am DomusEngine version 1.0.0\r\n",MIME(Text, Plain));
            return Net::Rest::Route::Result::Ok;
        }
    } /* namespace http */
} /* namespace zigbee */

