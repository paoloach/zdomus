/*
 * ShowHello.cpp
 *
 *  Created on: 27/giu/2015
 *      Author: Paolo Achdjian
 */

#include <http_header.h>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes/named_scope.hpp>

#include "ShowHello.h"


namespace zigbee {
    namespace http {
        using namespace Net::Rest;
        using namespace Net::Http;
        using namespace Net::Http::Header;


        Net::Rest::Route::Result ShowHello::operator()(const Net::Rest::Request &, Net::Http::ResponseWriter && response) {
            BOOST_LOG_NAMED_SCOPE("HTTP");
            response.send(Code::Ok, "Hello\n", MIME(Text, Plain));
            return Net::Rest::Route::Result::Ok;
        }
    } /* namespace http */
} /* namespace zigbee */

