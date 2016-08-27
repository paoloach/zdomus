//
// Created by paolo on 10/05/16.
//

#ifndef DOMUS_ENGINE_ANNUNCEMSGEXECUTER_H
#define DOMUS_ENGINE_ANNUNCEMSGEXECUTER_H

#include <boost/log/trivial.hpp>
#include "Executor.h"
#include "USBDevice.h"

namespace zigbee {
    class AnnunceMsgExecuter : public Executor {
    private:
        std::shared_ptr<ZDevices> zDevices;
        DomusEngineUSBDevice &usbDevice;
    public:
        AnnunceMsgExecuter(std::shared_ptr<ZDevices> zDevices, DomusEngineUSBDevice &usbDevice) : zDevices(zDevices), usbDevice(usbDevice) { }

        virtual void operator()(unsigned char *data, int) override {
            AnnunceMessage *annunceMessage = reinterpret_cast<AnnunceMessage *>(data);
            zDevices->put(*annunceMessage);
            BOOST_LOG_TRIVIAL(info) << "Annunce signal: device " << std::hex << NwkAddr(annunceMessage->nwkAddr);
            usbDevice.requestActiveEndpoints(NwkAddr(annunceMessage->nwkAddr));
            sleep(1);
            usbDevice.requestBindTable(NwkAddr(annunceMessage->nwkAddr));
        }
    };
}

#endif //DOMUS_ENGINE_ANNUNCEMSGEXECUTER_H
