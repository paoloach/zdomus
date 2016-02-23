//
// Created by paolo on 2/13/16.
//

#ifndef DOMUS_ENGINE_V8ALLOCATOR_H
#define DOMUS_ENGINE_V8ALLOCATOR_H

#include <v8.h>


class V8Allocator : public v8::ArrayBuffer::Allocator {
public:
    ~V8Allocator() = default;
    virtual void* Allocate(size_t length);
    virtual void* AllocateUninitialized(size_t length) ;
    virtual void Free(void* data, size_t length);
};


#endif //DOMUS_ENGINE_V8ALLOCATOR_H
