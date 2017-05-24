//
// Created by paolo on 02/05/17.
//

#ifndef DOMUS_ENGINE_HTTP_RESPONSE_EVENT_H
#define DOMUS_ENGINE_HTTP_RESPONSE_EVENT_H


#include <functional>
#include <chrono>
#include <list>
#include <mutex>

namespace zigbee {
    namespace http {
        class HttpResponseEvent {
        public:
            struct Event {
                virtual ~Event()= default;
                std::function<bool()> checkEvent;
                std::function<void()> event;
                std::function<void()> timeoutEvent;
                std::chrono::system_clock::time_point timeout;
            };

            HttpResponseEvent() : toStop(false), thread(HttpResponseEvent::staticRun, this) {}

            ~HttpResponseEvent() {
                if (thread.joinable()){
                    toStop=true;
                    thread.join();
                }
            }

            void addEvent(std::unique_ptr<Event> &&event);

            static void staticRun(HttpResponseEvent *This) { This->run(); }

            void run();

            void stop();

        private:
            std::list<std::unique_ptr<Event>> events;
            std::mutex mutex;
            bool toStop;
            std::thread thread;

        };
    }
}

#endif //DOMUS_ENGINE_HTTP_RESPONSE_EVENT_H
