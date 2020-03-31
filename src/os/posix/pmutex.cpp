#include "frmutex.h"

#include "../../../inc/asrt.h"

static /*signed*/ BaseType_t def_priority = pdFALSE;

bpp::os::PMutex::PMutex()
{
    mMutex = PTHREAD_MUTEX_INITIALIZER;
}

bpp::os::PMutex::~PMutex()
{
    //TODO
}

bool bpp::os::PMutex::lock(EMode mode)
{
    (void)mode;
    return (0 == pthread_mutex_lock( &mMutex ));
}

bool bpp::os::PMutex::unlock(EMode mode)
{
    (void)mode;
    return (0 ==  pthread_mutex_unlock( &mMutex ));
}

bpp::os::IMutex* bpp::os::IMutex::instance(bpp::ulib::IHeapManager* pHeapManager)
{
    (void)pHeapManager;
    return new (pHeapManager) bpp::os::PMutex;
}
