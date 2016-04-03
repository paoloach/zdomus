/*
 * ShowWhoAreYou.h
 *
 *  Created on: 18/lug/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTACTIONS_SHOWWHOAREYOU_H_
#define SRC_HTTPSERVER_RESTACTIONS_SHOWWHOAREYOU_H_

#include "../RestParser/RestActions.h"

namespace zigbee {

    class SingletonObjects;

    namespace http {

        class ShowWhoAreYou : public ActionHandler {
        public:
            ShowWhoAreYou(zigbee::SingletonObjects &singletons) noexcept  : singletons(singletons) { };

            void operator()(const PlaceHolders &&placeHolder, Poco::Net::HTTPServerRequest &request,
                            Poco::Net::HTTPServerResponse &response);

        private:
            SingletonObjects &singletons;
        };

    } /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTACTIONS_SHOWWHOAREYOU_H_ */
