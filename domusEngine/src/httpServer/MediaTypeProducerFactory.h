/*
 * MediaTypeProducerFactory.h
 *
 *  Created on: 23/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_MEDIATYPEPRODUCERFACTORY_H_
#define SRC_HTTPSERVER_MEDIATYPEPRODUCERFACTORY_H_

#include "MediaTypeProducer.h"
#include "ApplicationJSONProducer.h"
#include "PlainTextProducer.h"
#include "http_header.h"

namespace zigbee {
namespace http {

class MediaTypeProducerFactory {
public:
	virtual ~MediaTypeProducerFactory() noexcept;

    static const MediaTypeProducer & getMediaType(std::shared_ptr<const Net::Http::Header::ContentType> & contentType);
private:
	static ApplicationJSONProducer applicationJSONProducer;
	static PlainTextProducer plainTextProducer;
};

} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_MEDIATYPEPRODUCERFACTORY_H_ */
