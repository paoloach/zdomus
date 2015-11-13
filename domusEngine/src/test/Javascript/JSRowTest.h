/*
 * JSRowTest.h
 *
 *  Created on: 27/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_JSROWTEST_H_
#define SRC_TEST_JAVASCRIPT_JSROWTEST_H_


#include "JSBaseTest.h"
#include "../../JavaScript/JSRow.h"

namespace zigbee {
namespace test {

class JSRowTest  : public JSBaseTest{
public:
	virtual ~JSRowTest();
protected:
	virtual void SetUp() override ;
	virtual void TearDown() override ;
protected:
};


} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSROWTEST_H_ */
