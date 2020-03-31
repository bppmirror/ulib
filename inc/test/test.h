#pragma once

#include <stdint.h>

namespace bpp
{
namespace test
{

typedef void (*TestFunction) (void);

class UnitTester
{
public:

    bool addComponent(TestFunction fn, const char* name);

    void runTest(TestFunction fn, const char* name, int reps = 1);

    bool StartTests();

    bool printReport();

    void reportCondition(const char* file, int line, bool success, const char* msg = nullptr);

    void reportPointPassed(const char* file, int line, const char* msg = nullptr);

    void reset();

    static UnitTester& ref();

protected:
    UnitTester();

};

#define BPP_RUN_TEST(fn) bpp::test::UnitTester::ref().runTest(fn, #fn)
#define BPP_RUN_TESTS(fn, rep) bpp::test::UnitTester::ref().runTest(fn, #fn, rep)

#define BPP_TEST_CHECK(cond)          bpp::test::UnitTester::ref().reportCondition(__FILE__, __LINE__, ( cond ))
#define BPP_TEST_CHECK_MSG(cond, msg) bpp::test::UnitTester::ref().reportCondition(__FILE__, __LINE__, (cond), msg)
#define BPP_TEST_CHECK_RETURN (cond) { bool isSuccess = (cond); bpp::test::UnitTester::ref().reportCondition(__FILE__, __LINE__, (isSuccess)); if (!(isSuccess)) return
#define BPP_TEST_POINT_PASSED        bpp::test::UnitTester::ref().reportPointPassed(__FILE__, __LINE__)

}}
//namespace
