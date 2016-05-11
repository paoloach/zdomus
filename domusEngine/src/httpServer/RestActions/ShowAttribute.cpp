/*
 * ShowAttribute.cpp
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#include <chrono>
#include <thread>

#include <boost/log/trivial.hpp>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>
#include <zcl/ClusterTypeFactory.h>

#include "ShowAttribute.h"

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/PropertyTree/AttributePT.h"
#include "../../ZigbeeData/ZDevices.h"

#include "../../json/json/json.h"

using namespace Json;

namespace zigbee {
  namespace http {

    void ShowAttribute::operator()(const PlaceHolders &&placeHolder, Poco::Net::HTTPServerRequest &,
                                   Poco::Net::HTTPServerResponse &response) {
        auto nwkAddr(placeHolder.get<NwkAddr>("device"));
        auto endpoint(placeHolder.get<EndpointID>("endpoint"));
        auto clusterId(placeHolder.get<ClusterID>("cluster"));
        auto attributeParam(placeHolder.get<std::string>("attribute"));
        auto zDevice = singletons.getZDevices()->getDevice(nwkAddr);
        auto zEndpoint = zDevice.getEndpoint(boost::lexical_cast<EndpointID>(endpoint));
        if (zEndpoint.isInCluster(clusterId)) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            auto zDevice = singletons.getZigbeeDevice();
            auto cluster(singletons.getClusterTypeFactory()->getCluster(clusterId, zDevice, endpoint, nwkAddr));
            std::shared_ptr<ZCLAttribute> attribute;
            try {
                auto attributeId = boost::lexical_cast<int>(attributeParam);
                BOOST_LOG_TRIVIAL(info) << "get attribute " << attributeId;
                attribute = cluster->getAttribute(attributeId);
            } catch (boost::bad_lexical_cast &badCast) {
                BOOST_LOG_TRIVIAL(info) << "get attribute " << attributeParam;
                attribute = cluster->getAttribute(attributeParam);
            }

            attributeArrived.store(false);
            NewAttributeValueCallback fn = [this](int status){this->attributeReceived(status);};
            singletons.getAttributeValueSignalMap().insert(AttributeKey{nwkAddr, endpoint.getId(), cluster->getId().getId(),static_cast<ZigbeeAttributeId>(attribute->getIdentifier()) },fn);
            attribute->requestValue();

            std::chrono::milliseconds duration(100);
            while (!attributeArrived.load()) {
                std::this_thread::sleep_for(duration);
            }
            if (status != 0){
                response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            } else {
                send(response,attribute);
            }

        } else {
            throwWrongCluster(response, clusterId, endpoint, nwkAddr);
        }
    }

      void ShowAttribute::send(Poco::Net::HTTPServerResponse &response, std::shared_ptr<ZCLAttribute> attribute){
          response.setContentType(Poco::Net::MediaType("application","json"));
          response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_OK);
          Value root(objectValue);

          root["id"]  = Value(attribute->getIdentifier());
          root["name"]= Value(attribute->getName().to_string());
          root["readOnly"]= Value(attribute->isReadOnly());
          root["type"]= Value(static_cast<int>(attribute->getZCLType()));
          root["isAvailable"]= Value(attribute->isAvailable());
          root["isSupported"]= Value(!attribute->isUnsupported());
          root["status"]= Value(attribute->getStatus());
          if (attribute->isAvailable()){
              root["value"] = Value( boost::any_cast<std::string>(attribute->getValue()));
          }

          response.send()<< root << "\n";
      }

      void ShowAttribute::attributeReceived(int status) {
          this->status = status;
          attributeArrived.store(true);
      }


  } /* namespace http */
} /* namespace zigbee */

