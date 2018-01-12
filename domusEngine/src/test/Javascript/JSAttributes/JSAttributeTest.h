/*
 * JSAttributeTest.h
 *
 *  Created on: 09/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSATTRIBUTETEST_H_
#define SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSATTRIBUTETEST_H_

#include "../JSTest.h"
#include "../../../JavaScript/JSZAttribute.h"
#include <zcl/ZCLAttribute.h>
#include <zigbee/Callbacks.h>

namespace zigbee {
    class JSZAttribute;
    namespace test {


        class JSAttributeTest : public JSTest {
        public:
            virtual ~JSAttributeTest()=default;
        protected:
            std::string zAttributeVariable;
            void createTemplateTest(JSZAttribute *jsZAttribute);
            void createIstanceTest(const std::string &attributeName, JSZAttribute * jsZAttribute, ZCLAttribute * attributeMock);
            void isAvailableTest(bool availableStatus, JSZAttribute *jsZAttribute, ZCLAttribute * attributeMock);
            void isUnsupportedTest(bool availableStatus,JSZAttribute *jsZAttribute, ZCLAttribute * attributeMock);
            void getStatusTest(ZCLAttribute::Status statusExpected,JSZAttribute *jsZAttribute, ZCLAttribute * attributeMock);
            void getIdentifierTest(JSZAttribute * jsZAttribute, ZCLAttribute * attributeMock);
            void getNameTest(const std::string &expectedName,JSZAttribute *jsZAttribute, ZCLAttribute * attributeMock);
            void isReadonlyTest(bool readOnlyExpected,JSZAttribute *jsZAttribute, ZCLAttribute * attributeMock);

            ZDevice createZDevice();
            void setInitExpectation(ZDevice &zDevice, ZCLAttribute * attributeMock);
            std::string createZAttributeVariable(const std::string &attributeName);
            JSCallbackFifo fifo;


            std::unique_ptr<trompeloeil::expectation> exists;
            std::unique_ptr<trompeloeil::expectation> getDevice;
            std::unique_ptr<trompeloeil::expectation> getCluster;
            std::unique_ptr<trompeloeil::expectation> getAttribute;

        };

    } /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSATTRIBUTETEST_H_ */
