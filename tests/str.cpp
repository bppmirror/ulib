#include "tests.h"

#include "../inc/str.h"
#include "../inc/log.h"

using namespace bpp;
using namespace bpp::ulib;

static void Basic()
{
    String s, s1, s2;

    BPP_TEST_CHECK(s == s1);
    BPP_TEST_CHECK(!(s != s1));
    BPP_TEST_CHECK(s == "");
    s= "hello";
    s1="hello";
    BPP_TEST_CHECK(s == s1);
    BPP_TEST_CHECK(!(s != s1));
    BPP_TEST_CHECK(s == "hello");

    s1+=s;
    BPP_TEST_CHECK(!(s == s1));
    BPP_TEST_CHECK(s != s1);
    BPP_TEST_CHECK(s1 == "hellohello");

    s1=s;
    BPP_TEST_CHECK(s == s1);
    BPP_TEST_CHECK(!(s != s1));
    BPP_TEST_CHECK(s == "hello");

    s+=" world";
    BPP_TEST_CHECK(!(s == s1));
    BPP_TEST_CHECK(s != s1);
    BPP_TEST_CHECK(s == "hello world");

    s1+="";
    s+=s2;
    BPP_TEST_CHECK(!(s == s1));
    BPP_TEST_CHECK(s != s1);
    BPP_TEST_CHECK(s == "hello world");

    s1= "hello";
    s2= " ";
    s1 = s1 + s2 + "world";
    BPP_TEST_CHECK(s1 == "hello world");

    s2 = s1 + ' ';
    BPP_TEST_CHECK(s2 == "hello world ");
}

static void Find()
{
    String s1("aabcdefghgfedcbaa");
    BPP_TEST_CHECK(s1.find("yh") == String::npos);
    BPP_TEST_CHECK(s1.find("aa") == 0);
    BPP_TEST_CHECK(s1.find("aa", (size_t)2) == 15);
    BPP_TEST_CHECK(s1.rfind("aa") == 15);
    BPP_TEST_CHECK(s1.rfind("aa", (size_t)14) == 0);
}

static void Case()
{
    String s1(" aABbZz !");

    BPP_TEST_CHECK(s1.lowerCase() == " aabbzz !");
    BPP_TEST_CHECK(s1.upperCase() == " AABBZZ !");
}

void testString()
{
    BPP_RUN_TEST(Basic);
    BPP_RUN_TEST(Find);
    BPP_RUN_TEST(Case);
}
