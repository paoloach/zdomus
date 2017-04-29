/*
 * MediaTypeProducerFactory.cpp
 *
 *  Created on: 23/apr/2015
 *      Author: Paolo Achdjian
 */

#include "MediaTypeProducerFactory.h"


namespace zigbee {
    namespace http {

        ApplicationJSONProducer MediaTypeProducerFactory::applicationJSONProducer;
        PlainTextProducer MediaTypeProducerFactory::plainTextProducer;

        MediaTypeProducerFactory::~MediaTypeProducerFactory() noexcept = default;

        const MediaTypeProducer &MediaTypeProducerFactory::getMediaType(std::shared_ptr<const Net::Http::Header::ContentType> &contentType) {
            if (contentType->mime() == MIME(Application, Json)) {
                return applicationJSONProducer;
            } else {
                return plainTextProducer;
            }
        }


    } /* namespace http */
} /* namespace zigbee */
