/*
 * JSManager.cpp
 *
 *  Created on: 23/dic/2014
 *      Author: Paolo Achdjian
 */

#include <boost/log/trivial.hpp>
#include <iostream>
#include <functional>

#include "JSManager.h"
#include "../Utils/SingletonObjects.h"

namespace zigbee {

    using boost::asio::deadline_timer;
    using std::shared_ptr;
    using std::make_shared;
    using boost::system::error_code;

    JSManager::JSManager(SingletonObjects &singletonObjects) {
        for (const auto &js : singletonObjects.getConfiguration()->getJavascriptData()) {
            auto task = std::make_unique<Task>(singletonObjects, js.second);
            tasks.push_back(std::move(task));
        }

    }

    JSManager::Task::Task(SingletonObjects &singletonObjects, const JavaScriptData &js) : js(js), jsExecuter(singletonObjects, js.getPeriod(), log) {
        jsExecuter.run(js.getCode());
    }

//    void JSManager::Task::timerHandler(const error_code &) {
//        jsExecuter.join();
//        Log::LogData logData = log.get();
//        if (!logData.msg.empty())
//            BOOST_LOG_TRIVIAL(info) << js.getName() << ":" << logData.msg;
//        while (!logData.msg.empty()) {
//            logData = log.get();
//            if (!logData.msg.empty())
//                BOOST_LOG_TRIVIAL(info) << js.getName() << ":" << logData.msg;
//        }
//        BOOST_LOG_TRIVIAL(info) << "executing " << js.getName();
//        jsExecuter.run(js.getCode());
//    }

} /* namespace zigbee */
