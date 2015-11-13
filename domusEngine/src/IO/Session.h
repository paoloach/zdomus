/*
 * Session.h
 *
 *  Created on: 26/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_SESSION_H_
#define SRC_SESSION_H_

#include <array>
#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <zigbee/ZigbeeDevice.h>


#include "../ZigbeeData/ZDevices.h"
#include "AttributeDataContainer.h"
#include "IODataBuffer.h"
#include "../Comand/Comand.h"
#include "../Comand/ResponseCreator.h"

namespace zigbee {

class Session {
public:
	typedef std::array<char,1024> BufferData;
	typedef std::array<char,1024>::iterator BufferDataIterator;
public:
	Session(boost::asio::io_service & ioService, ZDevices & zDevices, std::shared_ptr<ZigbeeDevice> zigbeeDevice, AttributeDataContainer  & attributeDataContainer);

	virtual ~Session();
public:
	void start();
	boost::asio::local::stream_protocol::socket & getSocket() {return socket;}
private:
	void readHandler(const boost::system::error_code& error,std::size_t bytes_transferred );
	void writeHandler(const boost::system::error_code& error);
private:
	boost::asio::local::stream_protocol::socket socket;
	IODataBuffer dataBuffer;
	std::array<char,1024> tmpData;
	ZDevices & zDevices;
	std::shared_ptr<ZigbeeDevice> zigbeeDevice;
	AttributeDataContainer  & attributeDataContainer;
	ResponseCreator responseCreator;
};

} /* namespace zigbee */

#endif /* SRC_SESSION_H_ */
