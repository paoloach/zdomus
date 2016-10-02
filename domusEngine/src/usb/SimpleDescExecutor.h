//
// Created by paolo on 10/05/16.
//

#ifndef DOMUS_ENGINE_SIMPLEDESCEXECUTER_H
#define DOMUS_ENGINE_SIMPLEDESCEXECUTER_H

#include <boost/log/trivial.hpp>
#include <sstream>

namespace zigbee {
    class SimpleDescExecutor : public Executor {
    private:
        ZDevices * zDevices;
    public:
        SimpleDescExecutor(ZDevices* zDevices) : zDevices(zDevices) { }

        virtual void operator()(unsigned char *data, int) override {
            SimpleDescMessage *simpleDescMessage = reinterpret_cast<SimpleDescMessage *>(data);
            zDevices->put(*simpleDescMessage);
            std::stringstream stream;
            stream << "Simple desciption message: {nwkAddr: " <<simpleDescMessage->nwkAddr << ", endpoint: " << (int)simpleDescMessage->endpoint  << ", ";
            stream << "In Clusters {";
            for (int i=0; i< simpleDescMessage->numInClusters ; i++ ){
                stream << simpleDescMessage->clustersList[i] << " ";
            }
            stream << "}, Out Cluster {";
            for (int i=0; i< simpleDescMessage->numOutClusters ; i++ ){
                stream << simpleDescMessage->clustersList[i+simpleDescMessage->numInClusters] << " ";
            }
            stream << "} }";
            BOOST_LOG_TRIVIAL(info) << stream.str();
        }
    };
}

#endif //DOMUS_ENGINE_SIMPLEDESCEXECUTER_H
