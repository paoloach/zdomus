/*
 * DeviceBrowserHandler.h
 *
 *  Created on: 10/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_DEVICEBROWSERHANDLER_H_
#define SRC_HTTPSERVER_DEVICEBROWSERHANDLER_H_

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include <zcl/ClusterTypeFactory.h>
#include <zigbee/ZigbeeDevice.h>
#include "../ZigbeeData/ZDevices.h"
#include "RestParser/RestActions.h"

namespace zigbee {
    class SingletonObjects;
    namespace http {


        class DeviceBrowserHandler : public Poco::Net::HTTPRequestHandler {
        public:
            DeviceBrowserHandler(SingletonObjects &singletons);

        protected:
            virtual void handleRequest(Poco::Net::HTTPServerRequest &request,
                                       Poco::Net::HTTPServerResponse &response) override;

        private:
            SingletonObjects &singletons;
            RestActions restGetActions;
            RestActions restPostActions;

        };

    } /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_DEVICEBROWSERHANDLER_H_ */
