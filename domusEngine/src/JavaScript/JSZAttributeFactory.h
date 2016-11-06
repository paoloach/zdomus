/*
 * JSZAttributeFactory.h
 *
 *  Created on: 10/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSZATTRIBUTEFACTORY_H_
#define SRC_JAVASCRIPT_JSZATTRIBUTEFACTORY_H_

#include <v8.h>
#include <memory>
#include "JSZAttributes/JSZAttributeTemplate.h"

namespace zigbee {

class ZCLAttribute;
class ZDevices;
class ZigbeeDevice;
class ClusterTypeFactory;


class JSZAttributeFactory {
public:
	virtual ~JSZAttributeFactory()= default;
public:
	virtual void init( ZDevices * zDevices, ZigbeeDevice * zigbeeDevice,const std::shared_ptr<ClusterTypeFactory> & clusterFactory);
	virtual void initJsObjectsTemplate(v8::Isolate * isolate, v8::Handle<v8::Object> & global);
	virtual v8::Local<v8::Object> createAttributeInstance(v8::Isolate* isolate, std::shared_ptr<ZCLAttribute> attribute );
	virtual void resetPersistences();
private:
    std::array<std::unique_ptr<JSZAttribute>, 17> attributes;
};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSZATTRIBUTEFACTORY_H_ */
