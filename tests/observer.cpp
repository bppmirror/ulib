#include "tests.h"

#include "../inc/str.h"
#include "../inc/log.h"
#include "../inc/observer.h"

using namespace bpp;
using namespace bpp::ulib;

class ObserverBase
{
public:
    virtual void onFirstEvent() = 0;
    virtual void onSecondEvent(bool var) =0;
    virtual ~ObserverBase(){}
};

class Observer:public ObserverBase
{
public:
    virtual void onFirstEvent() {call_first_cnt++;}
    virtual void onSecondEvent(bool val){call_secons_cnt++; last_val = val;}

public:
    Observer()
    {
        call_first_cnt =0;
        call_secons_cnt = 0;
        last_val = false;
    }

    int firstCnt()  {return call_first_cnt;}
    int secondCnt() {return call_secons_cnt;}
    bool val() {return last_val;}

private:
    int call_first_cnt;
    int call_secons_cnt;
    bool last_val;
};

class Subject;
static Subject* pSubj = nullptr;

class Subject
{
    HAS_OBSERVERS(Observer)
public:
    void callFirst()
    {
        NOTIFY_OBSERVERS(Subject, onFirstEvent())
    }

    void callSecond(bool val)
    {
        NOTIFY_OBSERVERS(Subject, onSecondEvent(val))
    }

    static void callStaticFirst()
    {
        NOTIFY_OBSERVERS_FOR(pSubj, Subject, onFirstEvent())
    }

    static void callStaticSecond(bool val)
    {
        NOTIFY_OBSERVERS_FOR(pSubj, Subject, onSecondEvent(val))
    }

public:
    Subject()
    {
        pSubj = this;
    }
};

static void Basic()
{
    Observer observer;
    Subject subject;

    subject.callFirst();
    subject.callSecond(true);
    BPP_TEST_CHECK(observer.firstCnt() == 0);
    BPP_TEST_CHECK(observer.secondCnt() == 0);
    BPP_TEST_CHECK(observer.val() == false);

    subject.registerObserver(&observer);

    subject.callFirst();
    BPP_TEST_CHECK(observer.firstCnt() == 1);
    BPP_TEST_CHECK(observer.secondCnt() == 0);
    BPP_TEST_CHECK(observer.val() == false);

    Subject::callStaticFirst();
    BPP_TEST_CHECK(observer.firstCnt() == 2);
    BPP_TEST_CHECK(observer.secondCnt() == 0);
    BPP_TEST_CHECK(observer.val() == false);

    subject.callSecond(true);
    BPP_TEST_CHECK(observer.firstCnt() == 2);
    BPP_TEST_CHECK(observer.secondCnt() == 1);
    BPP_TEST_CHECK(observer.val() == true);

    subject.callStaticSecond(true);
    BPP_TEST_CHECK(observer.firstCnt() == 2);
    BPP_TEST_CHECK(observer.secondCnt() == 2);
    BPP_TEST_CHECK(observer.val() == true);
}

void testObserver()
{
    BPP_RUN_TEST(Basic);
}
