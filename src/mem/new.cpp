#include "../../inc/new.h"

const unsigned int HMMD_MAGIC = 0x1982;

typedef struct _SHMData
{
    _SHMData(bpp::ulib::IHeapManager* pHM):mMagic(HMMD_MAGIC), mpHeapManager(pHM){}
    unsigned int mMagic;
    bpp::ulib::IHeapManager* mpHeapManager;
    static bool Check(void* p)
        { if (!p) return false;
          return ( ((static_cast<_SHMData*>(p))->mMagic == HMMD_MAGIC )
                 && ((static_cast<_SHMData*>(p))->mpHeapManager != nullptr) ); }

}SHMData;

static void* doNew(size_t size, bpp::ulib::IHeapManager* hm)
{
    if (nullptr == hm)
    {
        return ::malloc(size);
    }

    void* p = hm->malloc(size + sizeof(SHMData));
    if (nullptr == p)
    {
        return p;
    }
    *(static_cast<SHMData*>(p)) = SHMData(hm);
    return (static_cast<unsigned char*>(p))+sizeof(SHMData);
}

void* operator new(size_t size, bpp::ulib::IHeapManager* hm)
{
    return doNew(size, hm);
}

void* operator new[](size_t size, bpp::ulib::IHeapManager *hm)
{
    return doNew(size, hm);
}

static void doDelete(void* p)
{
    if (nullptr == p)
    {
        return;
    }
    SHMData* pData = (SHMData*)( (static_cast<char*>(p) - sizeof(SHMData)) );
    if ( !SHMData::Check(pData))
    {
        ::free(p);
    }
    else
    {
        pData->mpHeapManager->free(pData);
    }
}

void operator delete(void *p) _GLIBCXX_USE_NOEXCEPT
{
    doDelete(p);
}

void operator delete[](void *p) _GLIBCXX_USE_NOEXCEPT
{
    doDelete(p);
}

bpp::ulib::IHeapManager *bpp::heapManager(void *p)
{
    if (nullptr == p)
    {
        return nullptr;
    }
    SHMData* pData = (SHMData*)( (static_cast<char*>(p) - sizeof(SHMData)) );
    if ( SHMData::Check(pData))
    {
        return pData->mpHeapManager;
    }
    else
    {
        return nullptr;
    }
}
