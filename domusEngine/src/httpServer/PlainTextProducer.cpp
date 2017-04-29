/*
 * PlainTextProducer.cpp
 *
 *  Created on: 23/apr/2015
 *      Author: Paolo Achdjian
 */

#include <boost/property_tree/ini_parser.hpp>

#include "PlainTextProducer.h"

namespace zigbee {
namespace http {

PlainTextProducer::~PlainTextProducer() noexcept = default;

void PlainTextProducer::produce(std::ostream& ostream, const boost::property_tree::ptree& properties) const noexcept {
	boost::property_tree::ini_parser::write_ini(ostream, properties, 0);
}

} /* namespace http */
} /* namespace zigbee */
