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
#include "../../JavaScript/JSResultSet.h"

namespace zigbee {
    namespace test {


        class JSDBTableTest : public JSBaseTest {
        public:
            virtual ~JSDBTableTest() = default;

        protected:
            virtual void SetUp() override;

            virtual void TearDown() override;


        protected:
            DBTableFactoryMock dbTableFactoryMock;
            std::unique_ptr<JSRow> jsRow;
            std::unique_ptr<JSResultSet> jsResultSet;
            std::unique_ptr<JSDBTable> jsDBTable;
            DBTableMock dbTable;

            std::unique_ptr<trompeloeil::expectation> getTable;
            std::unique_ptr<trompeloeil::expectation> find;

        };

    } /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSDBTABLETEST_H_ */
