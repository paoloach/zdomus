/*
 * ExtAddress.h
 *
 *  Created on: 30/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEEDATA_EXTADDRESS_H_
#define SRC_ZIGBEEDATA_EXTADDRESS_H_

#include <zigbee/zigbeeConfig.h>
#include <array>
#include <iostream>

namespace zigbee {

class ExtAddress {
public:
	ExtAddress();
	ExtAddress(std::array<uint8_t, Z_EXTADDR_LEN> extAddr);
	ExtAddress(const uint8_t * extAddr);
	ExtAddress & operator=(const std::array<uint8_t, Z_EXTADDR_LEN> & extAddr);
	ExtAddress & operator=(const uint8_t extAddr[Z_EXTADDR_LEN]);
	void assign(const std::array<uint8_t, Z_EXTADDR_LEN> & extAddr);
	bool operator==(const ExtAddress & other) const;
	bool operator<(const ExtAddress & other) const;
	virtual ~ExtAddress();
	uint32_t getNible(int i) const {return data[i];}
private:
	std::array<uint8_t, Z_EXTADDR_LEN> data;

};

std::ostream & operator<<(std::ostream & stream, const ExtAddress & extAddr);
std::istream & operator>>(std::istream & stream, ExtAddress & extAddr);

} /* namespace zigbee */

#endif /* SRC_ZIGBEEDATA_EXTADDRESS_H_ */
