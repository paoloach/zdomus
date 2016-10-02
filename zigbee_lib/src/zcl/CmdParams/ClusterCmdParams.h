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
        ClusterCmdParamsBase(std::string &&name) :
                name{name} {
        }

        ClusterCmdParamsBase(const char *name) :
                name{name} {
        }

        virtual ~ClusterCmdParamsBase() = default;

        std::string getName() const {
            return name;
        }

        virtual const ZCLTypeBase &getType() const = 0;

        virtual ZCLTypeDataType getZCLDataType() const = 0;

    private:
        std::string name;
    };

    template<ZCLTypeDataType z>
    class ClusterCmdParams : public ClusterCmdParamsBase {
    public:
        ClusterCmdParams(std::string &&name) :
                ClusterCmdParamsBase{std::move(name)} {
        }
        ClusterCmdParams(const char * name) :
                ClusterCmdParamsBase{name} {
        }

        ~ClusterCmdParams() override = default;
    public:
        const ZCLTypeBase &getType() const override {
            return dataType;
        }
        ZCLTypeDataType getZCLDataType() const override {
            return dataType.getZCLDataType();
        }

    private:
        ZCLType<z> dataType;
    };

    template<ZCLTypeDataType z>
    class ClusterCmdListParams : public ClusterCmdParamsBase {
    public:
        ClusterCmdListParams(std::string &&name) :
                ClusterCmdParamsBase(std::move(name)) {
        }

        ~ClusterCmdListParams() override = default;

    public:

        const ZCLTypeBase &getType() const override {
            return dataArrayType;
        }

        ZCLTypeDataType getZCLDataType() const override {
            return dataArrayType.getZCLDataType();
        }

    private:
        ZCLCmdList<z> dataArrayType;
    };

} /* namespace zigbee */

#endif /* CLUSTERCMDPARAMS_H_ */
