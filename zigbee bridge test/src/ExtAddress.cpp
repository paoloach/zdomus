/*
 * ExtAddress.cpp
 *
 *  Created on: 30/nov/2014
 *      Author: Paolo Achdjian
 */

#include <algorithm>
#include <ios>
#include <iomanip>
#include <boost/lexical_cast.hpp>

#include "ExtAddress.h"

namespace zigbee {
using namespace std;

ExtAddress::ExtAddress() {
	std::fill(data.begin(), data.end(), 0);
}

ExtAddress::ExtAddress(std::array<uint8_t, Z_EXTADDR_LEN> extAddr) {
	std::copy(std::begin(extAddr), std::end(extAddr), data.begin());
}

ExtAddress::ExtAddress(const uint8_t * extAddr) {
	std::copy(extAddr, extAddr + Z_EXTADDR_LEN, data.begin());
}

ExtAddress & ExtAddress::operator=(const std::array<uint8_t, Z_EXTADDR_LEN> & addr) {
	std::copy(std::begin(addr), std::end(addr), data.begin());
	return *this;
}

ExtAddress & ExtAddress::operator=(const uint8_t addr[Z_EXTADDR_LEN]) {
	std::copy(addr, addr + Z_EXTADDR_LEN, data.begin());
	return *this;
}

void ExtAddress::assign(const std::array<uint8_t, Z_EXTADDR_LEN>& addr) {
	std::copy(std::begin(addr), std::end(addr), data.begin());
}

ExtAddress::~ExtAddress() {
}

bool ExtAddress::operator==(const ExtAddress & other) const {
	return data == other.data;
}

std::ostream & operator<<(std::ostream & stream, const ExtAddress & extAddr) {

	for (int i = 0; i < Z_EXTADDR_LEN - 1; i++) {
		stream << std::setw(2) << std::setfill('0') << std::hex << extAddr.getNible(i) << "-";
	}

	stream << std::setw(2) << std::setfill('0') << std::hex << extAddr.getNible(Z_EXTADDR_LEN - 1);

	return stream;
}
std::istream & operator>>(std::istream & stream, ExtAddress & extAddr) {
	std::array<uint8_t, Z_EXTADDR_LEN> data;

	for (int i = 0; i < 7; i++) {
		char digit[3] { 0, 0, 0 };
		char minus { };
		stream >> digit[0] >> digit[1] >> minus;
		if (minus != '-') {
			stream.setstate(std::ios_base::failbit);
			return stream;
		}
		try {
			data[i] = std::stoi(digit, 0, 16);
		} catch (std::invalid_argument & e) {
			std::cerr << "unable to convert " << digit << " to integer" << std::endl;
			stream.setstate(std::ios_base::failbit);
			return stream;
		} catch (std::out_of_range & e) {
			std::cerr << "unable to convert " << digit << " to integer" << std::endl;
			stream.setstate(std::ios_base::failbit);
			return stream;
		}
	}
	char digit[3] { 0, 0, 0 };
	stream >> digit[0] >> digit[1];
	try {
		data[7] = std::stoi(digit, 0, 16);
	}  catch (std::invalid_argument & e) {
		std::cerr << "unable to convert " << digit << " to integer" << std::endl;
		stream.setstate(std::ios_base::failbit);
		return stream;
	} catch (std::out_of_range & e) {
		std::cerr << "unable to convert " << digit << " to integer" << std::endl;
		stream.setstate(std::ios_base::failbit);
		return stream;
	}

	extAddr.assign(data);

	return stream;
}

bool zigbee::ExtAddress::operator <(const ExtAddress& other) const {
	for (int i=0; i < Z_EXTADDR_LEN; i++){
		if (data[i] == other.data[i]){
			continue;
		}
		return data[i] < other.data[i];
	}
	return false;
}

} /* namespace zigbee */

