/*
 * ResponseCreator.h
 *
 *  Created on: 21/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_COMAND_RESPONSECREATOR_H_
#define SRC_COMAND_RESPONSECREATOR_H_

#include <vector>
#include <string>
#include "Comand.h"

namespace zigbee {

class ResponseCreator {
public:
	std::string generateResponse(std::vector<Comand_P> & comands);
};

} /* namespace zigbee */

#endif /* SRC_COMAND_RESPONSECREATOR_H_ */
