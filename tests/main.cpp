#include "./tests.h"

#include "list.h"
#include "str.h"
#include "log.h"

using namespace bpp;
using namespace bpp::test;

void start_app()
{
    UnitTester::ref().addComponent(testList, "List container");
    UnitTester::ref().addComponent(testString, "String");
    UnitTester::ref().addComponent(testStrstream, "Strstream");
    UnitTester::ref().addComponent(testObserver, "Observer");

    UnitTester::ref().StartTests();
    MSG<<"\n\n----------------- Unit tests report --------------------\n\n";
    UnitTester::ref().printReport();

    MSG<<"\n\n------------------ Sizes report ------------------------\n\n";
    MSG<<"size_t     : "<<sizeof(size_t)<<"\n";
    ulib::List<size_t>::outSizes();
    ulib::String::outSizes();
}
