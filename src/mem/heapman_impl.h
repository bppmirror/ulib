#pragma once

#include "../../inc/heapman.h"
namespace bpp
{
namespace ulib
{


class CHeapManagerBase:public IHeapManager
{
public:
    CHeapManagerBase();
    virtual ~CHeapManagerBase();
public:
    virtual void* malloc(size_t size);
    virtual void  free(void* p);
    virtual void *realloc(void* p, size_t new_size);
    virtual SHeapState state() {return mHeapState;}

protected:
    virtual void* doMalloc(size_t size)=0;
    virtual void doFree(void* p)=0;
    virtual void *doRealloc(void* p, size_t new_size);

protected:
    SHeapState& heapStateRef(){ return mHeapState;}

private:
    SHeapState mHeapState;

};

}}//namespace
