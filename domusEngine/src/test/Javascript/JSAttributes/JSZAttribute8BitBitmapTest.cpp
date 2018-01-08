/*
 * JSZAttribute8BitBitmapTest.cpp
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSZAttribute8BitBitmapTest.h"

#include "JSZAttribute8BitBitmapTest.h"
#include "../../../JavaScript/JSZAttributes/JSZAttributeTemplate.h"
#include "../../Mocks/ZigbeeDeviceMock.h"
#include "../../../JavaScript/JSObjects.h"

namespace zigbee {
    namespace test {

        using namespace v8;
        using namespace testing;
        using std::make_shared;
        using std::dynamic_pointer_cast;

        void JSZAttribute8BitBitmapTest::SetUp() {
            JSTest::SetUp();
            jsZAttribute = std::make_unique<JSZAttribute8BitBitmap>(&singletonObjectsMock, fifo);
            zAttributeVariable = createZAttributeVariable("Z" + ZCLBitmap8bitAttribute::name());
            zclTypeExpectation = NAMED_ALLOW_CALL(attributeMock,getZCLType()).RETURN(ZCLTypeDataType::ZCLType8bitBitmap);

        }

        void JSZAttribute8BitBitmapTest::TearDown() {
            zclTypeExpectation.release();
            jsZAttribute.reset();
            JSTest::TearDown();
        }

        TEST_F(JSZAttribute8BitBitmapTest, createTemplate) {
            createTemplateTest(jsZAttribute.get());
        }

        TEST_F(JSZAttribute8BitBitmapTest, createIstance) {
            createIstanceTest("Z" + ZCLBitmap8bitAttribute::name(), jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, getValue) {


            uint32_t expectedValue = 13;
            ZDevice zDevice{createZDevice()};
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, &attributeMock);
            REQUIRE_CALL(attributeMock, getValue()).RETURN(std::any(expectedValue));

            v8::TryCatch tryCatch;

            v8::Local<v8::Value> result = runScript(zAttributeVariable + "a.value");

            ASSERT_FALSE(tryCatch.HasCaught()) << *(String::Utf8Value(tryCatch.Message()->Get()));
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsUint32(), true);
            uint16_t value = result->ToUint32()->Value();

            ASSERT_THAT(value, Eq(expectedValue));
        }

        TEST_F(JSZAttribute8BitBitmapTest, setValue) {
            uint32_t expectedValue = 15;
            ZDevice zDevice{createZDevice()};
            std::stringstream stream;
            stream << zAttributeVariable << "a.value=" << expectedValue;
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, &attributeMock);

            v8::TryCatch tryCatch;
            runScript(stream.str());
            ASSERT_FALSE(tryCatch.HasCaught()) << *(String::Utf8Value(tryCatch.Message()->Get()));
        }

        TEST_F(JSZAttribute8BitBitmapTest, isAvailable) {
            bool availableStatus = true;
            REQUIRE_CALL(attributeMock, isAvailable()).RETURN(availableStatus);
            isAvailableTest(availableStatus, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, isNotAvailable) {
            bool availableStatus = false;
            REQUIRE_CALL(attributeMock, isAvailable()).RETURN(availableStatus);
            isAvailableTest(availableStatus, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, isUnsupported) {
            bool unsupported = true;
            REQUIRE_CALL(attributeMock, isUnsupported()).RETURN(unsupported);
            isUnsupportedTest(unsupported, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, isSupported) {
            bool unsupported = false;
            REQUIRE_CALL(attributeMock, isUnsupported()).RETURN(unsupported);
            isUnsupportedTest(unsupported, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, statusNotAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotAvailable;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, statusAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Available;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, statusNotSupported) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotSupported;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, statusRequesting) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Requesting;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, statusUndefined) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Undefined;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, getIdentifier) {
            REQUIRE_CALL(attributeMock, getIdentifier()).RETURN(ATTRIBUTE0_ID);
            getIdentifierTest(jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, getName) {
            std::string expectedName = "name";
            REQUIRE_CALL(attributeMock, getName()).RETURN(expectedName);
            getNameTest(expectedName, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, isReadOnly) {
            bool readOnlyValue = true;
            REQUIRE_CALL(attributeMock, isReadOnly()).RETURN(readOnlyValue);
            isReadonlyTest(readOnlyValue, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttribute8BitBitmapTest, isWritable) {
            bool readOnlyValue = false;
            REQUIRE_CALL(attributeMock, isReadOnly()).RETURN(readOnlyValue);
            isReadonlyTest(readOnlyValue, jsZAttribute.get(), &attributeMock);
        }


    } /* namespace test */
} /* namespace zigbee */
