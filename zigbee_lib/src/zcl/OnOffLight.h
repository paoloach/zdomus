/*
 * OnOffLight.h
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ONOFFLIGHT_H_
#define ONOFFLIGHT_H_

#include "../zigbee/messageStructure/SimpleDescMessage.h"

namespace zigbee {

class OnOffLight {
public:
	OnOffLight(SimpleDescMessage * simpleDesc);
	virtual ~OnOffLight();
};

} /* namespace zigbee */

#endif /* ONOFFLIGHT_H_ */
