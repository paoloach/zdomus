/*
 * ZigbeeDeviceException.h
 *
 *  Created on: 31/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEEDATA_ZIGBEEDEVICEEXCEPTION_H_
#define SRC_ZIGBEEDATA_ZIGBEEDEVICEEXCEPTION_H_

#include <exception>
#include <string>

namespace zigbee {

class ZigbeeDeviceException : public std::exception{
public:
	ZigbeeDeviceException(const std::string & message);
	ZigbeeDeviceException(){};
	virtual ~ZigbeeDeviceException();
public:
	virtual const char* what() const noexcept;
	std::string getMessage() const;
protected:
	std::string message;
};

} /* namespace zigbee */

#endif /* SRC_ZIGBEEDATA_ZIGBEEDEVICEEXCEPTION_H_ */
