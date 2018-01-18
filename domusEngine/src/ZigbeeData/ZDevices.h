/*
 * ZDevices.h
 *
 *  Created on: 28/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEEDATA_ZDEVICES_H_
#define SRC_ZIGBEEDATA_ZDEVICES_H_

#include <boost/property_tree/ptree.hpp>
#include <map>
#include <memory>
#include <functional>
#include <mutex>
#include <zigbee/messageStructure/AnnunceMessage.h>
#include <zigbee/messageStructure/SimpleDescMessage.h>
#include <zigbee/messageStructure/IEEEAddressResponse.h>
#include "ZDevice.h"
#include "../usb/BindResponse.h"
#include "NewDeviceObserver.h"

namespace zigbee {


    class ZDevices {
    public:
        using Observer=std::function<void(ZDevice *)>;

        ZDevices();

        virtual ~ZDevices() = default;

    public:

        virtual void put(const AnnunceMessage &message);

        virtual void put(const SimpleDescMessage &message);

        virtual void put(const ZEndpoint &message);

        virtual void put(const BindResponse &message);

        virtual void addDeviceInfo(const IEEEAddressResponse *ieeeAddressResponse);

        virtual boost::property_tree::ptree getDifferences(uint32_t token);

        virtual int getNumDevices() const { return ieeeAddrDevices.size(); }

        virtual std::vector<ZDevice *> getDevices();

        virtual ZDevice *getDevice(const ExtAddress &extAddress) const;

        virtual ZDevice *getDevice(NwkAddr nwkAddress) const;

        virtual ZDevice *getDeviceNoExcept(NwkAddr nwkAddress) const;

        virtual bool exists(const ExtAddress &extAddress) const;

        virtual void addObserver(Observer observer);

        virtual void removeObserver(Observer observer);

    private:
        boost::property_tree::ptree createPTree(ZDevice *zDevice);

        boost::property_tree::ptree createPTree(ZEndpoint &zEndpoint);

    private:
        std::map<ExtAddress, std::unique_ptr<ZDevice>> ieeeAddrDevices;
        std::map<NwkAddr, ZDevice *> nwkAddrDevices;
        std::vector<Observer> observers;
        uint32_t tokenUpdate;
        std::mutex mutexObserver;
    };

    using ZDevices_P = zigbee::ZDevices *;

} /* namespace zigbee */

#endif /* SRC_ZIGBEEDATA_ZDEVICES_H_ */
