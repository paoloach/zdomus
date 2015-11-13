/*
 * PlaceHolders.cpp
 *
 *  Created on: 20/mag/2015
 *      Author: Paolo Achdjian
 */

#include <iostream>

#include "Exceptions/PlaceholderNotFound.h"
#include "PlaceHolders.h"

namespace zigbee {
namespace http {

PlaceHolders::PlaceHolders(RestPath&& restPath, PathReceived&& pathReceived) noexcept :restPath(std::move(restPath)), pathReceived(std::move(pathReceived)) {

}

PlaceHolders::PlaceHolders(const RestPath& restPath, PathReceived&& pathReceived) noexcept :restPath(restPath), pathReceived(std::move(pathReceived)){
}

std::string PlaceHolders::getInternal(std::string&& placeHolder) const  {
	auto receivedElem =  pathReceived.begin() ;
	auto pathElemen = restPath.begin() ;

	std::cout << "placeHolder = " << placeHolder << std::endl;

	while (pathElemen != restPath.end()) {
		if (pathElemen->isPlaceholder()) {
			if (pathElemen->getValue() == placeHolder){
				return *receivedElem;
			}
		}
		receivedElem++;
		pathElemen++;

	}
	throw PlaceholderNotFound {};
}

} /* namespace http */
} /* namespace zigbee */

