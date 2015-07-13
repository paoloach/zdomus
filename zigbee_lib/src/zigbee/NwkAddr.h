/*
 * NwkAddr.h
 *
 *  Created on: 11/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEE_NWKADDR_H_
#define SRC_ZIGBEE_NWKADDR_H_

#include <string>
#include <boost/lexical_cast.hpp>
#include <ostream>
#include <istream>
#include <zigbee/ZigbeeTypes.h>

namespace zigbee {

class NwkAddr {
public:
	constexpr NwkAddr() :
			address(0) {
	}

	explicit constexpr NwkAddr(int address) :
			address(address) {
	}

	explicit NwkAddr(const std::string & addressSrc) :
			address(boost::lexical_cast<int>(addressSrc)) {
	}

	constexpr NwkAddr(const NwkAddr & other) :
			address(other.address) {
	}

	bool operator==(const NwkAddr other) const {
		return address == other.address;
	}

	bool operator==(int other) const {
		return address == other;
	}

	bool operator<(const NwkAddr other) const {
		return address < other.address;
	}

	bool operator<(int other) const {
		return address < other;
	}

	ZigbeeNwkAddress getId() const {
		return address;
	}

	void setId(int id) {
		address = id;
	}

	friend std::ostream & operator<<(std::ostream & out, const NwkAddr & address);
	friend std::istream & operator>>( std::istream & in, NwkAddr & address);
private:
	int address;
};

inline std::ostream & operator<<(std::ostream & out, const NwkAddr & address){
	out << address.address;
	return out;
}

inline std::istream & operator>>( std::istream & in, NwkAddr & address){
	in >> address.address;
	return in;
}

} /* namespace zigbee */

#endif /* SRC_ZIGBEE_NWKADDR_H_ */
