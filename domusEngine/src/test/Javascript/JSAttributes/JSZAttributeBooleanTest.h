/*
 * JSZAttributeBooleanTest.h
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTEBOOLEANTEST_H_
#define SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTEBOOLEANTEST_H_

#include "JSAttributeTest.h"
#include "../../Mocks/ZCLbooleanAttributeMock.h"

namespace zigbee {

class JSZAttribute;

namespace test {

class JSZAttributeBooleanTest: public JSAttributeTest {
public:
	virtual ~JSZAttributeBooleanTest();
protected:
	virtual void SetUp() override;
	virtual void TearDown() override;
protected:
	std::shared_ptr<JSZAttribute> jsZAttribute;
	ZCL_boolean_AttributeMock zcl_boolean_AttributeMock;
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTEBOOLEANTEST_H_ */
