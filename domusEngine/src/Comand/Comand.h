/*
 * Comand.h
 *
 *  Created on: 26/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_COMAND_COMAND_H_
#define SRC_COMAND_COMAND_H_


#include <vector>
#include <memory>
#include <boost/property_tree/ptree.hpp>

namespace zigbee {

class Comand {
public:
	virtual ~Comand(){}
	virtual bool parseData(const std::string &line)=0;
	virtual void execute()=0;
	virtual void getResponse(boost::property_tree::ptree & result)=0;
};

typedef std::shared_ptr<Comand> Comand_P;

}


#endif /* SRC_COMAND_COMAND_H_ */
