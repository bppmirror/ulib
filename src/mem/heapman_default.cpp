#include "heapman_default.h"

using namespace bpp;
using namespace ulib;

static CDefaultHeapManager DHMinstance;

IHeapManager* bpp::ulib::defaultHM()
{
    return &DHMinstance;
}
