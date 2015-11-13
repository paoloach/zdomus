/*
 * DBTableTest.cpp
 *
 *  Created on: 23/gen/2015
 *      Author: Paolo Achdjian
 */

#include <boost/spirit/include/karma.hpp>
#include <boost/date_time.hpp>
#include <math.h>


#include "DBTableTest.h"
#include "../../Database/Exceptions/DBExceptionNoTable.h"
#include "../../Database/Exceptions/DBExceptionResultNotSet.h"

namespace zigbee {
namespace test {

using namespace boost::spirit::karma;
using namespace boost::posix_time;
using namespace boost::gregorian;

static constexpr const char * server = "localhost:5432";
static constexpr const char * database = "domusEngine";
static constexpr const char * user = "DomusEngine";

static const std::string tableName = "testTable";

MATCHER_P(IsAnyString, expectedString, ""){
if (arg.type() == typeid(std::string)) {
	std::string value = boost::any_cast<std::string>(arg);
	return value == expectedString;
}
return false;
}

MATCHER_P(IsAnyPosixTime, expectedPosixTime, ""){
if (arg.type() == typeid(boost::posix_time::ptime)) {
	boost::posix_time::ptime value = boost::any_cast<boost::posix_time::ptime>(arg);
	std::cout << "Expected " <<  expectedPosixTime << " but got " << value << std::endl;
	return value == expectedPosixTime;
}
return false;
}

MATCHER_P(IsAnyChar, expectedChar, ""){
if (arg.type() == typeid(char)) {
	return boost::any_cast<char>(arg) == expectedChar;
}
return false;
}

MATCHER_P(IsAnyInteger, expectedInt, ""){
if (arg.type() == typeid(int32_t)) {
	return boost::any_cast<int32_t>(arg) == expectedInt;
}
return false;
}

MATCHER_P(IsAnyDouble, expecteDouble, ""){
if (arg.type() == typeid(double)) {
	return std::abs(boost::any_cast<double>(arg) - expecteDouble) < 0.001;
}
return false;
}

MATCHER_P(IsAnyBool, expecteBool, ""){
if (arg.type() == typeid(bool)) {
	return boost::any_cast<bool>(arg) == expecteBool;
}
return false;
}

DBTableTest::~DBTableTest() {
}

void DBTableTest::SetUp() {
}

void DBTableTest::TearDown() {
	dropTable(tableName);
}

TEST_F( DBTableTest, connection) {
	createTable(tableName);

	std::make_shared<DBTable>(tableName);
	dropTable(tableName);
}

TEST_F( DBTableTest, invalidTableName) {
	std::string tableName = "InvalidTestTable";

	ASSERT_THROW(std::make_shared<DBTable>(tableName), DBExceptionNoTable);
}

TEST_F( DBTableTest, find_data_integer) {
	std::string fieldName = "fieldName";
	createTable(tableName, { "a integer" });
	insertTable(tableName, "3");

	dbTable = std::make_shared<DBTable>(tableName);

	auto row = dbTable->find("");

	ASSERT_THAT(row->getValue("a"), IsAnyInteger(3));
}

TEST_F( DBTableTest, find_data_float) {
	std::string fieldName = "fieldName";
	createTable(tableName, { "a real" });
	insertTable(tableName, "3.6");

	dbTable = std::make_shared<DBTable>(tableName);

	auto row = dbTable->find("");

	ASSERT_THAT(row->getValue("a"), IsAnyDouble(3.6));
}

TEST_F( DBTableTest, find_data_bool) {
	std::string fieldName = "fieldName";
	createTable(tableName, { "a boolean" });
	insertTable(tableName, "'on'");

	dbTable = std::make_shared<DBTable>(tableName);

	auto row = dbTable->find("");

	ASSERT_THAT(row->getValue("a"), IsAnyBool(true));
}

TEST_F( DBTableTest, find_data_string) {
	std::string fieldName = "fieldName";
	createTable(tableName, { "a text" });
	insertTable(tableName, "'text-text'");

	dbTable = std::make_shared<DBTable>(tableName);

	auto row = dbTable->find("");

	ASSERT_THAT(row->getValue("a"), IsAnyString("text-text"));
}

TEST_F( DBTableTest, find_data_timestamp) {
	std::string fieldName = "fieldName";
	createTable(tableName, { "a timestamp" });
	insertTable(tableName, "'2015-01-25 12:11:54.88'");
	ptime expectedTime(date(2015,1,25),time_duration(12,11,54,880000));

	dbTable = std::make_shared<DBTable>(tableName);

	auto row = dbTable->find("");

	ASSERT_THAT(row->getValue("a"), IsAnyPosixTime(expectedTime));

}

TEST_F( DBTableTest, find_data_condition) {
	std::string tableName = "testTable";
	std::string fieldName = "fieldName";
	createTable(tableName, { "a integer, b integer" });
	insertTable(tableName, "1, 3");
	insertTable(tableName, "10, 30");
	insertTable(tableName, "100, 300");

	dbTable = std::make_shared<DBTable>(tableName);

	auto row = dbTable->find("a=10");

	ASSERT_THAT(row->getValue("b"), IsAnyInteger(30));
}

TEST_F( DBTableTest, next_row) {

	std::string fieldName = "fieldName";
	createTable(tableName, { "a integer, b integer" });
	insertTable(tableName, "1, 3");
	insertTable(tableName, "10, 30");
	insertTable(tableName, "100, 300");

	dbTable = std::make_shared<DBTable>(tableName);

	auto row1 = dbTable->find("");
	ASSERT_THAT(row1->getValue("b"), IsAnyInteger(3));
	auto row2 = dbTable->nextRow();
	ASSERT_THAT((bool )row2, true);
	ASSERT_THAT(row2->getValue("b"), IsAnyInteger(30));
	auto row3 = dbTable->nextRow();
	ASSERT_THAT((bool )row3, true);
	ASSERT_THAT(row3->getValue("b"), IsAnyInteger(300));
	auto row4 = dbTable->nextRow();
	ASSERT_THAT((bool )row4, false);
}

TEST_F( DBTableTest, prev_row) {

	std::string fieldName = "fieldName";
	createTable(tableName, { "a integer, b integer" });
	insertTable(tableName, "1, 3");
	insertTable(tableName, "10, 30");
	insertTable(tableName, "100, 300");

	dbTable = std::make_shared<DBTable>(tableName);

	auto row1 = dbTable->find("");
	auto row = dbTable->previousRow();
	ASSERT_THAT((bool )row, false);
	dbTable->nextRow();
	row = dbTable->previousRow();
	ASSERT_THAT(row1->getValue("b"), IsAnyInteger(3));
	dbTable->nextRow();
	dbTable->nextRow();
	dbTable->nextRow();
	row = dbTable->previousRow();
	ASSERT_THAT(row->getValue("b"), IsAnyInteger(30));

}

TEST_F( DBTableTest, insertRow) {
	std::string fieldName = "fieldName";
	createTable(tableName, { "a integer", "b real", "c text" });
	int expected_a = 10;
	double expected_b = 21.34;
	std::string expected_c = "text_c";

	dbTable = std::make_shared<DBTable>(tableName);

	std::shared_ptr<DBRow> row = std::make_shared<DBRow>();

	row->setValue("a", boost::any(expected_a));
	row->setValue("b", boost::any(expected_b));
	row->setValue("c", boost::any(expected_c));
	dbTable->insert(row.get());

	auto actualRow = dbTable->find("");

	ASSERT_THAT(actualRow->getValue("a"), IsAnyInteger(expected_a));
	ASSERT_THAT(actualRow->getValue("b"), IsAnyDouble(expected_b));
	ASSERT_THAT(actualRow->getValue("c"), IsAnyString(expected_c));
}

void DBTableTest::createTable(const std::string& tableName) {
	std::stringstream connectionStream;

	connectionStream << "postgresql://" << user << "@" << server << "/" << database;
	PGconn * conn = PQconnectdb(connectionStream.str().c_str());

	if (PQstatus(conn) != CONNECTION_OK) {
		FAIL();
	}
	std::stringstream createTableStream;
	createTableStream << "CREATE TABLE public.\"" << tableName << "\"()";
	PGresult * result = PQexecParams(conn, createTableStream.str().c_str(), 0, nullptr, nullptr, nullptr, nullptr, 1);
	PQclear(result);
	PQfinish(conn);
}

void DBTableTest::createTable(const std::string& tableName, std::initializer_list<std::string> columns) {
	std::stringstream connectionStream;

	connectionStream << "postgresql://" << user << "@" << server << "/" << database;
	PGconn * conn = PQconnectdb(connectionStream.str().c_str());

	if (PQstatus(conn) != CONNECTION_OK) {
		FAIL();
	}
	std::stringstream createTableStream;
	createTableStream << "CREATE TABLE public.\"" << tableName << "\"(";

	createTableStream << format(string % ',', columns) << ")" << std::endl;

	PGresult * result = PQexecParams(conn, createTableStream.str().c_str(), 0, nullptr, nullptr, nullptr, nullptr, 1);
	PQclear(result);
	PQfinish(conn);
}

void DBTableTest::insertTable(const std::string& tableName, const std::string& inizializer) {
	std::stringstream connectionStream;

	connectionStream << "postgresql://" << user << "@" << server << "/" << database;
	PGconn * conn = PQconnectdb(connectionStream.str().c_str());

	if (PQstatus(conn) != CONNECTION_OK) {
		FAIL();
	}
	std::stringstream insertStream;
	insertStream << "insert into public.\"" << tableName << "\" values (" << inizializer << ");";

	PGresult * result = PQexecParams(conn, insertStream.str().c_str(), 0, nullptr, nullptr, nullptr, nullptr, 1);
	PQclear(result);
	PQfinish(conn);
}

void DBTableTest::dropTable(const std::string& tableName) {
	std::stringstream connectionStream;

	connectionStream << "postgresql://" << user << "@" << server << "/" << database;
	PGconn * conn = PQconnectdb(connectionStream.str().c_str());

	if (PQstatus(conn) != CONNECTION_OK) {
		FAIL();
	}
	std::stringstream createTableStream;
	createTableStream << "DROP TABLE public.\"" << tableName << "\"";
	PGresult * result = PQexecParams(conn, createTableStream.str().c_str(), 0, nullptr, nullptr, nullptr, nullptr, 1);
	PQclear(result);
	PQfinish(conn);
}

} /* namespace test */
} /* namespace zigbee */
