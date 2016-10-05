/*
 * ZDevices.cpp
 *
 *  Created on: 28/nov/2014
 *      Author: Paolo Achdjian
 */

#include <iostream>
#include <boost/lexical_cast.hpp>
#include <memory>
#include <boost/log/trivial.hpp>


#include "NewDeviceObserver.h"
#include "ZDevices.h"
#include "jsonFields.h"
#include "Exceptions/InvalidZDevice.h"

using boost::property_tree::ptree;

using std::make_unique;
using std::shared_ptr;
using std::unique_lock;

namespace zigbee {

    ZDevices::ZDevices() {
        tokenUpdate = 0;
    }

    ZDevice * ZDevices::getDevice(const ExtAddress &extAddress) const {
        auto found = ieeeAddrDevices.find(extAddress);
        if (found != ieeeAddrDevices.end()) {
            return found->second.get();
        }
        throw InvalidZDevice(extAddress);
    }

    ZDevice *  ZDevices::getDevice(NwkAddr nwkAddress) const {
        auto found = nwkAddrDevices.find(nwkAddress);
        if (found != nwkAddrDevices.end()) {
            return found->second;
        }

        throw InvalidZDevice(nwkAddress);
    }

    ZDevice *  ZDevices::getDeviceNoExcept(NwkAddr nwkAddress) const {
        auto found = nwkAddrDevices.find(nwkAddress);
        if (found != nwkAddrDevices.end()) {
            return found->second;
        }

        return nullptr;
    }

    void ZDevices::put(const AnnunceMessage &message) {
        ExtAddress extAddress(message.extAddr);
        auto device = make_unique<ZDevice>(message);

        if (ieeeAddrDevices.count(extAddress) == 0) {
            ieeeAddrDevices.insert(std::make_pair (extAddress,  std::move(device)));
            tokenUpdate++;
        }
        NwkAddr nwkAddr{message.nwkAddr};
        if (nwkAddrDevices.count(nwkAddr) == 0) {
            nwkAddrDevices.insert({nwkAddr, ieeeAddrDevices[extAddress].get()});
        }
    }

    void ZDevices::put(const SimpleDescMessage &message) {
        NwkAddr nwkAddr{message.nwkAddr};
        auto device = nwkAddrDevices.find(nwkAddr);
        if (device != nwkAddrDevices.end()) {
            device->second->put(message);
            tokenUpdate++;
        }
    }

    ptree ZDevices::getDifferences(uint32_t token) {
        ptree result{};

        if (token < tokenUpdate) {
            result.put(TOKEN_NAME, tokenUpdate);
            for (auto & zDevice : ieeeAddrDevices) {
                ptree pDevice = createPTree(zDevice.second.get());
                result.add_child(DEVICE, pDevice);
            }
        }

        return result;
    }

    ptree ZDevices::createPTree(ZDevice * zDevice) {
        ptree result{};

        result.put(SHORT_ADDR_NAME, zDevice->getNwkAddr());
        result.put(CAPABILITY_NAME, zDevice->getCapabilities());
        result.put(EXT_ADDR_NAME, zDevice->getExtAddr());
        for (auto endpoint : zDevice->getEndpoints()) {
            ptree propertiesEndpoind = createPTree(endpoint.second);
            result.add_child(ENDPOINT, propertiesEndpoind);
        }

        return result;
    }

    boost::property_tree::ptree ZDevices::createPTree(ZEndpoint &zEndpoint) {
        ptree result{};

        result.put(SHORT_ADDR_NAME, zEndpoint.getNwkAddr());
        result.put(ENDPOINT_NAME, zEndpoint.getEndpoint());
        result.put(PROFILE_ID_NAME, zEndpoint.getAppProfId());
        result.put(DEVICE_ID_NAME, zEndpoint.getAppDeviceId());
        result.put(DEVICE_VERSION_NAME, zEndpoint.getAppDevVer());
        for (auto inCluster : zEndpoint.getInCluster()) {
            ptree inClusterTree{boost::lexical_cast<std::string>(inCluster)};
            result.push_back({std::string(IN_CLUSTER_NAME), inClusterTree});
        }
        for (auto outCluster : zEndpoint.getOutCluster()) {
            ptree outClusterTree{boost::lexical_cast<std::string>(outCluster)};
            result.push_back({OUT_CLUSTER_NAME, outClusterTree});
        }

        return result;
    }

    std::vector<ZDevice *> zigbee::ZDevices::getDevices() {
        std::vector<ZDevice *> result;

        for (const auto &device : ieeeAddrDevices) {
            result.push_back(device.second.get());
        }

        return result;
    }

    bool zigbee::ZDevices::exists(const ExtAddress &extAddress) const {
        return ieeeAddrDevices.find(extAddress) != ieeeAddrDevices.end();
    }

    void ZDevices::put(const BindResponse &) {

    }

    void ZDevices::addDeviceInfo(const IEEEAddrResp &ieeeAddressResponse) {
        auto iterDevice = ieeeAddrDevices.find(ieeeAddressResponse.ieeeAddr);
        auto device = std::make_unique<ZDevice>(ieeeAddressResponse.ieeeAddr, ieeeAddressResponse.nwkAddr,
                                                ieeeAddressResponse.children);
        BOOST_LOG_TRIVIAL(info) << "Arrived device " << ieeeAddressResponse.ieeeAddr << " ("<< ieeeAddressResponse.nwkAddr << ") with " << ieeeAddressResponse.children.size() << " children";

        if (iterDevice == ieeeAddrDevices.end()) {
            ieeeAddrDevices.insert(std::make_pair(ieeeAddressResponse.ieeeAddr, std::move(device)));
        }
        auto iterDevice2 = nwkAddrDevices.find(ieeeAddressResponse.nwkAddr);
        if (iterDevice2 == nwkAddrDevices.end()) {
            nwkAddrDevices.insert({ieeeAddressResponse.nwkAddr, ieeeAddrDevices[ieeeAddressResponse.ieeeAddr].get()});
        }
        unique_lock<std::mutex> lock(mutexObserver);
        for (auto &observer: observers) {
            observer(ieeeAddrDevices[ieeeAddressResponse.ieeeAddr].get());
        }
    }


    void ZDevices::removeObserver(std::function<void(ZDevice *)> observer) {
        unique_lock<std::mutex> lock(mutexObserver);
        auto iter = std::begin(observers);
        for (; iter != end(observers); ++iter) {
            if (iter->target<void(std::shared_ptr<ZDevice>)>() == observer.target<void(std::shared_ptr<ZDevice>)>()) {
                break;
            }
        }
        if (iter != std::end(observers)) {
            observers.erase(iter);
        }
    }

    void ZDevices::addObserver(std::function<void(ZDevice *)> observer) {
        unique_lock<std::mutex> lock(mutexObserver);
        observers.push_back(observer);
    }


} /* namespace zigbee */

