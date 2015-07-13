/*
 * JSZAttributeStringTest.h
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTESTRINGTEST_H_
#define SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTESTRINGTEST_H_

#include "JSAttributeTest.h"
#include "../../Mocks/ZCLstringAttributeMock.h"

namespace zigbee {

class JSZAttribute;

namespace test {

class JSZAttributeStringTest : public JSAttributeTest{
public:
	virtual ~JSZAttributeStringTest();
protected:
	virtual void SetUp() override;
	virtual void TearDown() override;
protected:
	std::shared_ptr<JSZAttribute> jsZAttribute;
	std::shared_ptr<ZCL_string_AttributeMock> zcl_string_AttributeMock;
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTESTRINGTEST_H_ */
