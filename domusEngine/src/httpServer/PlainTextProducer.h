/*
 * PlainTextProducer.h
 *
 *  Created on: 23/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_PLAINTEXTPRODUCER_H_
#define SRC_HTTPSERVER_PLAINTEXTPRODUCER_H_

#include "MediaTypeProducer.h"

namespace zigbee {
namespace http {

class PlainTextProducer: public MediaTypeProducer {
public:
	~PlainTextProducer() noexcept override;
	void produce(std::ostream & ostream, const boost::property_tree::ptree & properties) const noexcept override;
};

} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_PLAINTEXTPRODUCER_H_ */
