#include "tests.h"

#include "../inc/str.h"
#include "../inc/log.h"
#include "../inc/strstream.h"

using namespace bpp;
using namespace bpp::ulib;

static void Basic()
{
    String s1("a");
    StrStream ss(&s1);
    ss<<"one"<<1;

    BPP_TEST_CHECK(s1 == "aone1");
}

void testStrstream()
{
    BPP_RUN_TEST(Basic);
}
