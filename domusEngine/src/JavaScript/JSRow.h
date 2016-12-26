/*
 * JSRow.h
 *
 *  Created on: 22/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSROW_H_
#define SRC_JAVASCRIPT_JSROW_H_

#include <v8.h>
#include <memory>
#include <map>
#include <boost/any.hpp>
#include "../Database/DBRow.h"

namespace zigbee {


class JSRow {
public:
	virtual ~JSRow();
public:
	virtual void initJsObjectsTemplate(v8::Isolate * isolate, v8::Handle<v8::Object> & global);
	virtual v8::Local<v8::Object> createInstance(v8::Isolate* isolate, std::shared_ptr<DBRow>  dbRow);
	virtual void resetPersistences();
protected:
	static void constructor(const v8::FunctionCallbackInfo<v8::Value>& info);
	static void getValue(const v8::FunctionCallbackInfo<v8::Value>& info);
	static void setValue(const v8::FunctionCallbackInfo<v8::Value>& info);
private:
	v8::UniquePersistent<v8::FunctionTemplate> functionTemplate;
	std::map<std::shared_ptr<DBRow>, v8::Persistent<v8::Object,v8::CopyablePersistentTraits<v8::Object>> >  createdObject;

	static DBRow *  getDbRow(const v8::FunctionCallbackInfo<v8::Value>& info);
	static void checkSingleParam(const std::string & methodName, const v8::FunctionCallbackInfo<v8::Value>& info);
	static void checkTwoParam(const std::string & methodName, const v8::FunctionCallbackInfo<v8::Value>& info);
	static void checkStringParam(const std::string & methodName, const v8::FunctionCallbackInfo<v8::Value>& info, uint32_t index);
	static void weakCallback(const v8::WeakCallbackInfo<JSRow>& data);
};


} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSROW_H_ */
