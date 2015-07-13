/*
 * JSDBTableTest.h
 *
 *  Created on: 20/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_JSDBTABLETEST_H_
#define SRC_TEST_JAVASCRIPT_JSDBTABLETEST_H_

#include "../../JavaScript/JSDBTable.h"
#include "../Mocks/DBTableFactoryMock.h"
#include "JSBaseTest.h"
#include "../Mocks/DBTableMock.h"
#include "../../JavaScript/JSRow.h"
#include "../../Utils/Log.h"

namespace zigbee {
namespace test {


class JSDBTableTest : public JSBaseTest {
public:
	virtual ~JSDBTableTest();
protected:
	virtual void SetUp() override ;
	virtual void TearDown() override ;


protected:
	DBTableFactoryMock dbTableFactoryMock;
	std::shared_ptr<JSDBTable> jsDBTable;
	std::shared_ptr<JSRow> jsRow;
	DBTableMock dbTable;
	Log log;

};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSDBTABLETEST_H_ */
