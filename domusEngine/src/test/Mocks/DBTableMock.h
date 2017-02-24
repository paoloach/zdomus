/*
 * DBTableMock.h
 *
 *  Created on: 20/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_DBTABLEMOCK_H_
#define SRC_TEST_MOCKS_DBTABLEMOCK_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../Database/DBTable.h"

namespace zigbee {
namespace test {

class DBTableMock : public DBTable{
public:
	DBTableMock();
	virtual ~DBTableMock();

	MOCK_METHOD1(find, PGresult *  (const std::string & query));
	MOCK_METHOD1(insert,  void (DBRow * dbRow) );
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_DBTABLEMOCK_H_ */
