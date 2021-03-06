//
// Created by paolo on 19/09/16.
//

#include <boost/log/trivial.hpp>
#include <zigbee/NwkAddr.h>
#include <zigbee/ZigbeeDevice.h>
#include <thread>
#include <boost/log/attributes/named_scope.hpp>

#include "../MediaTypeProducerFactory.h"
#include "../../ZigbeeData/PropertyTree/ZDevicesPT.h"

#include "ShowDeviceInfo.h"
#include "../../json/json/json.h"
#include "../../Utils/Constant.h"

using namespace std::chrono;
using namespace Json;

namespace zigbee {
    namespace http {
        using namespace Pistache::Rest;
        using namespace Pistache::Http;
        using namespace Pistache::Http::Header;

        ShowDeviceInfo::~ShowDeviceInfo() {
            singletons->getDeviceInfoDispatcher()->remove(this, device);
        }

        Pistache::Rest::Route::Result ShowDeviceInfo::operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter  && response) {
            BOOST_LOG_NAMED_SCOPE("HTTP");
            device = request.param(":device").as<NwkAddr>();
            BOOST_LOG_TRIVIAL(info) << "Request device info " << device;
            auto zigbeeDevice = singletons->getZigbeeDevice();
            auto constants = singletons->getConstant();

            resultPresent = false;
            singletons->getDeviceInfoDispatcher()->add(this, device);
            if (zigbeeDevice != nullptr) {
                zigbeeDevice->sendReqDeviceInfo(device);

                auto start = system_clock::now();
                while (!resultPresent) {
                    std::this_thread::sleep_for(100ms);
                    milliseconds elapsed = duration_cast<std::chrono::milliseconds>(system_clock::now() - start);
                    if (elapsed > milliseconds(constants->requestTimeout)) {
                        response.send(Code::Bad_Request, "data timeout\n\r");
                        return Pistache::Rest::Route::Result::Ok;
                    }
                }
                sendJSON(response);
            }
            response.send(Code::Internal_Server_Error, "zigbee device not connected\n\r");
            return Pistache::Rest::Route::Result::Ok;
        }

        void ShowDeviceInfo::newDeviceInfo(zigbee::DeviceInfoMessage *deviceInfo) {
            if (deviceInfo != nullptr) {
                deviceInfoMessage = *deviceInfo;
                resultPresent = true;
            }
        }

        void ShowDeviceInfo::sendJSON(Pistache::Http::ResponseWriter &response) {
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