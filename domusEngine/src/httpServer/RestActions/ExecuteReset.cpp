//
// Created by paolo on 04/06/16.
//

#include <zigbee/ZigbeeDevice.h>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include "ExecuteReset.h"
#include "../../Utils/SingletonObjects.h"

Net::Rest::Route::Result zigbee::http::ExecuteReset::operator()(const Net::Rest::Request &, Net::Http::ResponseWriter  && response){
    BOOST_LOG_NAMED_SCOPE("HTTP");
    BOOST_LOG_TRIVIAL(info) << "ExecuteReset";
    singletons.getZigbeeDevice()->requestReset();
    response.send(Net::Http::Code::No_Content, "reset\n\r");
    return Net::Rest::Route::Result::Ok;
}

