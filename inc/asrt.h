#pragma once

namespace bpp
{
    typedef void (*AssertCallback)(char* formatted_msg, const char* file, int line, const char* msg);
    void setAssertHandler(AssertCallback cb);

    void trigerASSERT(const char* file, int line, const char* msg = nullptr);
}

#define BPP_ASSERT(cond) if (!(cond)) ::bpp::trigerASSERT(__FILE__,__LINE__);
#define BPP_ASSERT_MSG(cond, msg) if (!(cond)) ::bpp::trigerASSERT(__FILE__,__LINE__,(msg));
