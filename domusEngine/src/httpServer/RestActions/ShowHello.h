/*
 * ShowHello.h
 *
 *  Created on: 27/giu/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTACTIONS_SHOWHELLO_H_
#define SRC_HTTPSERVER_RESTACTIONS_SHOWHELLO_H_

#include "../RestParser/RestActions.h"

namespace zigbee {

    class SingletonObjects;

    namespace http {

        class PlaceHolders;

        class ShowHello : public ActionHandler {
        public:
            ShowHello() noexcept { };

            void operator()(const PlaceHolders &&placeHolder, ServerRequest &request,
                            Poco::Net::HTTPServerResponse &response);
        };

    } /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTACTIONS_SHOWHELLO_H_ */
