/*
 * JSManager.h
 *
 *  Created on: 23/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSMANAGER_H_
#define SRC_JAVASCRIPT_JSMANAGER_H_

#include <boost/asio.hpp>
#include <boost/date_time.hpp>
#include <vector>
#include <map>
#include <thread>
#include <memory>
#include <sstream>

#include "../Configuration/Configuration.h"
#include "JavaScriptExecuter.h"
#include "../ZigbeeData/ZDevices.h"
#include "../Utils/Log.h"
#include "../httpServer/ExternalRestPath.h"


namespace zigbee {

    class ZigbeeDevice;

    class SingletonObjects;

    class JSManager {
    private:
        class Task {
        public:
            Task(SingletonObjects &singletonObjects, const JavaScriptData &js);

            const JavaScriptData & js;
            JavaScriptExecuter jsExecuter;
        };

    public:
        JSManager(SingletonObjects &singletonObjects);

        virtual ~JSManager() = default;

    private:
        std::vector<std::unique_ptr<Task>> tasks;
    };

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSMANAGER_H_ */
