#pragma once

#include "trace.h"
#include "str.h"

namespace bpp
{
namespace ulib
{

class FunctionTracer
{
public:
    FunctionTracer(const char* name):mName(name)
    {
        LogOut& out = LOG(Log::TRACE);
        if (mDepth > 0 )
            for(size_t i=0; i<mDepth; i++)
            {
                out<<'.';
            }
        out<<">>"<<name<<"\n"<<bpp::LogOut::FLUSH;
        mDepth++;
    }

    ~FunctionTracer()
    {
        LogOut& out = LOG(Log::TRACE);
        mDepth--;
        if (mDepth > 0 )
            for(size_t i=0; i<mDepth; i++)
            {
                out<<'.';
            }
        out<<"<<"<<mName.c_str()<<"\n"<<bpp::LogOut::FLUSH;
    }

private:
    static size_t mDepth;
    bpp::ulib::String mName;
};

#define TRACED_FUNCTION\
    bpp::ulib::FunctionTracer tracer(__FUNCTION__);

}
}
