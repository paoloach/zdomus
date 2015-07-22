/*
 * EndpointID.h
 *
 *  Created on: 30/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEE_ENDPOINTID_H_
#define SRC_ZIGBEE_ENDPOINTID_H_

#include <ostream>
#include <istream>
#include <boost/lexical_cast.hpp>

#include <zigbee/ZigbeeTypes.h>

namespace zigbee {

class EndpointID {
public:
	constexpr EndpointID() :
			endpointId(0) {
	}

	explicit constexpr EndpointID(int endpointId) :
			endpointId(endpointId) {
	}

	explicit EndpointID(const std::string endpointSrc) {
		this->endpointId = boost::lexical_cast<int>(endpointSrc);
	}
	constexpr EndpointID(const EndpointID & endpointId) :
			endpointId(endpointId.endpointId) {
	}

	bool operator==(const EndpointID & other) const {
		return endpointId == other.endpointId;
	}

	bool operator==(int other) const {
		return endpointId == other;
	}

	bool operator<(const EndpointID & other) const {
		return endpointId < other.endpointId;
	}

	bool operator<(int other) const {
		return endpointId < other;
	}

	ZigbeeEndpoint getId() const {
		return endpointId;
	}

	void setId(int id) {
		endpointId = id;
	}

	friend std::ostream & operator<<(std::ostream & out, const zigbee::EndpointID & endpoint);
	friend std::istream & operator>>(std::istream & in, zigbee::EndpointID & endpoint);
private:
	int endpointId;
};

inline std::ostream & operator<<(std::ostream & out, const zigbee::EndpointID & endpoint) {
	out << endpoint.endpointId;
	return out;
}

inline std::istream & operator>>(std::istream & in, zigbee::EndpointID & endpoint) {
	in >> endpoint.endpointId;
	return in;
}

} /* namespace zigbee */

//inline std::ostream & operator<<(std::ostream & out, const zigbee::EndpointID & endpoint){
//	out << endpoint.getId();
//	return out;
//}
//
//inline std::istream & operator>>( std::istream & in, zigbee::EndpointID & endpoint){
//	int id;
//	in >> id;
//	endpoint.setId(id);
//	return in;
//}
#endif /* SRC_ZIGBEE_ENDPOINTID_H_ */