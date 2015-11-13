/*
 * JSZAttribute8BitEnumTest.cpp
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSZAttribute8BitEnumTest.h"
#include "../../../JavaScript/JSZAttributes/JSZAttributeTemplate.h"
#include "../../Mocks/ZigbeeDeviceMock.h"
#include "../../../JavaScript/JSObjects.h"

namespace zigbee {
namespace test {

using namespace v8;
using namespace testing;
using std::make_shared;
using std::dynamic_pointer_cast;

JSZAttribute8BitEnumTest::~JSZAttribute8BitEnumTest() {
}

void JSZAttribute8BitEnumTest::SetUp() {
	JSTest::SetUp();
	jsZAttribute = std::make_shared<JSZAttribute8BitEnum>(zDevices, zigbeeDevice, clusterTypeFactoryMock);
	zcl_enum8bit_AttributeMock = std::make_shared<ZCL_enum8bit_AttributeMock>();
	zAttributeVariable = createZAttributeVariable("Z"+ZCL_enum8bit_Attribute::name());
	EXPECT_CALL(*zcl_enum8bit_AttributeMock, getZCLType()).Times(AnyNumber()).WillOnce(Return(ZCLTypeDataType::ZCLTypeenum8));
}

void JSZAttribute8BitEnumTest::TearDown() {
	jsZAttribute.reset();
	zcl_enum8bit_AttributeMock.reset();
	JSTest::TearDown();
}

TEST_F( JSZAttribute8BitEnumTest, createTemplate) {
	createTemplateTest(jsZAttribute);
}

TEST_F( JSZAttribute8BitEnumTest, createIstance) {
	createIstanceTest("Z"+ZCL_enum8bit_Attribute::name(), jsZAttribute, zcl_enum8bit_AttributeMock);
}

TEST_F( JSZAttribute8BitEnumTest, getValue) {
	auto expectedValue = 13u;
	ZDevice zDevice { createZDevice() };
	V8_SETUP
	jsZAttribute->initJsObjectsTemplate(isolate, global);

	setInitExpectation(zDevice, zcl_enum8bit_AttributeMock);
	EXPECT_CALL(*zcl_enum8bit_AttributeMock, getValue()).WillOnce(Return(boost::any(expectedValue)));

	v8::Local<v8::Value> result = runScript(zAttributeVariable + "a.value");
	ASSERT_THAT(result.IsEmpty(), false);
	ASSERT_THAT(result->IsUint32(), true);
	uint16_t value = result->ToUint32()->Value();

	ASSERT_THAT(value, Eq(expectedValue));
}

TEST_F( JSZAttribute8BitEnumTest, setValue) {
	uint16_t expectedValue = 15;
	ZDevice zDevice { createZDevice() };
	std::stringstream stream { };
	stream << zAttributeVariable << "a.value=" << expectedValue;
	V8_SETUP
	jsZAttribute->initJsObjectsTemplate(isolate, global);

	setInitExpectation(zDevice, zcl_enum8bit_AttributeMock);
	EXPECT_CALL(*zcl_enum8bit_AttributeMock, sendValue(expectedValue));

	runScript(stream.str());
}

TEST_F( JSZAttribute8BitEnumTest, setWrongValue) {
	int16_t expectedValue = -15;
	ZDevice zDevice { createZDevice() };
	std::stringstream stream { };
	stream << zAttributeVariable << "a.value=" << expectedValue;
	V8_SETUP
	jsZAttribute->initJsObjectsTemplate(isolate, global);

	setInitExpectation(zDevice, zcl_enum8bit_AttributeMock);

	TryCatch trycatch;
	v8::Local<v8::Value> result = runScript(stream.str());
	ASSERT_THAT(result.IsEmpty(), true);
	ASSERT_THAT(trycatch.HasCaught(), true);
	v8::String::Utf8Value exceptionMessage(trycatch.Message()->Get());
	ASSERT_THAT(*exceptionMessage, HasSubstr("Invalid parameter"));

}

TEST_F( JSZAttribute8BitEnumTest, requestValue) {
	EXPECT_CALL(*zcl_enum8bit_AttributeMock, requestValue());
	requestValueTest(jsZAttribute, zcl_enum8bit_AttributeMock);
}

TEST_F( JSZAttribute8BitEnumTest, isAvailable) {
	bool availableStatus = true;
	EXPECT_CALL(*zcl_enum8bit_AttributeMock, isAvailable()).WillOnce(Return(availableStatus));
	isAvailableTest(availableStatus,jsZAttribute, zcl_enum8bit_AttributeMock);
}

TEST_F( JSZAttribute8BitEnumTest, isNotAvailable) {
	bool availableStatus = false;
	EXPECT_CALL(*zcl_enum8bit_AttributeMock, isAvailable()).WillOnce(Return(availableStatus));
	isAvailableTest(availableStatus,jsZAttribute, zcl_enum8bit_AttributeMock);
}

TEST_F( JSZAttribute8BitEnumTest, isUnsupported) {
	bool unsupported = true;
	EXPECT_CALL(*zcl_enum8bit_AttributeMock, isUnsupported()).WillOnce(Return(unsupported));
	isUnsupportedTest(unsupported,jsZAttribute, zcl_enum8bit_AttributeMock);
}

TEST_F( JSZAttribute8BitEnumTest, isSupported) {
	bool unsupported = false;
	EXPECT_CALL(*zcl_enum8bit_AttributeMock, isUnsupported()).WillOnce(Return(unsupported));
	isUnsupportedTest(unsupported,jsZAttribute, zcl_enum8bit_AttributeMock);
}

TEST_F( JSZAttribute8BitEnumTest, statusNotAvailable) {
	ZCLAttribute::Status statusExpected = ZCLAttribute::NotAvailable;
	EXPECT_CALL(*zcl_enum8bit_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
	getStatusTest(statusExpected,jsZAttribute, zcl_enum8bit_AttributeMock);
}

TEST_F( JSZAttribute8BitEnumTest, statusAvailable) {
	ZCLAttribute::Status statusExpected = ZCLAttribute::Available;
	EXPECT_CALL(*zcl_enum8bit_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
	getStatusTest(statusExpected,jsZAttribute, zcl_enum8bit_AttributeMock);
}

TEST_F( JSZAttribute8BitEnumTest, statusNotSupported) {
	ZCLAttribute::Status statusExpected = ZCLAttribute::NotSupported;
	EXPECT_CALL(*zcl_enum8bit_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
	getStatusTest(statusExpected,jsZAttribute, zcl_enum8bit_AttributeMock);
}

TEST_F( JSZAttribute8BitEnumTest, statusRequesting) {
	ZCLAttribute::Status statusExpected = ZCLAttribute::Requesting;
	EXPECT_CALL(*zcl_enum8bit_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
	getStatusTest(statusExpected,jsZAttribute, zcl_enum8bit_AttributeMock);
}

TEST_F( JSZAttribute8BitEnumTest, statusUndefined) {
	ZCLAttribute::Status statusExpected = ZCLAttribute::Undefined;
	EXPECT_CALL(*zcl_enum8bit_AttributeMock, getStatus()).WillOnce(Return(statusExpected));
	getStatusTest(statusExpected,jsZAttribute, zcl_enum8bit_AttributeMock);
}

TEST_F( JSZAttribute8BitEnumTest, getIdentifier) {
	EXPECT_CALL(*zcl_enum8bit_AttributeMock, getIdentifier()).WillOnce(Return(ATTRIBUTE0_ID));
	getIdentifierTest(jsZAttribute, zcl_enum8bit_AttributeMock);
}

TEST_F( JSZAttribute8BitEnumTest, getName) {
	std::string expectedName = "name";
	EXPECT_CALL(*zcl_enum8bit_AttributeMock, getName()).WillOnce(Return(expectedName));
	getNameTest(expectedName, jsZAttribute, zcl_enum8bit_AttributeMock);
}

TEST_F( JSZAttribute8BitEnumTest, isReadOnly) {
	bool readOnlyValue=true;
	EXPECT_CALL(*zcl_enum8bit_AttributeMock, isReadOnly()).WillOnce(Return(readOnlyValue));
	isReadonlyTest(readOnlyValue, jsZAttribute, zcl_enum8bit_AttributeMock);
}

TEST_F( JSZAttribute8BitEnumTest, isWritable) {
	bool readOnlyValue=false;
	EXPECT_CALL(*zcl_enum8bit_AttributeMock, isReadOnly()).WillOnce(Return(readOnlyValue));
	isReadonlyTest(readOnlyValue, jsZAttribute, zcl_enum8bit_AttributeMock);
}


} /* namespace test */
} /* namespace zigbee */
