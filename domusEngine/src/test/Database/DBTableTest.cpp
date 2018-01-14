/*
 * DBTableTest.cpp
 *
 *  Created on: 23/gen/2015
 *      Author: Paolo Achdjian
 */

#include <boost/spirit/include/karma.hpp>
#include <boost/date_time.hpp>
#include <math.h>
#include <libpq-fe.h>


#include "DBTableTest.h"
#include "../../Database/Exceptions/DBExceptionNoTable.h"
#include "../../Database/Exceptions/DBExceptionResultNotSet.h"
#include "../../json/json/json.h"

using namespace Json;

namespace zigbee {
    namespace test {

        using namespace boost::spirit::karma;
        using namespace boost::posix_time;
        using namespace boost::gregorian;
        using std::string_view;
        using std::any;
        using std::any_cast;

        static constexpr const char *server = "localhost:5432";
        static constexpr const char *database = "domusEngine";
        static constexpr const char *user = "DomusEngine";
        static constexpr const char *password = "DomusEngine";

        static const std::string_view tableName = "testTable";

        bool isAnyType(std::any arg, int expectedInt) {
            if (arg.type() == typeid(int)) {
                return std::any_cast<int>(arg) == expectedInt;
            } else {
                std::cout << "Got type " << arg.type().name();
            }
            return false;
        }

        bool isAnyType(std::any arg, double expectedInt) {
            if (arg.type() == typeid(double)) {
                return std::any_cast<double>(arg) == expectedInt;
            }else {
                std::cout << "Got type " << arg.type().name();
            }
            return false;
        }

        bool isAnyType(std::any arg, bool expected) {
            if (arg.type() == typeid(bool)) {
                return std::any_cast<bool>(arg) == expected;
            }
            return false;
        }

        bool isAnyType(std::any arg, const char * expected) {
            if (arg.type() == typeid(std::string)) {
                return std::any_cast<std::string>(arg) == expected;
            }else {
                std::cout << "Got type " << arg.type().name();
            }
            return false;
        }

        bool isAnyType(std::any arg, std::string expected) {
            if (arg.type() == typeid(std::string)) {
                return std::any_cast<std::string>(arg) == expected;
            }else {
                std::cout << "Got type " << arg.type().name();
            }
            return false;
        }


        bool isAnyType(std::any arg, std::string_view expected) {
            if (arg.type() == typeid(std::string)) {
                return std::any_cast<std::string>(arg) == expected;
            }else {
                std::cout << "Got type " << arg.type().name();
            }
            return false;
        }

        bool isAnyType(std::any arg, ptime expectedInt) {
            if (arg.type() == typeid(boost::posix_time::ptime)) {
                boost::posix_time::ptime value = std::any_cast<boost::posix_time::ptime>(arg);
//                std::cout << "Expected " << expectedPosixTime << " but got " << value << std::endl;
                return expectedInt == value;
            }else {
                std::cout << "Got type " << arg.type().name();
            }
            return false;
        }


        DBTableTest::~DBTableTest() {
        }

        void DBTableTest::SetUp() {
            std::stringstream connectionStream;

            connectionStream << "hostaddr = '127.0.0.1' dbname = " << database << " user = " << user << " password = " << password;
            conn = PQconnectdb(connectionStream.str().c_str());
            if (PQstatus(conn) != CONNECTION_OK) {
                FAIL();
            }
        }

        void DBTableTest::TearDown() {
            dropTable(tableName);
            PQfinish(conn);
        }

        TEST_F(DBTableTest, connection) {
            createTable(tableName);

            new DBTable(tableName, conn);
            dropTable(tableName);
        }

        TEST_F(DBTableTest, invalidTableName) {
            std::string tableName = "InvalidTestTable";

            ASSERT_THROW(new DBTable(tableName, conn), DBExceptionNoTable);
        }

        TEST_F(DBTableTest, find_data_integer) {
            createTable(tableName, {"a integer"});
            insertTable(tableName, "3");

            dbTable = new DBTable(tableName, conn);

            auto row = dbTable->find("");

            ASSERT_TRUE(isAnyType(row.getValue("a"), 3));
        }

        TEST_F(DBTableTest, find_data_float) {
            createTable(tableName, {"a real"});
            insertTable(tableName, "3.6");

            dbTable = new DBTable(tableName, conn);

            auto row = dbTable->find("");

            ASSERT_TRUE(isAnyType(row.getValue("a"), 3.6));
        }

        TEST_F(DBTableTest, find_data_bool) {
            createTable(tableName, {"a boolean"});
            insertTable(tableName, "'on'");

            dbTable = new DBTable(tableName, conn);

            auto row = dbTable->find("");

            ASSERT_TRUE(isAnyType(row.getValue("a"), true));
        }

        TEST_F(DBTableTest, find_data_string) {
            createTable(tableName, {"a text"});
            insertTable(tableName, "'text-text'");

            dbTable = new DBTable(tableName, conn);

            auto row = dbTable->find("");

            ASSERT_TRUE(isAnyType(row.getValue("a"), "text-text"));
        }

        TEST_F(DBTableTest, find_data_timestamp) {
            createTable(tableName, {"a timestamp"});
            insertTable(tableName, "'2015-01-25 12:11:54.88'");
            ptime expectedTime(date(2015, 1, 25), time_duration(12, 11, 54, 880000));

            dbTable = new DBTable(tableName, conn);

            auto row = dbTable->find("");

            ASSERT_TRUE(isAnyType(row.getValue("a"), expectedTime));

        }

        TEST_F(DBTableTest, find_data_condition) {
            createTable(tableName, {"a integer, b integer"});
            insertTable(tableName, "1, 3");
            insertTable(tableName, "10, 30");
            insertTable(tableName, "100, 300");

            dbTable = new DBTable(tableName, conn);

            auto row = dbTable->find("a=10");

            ASSERT_TRUE(isAnyType(row.getValue("b"), 30));
        }


        TEST_F(DBTableTest, insertRow) {
            createTable(tableName, {"a integer", "b real", "c text"});
            int expected_a = 10;
            double expected_b = 21.34;
            string_view expected_c = "text_c";

            dbTable = new DBTable(tableName, conn);

            DBRow row;

            row.setValue("a", any(expected_a));
            row.setValue("b", any(expected_b));
            row.setValue("c", any(expected_c));
            dbTable->insert(&row);

            auto actualRow = dbTable->find("");

            ASSERT_TRUE(isAnyType(actualRow.getValue("a"), expected_a));
            ASSERT_TRUE(isAnyType(actualRow.getValue("b"), expected_b));
            ASSERT_TRUE(isAnyType(actualRow.getValue("c"), expected_c));
        }


        TEST_F(DBTableTest, stringifyARow) {
            createTable(tableName, {"a integer", "b real", "c text", "d timestamp"});
            int expected_a = 10;
            double expected_b = 21.34;
            string_view expected_c = "text_c";
            string_view d = "2015-01-25 12:11:54.88";
            string_view expected_d = "20150125T121154.880000Z";

            dbTable = new DBTable(tableName, conn);

            DBRow row;

            row.setValue("a", any(expected_a));
            row.setValue("b", any(expected_b));
            row.setValue("c", any(expected_c));
            row.setValue("d", any(d));
            dbTable->insert(&row);

            Value root(arrayValue);
            Value object(objectValue);
            object["a"] = std::to_string(expected_a);
            object["b"] = "21.34";
            object["c"] = std::string(expected_c);
            object["d"] = std::string(expected_d);
            root.append(object);
            std::stringstream stream;
            stream << root << "\r\n";
            auto result = dbTable->find("");
            ASSERT_EQ(result.stringify(), stream.str());

        }

        void DBTableTest::createTable(const std::string_view tableName) {
            std::stringstream createTableStream;
            createTableStream << "CREATE TABLE public.\"" << tableName << "\"()";
            PGresult *result = PQexecParams(conn, createTableStream.str().c_str(), 0, nullptr, nullptr, nullptr, nullptr, 1);
            PQclear(result);
        }

        void DBTableTest::createTable(const std::string_view tableName, std::initializer_list<std::string> columns) {
            std::stringstream createTableStream;
            createTableStream << "CREATE TABLE public.\"" << tableName << "\"(";

            createTableStream << format(string % ',', columns) << ")" << std::endl;

            PGresult *result = PQexecParams(conn, createTableStream.str().c_str(), 0, nullptr, nullptr, nullptr, nullptr, 1);
            PQclear(result);
        }

        void DBTableTest::insertTable(const std::string_view tableName, const std::string &inizializer) {
            std::stringstream insertStream;
            insertStream << "insert into public.\"" << tableName << "\" values (" << inizializer << ");";

            PGresult *result = PQexecParams(conn, insertStream.str().c_str(), 0, nullptr, nullptr, nullptr, nullptr, 1);
            PQclear(result);
        }

        void DBTableTest::dropTable(const std::string_view tableName) {
            std::stringstream createTableStream;
            createTableStream << "DROP TABLE public.\"" << tableName << "\"";
            PGresult *result = PQexecParams(conn, createTableStream.str().c_str(), 0, nullptr, nullptr, nullptr, nullptr, 1);
            PQclear(result);
        }

    } /* namespace test */
} /* namespace zigbee */
