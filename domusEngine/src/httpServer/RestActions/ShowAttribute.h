/*
 * ShowAttribute.h
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTACTIONS_SHOWATTRIBUTE_H_
#define SRC_HTTPSERVER_RESTACTIONS_SHOWATTRIBUTE_H_

#include "../RestParser/RestActions.h"
#include "ClusterThrowingException.h"
#include <atomic>
#include <zcl/ZCLAttribute.h>

namespace zigbee {

    class SingletonObjects;

    namespace http {

        class PlaceHolders;

        class ShowAttribute : public ActionHandler, public ClusterThrowingException {
        private:
            std::vector<std::atomic<bool >> attributesArrived;
            std::map<int, int> mapAttributes;
            int status;
            SingletonObjects &singletons;
        public:
            ShowAttribute(SingletonObjects &singletons) noexcept : singletons(singletons) { };

            void operator()(const PlaceHolders &&placeHolder, Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

            void attributeReceived(int attributeId, int status);

            void send(Poco::Net::HTTPServerResponse &response, std::vector<std::shared_ptr<ZCLAttribute>> &&attributes);

        private:
            bool isAllAttributeArrived() const;

        };

    } /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTACTIONS_SHOWATTRIBUTE_H_ */
