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

#include "../ZigbeeData/ZDevices.h"
#include "JSZDevices.h"
#include "JSZDevice.h"
#include "JSZEndpoint.h"
#include "JSZEndpoints.h"
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
#include "GlobalJSFunctions.h"
#include "JSCallbackFifo.h"

namespace zigbee {

    class ZigbeeDevice;

    class SingletonObjects;

    class JavaScriptExecuter {
    public:
        typedef boost::signals2::signal<void()> NotifyEnd;
        typedef NotifyEnd::slot_type OnEnd;
    public:
        JavaScriptExecuter(SingletonObjects &singletonObjects, std::chrono::seconds period, Log &log);

        virtual ~JavaScriptExecuter();

    public:
        void run(const std::string &jsCode);

        void join();

        boost::signals2::connection notificationEnd(const OnEnd &onEnd);

    private:
        void runThread();

    private:
        std::chrono::seconds period;
        V8Allocator v8Allocator;
        v8::Isolate::CreateParams createParams;
        Log &log;
        v8::Isolate *isolate;
        v8::UniquePersistent<v8::Context> context;
        std::string jsCode;
        std::thread jsThread;
        NotifyEnd notifyEnd;
        JSZAttributeFactory jsZAttributeFactory;
        DBTableFactory dbTableFactory;
        JSLog jsLog;
        JSRow jsRow;
        JSZCluster jsZCluster;
        JSDBTable jsDBTable;
        JSZEndpoint jsZEndpoint;
        JSZEndpoints jsZEndpoints;
        JSZDevice jsZDevice;
        JSRestServer jsRestServer;
        JSZDevices jszDevices;
        GlobalJSFunctions globalJSFunctions;
        JSCallbackFifo callbackFifo;
        bool stop;
    };

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JAVASCRIPTEXECUTER_H_ */
