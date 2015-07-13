/*
 * Server.cpp
 *
 *  Created on: 26/nov/2014
 *      Author: Paolo Achdjian
 */

#include <memory>

#include "Server.h"

namespace zigbee {

const std::string Server::socketPath ("/tmp/domust_engine");

using boost::asio::local::stream_protocol;
using boost::bind;
using std::shared_ptr;
using std::make_shared;

Server::Server(boost::asio::io_service & serviceIO_, ZDevices & zDevices_,std::shared_ptr<ZigbeeDevice> zigbeeDevice_, AttributeDataContainer  & attributeDataContainer_) :
		ioService(serviceIO_), acceptor(serviceIO_, stream_protocol::endpoint(socketPath)),zDevices(zDevices_),zigbeeDevice(zigbeeDevice_),  attributeDataContainer(attributeDataContainer_) {
	shared_ptr<Session> session = make_shared<Session>(serviceIO_, zDevices_, zigbeeDevice_, attributeDataContainer_);
	sessions.push_back(session);
	acceptor.async_accept(session->getSocket(), bind(&Server::handlerAccept, this, session, _1));
}

Server::~Server() {
}

void Server::handlerAccept(shared_ptr<Session> session, const boost::system::error_code& error) {
	if (!error) {
		session->start();
	}

	shared_ptr<Session>  newSession = make_shared<Session>(ioService, zDevices, zigbeeDevice,attributeDataContainer);
	acceptor.async_accept(newSession->getSocket(), bind(&Server::handlerAccept, this, newSession, _1));
	sessions.push_back(session);

}

} /* namespace zigbee */
