/*
 * Session.cpp
 *
 *  Created on: 26/nov/2014
 *      Author: Paolo Achdjian
 */

#include <iostream>
#include "Session.h"
#include "../Comand/ComandFactory.h"
#include <boost/property_tree/ptree.hpp>

namespace zigbee {

using boost::bind;
using boost::asio::buffer;
using boost::asio::async_write;
using boost::property_tree::ptree;

Session::Session(boost::asio::io_service & ioService_, ZDevices & zDevices_, std::shared_ptr<ZigbeeDevice> zigbeeDevice_, AttributeDataContainer & attributeDataContainer_) :
		socket(ioService_), zDevices(zDevices_), zigbeeDevice(zigbeeDevice_), attributeDataContainer(attributeDataContainer_) {
}

Session::~Session() {
}

void Session::start() {
	std::cout << "Start session" << std::endl;
	socket.async_read_some(buffer(tmpData), bind(&Session::readHandler, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Session::readHandler(const boost::system::error_code& error, std::size_t bytes_transferred) {
	if (!error) {
		if (bytes_transferred > 0) {
			ptree treeResponse {};
			BufferDataIterator iterBegin = tmpData.begin();
			BufferDataIterator iterEnd = iterBegin + bytes_transferred;
			dataBuffer.put(iterBegin, iterEnd);
			std::string line = dataBuffer.getLine();
			while (!line.empty()) {
				std::cout << "cmd: " << line << std::endl;
				std::vector<Comand_P> comands = ComandFactory::createComands(line, zDevices, *(zigbeeDevice.get()), attributeDataContainer);
				std::string response = responseCreator.generateResponse(comands);
				async_write(socket, buffer(response), bind(&Session::writeHandler, this, boost::asio::placeholders::error));
				line = dataBuffer.getLine();
			}
		}
	} else {
		std::cerr << "ERROR at " << __FILE__ << ":" << __LINE__ << std::endl;
	}
}

void Session::writeHandler(const boost::system::error_code& error) {
	if (!error) {
		socket.async_read_some(buffer(tmpData), bind(&Session::readHandler, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	} else {
		std::cerr << "ERROR at " << __FILE__ << ":" << __LINE__ << std::endl;
	}
}

} /* namespace zigbee */
