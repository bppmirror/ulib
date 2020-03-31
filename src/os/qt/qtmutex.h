#pragma once

#include <QMutex>

#include "../../../inc/mutex.h"
#include "../../../inc/new.h"

namespace bpp
{
namespace os
{

class QtMutex:public IMutex
{
public:
    QtMutex();
    virtual ~QtMutex();

    virtual bool lock(EMode mode);
    virtual bool unlock(EMode mode);


private:
    QMutex* mpMutex;
};

}}
