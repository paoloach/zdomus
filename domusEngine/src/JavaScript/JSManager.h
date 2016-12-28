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
#include "../httpServer/FixedPathContainer.h"


namespace zigbee {

    class ZigbeeDevice;

    class SingletonObjects;

    class JSManager {
    private:
        class Task {
        public:
            Task(SingletonObjects &singletonObjects, const std::shared_ptr<JavaScriptData> &js);

            void timerHandler(const boost::system::error_code &error);

            void endJS();

            Log log;
            boost::asio::deadline_timer timer;
            std::shared_ptr<JavaScriptData> js;
            JavaScriptExecuter jsExecuter;
        };

    public:
        JSManager(SingletonObjects &singletonObjects);

        virtual ~JSManager() = default;

    private:
        std::map<std::shared_ptr<JavaScriptData>, std::shared_ptr<Task>> tasks;
    };

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPT_JSMANAGER_H_ */
