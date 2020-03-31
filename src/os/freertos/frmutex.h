#pragma once

#include "FreeRTOS.h"
#include "semphr.h"

#include "../../../inc/mutex.h"
#include "../../../inc/new.h"

namespace bpp
{
namespace os
{

class FRMutex:public IMutex
{
public:
    FRMutex();
    virtual ~FRMutex();

    virtual bool lock(EMode mode);
    virtual bool unlock(EMode mode);


private:
    SemaphoreHandle_t mMutex;
};

}}
