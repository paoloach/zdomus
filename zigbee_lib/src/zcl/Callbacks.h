//
// Created by developer on 12/3/15.
//

#ifndef ZIGBEE_LIB_CALLBACKS_H
#define ZIGBEE_LIB_CALLBACKS_H

#include <list>
#include <functional>

namespace zigbee {
    class Callbacks {
    public:
        using ListenerOnChange = std::list<std::function<void()>>::iterator;

        ListenerOnChange add(std::function<void()> callback){
            if (data.empty()){
                data.push_front(callback);
                return data.begin();
            } else {
                return data.insert(data.begin(), callback);
            }
        }

        void remove(ListenerOnChange & listener){
            data.erase(listener);
        }

        void operator()() {
            std::list<std::function<void()>> dataTmp(data);
            for(auto & callback: dataTmp){
                callback();
            }
        };
    private:
        std::list<std::function<void()>> data;
    };

}


#endif //ZIGBEE_LIB_CALLBACKS_H
