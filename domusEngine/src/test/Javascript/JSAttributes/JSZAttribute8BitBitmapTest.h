/*
 * JSZAttribute8BitBitmapTest.h
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTE8BITBITMAPTEST_H_
#define SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTE8BITBITMAPTEST_H_

#include "JSAttributeTest.h"
#include "../../Mocks/ZCLbitmap8bitAttributeMock.h"

namespace zigbee {
namespace test {

class JSZAttribute8BitBitmapTest : public JSAttributeTest{
public:
	virtual ~JSZAttribute8BitBitmapTest()= default;
protected:
	virtual void SetUp() override;
	virtual void TearDown() override;
protected:
	std::shared_ptr<JSZAttribute> jsZAttribute;
	ZCL_bitmap8bit_AttributeMock zcl_bitmap8bit_AttributeMock;
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTE8BITBITMAPTEST_H_ */
