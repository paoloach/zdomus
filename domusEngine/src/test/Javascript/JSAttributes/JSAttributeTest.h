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
#include <zcl/Callbacks.h>

namespace zigbee {
    class JSZAttribute;
    namespace test {

        class JSAttributeTest : public JSTest {
        public:
            virtual ~JSAttributeTest();
        protected:
            std::string zAttributeVariable;
            void createTemplateTest(std::shared_ptr<JSZAttribute> &jsZAttribute);
            void createIstanceTest(const std::string &attributeName, std::shared_ptr<JSZAttribute> &jsZAttribute, std::shared_ptr<ZCLAttribute> attributeMock);
            void requestValueTest(std::shared_ptr<JSZAttribute> &jsZAttribute, std::shared_ptr<ZCLAttribute> attributeMock);
            void requestValueWithCallbackTest(std::shared_ptr<JSZAttribute> &jsZAttribute, std::shared_ptr<ZCLAttribute> attributeMock, Callbacks &changeSignal);
            void requestValueWithCallbackTestOnlyFirstTime(std::shared_ptr<JSZAttribute> &jsZAttribute, std::shared_ptr<ZCLAttribute> attributeMock,
                                                           Callbacks &changeSignal);
            void requestValueWithCallbackTestTwoTime(std::shared_ptr<JSZAttribute> &jsZAttribute, std::shared_ptr<ZCLAttribute> attributeMock, Callbacks &changeSignal);
            void isAvailableTest(bool availableStatus, std::shared_ptr<JSZAttribute> &jsZAttribute, std::shared_ptr<ZCLAttribute> attributeMock);
            void isUnsupportedTest(bool availableStatus, std::shared_ptr<JSZAttribute> &jsZAttribute, std::shared_ptr<ZCLAttribute> attributeMock);
            void getStatusTest(ZCLAttribute::Status statusExpected, std::shared_ptr<JSZAttribute> &jsZAttribute, std::shared_ptr<ZCLAttribute> attributeMock);
            void getIdentifierTest(std::shared_ptr<JSZAttribute> &jsZAttribute, std::shared_ptr<ZCLAttribute> attributeMock);
            void getNameTest(const std::string &expectedName, std::shared_ptr<JSZAttribute> &jsZAttribute, std::shared_ptr<ZCLAttribute> attributeMock);
            void isReadonlyTest(bool readOnlyExpected, std::shared_ptr<JSZAttribute> &jsZAttribute, std::shared_ptr<ZCLAttribute> attributeMock);

            ZDevice createZDevice();
            void setInitExpectation(ZDevice &zDevice, const std::shared_ptr<ZCLAttribute> &attributeMock);
            std::string createZAttributeVariable(const std::string &attributeName);
            JSCallbackFifo fifo;

        };

    } /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSATTRIBUTETEST_H_ */
