/*
 * JavaScriptExecuter.h
 *
 *  Created on: 26/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JAVASCRIPTEXECUTER_H_
#define SRC_JAVASCRIPT_JAVASCRIPTEXECUTER_H_

#include <v8.h>
#include <thread>
#include <boost/signals2.hpp>
#include <zcl/ClusterTypeFactory.h>

#include "../ZigbeeData/ZDevices.h"
#include "JSZDevices.h"
#include "JSZDevice.h"
#include "JSZEndpoint.h"
#include "JSZAttributeFactory.h"
#include "JSZCluster.h"
#include "JSRow.h"
#include "JSDBTable.h"
#include "../Utils/Log.h"
#include "JSLog.h"
#include "JSRestServer.h"
#include "../Database/DBTableFactory.h"
#include "../httpServer/FixedPathContainer.h"
#include "V8Allocator.h"

namespace zigbee {

class ZigbeeDevice;
class SingletonObjects;

class JavaScriptExecuter {
public:
	typedef boost::signals2::signal<void ()> NotifyEnd;
	typedef NotifyEnd::slot_type OnEnd;
public:
	JavaScriptExecuter(SingletonObjects & singletonObjects, Log & log );
	virtual ~JavaScriptExecuter();
public:
	void run(const std::string & jsCode);
	void join();
	boost::signals2::connection notificationEnd(const OnEnd & onEnd);
private:
	void runThread();
private:
    V8Allocator v8Allocator;
    v8::Isolate::CreateParams createParams;
//	SingletonObjects & singletonObjects;
	Log & log;
	v8::Isolate * isolate;
	v8::UniquePersistent<v8::Context> context;
	std::string jsCode;
	std::thread jsThread;
	NotifyEnd notifyEnd;
	std::shared_ptr<ClusterTypeFactory>  clusterTypeFactory;
	JSZDevice_P jsZDevice;
	JSZEndpoint_P jsZEndpoint;
	JSZDevices_P jszDevices;
	DBTableFactory dbTableFactory;
	std::shared_ptr<JSZAttributeFactory>  jsZAttributeFactory;
	std::shared_ptr<JSZCluster> jsZCluster;
	std::shared_ptr<JSLog> jsLog;
	std::shared_ptr<JSRestServer> jsRestServer;
	std::shared_ptr<JSRow> jsRow;
	std::shared_ptr<JSDBTable> jsDBTable;

};

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JAVASCRIPTEXECUTER_H_ */
