//
// Created by paolo on 29/12/16.
//

#ifndef DOMUS_ENGINE_GLOBALJSFUNCTIONS_H
#define DOMUS_ENGINE_GLOBALJSFUNCTIONS_H

#include <v8.h>

namespace zigbee {
    class GlobalJSFunctions {
    public:
        virtual ~GlobalJSFunctions() = default;
        virtual void initFunctions(v8::Isolate *isolate, v8::Handle<v8::Object> &global);

    private:
        static void fnWait(const v8::FunctionCallbackInfo<v8::Value>& info);
    };

}

#endif //DOMUS_ENGINE_GLOBALJSFUNCTIONS_H
