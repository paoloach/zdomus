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

	MOCK_METHOD0(nextRow_,  DBRow *  ());
	std::shared_ptr<DBRow> nextRow(){
		return std::unique_ptr<DBRow> (nextRow_());
	}

	MOCK_METHOD0(previousRow_, DBRow *  ());
	std::shared_ptr<DBRow> previousRow(){
		return std::unique_ptr<DBRow> (previousRow_());
	}
	MOCK_METHOD1(find_, DBRow *  (const std::string & query));
	std::shared_ptr<DBRow> find(const std::string & query){
		return std::unique_ptr<DBRow> (find_(query));
	}
	MOCK_METHOD1(insert,  void (DBRow * dbRow) );
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_DBTABLEMOCK_H_ */
