#include "../../inc/test/test.h"
#include "../../inc/asrt.h"
#include "../../inc/stdfn/stdfn.h"
#include "../../inc/log.h"
#include <stdlib.h>

using namespace bpp;
using namespace bpp::test;

/*
 * Don't use uLib types to be able to test those types
 * Also we don't use any C++ memory allocations and IMemoryManagers
 * Just flat C-style code
 */

const char* const COLOR_FAIL = "\033[31m";
const char* const COLOR_PASS = "\033[32m";

typedef struct _STest
{
    _STest():mName(nullptr), mReps(0), mChecks(0), mFailures(0), mAsserts(0), mpNext(nullptr)
    {}
    char* mName;
    int   mReps;
    int   mChecks;
    int   mFailures;
    int   mAsserts;

    _STest* mpNext;

}STest;
typedef struct _STestComponent
{
    _STestComponent():mName(nullptr), mTotoalTests(0), mFailedTests(0), mpTests(nullptr), mpNext(nullptr)
    {}

    char* mName;
    int   mTotoalTests;
    int   mFailedTests;
    TestFunction mFn;
    _STest* mpTests;
    _STestComponent* mpNext;

}STestComponent;

static STestComponent* root = nullptr;
static STestComponent* last = nullptr;
static STestComponent* current_tp = nullptr;
static STest* current_test = nullptr;
//static STest* current_test_top = nullptr;

bool UnitTester::addComponent(TestFunction fn, const char *name)
{
    STestComponent* ptp = static_cast<STestComponent*>(malloc(sizeof(STestComponent)));
    BPP_ASSERT(ptp)
    *ptp = STestComponent();
    ptp->mFn = fn;
    if (name)
    {
        size_t string_size =bpp::stdfFn().strlen(name);
        ptp->mName = static_cast<char*>(malloc(string_size + 1));
        BPP_ASSERT(ptp->mName)
        bpp::stdfFn().strncpy(ptp->mName, name, string_size);
        ptp->mName[string_size] = '\0';
    }
    if (nullptr == last)
    {
        root = ptp;
        last = ptp;
    }
    else
    {
        last->mpNext = ptp;
        last = ptp;
    }
    return true;
}

void UnitTester::runTest(TestFunction fn, const char *name, int reps)
{
    STest* pt = static_cast<STest*>(malloc(sizeof(STest)));
    BPP_ASSERT(pt)
    *pt = STest();
    if (name)
    {
        size_t string_size =bpp::stdfFn().strlen(name);
        pt->mName = static_cast<char*>(malloc(string_size + 1));
        BPP_ASSERT(pt->mName)
        bpp::stdfFn().strncpy(pt->mName, name, string_size);
        pt->mName[string_size] = '\0';
    }
    pt->mReps = reps;

    MSG<<"---> Running test [";
    if (pt->mName) MSG<<pt->mName;
    else MSG<<"~UNKNOWN~";
    MSG<<"]...\n"<<bpp::LogOut::FLUSH;

    if (current_test != nullptr)
    {
        current_test->mpNext = pt;
    }
    else
    {
        BPP_ASSERT(current_tp)
        current_tp->mpTests = pt;
    }
    current_test = pt;

    for (int i=0; i<reps; i++)
    {
        fn();
    }

    if (current_tp)
    {
        current_tp->mTotoalTests++;
    }

    if (current_test->mFailures > 0)
    {
        LOG.outLineEscape(bpp::Log::MESSAGE, COLOR_FAIL, "<--- [!FAILED]", true);
        if (current_tp)
        {
            current_tp->mFailedTests++;
        }
    }
    else
    {
        LOG.outLineEscape(bpp::Log::MESSAGE, COLOR_PASS, "<--- [PASSED]", true);
    }

    MSG<<" ( Passes: "<<current_test->mReps<<" ";
    MSG<<" Checks: "<<current_test->mChecks<<" ";
    MSG<<" Failures: "<<current_test->mFailures<<" )\n\n";
    MSG<<bpp::LogOut::FLUSH;

    current_test = nullptr;
}

bool UnitTester::StartTests()
{
    STestComponent* ptp = root;
    while (ptp != nullptr)
    {
        current_tp = ptp;
        MSG<<">>>>>>> Testing [";
        if (ptp->mName) MSG<<ptp->mName;
        else MSG<<"~UNKNOWN~";
        MSG<<"]\n"<<bpp::LogOut::FLUSH;
        current_tp->mFn();
        //MSG<<"<<<<<<< DONE\n\n"<<
        if (current_tp->mFailedTests > 0)
        {
            LOG.outLineEscape(bpp::Log::MESSAGE, COLOR_FAIL, "<<<<<<< DONE FAILED", true);
        }
        else
        {
            LOG.outLineEscape(bpp::Log::MESSAGE, COLOR_PASS, "<<<<<<< DONE PASSED", true);
        }

        MSG<<" ( Total: "<<current_tp->mTotoalTests<<" Failed: "<<current_tp->mFailedTests<<")\n\n";
        MSG<<bpp::LogOut::FLUSH;

        ptp = ptp->mpNext;
    }
    return true;
}

bool UnitTester::printReport()
{
    STestComponent* ptp = root;
    static const char* const caption = " COMPONENT ";
    static const char* const unnamed = " ~Unnamed~ ";
    static char out[64];
    size_t name_length = stdfFn().strlen(caption);
    size_t caption_length = name_length;

    //Calculate maximal component name length to make proper alignment
    while (ptp != nullptr)
    {
        size_t len = 0;
        if (ptp->mName == nullptr)
        {
            len= stdfFn().strlen(unnamed);
        }
        else
        {
            len = stdfFn().strlen(ptp->mName);
        }
        if (len>name_length)
        {
            name_length= len;
        }
        ptp = ptp->mpNext;
    }

    //Print caption
    if (name_length>=sizeof (out)) name_length = sizeof (out)-1;
    stdfFn().strncpy(out, caption, sizeof (out));
    size_t i=0;
    for(i= caption_length; i<name_length; i++)
    {
        out[i]=' ';
    }
    out[i] = '\0';

    MSG<<"===============================================================================\n";
    MSG<<out<<" \tTotal\tPassed\tFailed\n";
    MSG<<"===============================================================================\n";

    ptp = root;
    while (ptp != nullptr)
    {
        //align name
        size_t len;
        if (ptp->mName == nullptr)
        {
            len= stdfFn().strlen(unnamed);
            stdfFn().strncpy(out, unnamed, sizeof (out));
        }
        else
        {
            len = stdfFn().strlen(ptp->mName);
            stdfFn().strncpy(out, ptp->mName, sizeof (out));
        }
        for(i= len; i<name_length; i++)
        {
            out[i]=' ';
        }
        out[i] = '\0';
        if (ptp->mFailedTests > 0)
        {
            LOG.outLineEscape(bpp::Log::MESSAGE, COLOR_FAIL, out);
        }
        else
        {
            LOG.outLineEscape(bpp::Log::MESSAGE, COLOR_PASS, out);
        }

        MSG<<" \t"<<ptp->mTotoalTests<<"\t"<<(ptp->mTotoalTests - ptp->mFailedTests)<<"\t"<<ptp->mFailedTests<<"\n";

        ptp = ptp->mpNext;
    }


    return true;
}

void UnitTester::reportCondition(const char *file, int line, bool success, const char *msg)
{
    if (current_test)
    {
        current_test->mChecks++;
    }
    if (!success)
    {
        if (current_test)
        {
            current_test->mFailures++;
        }

        LOG.outLineEscape(bpp::Log::MESSAGE, COLOR_FAIL, "[FAIL] ");
        MSG<<" at "<<file<<":"<<line;
        if (msg != nullptr)
        {
            MSG<<"("<<msg<<")";
        }
        MSG<<"\n"<<bpp::LogOut::FLUSH;
    }
}

void UnitTester::reset()
{
    STestComponent* ptp = root;
    STest*      pt = nullptr;
    while (ptp != nullptr)
    {
        pt = ptp->mpTests;
        while (pt)
        {
            if (pt->mName) free (pt->mName);
            STest* next = pt->mpNext;
            free(pt);
            pt = next;
        }
        if (ptp->mName) free (ptp->mName);
        STestComponent* next = ptp->mpNext;
        free(ptp);
        ptp = next;
    }
}

bpp::test::UnitTester &bpp::test::UnitTester::ref()
{
    static UnitTester* pMe = nullptr;
    if (nullptr == pMe)
    {
        pMe = new UnitTester;
        BPP_ASSERT(pMe)
    }
    return *pMe;
}

bpp::test::UnitTester::UnitTester()
{

}
