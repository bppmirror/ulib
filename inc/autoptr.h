#pragma once

#include <stdlib.h>

#include "../assert/assert.h"

template <typename T>
class AutoPtr
{
private:
    T** mPtr;

    void *operator new[](size_t size){(void) size; return nullptr;} // prevent dynamic allocations
    void *operator new(size_t size){(void) size; return nullptr;} // prevent dynamic allocations
    //! Hide copy constructor
    AutoPtr (const AutoPtr&){}
    //! Prevent assignment
    AutoPtr& operator=(AutoPtr){}
public:
    AutoPtr(T** aptr) {BPP_ASSERT(mPtr) mPtr = aptr;}
    ~AutoPtr(){if (*mPtr) {delete *mPtr; *mPtr = nullptr;}}

    T* pointer() {return *mPtr;}
    bool isNull() {return nullptr != *mPtr;}
    T* operator->() {BPP_ASSERT(*mPtr) return *mPtr;}
    T& operator*() {BPP_ASSERT(*mPtr) return **mPtr;}
};
