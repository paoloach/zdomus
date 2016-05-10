//
// Created by paolo on 10/05/16.
//

#ifndef DOMUS_ENGINE_SIMPLEDESCEXECUTER_H
#define DOMUS_ENGINE_SIMPLEDESCEXECUTER_H

#include <boost/log/trivial.hpp>

namespace zigbee {
    class SimpleDescExecutor : public Executor {
    private:
        std::shared_ptr<ZDevices> zDevices;
    public:
        SimpleDescExecutor(std::shared_ptr<ZDevices> zDevices):zDevices(zDevices){}
        virtual void operator()(unsigned char *data, int ) override {
            SimpleDescMessage * simpleDescMessage = reinterpret_cast<SimpleDescMessage *>(data);
            zDevices->put(*simpleDescMessage);
            BOOST_LOG_TRIVIAL(info) << "Simple desciption message ";
        }
    };
}

#endif //DOMUS_ENGINE_SIMPLEDESCEXECUTER_H
