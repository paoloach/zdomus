/*
 * JSManager.cpp
 *
 *  Created on: 23/dic/2014
 *      Author: Paolo Achdjian
 */

#include <iostream>
#include <functional>

#include "JSManager.h"
#include "../Utils/SingletonObjects.h"

namespace zigbee {

using boost::asio::deadline_timer;
using std::shared_ptr;
using std::make_shared;
using boost::system::error_code;

JSManager::JSManager(SingletonObjects & singletonObjects){
	for (const auto & js : singletonObjects.getConfiguration()->getJavascriptData()) {
		auto task = std::make_shared<Task>(singletonObjects, js.second);
		tasks.insert( { js.second, task });
	}

}

JSManager::~JSManager() {
}

JSManager::Task::Task(SingletonObjects & singletonObjects, const std::shared_ptr<JavaScriptData> & js) :
		timer(singletonObjects.getIO(), js->getPeriod()), js(js), jsExecuter(singletonObjects, log) {
	jsExecuter.notificationEnd(boost::bind(&Task::endJS, this));

	jsExecuter.run(js->getCode());
}

void JSManager::Task::endJS() {
	timer.expires_from_now(js->getPeriod());
	timer.async_wait(boost::bind(&Task::timerHandler, this, boost::asio::placeholders::error));
}

void JSManager::Task::timerHandler(const error_code&) {
	jsExecuter.join();
	Log::LogData logData = log.get();
	while (!logData.msg.empty()) {
		logData = log.get();
	}
	jsExecuter.run(js->getCode());
}

} /* namespace zigbee */
