/*
 * IODataBuffer.cpp
 *
 *  Created on: 06/dic/2014
 *      Author: Paolo Achdjian
 */

#include <algorithm>

#include "IODataBuffer.h"

namespace zigbee {

IODataBuffer::IODataBuffer() {
}

IODataBuffer::~IODataBuffer() {
}

std::string IODataBuffer::getLine() {
	std::string result {};

	std::vector<char>::iterator trimmed = std::find_if_not(data.begin(), data.end(), [](const char&c){return iscntrl(c) || isspace(c); });
	if (trimmed != data.end()){
		std::vector<char>::iterator found = std::find(trimmed, data.end(), '\n');
		if (found != data.end()){
			std::copy(trimmed, found, std::back_inserter(result));
			data.erase(data.begin(), found);
		}
	}
	return result;
}

} /* namespace zigbee */
