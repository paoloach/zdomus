//
// Created by paolo on 04/10/16.
//

#ifndef DOMUS_ENGINE_SHOWTOPOLGY_H
#define DOMUS_ENGINE_SHOWTOPOLGY_H

#include "../RestParser/RestActions.h"
#include "../../json/json/json.h"

namespace zigbee {

    class SingletonObjects;

    namespace http {

        class PlaceHolders;

        class ShowTopology : public ActionHandler {
        public:
            ShowTopology(SingletonObjects &singletons) noexcept : singletons(singletons) {};

            void operator()(const PlaceHolders &&placeHolder, ServerRequest &request,
                            Poco::Net::HTTPServerResponse &response);

        private:
            Json::Value createChildren(std::set<NwkAddr> &);
            Json::Value createNode(NwkAddr &);
            SingletonObjects &singletons;
        };

    }
}


#endif //DOMUS_ENGINE_SHOWTOPOLGY_H
