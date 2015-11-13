/*
 * ClusterCmdParams.h
 *
 *  Created on: 26/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef CLUSTERCMDPARAMS_H_
#define CLUSTERCMDPARAMS_H_

#include <string>
#include <vector>

#include "../ZCLDataType.h"

namespace zigbee {

class ClusterCmdParamsBase {
public:
	ClusterCmdParamsBase(std::string && name) :
			name{name} {
	}
	virtual ~ClusterCmdParamsBase() {
	}
	std::string getName() const {
		return name;
	}
	virtual const ZCLTypeBase & getType() const =0;
	virtual ZCLTypeDataType getZCLDataType() const =0;
private:
	std::string name;
};

template<ZCLTypeDataType z>
class ClusterCmdParams: public ClusterCmdParamsBase {
public:
	template <typename ARG>
	ClusterCmdParams(const ARG & name) :
			ClusterCmdParamsBase{std::move(name)} {
	}
	virtual ~ClusterCmdParams() {
	}
public:

	virtual const ZCLTypeBase & getType() const {
		return dataType;
	}
	virtual ZCLTypeDataType getZCLDataType() const {
		return dataType.getZCLDataType();
	}
private:
	ZCLType<z> dataType;
};

template<ZCLTypeDataType z>
class ClusterCmdListParams: public ClusterCmdParamsBase {
public:
	ClusterCmdListParams(std::string && name) :
			ClusterCmdParamsBase(std::move(name)) {
	}
	virtual ~ClusterCmdListParams() {
	}
public:

	virtual const ZCLTypeBase & getType() const {
		return dataArrayType;
	}
	virtual ZCLTypeDataType getZCLDataType() const {
		return dataArrayType.getZCLDataType();
	}
private:
	ZCLCmdList<z> dataArrayType;
};

} /* namespace zigbee */

#endif /* CLUSTERCMDPARAMS_H_ */
