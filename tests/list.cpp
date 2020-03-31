#include "./tests.h"
#include "../inc/list.h"
#include "../inc/log.h"

#include <stdlib.h>

using namespace bpp;
using namespace bpp::test;


typedef bpp::ulib::List<int> TestListT;
typedef bpp::ulib::List<int>::iterator TestListItT;
typedef bpp::ulib::List<int>::const_iterator TestListConstItT;

static void Basic()
{
    TestListT list;
    BPP_TEST_CHECK(list.size() == 0);
    list.add(1);
    BPP_TEST_CHECK(list.size() == 1);
    list.clear();
    BPP_TEST_CHECK(list.size() == 0);
}

static void AddBackAddFrontCompare()
{
    TestListT list;
    TestListT list2;

    BPP_TEST_CHECK(list == list2);
    BPP_TEST_CHECK(!(list2 != list));
    BPP_TEST_CHECK(list2 == list);
    BPP_TEST_CHECK(!(list != list2));

    int a[5] = {0,1,2,3,4};
    BPP_TEST_CHECK(list2.addCArray(a, sizeof(a) / sizeof (int)));

    BPP_TEST_CHECK(list2.size() == 5);

    BPP_TEST_CHECK(list.size() == 0);
    list.add(1);
    list.pushBack(2);
    list.pushBack(3);
    list.add(4);
    list.pushFront(0);
    BPP_TEST_CHECK(list.size() == 5);

    BPP_TEST_CHECK(list == list2);
    BPP_TEST_CHECK(!(list2 != list));
    BPP_TEST_CHECK(list2 == list);
    BPP_TEST_CHECK(!(list != list2));

    list.add(12);
    BPP_TEST_CHECK(!(list == list2));
    BPP_TEST_CHECK((list2 != list));
    BPP_TEST_CHECK(!(list2 == list));
    BPP_TEST_CHECK((list != list2));

    list2.clear();
    BPP_TEST_CHECK(!(list == list2));
    BPP_TEST_CHECK((list2 != list));
    BPP_TEST_CHECK(!(list2 == list));
    BPP_TEST_CHECK((list != list2));
}

static void Iterator()
{
    TestListT list;
    TestListItT it;

    it = list.begin();
    BPP_TEST_CHECK(it == list.end());

    int a[20];
    size_t a_size = (sizeof(a)/sizeof (int));
    for (size_t i=0; i<a_size; i++)
    {
        a[i] = rand();
    }

    list.addCArray(a, a_size);

    // Front direction - postfix ++
    size_t i=0;
    it= list.begin();
    while (it != list.end())
    {
        BPP_TEST_CHECK(a[i++] == *(it++));
    }
    BPP_TEST_CHECK(i == a_size);

    it= list.begin();
    i=0;
    while (it != list.end())
    {
        BPP_TEST_CHECK(a[i++] == *(it));
        ++it;
    }
    BPP_TEST_CHECK(i == a_size);


    // Reverse direction - prefix ++
    it = list.end();
    i = a_size;
    while (--it != list.end())
    {
        BPP_TEST_CHECK(a[--i] == *(it));
    }
    // Reverse direction - postfix ++
    it = list.end();
    it--;
    BPP_TEST_CHECK(it != list.end());
    i = a_size;
    while (it != list.end())
    {
        BPP_TEST_CHECK(a[--i] == *(it--));
    }

}

static void ConstIterator()
{
    TestListT list;
    TestListConstItT it;

    it = list.constBegin();
    BPP_TEST_CHECK(it == list.constEnd());

    int a[20];
    size_t a_size = (sizeof(a)/sizeof (int));
    for (size_t i=0; i<a_size; i++)
    {
        a[i] = rand();
    }

    list.addCArray(a, a_size);

    // Front direction - postfix ++
    size_t i=0;
    it= list.constBegin();
    while (it != list.constEnd())
    {
        BPP_TEST_CHECK(a[i++] == *(it++));
    }
    BPP_TEST_CHECK(i == a_size);
    // Front direction - prefix ++
    it= list.constBegin();
    i=0;
    while (it != list.constEnd())
    {
        BPP_TEST_CHECK(a[i++] == *(it));
        ++it;
    }
    // Reverse direction - prefix ++
    it = list.constEnd();
    i = a_size;
    while (--it != list.constEnd())
    {
        BPP_TEST_CHECK(a[--i] == *(it));
    }
    // Reverse direction - postfix ++
    it = list.constEnd();
    it--;
    BPP_TEST_CHECK(it != list.constEnd());
    i = a_size;
    while (it != list.constEnd())
    {
        BPP_TEST_CHECK(a[--i] == *(it--));
    }
}

static void Find()
{
    TestListT list;
    TestListItT it;

    int a[5] = {0,2,3,4,6};
    size_t a_size = (sizeof(a)/sizeof (int));

    it = list.find(99);
    BPP_TEST_CHECK(!it.hasValidValue());
    BPP_TEST_CHECK(it == list.end());
    it = list.findNext(list.begin(), 99);
    BPP_TEST_CHECK(!it.hasValidValue());
    BPP_TEST_CHECK(it == list.end());
    it = list.findPrevious(list.begin(), 99);
    BPP_TEST_CHECK(!it.hasValidValue());
    BPP_TEST_CHECK(it == list.end());

    BPP_TEST_CHECK(list.addCArray(a, a_size));

    it = list.find(99);
    BPP_TEST_CHECK(!it.hasValidValue());
    BPP_TEST_CHECK(it == list.end());

    it = list.find(2);
    BPP_TEST_CHECK(it.hasValidValue());
    BPP_TEST_CHECK(it != list.end());
    if (it.hasValidValue())
    {
        BPP_TEST_CHECK(*it == 2);
    }

    it = list.findNext(it, 6);
    BPP_TEST_CHECK(it.hasValidValue());
    BPP_TEST_CHECK(it != list.end());
    if (it.hasValidValue())
    {
        BPP_TEST_CHECK(*it == 6);
    }

    it = list.findPrevious(it, 2);
    BPP_TEST_CHECK(it.hasValidValue());
    BPP_TEST_CHECK(it != list.end());
    if (it.hasValidValue())
    {
        BPP_TEST_CHECK(*it == 2);
    }
    it = list.end();
    it = list.findPrevious(it, 2);
    BPP_TEST_CHECK(it.hasValidValue());
    BPP_TEST_CHECK(it != list.end());
    if (it.hasValidValue())
    {
        BPP_TEST_CHECK(*it == 2);
    }
}

static void ConstFind()
{
    TestListT list;
    TestListConstItT it;

    int a[5] = {0,2,3,4,6};
    size_t a_size = (sizeof(a)/sizeof (int));

    it = list.constFind(99);
    BPP_TEST_CHECK(!it.hasValidValue());
    BPP_TEST_CHECK(it == list.constEnd());
    it = list.findNext(list.constBegin(), 99);
    BPP_TEST_CHECK(!it.hasValidValue());
    BPP_TEST_CHECK(it == list.constEnd());
    it = list.findPrevious(list.constBegin(), 99);
    BPP_TEST_CHECK(!it.hasValidValue());
    BPP_TEST_CHECK(it == list.constEnd());

    BPP_TEST_CHECK(list.addCArray(a, a_size));

    it = list.constFind(99);
    BPP_TEST_CHECK(!it.hasValidValue());
    BPP_TEST_CHECK(it == list.constEnd());

    it = list.constFind(2);
    BPP_TEST_CHECK(it.hasValidValue());
    BPP_TEST_CHECK(it != list.constEnd());
    if (it.hasValidValue())
    {
        BPP_TEST_CHECK(*it == 2);
    }

    it = list.findNext(it, 6);
    BPP_TEST_CHECK(it.hasValidValue());
    BPP_TEST_CHECK(it != list.constEnd());
    if (it.hasValidValue())
    {
        BPP_TEST_CHECK(*it == 6);
    }

    it = list.findPrevious(it, 2);
    BPP_TEST_CHECK(it.hasValidValue());
    BPP_TEST_CHECK(it != list.constEnd());
    if (it.hasValidValue())
    {
        BPP_TEST_CHECK(*it == 2);
    }
    it = list.constEnd();
    it = list.findPrevious(it, 2);
    BPP_TEST_CHECK(it.hasValidValue());
    BPP_TEST_CHECK(it != list.constEnd());
    if (it.hasValidValue())
    {
        BPP_TEST_CHECK(*it == 2);
    }
}

static void Insert()
{
    TestListT list;
    TestListItT it;

    int a[4] = {2,4,5,6};
    size_t a_size = (sizeof(a)/sizeof (int));

    it = list.begin();
    list.insertAfter(it, 1);

    it= list.begin();
    BPP_TEST_CHECK(list.val(it) == 1);
    BPP_TEST_CHECK(list.size() == 1);

    list.insert(it, 0);
    it= list.begin();
    BPP_TEST_CHECK(list.val(it) == 0);

    list.addCArray(a, a_size);

    it = list.find(2);
    BPP_TEST_CHECK(it.hasValidValue());
    BPP_TEST_CHECK(list.val(it) == 2);
    list.insertAfter(it, 3);

    it=list.end();
    list.insert(it, 7);
    it=list.end();
    BPP_TEST_CHECK(false == list.insertAfter(it, 8));

    it = list.begin();
    for(int i=0; i<=7;i++)
    {
        BPP_TEST_CHECK(*it++ == i);
    }
}

static void Erase()
{
    int a[] = {0, 1, 2, 3, 4, 5, 6};
    size_t a_size = (sizeof(a)/sizeof (int));
    TestListT list;
    TestListItT it;

    list.addCArray(a, a_size);
    it =list.begin();
    it=list.erase(it);
    BPP_TEST_CHECK(*it==1);
    BPP_TEST_CHECK(list.size() == (a_size - 1));

    it = --list.end();
    it=list.erase(it);
    BPP_TEST_CHECK(it == list.end());
    BPP_TEST_CHECK(list.size() == (a_size - 2));

    it = list.find(4);
    BPP_TEST_CHECK(*it == 4);
    it = list.erase(it);
    BPP_TEST_CHECK(*it==5);
    BPP_TEST_CHECK(list.size() == (a_size - 3));

    it = list.begin();
    for(size_t i=1; i<(a_size-1); i++)
    {
        if (i==4) continue;
        BPP_TEST_CHECK(*it++ == a[i]);
    }
}

void testList()
{
    BPP_RUN_TEST(Basic);
    BPP_RUN_TEST(AddBackAddFrontCompare);
    BPP_RUN_TESTS(Iterator, 5);
    BPP_RUN_TESTS(ConstIterator, 5);
    BPP_RUN_TEST(Find);
    BPP_RUN_TEST(ConstFind);
    BPP_RUN_TEST(Insert);
    BPP_RUN_TEST(Erase);
}

