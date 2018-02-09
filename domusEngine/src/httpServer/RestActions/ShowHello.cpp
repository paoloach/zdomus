/*
 * ShowHello.cpp
 *
 *  Created on: 27/giu/2015
 *      Author: Paolo Achdjian
 */

#include <pistache/http_header.h>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes/named_scope.hpp>

#include "ShowHello.h"


namespace zigbee {
    namespace http {
        using namespace Pistache::Rest;
        using namespace Pistache::Http;
        using namespace Pistache::Http::Header;


        Pistache::Rest::Route::Result ShowHello::operator()(const Pistache::Rest::Request &, Pistache::Http::ResponseWriter && response) {
            BOOST_LOG_NAMED_SCOPE("HTTP");
            response.send(Code::Ok, "Hello\n", MIME(Text, Plain));
            return Pistache::Rest::Route::Result::Ok;
        }
    } /* namespace http */
} /* namespace zigbee */

