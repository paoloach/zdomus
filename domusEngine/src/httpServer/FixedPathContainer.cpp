/*
 * FixedPathContainer.cpp
 *
 *  Created on: 09/apr/2015
 *      Author: Paolo Achdjian
 */

#include "FixedPathContainer.h"

namespace zigbee {
namespace http {

void FixedPathContainer::addRestValue(const RestValue& restValue) {
	std::unique_lock<std::mutex> uniqueLock(mutexRestValue);

	mapRestValue.insert( {restValue.getPath(), restValue.getValue()});
}

std::string FixedPathContainer::getValue(const boost::filesystem::path& path) {
	std::unique_lock<std::mutex> uniqueLock(mutexRestValue);
	auto found = mapRestValue.find(path);
	if (found == mapRestValue.end()){
		return std::string();
	} else {
		return found->second;
	}
}

} /* namespace http */
} /* namespace zigbee */
