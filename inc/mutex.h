#pragma once

#include "./new.h"

namespace bpp
{
namespace os
{

class IMutex
{
public:
    typedef enum
    {
        eMUTEX_NORMAL =0,
        eMUTEX_ISR
    }EMode;

    virtual bool lock(EMode mode=eMUTEX_NORMAL) = 0;
    virtual bool unlock(EMode mode=eMUTEX_NORMAL) = 0;

    static IMutex* instance( bpp::ulib::IHeapManager* pHeapManager = nullptr);

public:
    virtual ~IMutex(){}
};
}}
