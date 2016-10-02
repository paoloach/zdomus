//
// Created by paolo on 04/06/16.
//

#include <zigbee/ZigbeeDevice.h>
#include <boost/log/trivial.hpp>
#include "ExecuteReset.h"
#include "../../Utils/SingletonObjects.h"

void zigbee::http::ExecuteReset::operator()(const zigbee::http::PlaceHolders &&,
                                            ServerRequest &,
                                            Poco::Net::HTTPServerResponse &response) {
    BOOST_LOG_TRIVIAL(info) << "ExecuteReset";
    singletons.getZigbeeDevice()->requestReset();
    response.setStatus(Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
    response.send() << "reset\n";
}

