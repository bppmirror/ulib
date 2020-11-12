#pragma once

namespace bpp
{
    typedef void (*AssertCallback)(char* formatted_msg, const char* file, int line, const char* msg);
    void setAssertHandler(AssertCallback cb);

    void trigerASSERT(const char* file, int line, void* caller, const char* msg = nullptr);
}

#define BPP_ASSERT(cond) if (!(cond)) ::bpp::trigerASSERT(__FILE__,__LINE__,__builtin_return_address(0), #cond);
#define BPP_ASSERT_MSG(cond, msg) if (!(cond)) ::bpp::trigerASSERT(__FILE__,__LINE__, __builtin_return_address(0),(msg));
