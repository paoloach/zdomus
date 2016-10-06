/*
 * MediaTypeProducer.h
 *
 *  Created on: 23/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_MEDIATYPEPRODUCER_H_
#define SRC_HTTPSERVER_MEDIATYPEPRODUCER_H_

#include <Poco/Net/MediaType.h>
#include <ostream>
#include <boost/property_tree/ptree.hpp>

namespace zigbee {
namespace http {

class MediaTypeProducer {
public:
	virtual ~MediaTypeProducer() noexcept = default;
public:
	virtual Poco::Net::MediaType  getMediaType() const noexcept = 0;
	virtual void produce(std::ostream & ostream, const boost::property_tree::ptree & properties) const noexcept = 0;
};

} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_MEDIATYPEPRODUCER_H_ */
