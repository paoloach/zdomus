/*
 * IODataBuffer.h
 *
 *  Created on: 06/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_IO_IODATABUFFER_H_
#define SRC_IO_IODATABUFFER_H_

#include <vector>
#include <array>

namespace zigbee {

class IODataBuffer {
public:
	using InputIterator=std::array<char,1024>::iterator;
public:
	IODataBuffer();
	virtual ~IODataBuffer();

public:
	template <typename Iterator>
	void put(const Iterator & begin, const Iterator & end) {
		std::copy(begin, end, std::back_inserter(data));
	}

	std::string getLine();
private:
	std::vector<char> data;
};

} /* namespace zigbee */

#endif /* SRC_IO_IODATABUFFER_H_ */
