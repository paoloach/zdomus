/*
 * ApplicationJSONProducer.cpp
 *
 *  Created on: 23/apr/2015
 *      Author: Paolo Achdjian
 */

#include <boost/property_tree/json_parser.hpp>

#include "ApplicationJSONProducer.h"

namespace zigbee {
namespace http {


ApplicationJSONProducer::~ApplicationJSONProducer() noexcept = default;

void ApplicationJSONProducer::produce(std::ostream& ostream, const boost::property_tree::ptree& properties) const noexcept {
	boost::property_tree::json_parser::write_json(ostream, properties, false);
}

} /* namespace http */
} /* namespace zigbee */
