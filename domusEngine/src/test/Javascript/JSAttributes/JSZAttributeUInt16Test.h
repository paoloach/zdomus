/*
 * JSZAttributeUInt16.h
 *
 *  Created on: 09/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTEUINT16TEST_H_
#define SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTEUINT16TEST_H_


#include <gmock/gmock.h>
#include <tuple>
#include "JSAttributeTest.h"
#include "../../Mocks/ZCLAttributeMock.h"

namespace zigbee {
namespace test {

class JSZAttributeUInt16Test : public JSAttributeTest{
public:


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

#endif /* SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTEUINT16TEST_H_ */
