//
// Created by paolo on 09/04/18.
//

#ifndef DOMUS_ENGINE_TOPOLOGYPARENT_H
#define DOMUS_ENGINE_TOPOLOGYPARENT_H


#include <cstdint>
#include <vector>
#include <zigbee/messageStructure/LqiResponse.h>
#include <memory>
#include <zigbee/ResponseCallback.h>


namespace zigbee {
    class TopologyCreation;
    class SingletonObjects;

    class TopologyParent {
    private:

        SingletonObjects*singletonObjects;
        TopologyCreation * owner;
        NwkAddr addr;
        int32_t pendingFor;
        int32_t totalTables;
        std::vector<TopologyParent *> routesChildren;
        std::vector<uint32_t > responded;
        boost::fibers::fiber worker;
    public:

        TopologyParent(NwkAddr addr, TopologyCreation * owner, SingletonObjects *singletonObjects);

        void requestChildren();
        void response(std::shared_ptr<LqiResponse> lqiResponse );
        void timeout();
    };

    class TopologyParentResponse : public ResponseCallback<std::shared_ptr<LqiResponse>> {
    private:
        TopologyParent *parent;
    public:
        TopologyParentResponse(TopologyParent * parent):parent(parent){};
        virtual void response(std::shared_ptr<LqiResponse> lqiResponse ){
            parent->response(lqiResponse);
        };
        virtual void timeout(){parent->timeout();};
    };

}

#endif //DOMUS_ENGINE_TOPOLOGYPARENT_H
