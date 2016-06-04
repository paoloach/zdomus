//
// Created by paolo on 04/06/16.
//

#include <zigbee/ZigbeeDevice.h>
#include "ExecuteReset.h"
#include "../../Utils/SingletonObjects.h"

void zigbee::http::ExecuteReset::operator()(const zigbee::http::PlaceHolders &&placeHolder,
                                            Poco::Net::HTTPServerRequest &request,
                                            Poco::Net::HTTPServerResponse &response) {
    singletons.getZigbeeDevice()->requestReset();
}

