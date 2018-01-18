/*
 * JSZAttributeTemplate.h
 *
 *  Created on: 13/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSZATTRIBUTES_JSZATTRIBUTETEMPLATE_H_
#define SRC_JAVASCRIPT_JSZATTRIBUTES_JSZATTRIBUTETEMPLATE_H_

#include <v8.h>
#include <memory>
#include <map>
#include <set>
#include <iostream>

#include <zcl/attributeTypes/ZCLbitmap8bitAttribute.h>
#include <zcl/attributeTypes/ZCLBitmap16bitAttribute.h>
#include <zcl/attributeTypes/ZCLBitmap32bitAttribute.h>
#include <zcl/attributeTypes/ZCLBooleanAttribute.h>
#include <zcl/attributeTypes/ZCLEnum8bitAttribute.h>
#include <zcl/attributeTypes/ZCLIEEEAddressAttribute.h>

#include <zcl/attributeTypes/ZCLint8Attribute.h>
#include <zcl/attributeTypes/ZCLint16Attribute.h>
#include <zcl/attributeTypes/ZCLint24Attribute.h>
#include <zcl/attributeTypes/ZCLint32Attribute.h>

#include <zcl/attributeTypes/ZCLOctectString.h>
#include <zcl/attributeTypes/ZCLStringAttribute.h>

#include <zcl/attributeTypes/ZCLuint8Attribute.h>
#include <zcl/attributeTypes/ZCLuint16Attribute.h>
#include <zcl/attributeTypes/ZCLuint24Attribute.h>
#include <zcl/attributeTypes/ZCLuint32Attribute.h>
#include <zcl/attributeTypes/ZCLuint48Attribute.h>

#include <zcl/attributeTypes/ZCLUTCTime.h>
#include <zigbee/ExtAddress.h>

#include "../JSCallbackFifo.h"

#include "../JSZAttribute.h"
#include "../JSObjects.h"
#include "ParamCheckNull.h"
#include "ParamString.h"
#include "ParaUInt32.h"
#include "ParamInt32.h"
#include "ParamBool.h"
#include "ParamIEEEAddress.h"

namespace zigbee {

    template<typename Source, typename Dest>
    Dest cast(const Source &) {
        return Dest();
    }

    template<typename AttributeType, typename ParamType>
    class JSZAttributeTemplate : public JSZAttribute {
    public:
        JSZAttributeTemplate(SingletonObjects *singletonObjects, JSCallbackFifo &callbackFifo) : JSZAttribute(singletonObjects, callbackFifo, AttributeType::type) {
        }

        virtual ~JSZAttributeTemplate() = default;

    public:
        void initJsObjectsTemplate(v8::Isolate *isolate, v8::Handle<v8::Object> &global) override {
            v8::Local<v8::String> jsZAttributeClassName = v8::String::NewFromUtf8(isolate, getName().c_str());

            // attributes
            v8::Local<v8::String> valueAttribute = v8::String::NewFromUtf8(isolate, VALUE);
            // method

            v8::Local<v8::FunctionTemplate> zAttributeFunctionTemplate = v8::FunctionTemplate::New(isolate, constructor, v8::External::New(isolate, this));
            zAttributeFunctionTemplate->SetClassName(jsZAttributeClassName);
            v8::Local<v8::ObjectTemplate> zAttributeClusterInstanceTemplate = zAttributeFunctionTemplate->InstanceTemplate();

            zAttributeClusterInstanceTemplate->SetInternalFieldCount(2);
            // attributes
            zAttributeClusterInstanceTemplate->SetAccessor(valueAttribute, getValue, &setValue);
            global->Set(jsZAttributeClassName, zAttributeFunctionTemplate->GetFunction());

            JSZAttribute::initJsObjectsTemplate(isolate, zAttributeFunctionTemplate);
            functionTemplate.Reset(isolate, zAttributeFunctionTemplate);
        }

    protected:
        std::string getName() const override {
            return "Z" + AttributeType::name();
        }

        static void getValue(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value> &info) {
            v8::Isolate *isolate = info.GetIsolate();
            try {
                v8::Local<v8::Object> self = info.Holder();
                v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(self->GetInternalField(0));
                AttributeType *attribute = (AttributeType *) wrap->Value();
                info.GetReturnValue().Set(ParamType::toV8(isolate, attribute->getValue()));
            } catch (std::exception &excp) {
                v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
                isolate->ThrowException(errorMsg);
            }
        }

        static void setValue(v8::Local<v8::String>, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void> &info) {
            v8::Isolate *isolate = info.GetIsolate();
            try {
                v8::Local<v8::Object> self = info.Holder();
                v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(self->GetInternalField(0));
                AttributeType *attribute = (AttributeType *) wrap->Value();
                std::any anyValue(ParamType::fromV8(value));
                attribute->setValue(anyValue);
            } catch (std::exception &excp) {
                v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
                isolate->ThrowException(errorMsg);
            }
        }
    };

    typedef JSZAttributeTemplate<ZCLBitmap8bitAttribute, ParamUInt32<0, 0xFF> > JSZAttribute8BitBitmap;
    typedef JSZAttributeTemplate<ZCLBitmap16bitAttribute, ParamUInt32<0, 0xFF> > JSZAttribute16BitBitmap;
    typedef JSZAttributeTemplate<ZCLBitmap32bitAttribute, ParamUInt32<0, 0xFF> > JSZAttribute32BitBitmap;
    typedef JSZAttributeTemplate<ZCLBooleanAttribute, ParamBool> JSZAttributeBool;
    typedef JSZAttributeTemplate<ZCLIEEEAddressAttribute, ParamIEEEAddress> JSZAttributeIEEEAddress;
    typedef JSZAttributeTemplate<ZCLint8Attribute, ParamInt32<-0x7F, 0x7F> > JSZAttributeInt8;
    typedef JSZAttributeTemplate<ZCLint16Attribute, ParamInt32<-0x7FFF, 0x7FFF>> JSZAttributeInt16;
    typedef JSZAttributeTemplate<ZCLint24Attribute, ParamInt32<-0x7FFFFF, 0x7FFFFF>> JSZAttributeInt24;
    typedef JSZAttributeTemplate<ZCLint32Attribute, ParamInt32<-0x7FFFFFFF, 0x7FFFFFFF>> JSZAttributeInt32;

    typedef JSZAttributeTemplate<ZCLOctetString, ParamString> JSZAttributeOctectString;
    typedef JSZAttributeTemplate<ZCLStringAttribute, ParamString> JSZAttributeString;

    typedef JSZAttributeTemplate<ZCLEnum8bitAttribute, ParamUInt32<0, 0xFF> > JSZAttribute8BitEnum;

    typedef JSZAttributeTemplate<ZCLuint8Attribute, ParamUInt32<0, 0xFF>> JSZAttributeUint8;
    typedef JSZAttributeTemplate<ZCLuint16Attribute, ParamUInt32<0, 0xFFFF>> JSZAttributeUint16;
    typedef JSZAttributeTemplate<ZCLuint24Attribute, ParamUInt32<0, 0xFFFFFF>> JSZAttributeUint24;
    typedef JSZAttributeTemplate<ZCLuint32Attribute, ParamUInt32<0, 0xFFFFFFFF>> JSZAttributeUint32;
    typedef JSZAttributeTemplate<ZCLuint48Attribute, ParamUInt32<0, 0xFFFFFFFF>> JSZAttributeUint48;

    typedef JSZAttributeTemplate<ZCLUTCTime, ParamUInt32<0, 0xFFFFFFFF>> JSZAttributeTCTime;


} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSZATTRIBUTES_JSZATTRIBUTETEMPLATE_H_ */
