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
#include "../../Utils/HttpResponseEvent.h"
#include "../../usb/AttributeValuesSignalMap.h"

namespace zigbee {

    class SingletonObjects;

    namespace http {

        class ShowAttribute : public ClusterThrowingException, public HttpResponseEvent::Event {
        private:
            std::vector<std::atomic<bool >> attributesArrived;
            std::map<int, int> mapAttributes;
            SingletonObjects &singletons;
            Net::Http::ResponseWriter response;
            int status;
            std::vector<ZCLAttribute *> attributes;
        public:
            ShowAttribute(SingletonObjects &singletons,const Net::Rest::Request &request, Net::Http::ResponseWriter && response);
            virtual ~ShowAttribute();
            void attributeReceived(int attributeId, int status);

        private:
            bool isAllAttributeArrived() const;
            void allArrived();
            void fnTimeout();
            std::vector<AttributeValueSignalMap::iterator> toRemove;
        };

    } /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTACTIONS_SHOWATTRIBUTE_H_ */
