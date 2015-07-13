/*
 * JSDBTableTest.cpp
 *
 *  Created on: 20/gen/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "../../Database/Exceptions/DBExceptionNoTable.h"
#include "../../Database/Exceptions/DBException.h"
#include "../../JavaScript/JSObjects.h"

#include "JSDBTableTest.h"

namespace zigbee {
namespace test {

using namespace testing;
using namespace v8;

using std::string;
using std::stringstream;
using boost::any;

MATCHER_P(IsAnyString, expectedString, ""){
	if (arg.type() == typeid(std::string)) {
		std::string value = boost::any_cast<std::string>(arg);
		return value == expectedString;
	}
	return false;
}

MATCHER_P(IsAnyInt32, expectedValue, ""){
	if (arg.type() == typeid(int32_t)) {
		int32_t value = boost::any_cast<int32_t>(arg);
		return value == expectedValue;
	}
	return false;
}

MATCHER_P(IsAnyUInt32, expectedValue, ""){
	if (arg.type() == typeid(uint32_t)) {
		uint32_t value = boost::any_cast<uint32_t>(arg);
		return value == expectedValue;
	}
	return false;
}

MATCHER_P2(HasPair, expectedKey, expectedVal, ""){
	return expectedVal == boost::any_cast<string>( arg->getValue(expectedKey) );
}

#define V8_SETUP HandleScope handle_scope(isolate);\
				Local<Context> context = Context::New(isolate, nullptr);\
				Context::Scope context_scope(context);\
				Local<Object>  global = context->Global();

JSDBTableTest::~JSDBTableTest() {
}

void JSDBTableTest::SetUp() {
	JSBaseTest::SetUp();
	jsRow = std::make_shared<JSRow>();
	jsDBTable = std::make_shared<JSDBTable>(dbTableFactoryMock,jsRow,log);


	ON_CALL(dbTableFactoryMock, getTable(_)).WillByDefault(Return(nullptr));
	ON_CALL(dbTable, find_(_)).WillByDefault(Return(nullptr));
	ON_CALL(dbTable, nextRow_()).WillByDefault(Return(nullptr));
	ON_CALL(dbTable, previousRow_()).WillByDefault(Return(nullptr));
}

void JSDBTableTest::TearDown() {
	jsRow->resetPersistences();
	jsDBTable->resetPersistences();
	JSBaseTest::TearDown();
}

TEST_F( JSDBTableTest, createTemplate) {
	HandleScope handle_scope(isolate);
	Local<Context> context = Context::New(isolate, nullptr);
	Context::Scope context_scope(context);

	Handle<Object> global = context->Global();
	jsDBTable->initJsObjectsTemplate(isolate, global);
}

TEST_F( JSDBTableTest, createInstance) {

	string tableName = "table name";
	stringstream stream;
	V8_SETUP
	jsDBTable->initJsObjectsTemplate(isolate, global);

	EXPECT_CALL(dbTableFactoryMock, getTable(tableName)).WillOnce(Return(&dbTable));

	stream << "var table=" << JSDBTABLE << "('" << tableName << "');";
	stream << "table;";
	TryCatch tryCatch { };
	v8::Local<v8::Value> result = runScript(stream.str());
	ASSERT_FALSE(result.IsEmpty());
	ASSERT_TRUE(result->IsObject());
	ASSERT_FALSE(tryCatch.HasCaught());
}

TEST_F( JSDBTableTest, createInvalidInstance) {

	string tableName = "no table name";
	stringstream stream;
	V8_SETUP
	jsDBTable->initJsObjectsTemplate(isolate, global);

	EXPECT_CALL(dbTableFactoryMock, getTable(tableName)).WillOnce(Throw(DBExceptionNoTable("Server","Database",tableName )));

	stream << "var table=" << JSDBTABLE << "('" << tableName << "');";
	stream << "table;";
	TryCatch tryCatch { };
	runScript(stream.str());
	ASSERT_TRUE(tryCatch.HasCaught());
	Log::LogData logData = log.get();
	ASSERT_THAT(logData.msg, HasSubstr(tableName));

}

TEST_F( JSDBTableTest, find) {
	string tableName = "table name";
	string query="this s  a query";
	stringstream stream;
	DBRow * expectedRow = new DBRow();
	V8_SETUP
	jsRow->initJsObjectsTemplate(isolate, global);
	jsDBTable->initJsObjectsTemplate(isolate, global);

	EXPECT_CALL(dbTableFactoryMock, getTable(tableName)).WillOnce(Return(&dbTable));
	EXPECT_CALL(dbTable, find_(query)).WillOnce(Return(expectedRow));

	stream << "var table=" << JSDBTABLE << "('" << tableName << "');";
	stream << "table.find('" << query << "');";
	TryCatch tryCatch { };
	v8::Local<v8::Value> result = runScript(stream.str());
	ASSERT_FALSE(result.IsEmpty());
	ASSERT_FALSE(tryCatch.HasCaught());
}


TEST_F( JSDBTableTest, nextRow) {
	string tableName = "table name";
	stringstream stream;
	DBRow * expectedRow = new DBRow();
	V8_SETUP
	jsRow->initJsObjectsTemplate(isolate, global);
	jsDBTable->initJsObjectsTemplate(isolate, global);

	EXPECT_CALL(dbTableFactoryMock, getTable(tableName)).WillOnce(Return(&dbTable));
	EXPECT_CALL(dbTable, nextRow_()).WillOnce(Return(expectedRow));

	stream << "var table=" << JSDBTABLE << "('" << tableName << "');";
	stream << "table.nextRow();";
	TryCatch tryCatch { };
	v8::Local<v8::Value> result = runScript(stream.str());
	ASSERT_FALSE(result.IsEmpty());
	ASSERT_FALSE(tryCatch.HasCaught());
}

TEST_F( JSDBTableTest, previousRow) {
	string tableName = "table name";
	stringstream stream;
	DBRow * expectedRow = new DBRow();
	V8_SETUP
	jsRow->initJsObjectsTemplate(isolate, global);
	jsDBTable->initJsObjectsTemplate(isolate, global);

	EXPECT_CALL(dbTableFactoryMock, getTable(tableName)).WillOnce(Return(&dbTable));
	EXPECT_CALL(dbTable, previousRow_()).WillOnce(Return(expectedRow));

	stream << "var table=" << JSDBTABLE << "('" << tableName << "');";
	stream << "table.previousRow();";
	TryCatch tryCatch { };
	v8::Local<v8::Value> result = runScript(stream.str());
	ASSERT_FALSE(result.IsEmpty());
	ASSERT_FALSE(tryCatch.HasCaught());
}

TEST_F( JSDBTableTest, insert) {
	string tableName = "table name";
	stringstream stream;
	string key="key";
	string value="value";
	V8_SETUP
	jsRow->initJsObjectsTemplate(isolate, global);
	jsDBTable->initJsObjectsTemplate(isolate, global);

	EXPECT_CALL(dbTableFactoryMock, getTable(tableName)).WillOnce(Return(&dbTable));
	EXPECT_CALL(dbTable, insert(HasPair(key,value))).WillOnce(Return());

	stream << "var row = " << JSDBROW << "();";
	stream << "row.setValue('" << key << "','" << value << "');";
	stream << "var table=" << JSDBTABLE << "('" << tableName << "');";
	stream << "table.insert(row);";
	TryCatch tryCatch { };
	v8::Local<v8::Value> result = runScript(stream.str());
	ASSERT_FALSE(result.IsEmpty());
	ASSERT_TRUE(result->IsUndefined());
	ASSERT_FALSE(tryCatch.HasCaught());
}



} /* namespace test */
} /* namespace zigbee */
