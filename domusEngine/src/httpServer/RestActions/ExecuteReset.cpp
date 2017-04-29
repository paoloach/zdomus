//
// Created by paolo on 04/06/16.
//

#include <zigbee/ZigbeeDevice.h>
#include <boost/log/trivial.hpp>
#include "ExecuteReset.h"
#include "../../Utils/SingletonObjects.h"

Net::Rest::Route::Result zigbee::http::ExecuteReset::operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter response){
    BOOST_LOG_TRIVIAL(info) << "ExecuteReset";
    singletons.getZigbeeDevice()->requestReset();
    response.send(Net::Http::Code::No_Content, "reset\n\r");
}

