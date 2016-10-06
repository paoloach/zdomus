/*
 * ApplicationJSONProducer.h
 *
 *  Created on: 23/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_APPLICATIONJSONPRODUCER_H_
#define SRC_HTTPSERVER_APPLICATIONJSONPRODUCER_H_

#include "MediaTypeProducer.h"

namespace zigbee {
namespace http {

class ApplicationJSONProducer : public MediaTypeProducer{
public:
	~ApplicationJSONProducer() noexcept override;
	Poco::Net::MediaType getMediaType()const  noexcept override;
	void produce(std::ostream & ostream, const boost::property_tree::ptree & properties) const noexcept override;
};

} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_APPLICATIONJSONPRODUCER_H_ */
