/*
 * Cluster.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include <exception>

#include <iostream>
#include <algorithm>
#include <src/zcl/attributeTypes/implementation/ZCLOctetStringImp.h>
#include <src/zcl/attributeTypes/implementation/ZCLint8AttributeImpl.h>
#include <src/zcl/attributeTypes/implementation/ZCLint16AttributeImpl.h>
#include <src/zcl/attributeTypes/implementation/ZCLint24AttributeImpl.h>
#include <src/zcl/attributeTypes/implementation/ZCLint32AttributeImpl.h>
#include "ClusterImpl.h"
#include "src/zcl/attributeTypes/implementation/ZCLuint8AttributeImpl.h"
#include "src/zcl/attributeTypes/implementation/ZCLuint16AttributeImpl.h"
#include "src/zcl/attributeTypes/implementation/ZCLuint24AttributeImpl.h"
#include "src/zcl/attributeTypes/implementation/ZCLuint32AttributeImpl.h"
#include "src/zcl/attributeTypes/implementation/ZCLuint48AttributeImpl.h"
#include "src/zcl/attributeTypes/implementation/ZCLStringAttributeImpl.h"
#include "src/zcl/attributeTypes/implementation/ZCLbitmap8bitAttribute.h"
#include "src/zcl/attributeTypes/implementation/ZCLBitmap16bitAttributeImpl.h"
#include "src/zcl/attributeTypes/implementation/ZCLBitmap32bitAttributeImpl.h"
#include "src/zcl/attributeTypes/implementation/ZCLbooleanAttributeImpl.h"
#include "src/zcl/attributeTypes/implementation/ZCLenum8bitAttributeImpl.h"
#include "src/zcl/attributeTypes/implementation/ZCLIEEEAddressAttributeImpl.h"
#include "src/zcl/attributeTypes/implementation/ZCLUTCTimeImpl.h"
#include "src/zcl/exceptions/AttributeNotFoundException.h"

using std::copy;
using std::back_inserter;

namespace zigbee {

    ClusterImpl::ClusterImpl(ZigbeeDevice *zigbeeDevice, const EndpointID &endpoint, NwkAddr networkAddress) :
            zigbeeDevice(zigbeeDevice), endpoint(endpoint), networkAddress(networkAddress) {

    }

    void ClusterImpl::createAttributes(const std::vector<ClusterImpl::AttributeDef> &attributesDef) {
        attributes.clear();
        copy(attributesDef.begin(), attributesDef.end(), back_inserter(_attributesDef));
        for (const ClusterImpl::AttributeDef &attributeDef : attributesDef) {
            attributes.push_back(createAttribute(attributeDef));
        }
    }

    void ClusterImpl::executeCommand(uint32_t cmdId, std::vector<uint8_t> data) {
        auto found = std::find_if(_commandsDef.begin(), _commandsDef.end(),
                                  [cmdId](const CommandDef &cmd) -> bool { return cmd.cmdId == cmdId; });
        if (found != _commandsDef.end()) {
            (*found).cmd(std::move(data));
        }
    }

    ZCLAttribute *ClusterImpl::getAttribute(int id) const {
        for (auto &attribute : attributes) {
            if (attribute->getIdentifier() == id) {
                return attribute.get();
            }
        }
        return nullptr;
    }

    ZCLAttribute *ClusterImpl::getAttribute(std::string_view name) const {
        for (auto &attribute : attributes) {
            if (attribute->getName() == name) {
                return attribute.get();
            }
        }
        throw AttributeNotFoundException();
    }

    std::vector<ClusterCmdParamsBase * > ClusterImpl::getCmdParams(uint32_t cmdId) {
        std::vector<ClusterCmdParamsBase * > result;
        auto found = std::find_if(_commandsDef.begin(), _commandsDef.end(),
                                  [cmdId](const CommandDef &cmd) -> bool { return cmd.cmdId == cmdId; });
        if (found != _commandsDef.end()) {
            for(auto & cmd: found->params){
                result.push_back(cmd.get());
            }
        }
        return result;
    }

    void ClusterImpl::printRawData(const std::vector<uint8_t> &data) {
        for (uint8_t d : data) {
            std::cout << (int) (d) << " ";
        }
        std::cout << std::endl;
    }

    std::unique_ptr<ZCLAttributeImpl> ClusterImpl::createAttribute(const AttributeDef &attributeDef) {
        switch (attributeDef.type) {
            case ZCLTypeDataType::ZCLTypeenum8:
                return createAttribute<ZCLEnum8bitAttributeImpl>(attributeDef);
            case ZCLTypeDataType::ZCLTypeSInt8:
                return createAttribute<ZCLint8AttributeImpl>(attributeDef);
            case ZCLTypeDataType::ZCLTypeSInt16:
                return createAttribute<ZCLint16AttributeImpl>(attributeDef);
            case ZCLTypeDataType::ZCLTypeUInt8:
                return createAttribute<ZCLUINT8AttributeImpl>(attributeDef);
            case ZCLTypeDataType::ZCLTypeUInt16:
                return createAttribute<ZCLUINT16AttributeImpl>(attributeDef);
            case ZCLTypeDataType::ZCLTypeSInt24:
                return createAttribute<ZCLint24AttributeImpl>(attributeDef);
            case ZCLTypeDataType::ZCLTypeUInt24:
                return createAttribute<ZCLUINT16AttributeImpl>(attributeDef);
            case ZCLTypeDataType::ZCLTypeSInt32:
                return createAttribute<ZCLint32AttributeImpl>(attributeDef);
            case ZCLTypeDataType::ZCLTypeUInt32:
                return createAttribute<ZCLUINT32AttributeImpl>(attributeDef);
            case ZCLTypeDataType::ZCLTypeUInt48:
                return createAttribute<ZCLUINT48AttributeImpl>(attributeDef);
            case ZCLTypeDataType::ZCLType8bitBitmap:
                return createAttribute<ZCLBitmap8bitAttributeImpl>(attributeDef);
            case ZCLTypeDataType::ZCLType16bitBitmap:
                return createAttribute<ZCLBitmap16bitAttributeImpl>(attributeDef);
            case ZCLTypeDataType::ZCLType32bitBitmap:
                return createAttribute<ZCLBitmap32bitAttributeImpl>(attributeDef);
            case ZCLTypeDataType::ZCLTypeStringChar:
                return createAttribute<ZCLStringAttributeImpl>(attributeDef);
            case ZCLTypeDataType::ZCLTypeStringOctect:
                return createAttribute<ZCLOctetStringImpl>(attributeDef);
            case ZCLTypeDataType::ZCLTypeBool:
                return createAttribute<ZCLBooleanAttributeImpl>(attributeDef);
            case ZCLTypeDataType::ZCLTypeUTCTime:
                return createAttribute<ZCLUTCTimeImpl>(attributeDef);
            case ZCLTypeDataType::ZCLTypeIEEEaddress:
                return createAttribute<ZCLIEEEAddressAttributeImpl>(attributeDef);
            default:
                std::cerr << __FILE__ << ":" << __LINE__ << ": Used an invalid type: " << attributeDef.type
                          << std::endl;
                throw std::exception();
        }
    }

} /* namespace zigbee */

