//
// Created by paolo on 01/01/17.
//

#include <boost/log/attributes/named_scope.hpp>

#include "SerialResponseExecutor.h"
#include "IEEEAddressResponseSerialExecutor.h"
#include "IEEEAddressResponseErrorSerialExecutor.h"
#include "InvalidResponseSerialExecutor.h"
#include "AnnunceSerialExecutor.h"
#include "SimpleDescSerialExecutor.h"
#include "ActiveEndpointErrorExecutor.h"
#include "BindTableSerialExecuter.h"
#include "ReadAttributeResponseErrorSerial.h"
#include "ReadAttributeResponseSerial.h"
#include "DeviceInfoSerialExecutor.h"
#include "PowerNodeResponse.h"
#include "PowerNodeResponseError.h"
#include "AliveMessage.h"

namespace zigbee {
    SerialResponseExecutor::SerialResponseExecutor(SingletonObjects &singletonObjects) {
        executors[CmdType::IEEEAddress] = std::make_unique<IEEEAddressResponseSerialExecutor>(singletonObjects);
        executors[CmdType::IEEEAddressError] = std::make_unique<IEEEAddressResponseErrorSerialExecutor>();
        executors[CmdType::AnnunceDevice] = std::make_unique<AnnunceSerialExecutor>(singletonObjects);
        executors[CmdType::SimpleDescriptor] = std::make_unique<SimpleDescSerialExecutor>(singletonObjects);
        executors[CmdType::ActiveEndpointError] = std::make_unique<ActiveEndpointSerialErrorExecutor>();
        executors[CmdType::BindTableEntry] = std::make_unique<BindTableSerialExecutor>(singletonObjects);
        executors[CmdType::ReadAttributeError] = std::make_unique<ReadAttributeResponseErrorSerial>(singletonObjects);
        executors[CmdType::ReadAttribute] = std::make_unique<ReadAttributeResponseSerial>(singletonObjects);
        executors[CmdType::Invalid] = std::make_unique<InvalidResponseSerialExecutor>();
        executors[CmdType::DeviceInfo] = std::make_unique<DeviceInfoSerialExecutor>(singletonObjects);
        executors[CmdType::PowerNode] = std::make_unique<PowerNodeResponse>(singletonObjects);
        executors[CmdType::PowerNodeError] = std::make_unique<PowerNodeResponseError>(singletonObjects);
        executors[CmdType::Alive] = std::make_unique<AliveMessage>();
    }

    void SerialResponseExecutor::execute(const std::string &str) {
        auto type = getResponseType(str);
        executors[type]->operator()(str);
    }

    SerialResponseExecutor::CmdType SerialResponseExecutor::getResponseType(const std::string &str) {
        if (str.size() >= 4) {
            if (str.substr(0, 4) == "IE: ") {
                return CmdType::IEEEAddress;
            }
            if (str.substr(0, 4) == "EI: ") {
                return CmdType::IEEEAddressError;
            }
            if (str.substr(0, 4) == "AN: ") {
                return CmdType::AnnunceDevice;
            }
            if (str.substr(0, 4) == "SD: ") {
                return CmdType::SimpleDescriptor;
            }
            if (str.substr(0, 4) == "BT: ") {
                return CmdType::ActiveEndpointError;
            }
            if (str.substr(0, 4) == "RA: ") {
                return CmdType::ReadAttribute;
            }
            if (str.substr(0, 4) == "DI: ") {
                return CmdType::DeviceInfo;
            }
            if (str.size() >= 5){
                if (str.substr(0, 5) == "AEE: ") {
                    return CmdType::ActiveEndpointError;
                }
                if (str.substr(0, 5) == "RAE: ") {
                    return CmdType::ReadAttributeError;
                }
                if (str.substr(0, 5) == "NPR: ") {
                    return CmdType::PowerNode;
                }
                if (str.size() >= 6){
                    if (str.substr(0,6) == "NPRE: "){
                        return CmdType::PowerNodeError;
                    }
                    if (str.substr(0,6) == "Alive."){
                        return CmdType::Alive;
                    }
                }
            }
        }
        return CmdType::Invalid;
    }


}