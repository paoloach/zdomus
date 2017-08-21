//
// Created by paolo on 03/04/16.
//
#include <thread>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes/named_scope.hpp>

#include "ShowBindTable.h"
#include "../../json/json/json.h"

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"

using namespace Json;

namespace zigbee {
    namespace http {
        using namespace Net::Rest;
        using namespace Net::Http;
        using namespace Net::Http::Header;


        Net::Rest::Route::Result ShowBindTable::operator()(const Net::Rest::Request &, Net::Http::ResponseWriter  && response) {
            BOOST_LOG_NAMED_SCOPE("HTTP");
            BOOST_LOG_TRIVIAL(info) << "request BindTable: ";
            Value root(arrayValue);
            auto &bindTable = singletons.getBindTable();
            for (auto &entry: bindTable.getEntries()) {
                Value jsonEntry(objectValue);
                jsonEntry["sourceAddr"] = Value(std::get<0>(entry).address.getId());
                jsonEntry["sourceEndpoint"] = Value(std::get<0>(entry).endpoint.getId());
                jsonEntry["cluster"] = Value(std::get<1>(entry).getId());
                jsonEntry["destAddr"] = Value(std::get<2>(entry).address.getId());
                jsonEntry["destEndpoint"] = Value(std::get<2>(entry).endpoint.getId());
                root.append(jsonEntry);
            }
            std::stringstream stream;
            stream << root;
            response.send(Code::Ok, stream.str(), MIME(Application, Json));
            return Net::Rest::Route::Result::Ok;
        }

    }
}

