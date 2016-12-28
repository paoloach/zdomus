//
// Created by paolo on 28/12/16.
//

#ifndef DOMUS_ENGINE_JSZCLUSTERMOCK_H
#define DOMUS_ENGINE_JSZCLUSTERMOCK_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../JavaScript/JSZCluster.h"
#include "shared_ptr_mock.h"

namespace zigbee {
    namespace test {

        class JSZClusterMock  : public JSZCluster, public sharedMockClass<JSZCluster, JSZClusterMock> {
        public:
            JSZClusterMock();
            virtual ~JSZClusterMock();
            MOCK_METHOD2(initJsObjectsTemplate,  void(v8::Isolate *, v8::Handle<v8::Object> &));

            MOCK_METHOD4(createInstance, v8::Local<v8::Object> (v8::Isolate *, const ExtAddress &, EndpointID , ClusterID ));

            MOCK_METHOD0(resetPersistences, void ());
        };

    } /* namespace test */
} /* namespace zigbee */


#endif //DOMUS_ENGINE_JSZCLUSTERMOCK_H
