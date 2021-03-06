//
// Created by paolo on 10/05/16.
//

#include <zigbee/zigbeeConfig.h>
#include "UsbResponseExecutors.h"
#include "AnnunceMsgExecuter.h"
#include "SimpleDescExecutor.h"
#include "AttributeValuesExecuter.h"
#include "BindTableExecuter.h"
#include "AttributeValueReqError.h"
#include "ActiveEPReqError.h"
#include "InfoMessageExecuter.h"
#include "DeviceInfoExecutor.h"
#include "IEEEAddressResponseExecutor.h"
#include "messages/zigbeeConfig.h"
#include "PowerNodeReqError.h"

using std::make_unique;

zigbee::UsbResponseExecutors::UsbResponseExecutors(SingletonObjects * singletonObjects,  DomusEngineUSBDevice &usbDevice) {
    executors[ANNUNCE_MSG] = make_unique<AnnunceMsgExecuter>(singletonObjects->getZDevices(), usbDevice);
    executors[SIMPLE_DESC] = make_unique<SimpleDescExecutor>(singletonObjects->getZDevices());
    executors[ATTRIBUTE_VALUES] = make_unique<AttributeValuesExecuter>(singletonObjects);
    executors[BIND_TABLE] = make_unique<BindTableExecuter>(singletonObjects);
    executors[ATTRIBUTE_VALUE_REQ_ERROR] = make_unique<AttributeValueReqError>(singletonObjects->getZigbeeDevice());
    executors[ACTIVE_EP_REQ_ERROR] = make_unique<ActiveEPReqError>();
    executors[INFO_MESSAGE] = make_unique<InfoMessageExecuter>();
    executors[DEVICE_INFO] = make_unique<DeviceInfoExecutor>(singletonObjects);
    executors[IEEE_ADDRESS_RESPONSE] = make_unique<IEEEAddressResponseExecutor>(singletonObjects);
    executors[POWER_NODE_REQ_ERROR] = make_unique<PowerNodeReqError>(singletonObjects);
}

void zigbee::UsbResponseExecutors::execute(unsigned char *data, int length) {
    if (executors.count(*data) > 0) {
        executors[*data]->operator()(data, length);
    } else {
        BOOST_LOG_TRIVIAL(info) << "Unknow message type:  " << (int) (*data) << " of length " << length;
        std::stringstream stream;
        std::stringstream streamText;
        for (int i=0; i < length; i++){
            stream << (int)data[i]  << " ";
            stream << (data[i] >= 32 ? (char)data[i] : '?') << " ";
        }
        BOOST_LOG_TRIVIAL(info) << stream.str();
    }
}



