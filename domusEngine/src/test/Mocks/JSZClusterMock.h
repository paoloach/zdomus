//
// Created by paolo on 28/12/16.
//

#ifndef DOMUS_ENGINE_JSZCLUSTERMOCK_H
#define DOMUS_ENGINE_JSZCLUSTERMOCK_H

#include <gtest/gtest.h>
#include "../../JavaScript/JSZCluster.h"
#include "../../trompeloeil/src/trompeloeil/include/trompeloeil.hpp"

namespace zigbee {
    namespace test {

        class JSZClusterMock  : public JSZCluster{
        public:
            JSZClusterMock();
            virtual ~JSZClusterMock();
            MAKE_MOCK2(initJsObjectsTemplate,  void(v8::Isolate *, v8::Handle<v8::Object> &));

            MAKE_MOCK4(createInstance, v8::Local<v8::Object> (v8::Isolate *, const ExtAddress &, EndpointID , ClusterID ));

            MAKE_MOCK0(resetPersistences, void ());
        };

    } /* namespace test */
} /* namespace zigbee */


#endif //DOMUS_ENGINE_JSZCLUSTERMOCK_H
