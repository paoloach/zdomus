//
// Created by paolo on 23/06/16.
//

#ifndef DOMUS_ENGINE_UPDATEATTRIBUTES_H
#define DOMUS_ENGINE_UPDATEATTRIBUTES_H

#include "../RestParser/RestActions.h"
#include "ClusterThrowingException.h"

namespace zigbee {

    class SingletonObjects;

    namespace http {
        class UpdateAttributes : public ActionHandler, public ClusterThrowingException{
        public:
            UpdateAttributes(SingletonObjects &singletons) noexcept : singletons(singletons) { };

            void operator()(const PlaceHolders &&placeHolder, Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

        private:
            SingletonObjects &singletons;
        };

    } /* namespace http */
} /* namespace zigbee */


#endif //DOMUS_ENGINE_UPDATEATTRIBUTES_H
