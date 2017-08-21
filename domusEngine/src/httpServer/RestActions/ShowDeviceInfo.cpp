//
// Created by paolo on 19/09/16.
//

#include <boost/log/trivial.hpp>
#include <zigbee/NwkAddr.h>
#include <zigbee/ZigbeeDevice.h>
#include <thread>
#include <boost/log/attributes/named_scope.hpp>

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"
#include "../../ZigbeeData/PropertyTree/ZDevicesPT.h"

#include "ShowDeviceInfo.h"

using namespace std::chrono;
using namespace Json;

namespace zigbee {
    namespace http {
        using namespace Net::Rest;
        using namespace Net::Http;
        using namespace Net::Http::Header;

        ShowDeviceInfo::~ShowDeviceInfo() {
            singletons.getDeviceInfoDispatcher()->remove(this, device);
        }

        Net::Rest::Route::Result ShowDeviceInfo::operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter  && response) {
            BOOST_LOG_NAMED_SCOPE("HTTP");
            device = request.param(":device").as<NwkAddr>();
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
                    milliseconds elapsed = duration_cast<std::chrono::milliseconds>(system_clock::now() - start);
                    if (elapsed > milliseconds(constants.requestTimeout)) {
                        response.send(Code::Bad_Request, "data timeout\n\r");
                        return Net::Rest::Route::Result::Ok;
                    }
                }
                sendJSON(response);
            }
            response.send(Code::Internal_Server_Error, "zigbee device not connected\n\r");
            return Net::Rest::Route::Result::Ok;
        }

        void ShowDeviceInfo::newDeviceInfo(zigbee::DeviceInfoMessage *deviceInfo) {
            if (deviceInfo != nullptr) {
                deviceInfoMessage = *deviceInfo;
                resultPresent = true;
            }
        }

        void ShowDeviceInfo::sendJSON(Net::Http::ResponseWriter &response) {
            Value root(objectValue);

            root["nwkAddr"] = Value(deviceInfoMessage.nwkAddr);
            root["nodeRelation"] = Value(deviceInfoMessage.nodeRelation);
            root["devStatus"] = Value(deviceInfoMessage.devStatus);
            root["assocCnt"] = Value(deviceInfoMessage.assocCnt);
            root["age"] = Value(deviceInfoMessage.age);
            root["txCounter"] = Value(deviceInfoMessage.txCounter);
            root["txCost"] = Value(deviceInfoMessage.txCost);
            root["rxLqi"] = Value(deviceInfoMessage.rxLqi);

            std::stringstream output;
            output << root << "\n\r";

            response.send(Code::Ok, output.str(), MIME(Application, Json));
        }


    }

}