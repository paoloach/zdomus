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

using std::make_unique;

zigbee::UsbResponseExecutors::UsbResponseExecutors(SingletonObjects &singletonObjects,  DomusEngineUSBDevice &usbDevice) {
    executors[ANNUNCE_MSG] = make_unique<AnnunceMsgExecuter>(singletonObjects.getZDevices(), usbDevice);
    executors[SIMPLE_DESC] = make_unique<SimpleDescExecutor>(singletonObjects.getZDevices());
    executors[ATTRIBUTE_VALUES] = make_unique<AttributeValuesExecuter>(singletonObjects.getAttributeDataContainer());
    executors[BIND_TABLE] = make_unique<BindTableExecuter>(singletonObjects);
    executors[ATTRIBUTE_VALUE_REQ_ERROR] = make_unique<AttributeValueReqError>(singletonObjects.getAttributeValueSignalMap());
}

void zigbee::UsbResponseExecutors::execute(unsigned char *data, int length) {
    if (executors.count(*data) > 0) {
        executors[*data]->operator()(data, length);
    } else {
        BOOST_LOG_TRIVIAL(info) << "Unknow message type:  " << (int) (*data);
    }
}



