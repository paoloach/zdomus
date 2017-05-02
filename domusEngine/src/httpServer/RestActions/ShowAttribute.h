/*
 * ShowAttribute.h
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTACTIONS_SHOWATTRIBUTE_H_
#define SRC_HTTPSERVER_RESTACTIONS_SHOWATTRIBUTE_H_

#include <atomic>
#include <zcl/ZCLAttribute.h>
#include <iostream>

#include "endpoint.h"
#include "router.h"
#include "ClusterThrowingException.h"

namespace zigbee {

    class SingletonObjects;

    namespace http {

        class ShowAttribute : public ClusterThrowingException {
        private:
            std::vector<std::atomic<bool >> attributesArrived;
            std::map<int, int> mapAttributes;
            int status;
            SingletonObjects &singletons;
        public:
            ShowAttribute(SingletonObjects &singletons) noexcept : singletons(singletons) {};

            void operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter && response);

            void attributeReceived(int attributeId, int status);

            void send(Net::Http::ResponseWriter && response, std::vector< ZCLAttribute * > &&attributes);

        private:
            bool isAllAttributeArrived() const;

        };

    } /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTACTIONS_SHOWATTRIBUTE_H_ */
