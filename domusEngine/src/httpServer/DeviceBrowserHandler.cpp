/*
 * DeviceBrowserHandler.cpp
 *
 *  Created on: 10/apr/2015
 *      Author: Paolo Achdjian
 */
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/MediaType.h>
#include <boost/lexical_cast.hpp>
#include <iostream>

#include "DeviceBrowserHandler.h"
#include "../ZigbeeData/Exceptions/ZigbeeDeviceException.h"

#include "RestActions/ShowDevices.h"
#include "RestActions/ShowDevice.h"
#include "RestActions/ShowEndpoint.h"
#include "RestActions/ShowInCluster.h"
#include "RestActions/ShowOutCluster.h"
#include "RestActions/ShowAttributeFactory.h"
#include "RestActions/ShowBindTable.h"
#include "RestActions/ExecuteCmd.h"
#include "RestActions/ResponseFile.h"
#include "RestActions/ShowHello.h"
#include "RestActions/ShowWhoAreYou.h"
#include "RestActions/ExecuteBind.h"
#include "RestActions/ExecuteReset.h"


namespace zigbee {
  namespace http {

    using boost::lexical_cast;
    using std::string;

    DeviceBrowserHandler::DeviceBrowserHandler(zigbee::SingletonObjects &singletons) :
            singletons(singletons) {

        restGetActions.addActions(RestPath {"/hello"}, ShowHello{});
        restGetActions.addActions(RestPath {"/who_are_you"}, ShowWhoAreYou{singletons});
        restGetActions.addActions(RestPath {"/devices"}, ShowDevices{singletons});
        restGetActions.addActions(RestPath {"/devices/{device}"}, ShowDevice{singletons});
        restGetActions.addActions(RestPath {"/devices/{device}/endpoint/{endpoint}"}, ShowEndpoint{singletons});
        restGetActions.addActions(RestPath {"/devices/{device}/endpoint/{endpoint}/cluster/in/{cluster}"}, ShowInCluster{singletons});
        restGetActions.addActions(RestPath {"/devices/{device}/endpoint/{endpoint}/cluster/out/{cluster}"}, ShowOutCluster{singletons});
        restGetActions.addActions(RestPath {"/devices/{device}/endpoint/{endpoint}/cluster/in/{cluster}/attributes"}, ShowAttributeFactory{singletons});
        restGetActions.addActions(RestPath {"/binds"}, ShowBindTable{singletons});
        restGetActions.setDefaultAction(ResponseFile(singletons));

        restPostActions.addActions(RestPath {"/devices/{device}/endpoint/{endpoint}/cluster/in/{cluster}/command/{command}"}, ExecuteCmd{singletons});
        restPostActions.addActions(RestPath {"/reset"}, ExecuteReset{singletons});
        restPostActions.addActions(RestPath {"/bind/src/{srcDevice}/endpoint/{srcEndpoint}/cluster/{cluster}/dst/{dstDevice}/endpoint/{dstEndpoint}"}, ExecuteBind{singletons,true});

        restDeleteActions.addActions(RestPath {"/bind/src/{srcDevice}/endpoint/{srcEndpoint}/cluster/{cluster}/dst/{dstDevice}/endpoint/{dstEndpoint}"}, ExecuteBind{singletons,false});
    }

    void DeviceBrowserHandler::handleRequest(Poco::Net::HTTPServerRequest &request,
                                             Poco::Net::HTTPServerResponse &response) {
        std::cout << "request: " << request.getURI() << std::endl;

        try {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            PathReceived pathReceived(std::string(request.getURI()));
            if (request.getMethod() == "GET") {
                restGetActions.execute(std::move(pathReceived), request, response);
            } else if (request.getMethod() == "POST") {
                restPostActions.execute(std::move(pathReceived), request, response);
            }else if (request.getMethod() == "DELETE") {
                restDeleteActions
                        .execute(std::move(pathReceived), request, response);
            }

        } catch (boost::bad_lexical_cast &cast) {
            std::cerr << "ERROR: " << cast.what() << std::endl;
            response.send() << cast.what();
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
        } catch (ZigbeeDeviceException &e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
            response.send() << e.what();
            response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

    }


  } /* namespace http */
} /* namespace zigbee */

