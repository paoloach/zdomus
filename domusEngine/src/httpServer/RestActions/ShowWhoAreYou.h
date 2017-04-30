/*
 * ShowWhoAreYou.h
 *
 *  Created on: 18/lug/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTACTIONS_SHOWWHOAREYOU_H_
#define SRC_HTTPSERVER_RESTACTIONS_SHOWWHOAREYOU_H_

#include "endpoint.h"
#include "router.h"

namespace zigbee {

    class SingletonObjects;

    namespace http {

        class ShowWhoAreYou {
        public:
            Net::Rest::Route::Result  operator()(const Net::Rest::Request& request, Net::Http::ResponseWriter response);

        };

    } /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTACTIONS_SHOWWHOAREYOU_H_ */
