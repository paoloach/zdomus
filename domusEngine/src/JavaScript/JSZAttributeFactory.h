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
	JSZAttributeFactory();
	virtual ~JSZAttributeFactory();
public:
	virtual void init(const std::shared_ptr<ZDevices> & zDevices,const std::shared_ptr<ZigbeeDevice> & zigbeeDevice,const std::shared_ptr<ClusterTypeFactory> & clusterFactory);
	virtual void initJsObjectsTemplate(v8::Isolate * isolate, v8::Handle<v8::Object> & global);
	virtual v8::Local<v8::Object> createAttributeInstance(v8::Isolate* isolate, std::shared_ptr<ZCLAttribute> attribute );
	virtual void resetPersistences();
private:
    std::shared_ptr<JSZAttribute8BitBitmap> jsZAttribute8BitBitmap;
    std::shared_ptr<JSZAttribute16BitBitmap> jsZAttribute16BitBitmap;
    std::shared_ptr<JSZAttribute32BitBitmap> jsZAttribute32BitBitmap;
    std::shared_ptr<JSZAttributeBool> jsZAttributeBool;
    std::shared_ptr<JSZAttributeIEEEAddress>  jsZAttributeIEEEAddress;
    std::shared_ptr<JSZAttributeInt8> jsZAttributeInt8;
    std::shared_ptr<JSZAttributeInt16> jsZAttributeInt16;
    std::shared_ptr<JSZAttributeInt24> jsZAttributeInt24;
    std::shared_ptr<JSZAttributeInt32> jsZAttributeInt32;

    std::shared_ptr<JSZAttributeOctectString> jsZAttributeOctectString;
    std::shared_ptr<JSZAttributeString> jsZAttributeString;

    std::shared_ptr<JSZAttribute8BitEnum> jsZAttribute8BitEnum;

    std::shared_ptr<JSZAttributeUint8> jsZAttributeUInt8;
    std::shared_ptr<JSZAttributeUint16> jsZAttributeUInt16;
    std::shared_ptr<JSZAttributeUint24> jsZAttributeUInt24;
    std::shared_ptr<JSZAttributeUint32> jsZAttributeUInt32;
    std::shared_ptr<JSZAttributeUint48> jsZAttributeUInt48;

    std::shared_ptr<ZCLUTCTime> jsZAttributeUTCTime;


};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSZATTRIBUTEFACTORY_H_ */
