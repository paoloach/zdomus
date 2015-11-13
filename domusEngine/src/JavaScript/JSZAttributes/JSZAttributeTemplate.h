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

#include <zcl/attributeTypes/ZCLint16Attribute.h>
#include <zcl/attributeTypes/ZCLIEEEAddressAttribute.h>
#include <zcl/attributeTypes/ZCLbitmap8bitAttribute.h>
#include <zcl/attributeTypes/ZCLbooleanAttribute.h>
#include <zcl/attributeTypes/ZCLenum8bitAttribute.h>
#include <zcl/attributeTypes/ZCLuint16Attribute.h>
#include <zcl/attributeTypes/ZCLuint8Attribute.h>
#include <zcl/attributeTypes/ZCLuint24Attribute.h>
#include <zcl/attributeTypes/ZCLstringAttribute.h>

#include "../../ZigbeeData/ExtAddress.h"
#include "../JSZAttribute.h"
#include "../JSObjects.h"
#include "ParamCheckNull.h"
#include "ParamString.h"
#include "ParaUInt32.h"
#include "ParamInt32.h"
#include "ParamBool.h"
#include "ParamIEEEAddress.h"

namespace zigbee {

template <typename Source, typename Dest>
Dest cast(const  Source & ){
	return Dest();
}

template<typename AttributeType, typename ParamType>
class JSZAttributeTemplate: public JSZAttribute {
public:
	JSZAttributeTemplate(const std::shared_ptr<ZDevices> & zDevices, const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, const std::shared_ptr<ClusterTypeFactory> & clusterFactory) :
			JSZAttribute(zDevices, zigbeeDevice, clusterFactory) {
	}
	virtual ~JSZAttributeTemplate() {
	}
public:
	void initJsObjectsTemplate(v8::Isolate* isolate, v8::Handle<v8::Object>& global) override {
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
	ZCLTypeDataType getZCLDataType() const override {
		return AttributeType::type();
	}
	std::string getName() const override {
		return "Z" + AttributeType::name();
	}

	static void getValue(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info) {
		v8::Isolate * isolate = info.GetIsolate();
		try {
			v8::Local<v8::Object> self = info.Holder();
			v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(self->GetInternalField(0));
			AttributeType * attribute = (AttributeType *) wrap->Value();
			info.GetReturnValue().Set(ParamType::toV8(isolate, attribute->getValue()));
		} catch (std::exception & excp) {
			v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
			isolate->ThrowException(errorMsg);
		}
	}

	static void setValue(v8::Local<v8::String>, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info) {
		v8::Isolate * isolate = info.GetIsolate();
		try {
			v8::Local<v8::Object> self = info.Holder();
			v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(self->GetInternalField(0));
			AttributeType * attribute = (AttributeType *) wrap->Value();
			attribute->sendValue(ParamType::fromV8(value));
		} catch (std::exception & excp) {
			v8::Local<v8::String> errorMsg = v8::String::NewFromUtf8(isolate, excp.what());
			isolate->ThrowException(errorMsg);
		}
	}
};

typedef JSZAttributeTemplate<ZCLIEEEAddressAttribute,ParamIEEEAddress >   JSZAttributeIEEEAddress;
typedef JSZAttributeTemplate<ZCL_boolean_Attribute,ParamBool >   JSZAttributeBool;
typedef JSZAttributeTemplate<ZCL_enum8bit_Attribute,ParamUInt32<0, 0xFF> >   JSZAttribute8BitEnum;
typedef JSZAttributeTemplate<ZCL_bitmap8bit_Attribute,ParamUInt32<0, 0xFF> >   JSZAttribute8BitBitmap;
typedef JSZAttributeTemplate<ZCL_int16_Attribute,ParamInt32>   JSZAttributeInt16;
typedef JSZAttributeTemplate<ZCL_uint8_Attribute,ParamUInt32<0, 0xFF>>   JSZAttributeUint8;
typedef JSZAttributeTemplate<ZCL_uint16_Attribute,ParamUInt32<0,0xFFFF>>   JSZAttributeUint16;
typedef JSZAttributeTemplate<ZCL_uint24_Attribute,ParamUInt32<0, 0xFFFFFF>>   JSZAttributeUint24;
typedef JSZAttributeTemplate<ZCL_string_Attribute,ParamString>   JSZAttributeString;


} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSZATTRIBUTES_JSZATTRIBUTETEMPLATE_H_ */
