/*
 * JSZAttributeUInt16.cpp
 *
 *  Created on: 09/gen/2015
 *      Author: Paolo Achdjian
 */

#include <tuple>
#include "JSZAttributeUInt16Test.h"
#include "../../../JavaScript/JSZAttributes/JSZAttributeTemplate.h"
#include "../../Mocks/ZigbeeDeviceMock.h"
#include "../../../JavaScript/JSObjects.h"

namespace zigbee {
    namespace test {

        using namespace v8;
        using namespace testing;
        using std::make_shared;
        using std::dynamic_pointer_cast;


        void JSZAttributeUInt16Test::SetUp() {
            JSTest::SetUp();
            jsZAttribute = std::make_unique<JSZAttributeUint16>(&singletonObjectsMock, fifo);
            zAttributeVariable = createZAttributeVariable("Z" + ZCLuint16Attribute::name());
            zclTypeExpectation = NAMED_ALLOW_CALL(attributeMock,getZCLType()).RETURN(ZCLTypeDataType::ZCLTypeUInt16);
        }

        void JSZAttributeUInt16Test::TearDown() {
            zclTypeExpectation.reset();
            jsZAttribute.reset();
            JSTest::TearDown();
        }

        TEST_F(JSZAttributeUInt16Test, createTemplate) {
            createTemplateTest(jsZAttribute.get());
        }

        TEST_F(JSZAttributeUInt16Test, createIstance) {
            createIstanceTest("Z" + ZCLuint16Attribute::name(), jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt16Test, getValue) {
            auto expectedValue = 13u;
            ZDevice zDevice{createZDevice()};
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, &attributeMock);
            REQUIRE_CALL(attributeMock, getValue()).RETURN(std::any(expectedValue));

            v8::Local<v8::Value> result = runScript(zAttributeVariable + "a.value");
            ASSERT_THAT(result.IsEmpty(), false);
            ASSERT_THAT(result->IsUint32(), true);
            ASSERT_THAT(result->ToUint32()->Value(), Eq(expectedValue));
        }

        TEST_F(JSZAttributeUInt16Test, setValue) {
            uint16_t expectedValue = 15;
            ZDevice zDevice{createZDevice()};
            std::stringstream stream{};
            stream << zAttributeVariable << "a.value=" << expectedValue;
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, &attributeMock);

            runScript(stream.str());
        }

//        TEST_F(JSZAttributeUInt16Test, setWrongValue) {
//            int16_t expectedValue = -15;
//            ZDevice zDevice{createZDevice()};
//            std::stringstream stream{};
//            stream << zAttributeVariable << "a.value=" << expectedValue;
//            V8_SETUP
//            jsZAttribute->initJsObjectsTemplate(isolate, global);
//
//            setInitExpectation(zDevice, &zclUint16Attribute);
//
//            TryCatch trycatch;
//            runScript(stream.str());
//            ASSERT_THAT(trycatch.HasCaught(), true);
//            v8::String::Utf8Value exceptionMessage(trycatch.Message()->Get());
//            ASSERT_THAT(*exceptionMessage, HasSubstr("Invalid parameter"));
//
//        }

//
//        TEST_F(JSZAttributeUInt16Test, requestValueWithCallback) {
//            Callbacks callbacks;
//            REQUIRE_CALL(zclUint16Attribute, onChange(_)).WillOnce(Invoke(&callbacks, &Callbacks::add));
//            REQUIRE_CALL(zclUint16Attribute, requestValue());
//            REQUIRE_CALL(zclUint16Attribute, removeOnChangeListener(_)).WillOnce(
//                    Invoke(&callbacks, &Callbacks::remove));
//
//            requestValueWithCallbackTest(jsZAttribute.get(), &zclUint16Attribute, callbacks);
//        }
//
//        TEST_F(JSZAttributeUInt16Test, requestValueWithCallback_after_the_callback_is_not_called) {
//            Callbacks callbacks;
//            REQUIRE_CALL(zclUint16Attribute, onChange(_)).WillOnce(Invoke(&callbacks, &Callbacks::add));
//            REQUIRE_CALL(zclUint16Attribute, requestValue()).Times(1);
//
//            requestValueWithCallbackTestOnlyFirstTime(jsZAttribute.get(), &zclUint16Attribute, callbacks);
//        }


//        TEST_F(JSZAttributeUInt16Test, requestValueWithCallback_for_two_functions) {
//            Callbacks callbacks;
//            REQUIRE_CALL(zclUint16Attribute, onChange(_)).WillOnce(Invoke(&callbacks, &Callbacks::add));
//            REQUIRE_CALL(zclUint16Attribute, requestValue()).Times(1);
//
//            requestValueWithCallbackTestOnlyFirstTime(jsZAttribute.get(), &zclUint16Attribute, callbacks);
//        }


        TEST_F(JSZAttributeUInt16Test, isAvailable) {
            bool availableStatus = true;
            REQUIRE_CALL(attributeMock, isAvailable()).RETURN(availableStatus);
            isAvailableTest(availableStatus, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt16Test, isNotAvailable) {
            bool availableStatus = false;
            REQUIRE_CALL(attributeMock, isAvailable()).RETURN(availableStatus);
            isAvailableTest(availableStatus, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt16Test, isUnsupported) {
            bool unsupported = true;
            REQUIRE_CALL(attributeMock, isUnsupported()).RETURN(unsupported);
            isUnsupportedTest(unsupported, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt16Test, isSupported) {
            bool unsupported = false;
            REQUIRE_CALL(attributeMock, isUnsupported()).RETURN(unsupported);
            isUnsupportedTest(unsupported, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt16Test, statusNotAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotAvailable;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt16Test, statusAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Available;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt16Test, statusNotSupported) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotSupported;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt16Test, statusRequesting) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Requesting;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt16Test, statusUndefined) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Undefined;
            REQUIRE_CALL(attributeMock, getStatus()).RETURN(statusExpected);
            getStatusTest(statusExpected, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt16Test, getIdentifier) {
            REQUIRE_CALL(attributeMock, getIdentifier()).RETURN(ATTRIBUTE0_ID);
            getIdentifierTest(jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt16Test, getName) {
            std::string expectedName = "name";
            REQUIRE_CALL(attributeMock, getName()).RETURN(expectedName);
            getNameTest(expectedName, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt16Test, isReadOnly) {
            bool readOnlyValue = true;
            REQUIRE_CALL(attributeMock, isReadOnly()).RETURN(readOnlyValue);
            isReadonlyTest(readOnlyValue, jsZAttribute.get(), &attributeMock);
        }

        TEST_F(JSZAttributeUInt16Test, isWritable) {
            bool readOnlyValue = false;
            REQUIRE_CALL(attributeMock, isReadOnly()).RETURN(readOnlyValue);
            isReadonlyTest(readOnlyValue, jsZAttribute.get(), &attributeMock);
        }

    } /* namespace test */
} /* namespace zigbee */
