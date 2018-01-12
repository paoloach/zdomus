/*
 * DBTableTest.h
 *
 *  Created on: 23/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_DATABASE_DBTABLETEST_H_
#define SRC_TEST_DATABASE_DBTABLETEST_H_

#include <gtest/gtest.h>
#include <initializer_list>

#include "../../Database/DBTable.h"

namespace zigbee {
namespace test {

class DBTableTest : public ::testing::Test{
public:
	virtual ~DBTableTest();
protected:
	virtual void SetUp() override ;
	virtual void TearDown() override ;
	void createTable(const std::string_view tableName);
	void createTable(const std::string_view tableName, std::initializer_list<std::string> columns);
	void insertTable(const std::string_view tableName, const std::string & inizializer);
	void dropTable(const std::string_view  tableName);
protected:
	DBTable * dbTable;
    PGconn *conn;
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_DATABASE_DBTABLETEST_H_ */
