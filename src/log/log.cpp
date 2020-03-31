#include "../../inc/log.h"

#include "../../inc/list.h"

static  bpp::ulib::List<bpp::Log::OutputHandler> handlers;
typedef bpp::ulib::List<bpp::Log::OutputHandler>::iterator handlers_it;


static bpp::Log log_instance;
static bpp::LogOut logouts[]{
    bpp::LogOut(&log_instance, bpp::Log::CRITICAL),
    bpp::LogOut(&log_instance, bpp::Log::ERROR),
    bpp::LogOut(&log_instance, bpp::Log::WARNING),
    bpp::LogOut(&log_instance, bpp::Log::INFO),
    bpp::LogOut(&log_instance, bpp::Log::MESSAGE),
    bpp::LogOut(&log_instance, bpp::Log::DEBUG),
    bpp::LogOut(&log_instance, bpp::Log::TRACE),
    };

#define COLOR_CRITICAL_MSG "\033[31;1;4m"
#define COLOR_CRITICAL  "\033[41;1;4m"
#define COLOR_ERROR_MSG "\033[31m"
#define COLOR_ERROR  "\033[41m"
#define COLOR_WARNING_MSG "\033[33m"
#define COLOR_WARNING  "\033[43m"
#define COLOR_INFO_MSG "\033[32m"
#define COLOR_INFO  "\033[42m"
#define COLOR_DEBUG_MSG "\033[34m"
#define COLOR_DEBUG  "\033[44m"
#define COLOR_TRACE_MSG "\033[35m"
#define COLOR_TRACE  "\033[45m"

#define COLOR_RESET "\033[0m"

static bpp::Log::ELogLevel current_ll = bpp::Log::INFO;

static bpp::Log::SColorEffects ce = bpp::Log::SColorEffects(false, false);


void internal_out( bpp::Log::ELogLevel ll, const char* msg, bool isFlush = false, const char* preffix = nullptr, const char* postfix = nullptr);

bpp::Log::Log()
{
    current_ll = MESSAGE;
}

void bpp::Log::setLogLevel(bpp::Log::ELogLevel ll)
{
    current_ll = ll;
}

bpp::Log::ELogLevel bpp::Log::logLevel()
{
    return current_ll;
}

void bpp::Log::setColorEffects(const bpp::Log::SColorEffects &val)
{
    ce = val;
}

bpp::Log::SColorEffects bpp::Log::colorEffects()
{
    return ce;
}

bpp::LogOut &bpp::Log::operator()(bpp::Log::ELogLevel log_level)
{
    switch (log_level)
    {
        case bpp::Log::CRITICAL:
                (ce.mTypeColorEnabled)?internal_out(log_level, "[!CRITICAL!] ", true, COLOR_CRITICAL, COLOR_RESET)
                                     : internal_out(log_level, "[!CRITICAL!] "); break;
        case bpp::Log::ERROR:
                (ce.mTypeColorEnabled)?internal_out(log_level, "[  ERROR  ] ", true, COLOR_ERROR, COLOR_RESET)
                                     : internal_out(log_level, "[  ERROR  ] "); break;
        case bpp::Log::WARNING:
                (ce.mTypeColorEnabled)?internal_out(log_level, "[ WARNING ] ", false, COLOR_WARNING, COLOR_RESET )
                                     : internal_out(log_level, "[ WARNING ] "); break;
        case bpp::Log::INFO:
                (ce.mTypeColorEnabled)?internal_out(log_level, "[  INFO   ] ", false, COLOR_INFO, COLOR_RESET)
                                     : internal_out(log_level, "[  INFO   ] "); break;
        case bpp::Log::MESSAGE:
                break;
        case bpp::Log::DEBUG:
                (ce.mTypeColorEnabled)?internal_out(log_level, "[  DEBUG  ]", false, COLOR_DEBUG, COLOR_RESET)
                                     : internal_out(log_level, "[  DEBUG  ] "); break;
        case bpp::Log::TRACE:
                (ce.mTypeColorEnabled)?internal_out(log_level, "[  TRACE  ]", false, COLOR_TRACE, COLOR_RESET)
                                     : internal_out(log_level, "[  TRACE  ] "); break;
    }

    return logouts[log_level];
}

void bpp::Log::outLine(bpp::Log::ELogLevel ll, const char *line, bool flush)
{
    if (ll>current_ll)
    {
        return;
    }    

    if (!ce.mTextColorEnabled)
    {
        internal_out(ll, line, flush);
    }
    else
    {
        switch (ll)
        {
            case bpp::Log::CRITICAL: internal_out(ll, line, flush, COLOR_CRITICAL_MSG, COLOR_RESET); break;
            case bpp::Log::ERROR:    internal_out(ll, line, flush, COLOR_ERROR_MSG, COLOR_RESET); break;
            case bpp::Log::WARNING:  internal_out(ll, line, flush, COLOR_WARNING_MSG, COLOR_RESET); break;
            case bpp::Log::INFO:     internal_out(ll, line, flush, COLOR_INFO_MSG, COLOR_RESET); break;
            case bpp::Log::MESSAGE:      internal_out(ll, line, flush); break;
            case bpp::Log::DEBUG:    internal_out(ll, line, flush, COLOR_DEBUG_MSG, COLOR_RESET); break;
            case bpp::Log::TRACE:    internal_out(ll, line, flush, COLOR_TRACE_MSG, COLOR_RESET); break;
        }//switch
    }//else
}

void bpp::Log::outLineEscape(bpp::Log::ELogLevel ll, const char *escape, const char *line, bool flush)
{
    if (ll>current_ll)
    {
        return;
    }
    internal_out(ll, line, flush, escape, COLOR_RESET);
}

bpp::Log &bpp::Log::ref()
{
    return log_instance;
}

bool bpp::Log::addOutputHandler(OutputHandler cb)
{
    if (handlers.has(cb))
    {
        return false;
    }
    handlers.add(cb);
    return true;
}

bool bpp::Log::removeOutputHandler(OutputHandler cb)
{
    handlers_it it = handlers.find(cb);
    if (!it.hasValidValue())
    {
        return false;
    }
    it = handlers.erase(it);
    return true;
}



void internal_out( bpp::Log::ELogLevel ll, const char* msg, bool isFlush, const char* preffix, const char* postfix)
{
    if (!handlers.empty())
    {
        //pHandler(ll, msg, isFlush, preffix, postfix);
        handlers_it it = handlers.begin();
        while (it != handlers.end())
        {
            (*it++)(ll, msg, isFlush, preffix, postfix);
        }
    }
    else
    {
        if (nullptr != preffix)
        {
            printf("%s", preffix);
        }
        printf("%s", msg);
        if (nullptr != postfix)
        {
            printf("%s", postfix);
        }
    }
}
