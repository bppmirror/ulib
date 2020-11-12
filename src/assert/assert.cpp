#include "../../inc/asrt.h"
#include "../../inc/assert/asrt_halt_stdio.h"


#include <stdlib.h>
#include <stdio.h>

#if not defined ASSERT_OUT_BUFF_SIZE
const size_t ASSERT_OUT_BUFF_SIZE = 96;
#endif

static bpp::AssertCallback pHandler= nullptr;

void bpp::setAssertHandler(bpp::AssertCallback cb)
{
    pHandler = cb;
}

void bpp::trigerASSERT(const char* file, int line, void *caller, const char* msg)
{
    static char buf[ASSERT_OUT_BUFF_SIZE];
    if (msg)
    {
        snprintf(buf, sizeof(buf), "ASSERT: %s:%d (%p) - %s\n", file, line, caller, msg);
    }
    else
    {
        snprintf(buf, sizeof(buf), "ASSERT: %s:%d (%p)\n", file, line, caller);
    }
    if (!pHandler)
    {
        ASSERT_HALT_STDIO(buf, file, line, msg);
    }
    else
    {
        pHandler(buf, file, line, msg);
    }
}
