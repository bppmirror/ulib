#include "qtmutex.h"

#include "../../../inc/asrt.h"

bpp::os::QtMutex::QtMutex()
{
    mpMutex = new MY_HEAP_MANAGER QMutex();
    BPP_ASSERT(mpMutex)
}

bpp::os::QtMutex::~QtMutex()
{
    if (mpMutex)
    {
        delete mpMutex;
    }
}

bool bpp::os::QtMutex::lock(EMode mode)
{
    BPP_ASSERT(mpMutex)
    (void)mode;
    mpMutex->lock();
    return true;
}

bool bpp::os::QtMutex::unlock(EMode mode)
{
    BPP_ASSERT(mpMutex)
    (void)mode;
    mpMutex->unlock();
    return true;
}

bpp::os::IMutex* bpp::os::IMutex::instance(bpp::ulib::IHeapManager* pHeapManager)
{
    (void)pHeapManager;
    return new (pHeapManager) bpp::os::QtMutex;
}
