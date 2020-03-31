#include "log.h"
#include "list.h"
using namespace bpp;

static void CustomOut1(Log::ELogLevel ll, const char* msg, bool isFlush, const char* preffix, const char* postfix)
{
    printf("~Custom out (no color)~ : %s\n", msg);
    if (isFlush)
    {
        fflush( stdout);
    }
}

static void CustomOut2(Log::ELogLevel ll, const char* msg, bool isFlush, const char* preffix, const char* postfix)
{
    printf("~Custom out (color)~ : %s%s%s\n", preffix, msg, postfix);
    if (isFlush)
    {
        fflush( stdout);
    }
}

static void out_all_types()
{
    LOG(Log::CRITICAL)<<"Example of CRITICAL out"<<LogOut::ENDL;
    LOG(Log::ERROR)<<"Example of ERROR out"<<LogOut::ENDL;
    LOG(Log::WARNING)<<"Example of WARNING out"<<LogOut::ENDL;
    LOG(Log::INFO)<<"Example of INFO out"<<LogOut::ENDL;
    LOG(Log::MESSAGE)<<"Example of MSG out"<<LogOut::ENDL;
    LOG(Log::DEBUG)<<"Example of DEBUG out"<<LogOut::ENDL;
    LOG(Log::TRACE)<<"Example of TRACE out"<<LogOut::ENDL;
}

void start_app(void)
{
    LOG.setLogLevel(Log::TRACE);

    MSG<<"\n\nHello from BPP uLib logger demo!\n\n";

    MSG<<" ====> Colored out ===>"<<LogOut::ENDL;

    MSG<<" Defailt message out: \n\n";
    out_all_types();

    MSG<<"\n Colored labels: \n\n";
    LOG.setColorEffects(Log::SColorEffects(true, false));
    out_all_types();


    MSG<<"\n Colored text: \n\n";
    LOG.setColorEffects(Log::SColorEffects(false, true));
    out_all_types();

    MSG<<"\n All colored: \n\n";
    LOG.setColorEffects(Log::SColorEffects(true, true));
    out_all_types();


    MSG<<"\n\n ====> Integers and pointers out ===>\n";

    int var = 0x1aff;

    MSG<<"This is example of Hex output : "<<var<<"(dec) "<<LogOut::HEXInt(var)<<"(hex)"<<LogOut::ENDL;
    MSG<<"Memory address : "<<&var<<LogOut::ENDL;


    MSG<<"\n\n ====> Complex types out out ===>\n";

    bpp::ulib::List<int> L;
    for (int i=0; i<20; i++)
    {
        L.add(i);
    }
    MSG<<"List of integers: "<<L<<"\n";

    MSG<<"\n\n ====> User output handlers ===>\n";
    LOG.addOutputHandler(CustomOut1);
    LOG.addOutputHandler(CustomOut2);

    LOG(Log::INFO)<<"Info message\n";
    LOG.removeOutputHandler(CustomOut1);
    LOG.removeOutputHandler(CustomOut2);

}
