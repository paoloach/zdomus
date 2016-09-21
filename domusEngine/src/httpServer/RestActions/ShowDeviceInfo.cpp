//
// Created by paolo on 19/09/16.
//

#include <boost/log/trivial.hpp>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <zigbee/NwkAddr.h>
#include <zigbee/ZigbeeDevice.h>
#include <thread>

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../Utils/DeviceInfoDispatcher.h"
#include "../../ZigbeeData/PropertyTree/ZDevicesPT.h"

#include "ShowDeviceInfo.h"
#include "../../json/json/json.h"

using namespace std::chrono;
using namespace Json;

namespace  zigbee {
    namespace  http {
        ShowDeviceInfo::~ShowDeviceInfo() {
            singletons.getDeviceInfoDispatcher()->remove(this, device);
        }

        void ShowDeviceInfo::operator()(const zigbee::http::PlaceHolders &&placeHolder,
                                                      zigbee::http::ServerRequest &request,
                                                      Poco::Net::HTTPServerResponse &response) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            device = placeHolder.get<NwkAddr>("device");
            BOOST_LOG_TRIVIAL(info) << "Request device info " << device;
            auto zigbeeDevice = singletons.getZigbeeDevice();
            auto constants = singletons.getConstant();

            resultPresent = false;
            singletons.getDeviceInfoDispatcher()->add(this, device);
            if (zigbeeDevice != nullptr) {
                zigbeeDevice->sendReqDeviceInfo(device);

                milliseconds duration(100);
                auto start = system_clock::now();
                while (!resultPresent) {
                    std::this_thread::sleep_for(duration);
                    milliseconds elapsed =  duration_cast<std::chrono::milliseconds>(system_clock::now()- start);
                    if (elapsed > milliseconds(constants.requestTimeout) ){
                        response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                        response.send() << "data timeout\n";
                        return;
                    }
                }
                sendJSON(response);
            }
            response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
            response.send() << "zigbee device not connected\n";
        }

        void ShowDeviceInfo::newDeviceInfo(zigbee::DeviceInfoMessage *deviceInfo) {
            if (deviceInfo != nullptr) {
                deviceInfoMessage = *deviceInfo;
                resultPresent = true;
            }
        }

        void ShowDeviceInfo::sendJSON(Poco::Net::HTTPServerResponse &response) {
            response.setContentType(Poco::Net::MediaType("application", "json"));
            response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_OK);
            Value root(objectValue);

            root["nwkAddr"] = Value(deviceInfoMessage.nwkAddr);
            root["nodeRelation"] = Value(deviceInfoMessage.nodeRelation);
            root["devStatus"] = Value(deviceInfoMessage.devStatus);
            root["assocCnt"] = Value(deviceInfoMessage.assocCnt);
            root["age"] = Value(deviceInfoMessage.age);
            root["txCounter"] = Value(deviceInfoMessage.txCounter);
            root["txCost"] = Value(deviceInfoMessage.txCost);
            root["rxLqi"] = Value(deviceInfoMessage.rxLqi);
            response.send() << root << "\n";
        }



    }

}