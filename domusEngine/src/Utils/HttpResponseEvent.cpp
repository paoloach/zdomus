//
// Created by paolo on 02/05/17.
//

#include <thread>
#include <boost/log/trivial.hpp>
#include "HttpResponseEvent.h"

using namespace std::literals;
using std::chrono::system_clock;
namespace zigbee {
    namespace http {
        void HttpResponseEvent::addEvent(std::unique_ptr<HttpResponseEvent::Event> &&event) {
            std::lock_guard<std::mutex> lock(mutex);
            events.push_back(std::move(event));
        }

        void HttpResponseEvent::run() {
            while (!toStop) {
                {
                    std::lock_guard<std::mutex> lock(mutex);
                    auto it = events.begin();
                    while (it != events.end()) {
                        if ((*it)->checkEvent()) {
                            (*it)->event();
                            auto toRemove = it;
                            it++;
                            events.erase(toRemove);
                        } else {
                            it++;
                        }
                    }
                    it = events.begin();
                    auto now = system_clock::now();
                    while (it != events.end()) {
                        if (now > (*it)->timeout) {
                            (*it)->timeoutEvent();
                            auto toRemove = it;
                            it++;
                            events.erase(toRemove);
                        } else {
                            it++;
                        }

                    }
                }
                std::this_thread::sleep_for(100ms);
            }
        }

        void HttpResponseEvent::stop() {
            toStop = true;
        }

    }
}