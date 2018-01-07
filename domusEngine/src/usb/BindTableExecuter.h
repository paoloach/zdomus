//
// Created by paolo on 10/05/16.
//

#ifndef DOMUS_ENGINE_BINDTABLEEXECUTER_H
#define DOMUS_ENGINE_BINDTABLEEXECUTER_H

#include <boost/log/trivial.hpp>
#include "Executor.h"
#include "../Utils/SingletonObjects.h"
#include "../ZigbeeData/BindTable.h"

namespace zigbee {
    class BindTableExecuter : public Executor {
    private:
        SingletonObjects * singletonObjects;
    public:
        BindTableExecuter(SingletonObjects * singletonObjects) : singletonObjects(singletonObjects) { }

        virtual void operator()(unsigned char *data, int) override {
            std::vector<BindResponse> responses;
            int count = data[1];
            data += 2;
            BOOST_LOG_TRIVIAL(info) << "Bind response  with " << count << " entries";
            for (int i = 0; i < count; i++) {
                singletonObjects->getBindTable()->add(BindResponse(data));
            }
        }
    };
}

#endif //DOMUS_ENGINE_BINDTABLEEXECUTER_H
