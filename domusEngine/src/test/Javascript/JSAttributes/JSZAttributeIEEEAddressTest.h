/*
 * JSZAttributeIEEEAddressTest.h
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTEIEEEADDRESSTEST_H_
#define SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTEIEEEADDRESSTEST_H_

#include "JSAttributeTest.h"
#include "../../Mocks/ZCLIEEEAddressAttributeMock.h"

namespace zigbee {

    class JSZAttribute;
    namespace test {

        class JSZAttributeIEEEAddressTest : public JSAttributeTest {
        public:
            virtual ~JSZAttributeIEEEAddressTest()=default;

        protected:
            virtual void SetUp() override;

            virtual void TearDown() override;

        protected:
            std::shared_ptr<JSZAttribute> jsZAttribute;
            std::shared_ptr<ZCLIEEEAddressAttributeMock> zclIEEEAddressAttributeMock;
        };

    } /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTEIEEEADDRESSTEST_H_ */
