//
// Created by paolo on 10/05/16.
//

#ifndef DOMUS_ENGINE_SHOWATTRIBUTEFACTORY_H
#define DOMUS_ENGINE_SHOWATTRIBUTEFACTORY_H

#include "../RestParser/RestActions.h"
namespace zigbee {

    class SingletonObjects;

    namespace http {

        class PlaceHolders;

        class ShowAttributeFactory {
        public:
            ShowAttributeFactory(SingletonObjects &singletons): singletons(singletons){}
            void operator()(const PlaceHolders &&placeHolder, ServerRequest &request, Poco::Net::HTTPServerResponse &response);
        private:
            SingletonObjects &singletons;
        };
    }
}

#endif //DOMUS_ENGINE_SHOWATTRIBUTEFACTORY_H
