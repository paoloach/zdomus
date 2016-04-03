//
// Created by paolo on 03/04/16.
//

#ifndef DOMUS_ENGINE_SHOWBINDTABLE_H
#define DOMUS_ENGINE_SHOWBINDTABLE_H

#include "../RestParser/RestActions.h"


namespace zigbee {

  class SingletonObjects;
  namespace http {

    class ShowBindTable : public ActionHandler {
    public:
        ShowBindTable(zigbee::SingletonObjects &singletons) noexcept : singletons(singletons) { };

        void operator()(const PlaceHolders &&placeHolder, Poco::Net::HTTPServerRequest &request,
                        Poco::Net::HTTPServerResponse &response);

    private:
        SingletonObjects &singletons;
    };
  }
}


#endif //DOMUS_ENGINE_SHOWBINDTABLE_H
