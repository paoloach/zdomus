/*
 * ShowDevice.h
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTACTIONS_SHOWDEVICE_H_
#define SRC_HTTPSERVER_RESTACTIONS_SHOWDEVICE_H_

#include "../RestParser/RestActions.h"

namespace zigbee {

class SingletonObjects;
namespace http {

class PlaceHolders;

class ShowDevice : public ActionHandler {
public:
	ShowDevice(SingletonObjects & singletons) noexcept : singletons(singletons){};
	void operator()(const PlaceHolders && placeHolder, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
private:
	SingletonObjects & singletons;
};

} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTACTIONS_SHOWDEVICE_H_ */
