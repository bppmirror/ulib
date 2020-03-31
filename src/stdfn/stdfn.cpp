#include "../../inc/stdfn/stdfn.h"

using namespace bpp;

static SStdFunc fn;

const SStdFunc& bpp::stdfFn()
{
    if (!fn.memcpy)
    {
        fn = SStdFunc();
    }
    return fn;
}

void bpp::setStdFn(const SStdFunc& stdfn)
{
    fn = stdfn;
}
