/*
 * JSZAttribute8BitEnumTest.h
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTE8BITENUMTEST_H_
#define SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTE8BITENUMTEST_H_


#include "JSAttributeTest.h"
#include "../../Mocks/ZCLAttributeMock.h"

namespace zigbee {

class JSZAttribute;

namespace test {


class JSZAttribute8BitEnumTest : public JSAttributeTest{
public:
	virtual ~JSZAttribute8BitEnumTest();
protected:
	virtual void SetUp() override;
	virtual void TearDown() override;
protected:
	std::unique_ptr<JSZAttribute> jsZAttribute;
	ZCLAttributeMock attributeMock;
    std::unique_ptr<trompeloeil::expectation> zclTypeExpectation;
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTE8BITENUMTEST_H_ */
