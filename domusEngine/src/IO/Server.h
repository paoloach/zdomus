/*
 * Server.h
 *
 *  Created on: 26/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_SERVER_H_
#define SRC_SERVER_H_

#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <cstdio>
#include <vector>
#include "Session.h"

#include "../ZigbeeData/ZDevices.h"
#include "AttributeDataContainer.h"

namespace zigbee {


class Server {
public:
	static const std::string socketPath;
public:
	Server(boost::asio::io_service & ioService, ZDevices & zDevices, std::shared_ptr<ZigbeeDevice> zigbeeDevice, AttributeDataContainer  & attributeDataContainer);
	virtual ~Server();
private:
	void handlerAccept(std::shared_ptr<Session> newSession, const boost::system::error_code& error);
private:
	boost::asio::io_service & ioService;
	boost::asio::local::stream_protocol::acceptor acceptor;
	ZDevices & zDevices;
	std::shared_ptr<ZigbeeDevice> zigbeeDevice;
	AttributeDataContainer  & attributeDataContainer;
	std::vector<std::shared_ptr<Session>> sessions;
};

} /* namespace zigbee */

#endif /* SRC_SERVER_H_ */
