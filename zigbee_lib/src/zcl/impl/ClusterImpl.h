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
#include <utility>
#include <vector>
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include <functional>
#include <initializer_list>
#include "src/zigbee/ZigbeeTypes.h"
#include "src/zigbee/ZigbeeDevice.h"
#include "src/zcl/ZCLDataType.h"
#include "src/zcl/impl/ZCLAttributeImpl.h"
#include "src/zcl/ClustersEnum.h"
#include "src/zcl/CmdParams/ClusterCmdParams.h"
#include "src/zigbee/EndpointID.h"
#include "src/zigbee/ClusterID.h"
#include "src/zigbee/NwkAddr.h"
#include "zcl/Cluster.h"


namespace zigbee {

    class ClusterImpl : public  Cluster{
    public:
        ClusterImpl(ZigbeeDevice *zigbeeDevice, const EndpointID &endpoint, NwkAddr networkAddress);

        virtual ~ClusterImpl() = default;

    public:
        virtual void createAttributes(const std::vector<AttributeDef> &attributesDef);

        const EndpointID getEndpoint() const override {
            return endpoint;
        }

        NwkAddr getNetworkAddress() const  override {
            return networkAddress;
        }

        std::vector<AttributeDef> getAttributes() const override {
            return _attributesDef;
        }

        const std::vector<CommandDef> & getCommands() const override {
            return _commandsDef;
        }

        std::vector<ClusterCmdParamsBase *> getCmdParams(uint32_t cmd) override ;

        void executeCommand(uint32_t cmd, std::vector<uint8_t> data) override ;

        ZCLAttribute * getAttribute(int id) const override ;

        ZCLAttribute * getAttribute(std::string_view name) const override ;

    protected:
        template<typename tp_attrType>
        std::unique_ptr<ZCLAttributeImpl> createAttribute(const AttributeDef &attributeDef) {
            return std::make_unique<tp_attrType>(zigbeeDevice, this, attributeDef.id, attributeDef.name,
                                                 attributeDef.readOnly);
        }

        void printRawData(const std::vector<uint8_t> &data);

    private:
        std::unique_ptr<ZCLAttributeImpl> createAttribute(const AttributeDef &attributeDef);

    protected:
        std::vector<CommandDef> _commandsDef;
        std::vector<AttributeDef> _attributesDef;
        std::vector<std::unique_ptr<ZCLAttribute> > attributes;
        ZigbeeDevice *zigbeeDevice;
        const EndpointID endpoint;
        NwkAddr networkAddress;

    };

} /* namespace zigbee */

#endif /* CLUSTER_H_ */
