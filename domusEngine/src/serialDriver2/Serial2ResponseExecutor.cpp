//
// Created by paolo on 01/01/17.
//

#include <boost/log/attributes/named_scope.hpp>

#include "Serial2ResponseExecutor.h"
#include "IEEEAddressResponseSerial2Executor.h"
#include "AnnunceSerial2Executor.h"
#include "SimpleDescSerial2Executor.h"
#include "ActiveEndpointSerial2ErrorExecutor.h"
#include "BindTableSerial2Executer.h"
#include "ReadAttributeResponseErrorSerial2.h"
#include "ReadAttributeResponseSerial2.h"
#include "DeviceInfoSerial2Executor.h"
#include "IEEEAddressResponseErrorSerial2Executor.h"
#include "InvalidResponseSerial2Executor.h"
#include "PowerNodeResponse2.h"
#include "PowerNodeResponse2Error.h"
#include "AliveMessage2.h"
#include "StringExecutor.h"
#include "NodeDescriptionResponse2.h"
#include "NodeDescriptionResponseError2.h"

namespace zigbee {
    Serial2ResponseExecutor::Serial2ResponseExecutor(SingletonObjects * singletonObjects) {
        executors[CmdType::IEEEAddress] = std::make_unique<IEEEAddressResponseSerial2Executor>(singletonObjects);
        executors[CmdType::IEEEAddressError] = std::make_unique<IEEEAddressResponseErrorSerial2Executor>();
        executors[CmdType::AnnunceDevice] = std::make_unique<AnnunceSerial2Executor>(singletonObjects);
        executors[CmdType::SimpleDescriptor] = std::make_unique<SimpleDescSerial2Executor>(singletonObjects);
        executors[CmdType::ActiveEndpointError] = std::make_unique<ActiveEndpointSerial2ErrorExecutor>();
        executors[CmdType::BindTableEntry] = std::make_unique<BindTableSerial2Executor>(singletonObjects);
        executors[CmdType::ReadAttributeError] = std::make_unique<ReadAttributeResponseErrorSerial2>(singletonObjects);
        executors[CmdType::ReadAttribute] = std::make_unique<ReadAttributeResponseSerial2>(singletonObjects);
        executors[CmdType::Invalid] = std::make_unique<InvalidResponseSerial2Executor>();
        executors[CmdType::DeviceInfo] = std::make_unique<DeviceInfoSerial2Executor>(singletonObjects);
        executors[CmdType::PowerNode] = std::make_unique<PowerNodeResponse2>(singletonObjects);
        executors[CmdType::PowerNodeError] = std::make_unique<PowerNodeResponse2Error>(singletonObjects);
        executors[CmdType::Alive] = std::make_unique<AliveMessage2>();
        executors[CmdType::STRING] = std::make_unique<StringExecutor>();
        executors[CmdType::NodeDescriptionError] = std::make_unique<NodeDescriptionResponseError2>();
        executors[CmdType::NodeDescription] = std::make_unique<NodeDescriptionResponse2>(singletonObjects);
    }

    void Serial2ResponseExecutor::execute(Packet &&packet) {
        CmdType type = CmdType::Invalid;
        if (packet.getCmdCode() <= 13)
            type = static_cast<CmdType>(packet.getCmdCode());
        executors[type]->operator()(std::move(packet));
    }


}