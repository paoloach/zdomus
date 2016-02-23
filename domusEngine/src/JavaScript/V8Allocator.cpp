//
// Created by paolo on 2/13/16.
//
#include <stdlib.h>
#include <string.h>
#include "V8Allocator.h"

void *V8Allocator::Allocate(size_t length) {
    void* data = AllocateUninitialized(length);
    return data == NULL ? data : memset(data, 0, length);
}

void *V8Allocator::AllocateUninitialized(size_t length) {
    return malloc(length);
}

void V8Allocator::Free(void *data, size_t length) {
    free(data);

}
