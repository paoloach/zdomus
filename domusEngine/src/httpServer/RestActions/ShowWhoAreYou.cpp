/*
 * ShowWhoAreYou.cpp
 *
 *  Created on: 18/lug/2015
 *      Author: Paolo Achdjian
 */

#include <boost/log/trivial.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include "ShowWhoAreYou.h"

namespace zigbee {
    namespace http {
        using namespace Pistache::Rest;
        using namespace Pistache::Http;
        using namespace Pistache::Http::Header;

        Pistache::Rest::Route::Result ShowWhoAreYou::operator()(const Pistache::Rest::Request &, Pistache::Http::ResponseWriter &&response) {
            BOOST_LOG_NAMED_SCOPE("HTTP");
            BOOST_LOG_TRIVIAL(debug) << "Who are you called";
            response.send(Code::Ok, "I am DomusEngine version 1.0.0\r\n", MIME(Text, Plain));
            return Pistache::Rest::Route::Result::Ok;
        }
    } /* namespace http */
} /* namespace zigbee */

