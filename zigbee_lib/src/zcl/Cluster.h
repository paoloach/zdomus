/*
 * Cluster.h
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef CLUSTER_H_
#define CLUSTER_H_

#include <experimental/string_view>
#include <string>
#include <memory>
#include <vector>
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include <functional>
#include <initializer_list>
#include "../zigbee/ZigbeeTypes.h"
#include "../zigbee/ZigbeeDevice.h"
#include "ZCLDataType.h"
#include "ZCLAttribute.h"
#include "ClustersEnum.h"
#include "CmdParams/ClusterCmdParams.h"
#include "../zigbee/EndpointID.h"
#include "../zigbee/ClusterID.h"
#include "../zigbee/NwkAddr.h"



namespace zigbee {

class Cluster {
public:

	struct AttributeDef {
		AttributeDef(ZCLTypeDataType type, int id,std::experimental::string_view  name, bool readOnly = false) :
				type{type}, id(id), name(name), readOnly(readOnly) {
		}
		ZCLTypeDataType type;
		int id;
		std::experimental::string_view name;
		bool readOnly;
	};

	using Cmd = std::function<void(std::vector<uint8_t> && data)>;

	struct CommandDef {
		CommandDef(Cmd cmd,uint32_t cmdId,  std::string && name) :
				cmd(cmd), cmdId(cmdId),name(name) {
		}
		CommandDef(Cmd cmd, uint32_t cmdId, std::string && name, std::vector<std::shared_ptr<ClusterCmdParamsBase>> params) :
				cmd(cmd), cmdId(cmdId),name(name), params(params) {
		}
		CommandDef(Cmd cmd, uint32_t cmdId, std::string && name, std::initializer_list<std::shared_ptr<ClusterCmdParamsBase>> cmdParams) :
				cmd(cmd), cmdId(cmdId),name(name) {
            std::copy(cmdParams.begin(), cmdParams.end(), std::back_inserter(params) );
		}


        CommandDef(Cmd cmd, uint32_t cmdId, std::string && name, std::shared_ptr<ClusterCmdParamsBase> cmdParams) :
                cmd(cmd), cmdId(cmdId),name(name) {
            params.push_back(cmdParams);
        }

		CommandDef(Cmd cmd, uint32_t cmdId, std::string && name, std::shared_ptr<ClusterCmdParamsBase> param1, std::shared_ptr<ClusterCmdParamsBase> param2) :
				cmd(cmd), cmdId(cmdId),name(name) {
			params.push_back(param1);
			params.push_back(param2);
		}
		CommandDef(Cmd cmd, uint32_t cmdId, std::string && name, std::shared_ptr<ClusterCmdParamsBase> param1, std::shared_ptr<ClusterCmdParamsBase> param2, std::shared_ptr<ClusterCmdParamsBase> param3) :
				cmd(cmd),cmdId(cmdId), name(name) {
			params.push_back(param1);
			params.push_back(param2);
			params.push_back(param3);
		}
		CommandDef(Cmd cmd, uint32_t cmdId, std::string && name, std::shared_ptr<ClusterCmdParamsBase> param1, std::shared_ptr<ClusterCmdParamsBase> param2, std::shared_ptr<ClusterCmdParamsBase> param3,
				std::shared_ptr<ClusterCmdParamsBase> param4) :
				cmd(cmd), cmdId(cmdId),name(name) {
			params.push_back(param1);
			params.push_back(param2);
			params.push_back(param3);
			params.push_back(param4);
		}
		CommandDef(Cmd cmd,uint32_t cmdId,  std::string && name, std::shared_ptr<ClusterCmdParamsBase> param1, std::shared_ptr<ClusterCmdParamsBase> param2, std::shared_ptr<ClusterCmdParamsBase> param3,
				std::shared_ptr<ClusterCmdParamsBase> param4,std::shared_ptr<ClusterCmdParamsBase> param5) :
				cmd(cmd), cmdId(cmdId),name(name) {
			params.push_back(param1);
			params.push_back(param2);
			params.push_back(param3);
			params.push_back(param4);
			params.push_back(param5);
		}
		CommandDef(Cmd cmd,uint32_t cmdId,  std::string && name, std::shared_ptr<ClusterCmdParamsBase> param1, std::shared_ptr<ClusterCmdParamsBase> param2, std::shared_ptr<ClusterCmdParamsBase> param3,
				std::shared_ptr<ClusterCmdParamsBase> param4,std::shared_ptr<ClusterCmdParamsBase> param5,std::shared_ptr<ClusterCmdParamsBase> param6) :
				cmd(cmd), cmdId(cmdId),name(name) {
			params.push_back(param1);
			params.push_back(param2);
			params.push_back(param3);
			params.push_back(param4);
			params.push_back(param5);
			params.push_back(param6);
		}
		Cmd cmd;
		uint32_t cmdId;
		std::string name;
		std::vector<std::shared_ptr<ClusterCmdParamsBase>> params;
	};

public:
	Cluster(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress);
	virtual ~Cluster() = default;
public:
	virtual ClusterID getId() const = 0;
	virtual std::string getClusterName() const = 0;
	virtual void createAttributes(const std::vector<AttributeDef>  & attributesDef);
	virtual const EndpointID getEndpoint() const {
		return endpoint;
	}
	virtual NwkAddr getNetworkAddress() const {
		return networkAddress;
	}
	virtual std::vector<AttributeDef> getAttributes() const {
		return _attributesDef;
	}
	virtual std::vector<CommandDef> getCommands() const {
		return _commandsDef;
	}

	virtual std::vector<std::shared_ptr<ClusterCmdParamsBase>> getCmdParams(uint32_t cmd);
	virtual void executeComand(uint32_t cmd, std::vector<uint8_t>   data);

	virtual std::shared_ptr<ZCLAttribute> getAttribute(int id) const;
	virtual std::shared_ptr<ZCLAttribute> getAttribute(std::experimental::string_view name) const;
protected:
	template<typename tp_attrType>
	std::shared_ptr<ZCLAttribute> createAttribute(const AttributeDef & attributeDef) {
		return std::make_shared<tp_attrType>(zigbeeDevice, this, attributeDef.id, attributeDef.name, attributeDef.readOnly);
	}
	void printRawData(const std::vector<uint8_t>& data);
private:
	std::shared_ptr<ZCLAttribute> createAttribute(const AttributeDef & attributeDef);
protected:
	std::vector<CommandDef> _commandsDef;
	std::vector<AttributeDef> _attributesDef;
	std::vector<std::shared_ptr<ZCLAttribute> > attributes;
	const std::shared_ptr<ZigbeeDevice> & zigbeeDevice;
	const EndpointID endpoint;
	NwkAddr networkAddress;

};

} /* namespace zigbee */

#endif /* CLUSTER_H_ */
