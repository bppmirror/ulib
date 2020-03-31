#pragma once

#include <pthread.h>

#include "../../../inc/mutex.h"
#include "../../../inc/new.h"

namespace bpp
{
namespace os
{

class PMutex:public IMutex
{
public:
    PMutex();
    virtual ~PMutex();

    virtual bool lock(EMode mode);
    virtual bool unlock(EMode mode);


private:
    pthread_mutex_t mMutex;
};

}}
