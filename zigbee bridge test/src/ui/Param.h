/*
 * Param.h
 *
 *  Created on: 28/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef PARAM_H_
#define PARAM_H_

namespace zigbee {
class Param {
public:
	virtual std::vector<uint8_t> getParamData()=0;
};
}

#endif /* PARAM_H_ */
