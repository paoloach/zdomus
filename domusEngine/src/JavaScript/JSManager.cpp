/*
 * JSManager.cpp
 *
 *  Created on: 23/dic/2014
 *      Author: Paolo Achdjian
 */

#include <boost/log/trivial.hpp>
#include <iostream>

#include "JSManager.h"

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

    JSManager::Task::Task(SingletonObjects &singletonObjects, const JavaScriptData &js) : js(js), jsExecuter(singletonObjects, js.getPeriod()) {
        jsExecuter.run(js.getCode());
    }


} /* namespace zigbee */
