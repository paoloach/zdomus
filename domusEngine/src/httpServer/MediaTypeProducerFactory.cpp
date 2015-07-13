/*
 * MediaTypeProducerFactory.cpp
 *
 *  Created on: 23/apr/2015
 *      Author: Paolo Achdjian
 */

#include "MediaTypeProducerFactory.h"
#include "ApplicationJSONProducer.h"
#include "PlainTextProducer.h"

namespace zigbee {
namespace http {

ApplicationJSONProducer MediaTypeProducerFactory::applicationJSONProducer;
PlainTextProducer MediaTypeProducerFactory::plainTextProducer;

MediaTypeProducerFactory::~MediaTypeProducerFactory() noexcept {
}

const MediaTypeProducer& MediaTypeProducerFactory::getMediaType(const std::string & mediaType)  noexcept{
	if (mediaType == "application/json" ){
		return applicationJSONProducer;
	} else {
		return plainTextProducer;
	}
}

} /* namespace http */
} /* namespace zigbee */
