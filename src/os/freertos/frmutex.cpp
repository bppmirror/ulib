#include "frmutex.h"

#include "../../../inc/asrt.h"

static /*signed*/ BaseType_t def_priority = pdFALSE;

bpp::os::FRMutex::FRMutex()
{
    mMutex = xSemaphoreCreateMutex();
    BPP_ASSERT(mMutex != 0)
}

bpp::os::FRMutex::~FRMutex()
{
    if (mMutex)
    {
        vSemaphoreDelete(mMutex);
    }
}

bool bpp::os::FRMutex::lock(EMode mode)
{
    BPP_ASSERT(mMutex)    
    bool ret = false;

    if (eMUTEX_NORMAL == mode)
    {
        ret = pdTRUE == xSemaphoreTake(mMutex, (TickType_t)portMAX_DELAY);
    }
    else
    {
        ret = pdTRUE == xSemaphoreTakeFromISR(mMutex, &def_priority);
    }
    return ret;
}

bool bpp::os::FRMutex::unlock(EMode mode)
{
    BPP_ASSERT(mMutex)
    bool ret = false;
    if (eMUTEX_NORMAL == mode)
    {
        ret = pdTRUE == xSemaphoreGive(mMutex);
    }else{
        ret = pdTRUE == xSemaphoreGiveFromISR(mMutex, &def_priority);    
    }
    return ret;
}

bpp::os::IMutex* bpp::os::IMutex::instance(bpp::ulib::IHeapManager* pHeapManager)
{
    (void)pHeapManager;
    return new (pHeapManager) bpp::os::FRMutex;
}
