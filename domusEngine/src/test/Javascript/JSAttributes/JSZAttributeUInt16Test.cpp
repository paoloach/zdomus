/*
 * JSZAttributeUInt16.cpp
 *
 *  Created on: 09/gen/2015
 *      Author: Paolo Achdjian
 */

#include <tuple>
#include <zcl/Callbacks.h>
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
        using boost::function;


        void JSZAttributeUInt16Test::SetUp() {
            JSTest::SetUp();
            jsZAttribute = std::make_shared<JSZAttributeUint16>(&singletonObjectsMock, fifo);
            zAttributeVariable = createZAttributeVariable("Z" + ZCLUint16AttributeMock::name());
        }

        void JSZAttributeUInt16Test::TearDown() {
            jsZAttribute.reset();
            JSTest::TearDown();
        }

        TEST_F(JSZAttributeUInt16Test, createTemplate) {
            createTemplateTest(jsZAttribute);
        }

        TEST_F(JSZAttributeUInt16Test, createIstance) {
            createIstanceTest("Z" + ZCLUint16AttributeMock::name(), jsZAttribute, &zclUint16Attribute);
        }

        TEST_F(JSZAttributeUInt16Test, getValue) {
            auto expectedValue = 13u;
            ZDevice zDevice{createZDevice()};
            V8_SETUP
            jsZAttribute->initJsObjectsTemplate(isolate, global);

            setInitExpectation(zDevice, &zclUint16Attribute);
            EXPECT_CALL(zclUint16Attribute, getValue()).WillOnce(Return(std::any(expectedValue)));

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

            setInitExpectation(zDevice, &zclUint16Attribute);

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

        TEST_F(JSZAttributeUInt16Test, requestValue) {
            EXPECT_CALL(zclUint16Attribute, requestValue());
            requestValueTest(jsZAttribute, &zclUint16Attribute);
        }
//
//        TEST_F(JSZAttributeUInt16Test, requestValueWithCallback) {
//            Callbacks callbacks;
//            EXPECT_CALL(zclUint16Attribute, onChange(_)).WillOnce(Invoke(&callbacks, &Callbacks::add));
//            EXPECT_CALL(zclUint16Attribute, requestValue());
//            EXPECT_CALL(zclUint16Attribute, removeOnChangeListener(_)).WillOnce(
//                    Invoke(&callbacks, &Callbacks::remove));
//
//            requestValueWithCallbackTest(jsZAttribute, &zclUint16Attribute, callbacks);
//        }
//
//        TEST_F(JSZAttributeUInt16Test, requestValueWithCallback_after_the_callback_is_not_called) {
//            Callbacks callbacks;
//            EXPECT_CALL(zclUint16Attribute, onChange(_)).WillOnce(Invoke(&callbacks, &Callbacks::add));
//            EXPECT_CALL(zclUint16Attribute, requestValue()).Times(1);
//
//            requestValueWithCallbackTestOnlyFirstTime(jsZAttribute, &zclUint16Attribute, callbacks);
//        }


//        TEST_F(JSZAttributeUInt16Test, requestValueWithCallback_for_two_functions) {
//            Callbacks callbacks;
//            EXPECT_CALL(zclUint16Attribute, onChange(_)).WillOnce(Invoke(&callbacks, &Callbacks::add));
//            EXPECT_CALL(zclUint16Attribute, requestValue()).Times(1);
//
//            requestValueWithCallbackTestOnlyFirstTime(jsZAttribute, &zclUint16Attribute, callbacks);
//        }


        TEST_F(JSZAttributeUInt16Test, isAvailable) {
            bool availableStatus = true;
            EXPECT_CALL(zclUint16Attribute, isAvailable()).WillOnce(Return(availableStatus));
            isAvailableTest(availableStatus, jsZAttribute, &zclUint16Attribute);
        }

        TEST_F(JSZAttributeUInt16Test, isNotAvailable) {
            bool availableStatus = false;
            EXPECT_CALL(zclUint16Attribute, isAvailable()).WillOnce(Return(availableStatus));
            isAvailableTest(availableStatus, jsZAttribute, &zclUint16Attribute);
        }

        TEST_F(JSZAttributeUInt16Test, isUnsupported) {
            bool unsupported = true;
            EXPECT_CALL(zclUint16Attribute, isUnsupported()).WillOnce(Return(unsupported));
            isUnsupportedTest(unsupported, jsZAttribute, &zclUint16Attribute);
        }

        TEST_F(JSZAttributeUInt16Test, isSupported) {
            bool unsupported = false;
            EXPECT_CALL(zclUint16Attribute, isUnsupported()).WillOnce(Return(unsupported));
            isUnsupportedTest(unsupported, jsZAttribute, &zclUint16Attribute);
        }

        TEST_F(JSZAttributeUInt16Test, statusNotAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotAvailable;
            EXPECT_CALL(zclUint16Attribute, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, &zclUint16Attribute);
        }

        TEST_F(JSZAttributeUInt16Test, statusAvailable) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Available;
            EXPECT_CALL(zclUint16Attribute, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, &zclUint16Attribute);
        }

        TEST_F(JSZAttributeUInt16Test, statusNotSupported) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::NotSupported;
            EXPECT_CALL(zclUint16Attribute, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, &zclUint16Attribute);
        }

        TEST_F(JSZAttributeUInt16Test, statusRequesting) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Requesting;
            EXPECT_CALL(zclUint16Attribute, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, &zclUint16Attribute);
        }

        TEST_F(JSZAttributeUInt16Test, statusUndefined) {
            ZCLAttribute::Status statusExpected = ZCLAttribute::Undefined;
            EXPECT_CALL(zclUint16Attribute, getStatus()).WillOnce(Return(statusExpected));
            getStatusTest(statusExpected, jsZAttribute, &zclUint16Attribute);
        }

        TEST_F(JSZAttributeUInt16Test, getIdentifier) {
            EXPECT_CALL(zclUint16Attribute, getIdentifier()).WillOnce(Return(ATTRIBUTE0_ID));
            getIdentifierTest(jsZAttribute, &zclUint16Attribute);
        }

        TEST_F(JSZAttributeUInt16Test, getName) {
            std::string expectedName = "name";
            EXPECT_CALL(zclUint16Attribute, getName()).WillOnce(Return(expectedName));
            getNameTest(expectedName, jsZAttribute, &zclUint16Attribute);
        }

        TEST_F(JSZAttributeUInt16Test, isReadOnly) {
            bool readOnlyValue = true;
            EXPECT_CALL(zclUint16Attribute, isReadOnly()).WillOnce(Return(readOnlyValue));
            isReadonlyTest(readOnlyValue, jsZAttribute, &zclUint16Attribute);
        }

        TEST_F(JSZAttributeUInt16Test, isWritable) {
            bool readOnlyValue = false;
            EXPECT_CALL(zclUint16Attribute, isReadOnly()).WillOnce(Return(readOnlyValue));
            isReadonlyTest(readOnlyValue, jsZAttribute, &zclUint16Attribute);
        }

    } /* namespace test */
} /* namespace zigbee */
