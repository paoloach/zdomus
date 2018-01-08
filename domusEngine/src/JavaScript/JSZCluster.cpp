/*
 * JSZCluster.cpp
 *
 *  Created on: 04/gen/2015
 *      Author: Paolo Achdjian
 */

#include <boost/log/trivial.hpp>
#include <zcl/Cluster.h>
#include "JSObjects.h"
#include "JSZCluster.h"
#include "JSZAttribute.h"
#include "Exceptions/JSExceptionStream.h"
#include "Exceptions/JSException.h"
#include "JSZAttributeFactory.h"
#include "Exceptions/JSExceptionArgNoExtAddress.h"
#include "Exceptions/JSExceptionWrongArgumentsNumber.h"
#include "Exceptions/JSExceptionNoDevice.h"
#include "Exceptions/JSExceptionNoInCluster.h"
#include "Exceptions/JSExceptionNoEndpoint.h"
#include "../Utils/Clusters.h"

using std::stringstream;
using namespace v8;
using std::shared_ptr;

namespace zigbee {

    JSZCluster::JSZCluster(JSZAttributeFactory *jsZAttributeFactory_, SingletonObjects *singletonObjects) : singletonObjects(singletonObjects),
                                                                                                            jsZAttributeFactory(jsZAttributeFactory_) {
    }

    void JSZCluster::initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::Object> &global) {
        Local<String> jszClusterClassName = String::NewFromUtf8(isolate, JSZCLUSTER);
        // methods
        Local<String> getProperyByIdMethod = String::NewFromUtf8(isolate, GET_PROPERTY_BY_ID);
        Local<String> executeCmdByIdMethod = String::NewFromUtf8(isolate, EXECUTE_CMD_BY_ID);

        Local<FunctionTemplate> zClusterFunctionTemplate = FunctionTemplate::New(isolate, constructor, External::New(isolate, this));
        zClusterFunctionTemplate->SetClassName(jszClusterClassName);
        Local<ObjectTemplate> zClusterInstanceTemplate = zClusterFunctionTemplate->InstanceTemplate();

        zClusterInstanceTemplate->SetInternalFieldCount(3);
        // attributes
        // functions
        zClusterInstanceTemplate->Set(getProperyByIdMethod, FunctionTemplate::New(isolate, jsGetPropertyById));
        zClusterInstanceTemplate->Set(executeCmdByIdMethod, FunctionTemplate::New(isolate, jsExecuteCmdById));
        global->Set(jszClusterClassName, zClusterFunctionTemplate->GetFunction());

        functionTemplate.Reset(isolate, zClusterFunctionTemplate);
    }

    v8::Local<v8::Object> JSZCluster::createInstance(v8::Isolate *isolate, const ExtAddress &extAddress, EndpointID endpointId, ClusterID clusterId) {

        if (!singletonObjects->getZDevices()->exists(extAddress)) {
            throw JSExceptionNoDevice(extAddress);
        }
        auto zDevice = singletonObjects->getZDevices()->getDevice(extAddress);

        NwkAddr nwkAddress = zDevice->getNwkAddr();
        Key key(nwkAddress, endpointId, clusterId);
        if (usedCluster.count(key) > 0) {
            return Local<Object>::New(isolate, usedCluster[key].get<0>());
        }

        if (!zDevice->isEndpointPresents(endpointId)) {
            throw JSExceptionNoEndpoint(extAddress, endpointId);
        }

        ZEndpoint zEndpoint = zDevice->getEndpoint(endpointId);
        if (!zEndpoint.hasInCluster(clusterId)) {
            throw JSExceptionNoInCluster(extAddress, endpointId, clusterId);
        }

        Local<ObjectTemplate> zClusterTemplate = Local<FunctionTemplate>::New(isolate, functionTemplate)->InstanceTemplate();
        Local<Object> zClusterInstance = zClusterTemplate->NewInstance();

        zClusterInstance->SetInternalField(0, External::New(isolate, this));

        Clusters * clusters = singletonObjects->getClusters();
        Cluster * cluster = clusters->getCluster(nwkAddress, endpointId, clusterId);
        zClusterInstance->SetInternalField(1, External::New(isolate, cluster));

        std::shared_ptr<ExtAddress> usedAddr = getPersistenceExtAddress(extAddress);
        zClusterInstance->SetInternalField(2, External::New(isolate, usedAddr.get()));

        Value value{};

        value.get<0>().Reset(isolate, zClusterInstance);
        boost::get<1>(value) = cluster;

        usedCluster.insert({key, value});

        return zClusterInstance;
    }

    void JSZCluster::weakCallback(const v8::WeakCallbackInfo<JSZCluster> &data) {

        JSZCluster *This = data.GetParameter();
        Cluster *cluster = (Cluster *) data.GetInternalField(1);

        NwkAddr nwkAddress = cluster->getNetworkAddress();
        EndpointID endpointId = cluster->getEndpoint();
        ClusterID clusterId = cluster->getId();

        Key key(nwkAddress, endpointId, clusterId);

        This->usedCluster.erase(key);
    }

    // Constructor:
    //   param1: extented adderess
    //   param2: endpointId
    //   param3: clusterId
    void JSZCluster::constructor(const v8::FunctionCallbackInfo<v8::Value> &info) {
        if (info.IsConstructCall()) {
            return;
        }
        Isolate *isolate = info.GetIsolate();
        try {
            JSZCluster *This = (JSZCluster *) (Local<External>::Cast(info.Data())->Value());
            checkConstructorValidArgument(isolate, info);
            ExtAddress extAddress;
            if (info[0]->IsUint32()) {
                NwkAddr nwkAddr(info[0].As<v8::Integer>()->Value());
                auto device = This->singletonObjects->getZDevices()->getDevice(nwkAddr);
                extAddress = device->getExtAddr();
            } else {
                extAddress = getExtAddressFromArg(info, 0);
            }
            EndpointID endpointId(info[1].As<v8::Integer>()->Value());
            ClusterID clusterId(info[2].As<v8::Integer>()->Value());

            info.GetReturnValue().Set(This->createInstance(info.GetIsolate(), extAddress, endpointId, clusterId));
        } catch (std::exception &excp) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
            isolate->ThrowException(errorMsg);
        }
    }

    void JSZCluster::checkConstructorValidArgument(v8::Isolate *, const v8::FunctionCallbackInfo<v8::Value> &info) {
        if (info.Length() != 3) {
            throw JSExceptionWrongArgumentsNumber(JSZCLUSTER, info.Length(), 3);
        }
        Local<v8::Value> arg0 = info[0];
        if (!arg0->IsString() && !arg0->IsUint32()) {
            throw JSExceptionArgNoExtAddress(JSZCLUSTER, 1);
        }
        Local<v8::Value> arg1 = info[1];
        if (!arg1->IsUint32()) {
            throw JSExceptionArgNoUInteger(JSZCLUSTER, 2);
        }
        Local<v8::Value> arg2 = info[2];
        if (!arg2->IsUint32()) {
            throw JSExceptionArgNoUInteger(JSZCLUSTER, 3);
        }
    }

    ExtAddress JSZCluster::getExtAddressFromArg(const v8::FunctionCallbackInfo<v8::Value> &info, int index) {
        v8::String::Utf8Value extAddressString(info[index]);
        std::stringstream stream{*extAddressString};
        ExtAddress extAddress{};
        stream >> extAddress;
        return extAddress;
    }

    void JSZCluster::jsGetPropertyById(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        if (info.Length() != 1) {
            JSExceptionStream stream{isolate};
            stream << GET_PROPERTY_BY_ID << " needs one argument: an integer for the property id";
            stream.throwException();
            return;
        }
        uint32_t propertyId = info[0]->ToUint32()->Value();
        Cluster *cluster = getCluster(info);
        JSZCluster *This = getThis(info);
        ZCLAttribute * attribute = cluster->getAttribute(propertyId);
        auto attributeValue = This->jsZAttributeFactory->createAttributeInstance(isolate, attribute);
        info.GetReturnValue().Set(attributeValue);
    }

    std::shared_ptr<ExtAddress> JSZCluster::getPersistenceExtAddress(const ExtAddress &extAddress) {
        std::shared_ptr<ExtAddress> usedAddr{};
        if (usedExtAddresses.count(extAddress) == 0) {
            usedAddr = std::make_shared<ExtAddress>(extAddress);
            usedExtAddresses[extAddress] = usedAddr;
        } else {
            usedAddr = usedExtAddresses[extAddress];
        }
        return usedAddr;
    }

    Cluster *JSZCluster::getCluster(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Local<Object> self = info.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(1));
        return (Cluster *) wrap->Value();
    }

    void JSZCluster::jsExecuteCmdById(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Isolate *isolate = info.GetIsolate();
        try {
            checkIdCmd(info);
            std::vector<uint8_t> data;
            uint32_t cmdId = info[0]->ToUint32()->Value();
            Cluster *cluster = getCluster(info);
            auto cmdParams(cluster->getCmdParams(cmdId));

            for (unsigned int index = 0; index < cmdParams.size(); index++) {
                checkArgument(info, index, cmdParams[index]);
                auto argumentData(addArgument(info[index + 1], cmdParams[index]));
                std::copy(std::begin(argumentData), std::end(argumentData), std::back_inserter(data));
            }
            cluster->executeCommand(cmdId, std::move(data));
        } catch (JSException &jsException) {
            v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, jsException.what());
            isolate->ThrowException(errorMsg);
        }
    }

    JSZCluster *JSZCluster::getThis(const v8::FunctionCallbackInfo<v8::Value> &info) {
        Local<Object> self = info.Holder();
        Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
        return (JSZCluster *) wrap->Value();
    }

    void JSZCluster::checkArgument(const v8::FunctionCallbackInfo<v8::Value> &info, unsigned int index, const ClusterCmdParamsBase * cmdParam) {
        if (info.Length() <= ((int) index + 1)) {
            stringstream stream;
            stream << EXECUTE_CMD_BY_ID << " needs almost " << index << " arguments where the first is the cmd";
            throw JSException(stream.str());
        }
        Local<v8::Value> arg = info[index + 1];
        switch (cmdParam->getZCLDataType()) {
            case ZCLTypeDataType::ZCLTypeUInt8:
            case ZCLTypeDataType::ZCLTypeUInt16:
            case ZCLTypeDataType::ZCLTypeUInt24:
            case ZCLTypeDataType::ZCLTypeUInt32:
            case ZCLTypeDataType::ZCLTypeUInt40:
            case ZCLTypeDataType::ZCLTypeUInt48:
            case ZCLTypeDataType::ZCLTypeUInt56:
            case ZCLTypeDataType::ZCLTypeUInt64:
                if (!arg->IsUint32()) {
                    stringstream stream;
                    stream << EXECUTE_CMD_BY_ID << " needs as argument " << index << " an unsigned integer";
                    throw JSException(stream.str());
                }
                break;
            case ZCLTypeDataType::ZCLTypeSInt8:
            case ZCLTypeDataType::ZCLTypeSInt16:
            case ZCLTypeDataType::ZCLTypeSInt24:
            case ZCLTypeDataType::ZCLTypeSInt32:
            case ZCLTypeDataType::ZCLTypeSInt40:
            case ZCLTypeDataType::ZCLTypeSInt48:
            case ZCLTypeDataType::ZCLTypeSInt56:
            case ZCLTypeDataType::ZCLTypeSInt64:
                if (!arg->IsInt32()) {
                    stringstream stream;
                    stream << EXECUTE_CMD_BY_ID << " needs as argument " << index << " an integer";
                    throw JSException(stream.str());
                }
                break;
            case ZCLTypeDataType::ZCLTypeIEEEaddress:
            case ZCLTypeDataType::ZCLTypeStringChar:
                if (!arg->IsString()) {
                    stringstream stream;
                    stream << EXECUTE_CMD_BY_ID << " needs as argument " << index << " a string";
                    throw JSException(stream.str());
                }
                break;
            case ZCLTypeDataType::ZCLTypeArray:
                if (!arg->IsUint32Array() && !arg->IsUint32Array()) {
                    if (!arg->IsArray()) {
                        stringstream stream;
                        stream << EXECUTE_CMD_BY_ID << " needs as argument " << index << " an array";
                        throw JSException(stream.str());
                    }
                }
                break;
            default:
                stringstream stream;
                stream << EXECUTE_CMD_BY_ID << " needs as argument " << index << " a type " << cmdParam->getZCLDataType() << " the it is not managed";
                throw JSException(stream.str());
        }
    }

    std::vector<uint8_t> JSZCluster::addArgument(v8::Local<v8::Value> value, const ClusterCmdParamsBase * cmdParam) {
        if (value->IsUint32()) {
            return cmdParam->getType().getRaw(value->ToUint32()->Value());
        }
        if (value->IsInt32()) {
            return cmdParam->getType().getRaw(value->ToInt32()->Value());
        }
        if (value->IsString()) {
            String::Utf8Value utf8Value(value);
            return cmdParam->getType().getRaw(*utf8Value);
        }
        if (value->IsArray()) {
            Local<Array> array = value.As<Array>();
            std::vector<std::string> strArray;
            for (uint32_t index = 0; index < array->Length(); index++) {
                String::Utf8Value utf8Value(array->Get(index));
                strArray.push_back(*utf8Value);
            }
            return cmdParam->getType().getRaw(strArray);
        }
        stringstream stream;
        stream << "To " << EXECUTE_CMD_BY_ID << " it is passed an invalid argument instead of type " << cmdParam->getZCLDataType();
        throw JSException(stream.str());
    }

    void JSZCluster::resetPersistences() {
        functionTemplate.Reset();
    }

    void JSZCluster::checkIdCmd(const v8::FunctionCallbackInfo<v8::Value> &info) {
        if (info.Length() == 0) {
            stringstream stream;
            stream << EXECUTE_CMD_BY_ID << " needs almost one argument: an integer for the cmd id followed by possibly parameters";
            throw JSException(stream.str());
        }
    }

} /* namespace zigbee */

