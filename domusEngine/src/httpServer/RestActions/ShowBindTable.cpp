//
// Created by paolo on 03/04/16.
//
#include <thread>

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>

#include "ShowBindTable.h"

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/PropertyTree/BindTablePT.h"

namespace zigbee {

  namespace http {
    void ShowBindTable::operator()(const zigbee::http::PlaceHolders &&,
                                   Poco::Net::HTTPServerRequest &request,
                                   Poco::Net::HTTPServerResponse &response) {
        const auto &producer = MediaTypeProducerFactory::getMediaType(request.getContentType());

        producer.produce(response.send(), BindTablePT(singletons.getBindTable()));

    }

  }
}

