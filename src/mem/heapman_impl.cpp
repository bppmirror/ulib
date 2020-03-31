#include "heapman_impl.h"

#include "../../inc/asrt.h"
#include "../../inc/stdfn/stdfn.h"

bpp::ulib::CHeapManagerBase::CHeapManagerBase()
{
    // do nothing
}

bpp::ulib::CHeapManagerBase::~CHeapManagerBase()
{
    BPP_ASSERT(heapStateRef().mFreeCount >= heapStateRef().mMallocCount)
}

void *bpp::ulib::CHeapManagerBase::malloc(size_t size)
{
    heapStateRef().mMallocCount++;
    return doMalloc(size);
}

void bpp::ulib::CHeapManagerBase::free(void *p)
{
    if (p == nullptr)
    {
        // do nothing
        return;
    }
    heapStateRef().mFreeCount++;

    BPP_ASSERT(heapStateRef().mFreeCount >= heapStateRef().mMallocCount)

    return doFree(p);
}

void *bpp::ulib::CHeapManagerBase::realloc(void *p, size_t new_size)
{
    if (p == nullptr)
    {
        // do nothing
        return nullptr;
    }
    return doRealloc(p, new_size);
}

void *bpp::ulib::CHeapManagerBase::doRealloc(void *p, size_t new_size)
{
    void* ptr = this->malloc(new_size);
    if (ptr == nullptr)
    {
        return nullptr;
    }
    bpp::stdfFn().memcpy(p, ptr, new_size);
    free(p);
    return ptr;
}
