/*
 * ZDevices.cpp
 *
 *  Created on: 28/nov/2014
 *      Author: Paolo Achdjian
 */

#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>

#include "ZDevices.h"
#include "jsonFields.h"
#include "Exceptions/InvalidZDevice.h"

namespace zigbee {

  using boost::property_tree::ptree;


  ZDevices::ZDevices() {
      tokenUpdate = 0;
  }

  const ZDevice &ZDevices::getDevice(const ExtAddress &extAddress) const {
      auto found = devices.find(extAddress);
      if (found != devices.end()) {
          return found->second;
      }
      throw InvalidZDevice(extAddress);
  }

  const ZDevice &ZDevices::getDevice(NwkAddr nwkAddress) const {
      for (const auto &device : devices) {
          if (device.second.getNwkAddr() == nwkAddress) {
              return device.second;
          }
      }

      throw InvalidZDevice(nwkAddress);
  }

  void ZDevices::put(const AnnunceMessage &message) {
      ExtAddress extAddress(message.extAddr);

      if (devices.count(extAddress) == 0) {
          devices.insert({extAddress, ZDevice {message}});
          tokenUpdate++;
      }
  }

  void ZDevices::put(const SimpleDescMessage &message) {

      for (auto &zDevice : devices) {
          if (zDevice.second.getNwkAddr() == message.nwkAddr) {
              zDevice.second.put(message);
              tokenUpdate++;
          }
      }
  }

  ptree ZDevices::getDifferences(uint32_t token) {
      ptree result{};

      if (token < tokenUpdate) {
          result.put(TOKEN_NAME, tokenUpdate);
          for (auto zDevice : devices) {
              ptree pDevice = createPTree(zDevice.second);
              result.add_child(DEVICE, pDevice);
          }
      }

      return result;
  }

  ptree ZDevices::createPTree(ZDevice &zDevice) {
      ptree result{};

      result.put(SHORT_ADDR_NAME, zDevice.getNwkAddr());
      result.put(CAPABILITY_NAME, zDevice.getCapabilities());
      result.put(EXT_ADDR_NAME, zDevice.getExtAddr());
      for (auto endpoint : zDevice.getEndpoints()) {
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

  std::vector<ZDevice> zigbee::ZDevices::getDevices() {
      std::vector<ZDevice> result{};

      for (const auto &device : devices) {
          result.push_back(device.second);
      }

      return result;
  }

  bool zigbee::ZDevices::exists(const ExtAddress &extAddress) const {
      return devices.find(extAddress) != devices.end();
  }

  void ZDevices::put(const BindResponse &) {

  }


} /* namespace zigbee */

