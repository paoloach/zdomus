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
        using namespace Net::Rest;
        using namespace Net::Http;
        using namespace Net::Http::Header;

        Net::Rest::Route::Result ShowWhoAreYou::operator()(const Net::Rest::Request &, Net::Http::ResponseWriter &&response) {
            BOOST_LOG_NAMED_SCOPE("HTTP");
            BOOST_LOG_TRIVIAL(debug) << "Who are you called";
            response.send(Code::Ok, "I am DomusEngine version 1.0.0\r\n", MIME(Text, Plain));
            return Net::Rest::Route::Result::Ok;
        }
    } /* namespace http */
} /* namespace zigbee */

