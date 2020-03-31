#pragma once
#include "heapman_impl.h"

namespace bpp
{
namespace ulib
{


class CDefaultHeapManager: public CHeapManagerBase
{
    virtual void* doMalloc(size_t size) { return ::malloc(size);}
    virtual void doFree(void* p)        { return ::free(p);}
    virtual void *doRealloc(void* p, size_t new_size) {return realloc(p, new_size);}
};

}} //namespace
