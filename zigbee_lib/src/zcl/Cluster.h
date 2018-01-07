//
// Created by paolo on 06/01/18.
//

#ifndef ZIGBEE_LIB_CLUSTER_H
#define ZIGBEE_LIB_CLUSTER_H

#include <string>
#include <memory>
#include <zigbee/EndpointID.h>
#include <zigbee/NwkAddr.h>
#include <zigbee/ClusterID.h>
#include "zcl/CmdParams/ClusterCmdParams.h"
#include "ZCLDataType.h"

namespace zigbee {
    class ZCLAttribute;

    class ZigbeeDevice;

    class Cluster {
    public:

        struct AttributeDef {
            AttributeDef(ZCLTypeDataType type, int id, std::string_view name, bool readOnly = false) :
                    type{type}, id(id), name(name), readOnly(readOnly) {
            }

            ZCLTypeDataType type;
            int id;
            std::string_view name;
            bool readOnly;
        };

        using Cmd = std::function<void(std::vector<uint8_t> &&data)>;

        struct CommandDef {
            CommandDef(Cmd &&cmd, uint32_t cmdId, std::string &&name) :
                    cmd(std::move(cmd)), cmdId(cmdId), name(std::move(name)) {
            }

//            CommandDef(Cmd cmd, uint32_t cmdId, std::string &&name,
//                       std::vector<ClusterCmdParamsBase> params) :
//                    cmd(std::move(std::move(cmd))), cmdId(cmdId), name(name), params(std::move(params)) {
//            }

//            CommandDef(Cmd cmd, uint32_t cmdId, std::string &&name,
//                       std::initializer_list<ClusterCmdParamsBase> cmdParams) :
//                    cmd(std::move(std::move(cmd))), cmdId(cmdId), name(name) {
//                std::copy(cmdParams.begin(), cmdParams.end(), std::back_inserter(params));
//            }


            CommandDef(Cmd && cmd, uint32_t cmdId, std::string &&name, std::unique_ptr<ClusterCmdParamsBase> && param) :
                    cmd(std::move(std::move(cmd))), cmdId(cmdId), name(std::move(name)) {
                params.push_back(std::move(param));
            }

            CommandDef(Cmd cmd, uint32_t cmdId, std::string &&name, std::unique_ptr<ClusterCmdParamsBase> &&param1,
                       std::unique_ptr<ClusterCmdParamsBase> && param2) :
                    cmd(std::move(std::move(cmd))), cmdId(cmdId), name(name) {
                params.push_back(std::move(param1));
                params.push_back(std::move(param2));
            }

            CommandDef(Cmd cmd, uint32_t cmdId, std::string &&name,
                       std::unique_ptr<ClusterCmdParamsBase> && param1,
                       std::unique_ptr<ClusterCmdParamsBase> && param2,
                       std::unique_ptr<ClusterCmdParamsBase> && param3) :
                    cmd(std::move(std::move(cmd))), cmdId(cmdId), name(name) {
                params.push_back(std::move(param1));
                params.push_back(std::move(param2));
                params.push_back(std::move(param3));
            }

            CommandDef(Cmd cmd, uint32_t cmdId, std::string &&name, std::unique_ptr<ClusterCmdParamsBase> && param1,
                       std::unique_ptr<ClusterCmdParamsBase> && param2, std::unique_ptr<ClusterCmdParamsBase> && param3,
                       std::unique_ptr<ClusterCmdParamsBase> && param4) :
                    cmd(std::move(std::move(cmd))), cmdId(cmdId), name(name) {
                params.push_back(std::move(param1));
                params.push_back(std::move(param2));
                params.push_back(std::move(param3));
                params.push_back(std::move(param4));
            }

            CommandDef(Cmd cmd, uint32_t cmdId, std::string &&name, std::unique_ptr<ClusterCmdParamsBase> && param1,
                       std::unique_ptr<ClusterCmdParamsBase> && param2, std::unique_ptr<ClusterCmdParamsBase> && param3,
                       std::unique_ptr<ClusterCmdParamsBase> && param4, std::unique_ptr<ClusterCmdParamsBase> && param5) :
                    cmd(std::move(std::move(cmd))), cmdId(cmdId), name(name) {
                params.push_back(std::move(param1));
                params.push_back(std::move(param2));
                params.push_back(std::move(param3));
                params.push_back(std::move(param4));
                params.push_back(std::move(param5));
            }

            CommandDef(Cmd cmd, uint32_t cmdId, std::string &&name, std::unique_ptr<ClusterCmdParamsBase> && param1,
                       std::unique_ptr<ClusterCmdParamsBase> && param2, std::unique_ptr<ClusterCmdParamsBase> && param3,
                       std::unique_ptr<ClusterCmdParamsBase> && param4, std::unique_ptr<ClusterCmdParamsBase> && param5,
                       std::unique_ptr<ClusterCmdParamsBase> && param6) :
                    cmd(std::move(std::move(cmd))), cmdId(cmdId), name(name) {
                params.push_back(std::move(param1));
                params.push_back(std::move(param2));
                params.push_back(std::move(param3));
                params.push_back(std::move(param4));
                params.push_back(std::move(param5));
                params.push_back(std::move(param6));
            }

            Cmd cmd;
            uint32_t cmdId;
            std::string name;
            std::vector<std::unique_ptr<ClusterCmdParamsBase>> params;
        };

    public:

        virtual ~Cluster() = default;

    public:
        virtual ClusterID getId() const = 0;

        virtual std::string getClusterName() const = 0;

        virtual void createAttributes(const std::vector<AttributeDef> &attributesDef)=0;

        virtual const EndpointID getEndpoint() const = 0;

        virtual NwkAddr getNetworkAddress() const = 0;

        virtual std::vector<AttributeDef> getAttributes() const =0;

        virtual const std::vector<CommandDef> & getCommands() const =0;

        virtual std::vector<ClusterCmdParamsBase *> getCmdParams(uint32_t cmd)=0;

        virtual void executeCommand(uint32_t cmd, std::vector<uint8_t> data)=0;

        virtual ZCLAttribute *getAttribute(int id) const=0;

        virtual ZCLAttribute *getAttribute(std::string_view name) const=0;

    };
}


#endif //ZIGBEE_LIB_CLUSTER_H
