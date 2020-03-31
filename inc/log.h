#pragma once

#include "./streamops.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

namespace bpp
{

class LogOut;

////////////// User output handler ////////////////////


class Log
{
public:

    //! Logging levels
    typedef enum
    {
        CRITICAL,  ///< Critical message
        ERROR,     ///< Error message
        WARNING,   ///< Warning message
        INFO,      ///< Information
        MESSAGE,   ///< Just message (will be out without any preffixes)
        DEBUG,     ///< Debug message
        TRACE      ///< Trace message
    }ELogLevel;

    //! Color effects settings
    typedef struct _SColorEffects
    {
        /** Constructor
         *
         * @param isTypeCE - if true - colored type preffix is enabled
         * @param isTextCE - if true - colored text is enabled
         */
        _SColorEffects(bool isTypeCE =false, bool isTextCE = false): mTypeColorEnabled(isTypeCE), mTextColorEnabled(isTextCE){}
        bool mTypeColorEnabled; ///< if true - colored type preffix is enabled
        bool mTextColorEnabled; ///< if true - colored text is enabled
    }SColorEffects;

    /** Custom output handler
     *
     * @param ll - message log level
     * @param msg - message
     * @param isFlush - if true- output buffer should be flushed
     * @param preffix - used for message colour escape sequence. May be ignored
     * @param postfix - used for reset color settings escape sequence. May be ignored
     */
    typedef void (*OutputHandler)(Log::ELogLevel ll, const char* msg, bool isFlush, const char* preffix, const char* postfix);

    Log();

    /** Set current logging level
     *
     * @param ll - new logging level
     */
    void setLogLevel(ELogLevel ll);

    //! Get current logging level
    ELogLevel logLevel();
    void setColorEffects(const SColorEffects& val);
    SColorEffects colorEffects();

    LogOut &operator()(ELogLevel log_level);
    void outLine(ELogLevel ll, const char* line, bool flush = false);
    void outLineEscape(ELogLevel ll, const char* escape, const char* line, bool flush = false);

    static Log& ref();

    bool addOutputHandler(OutputHandler cb);

    bool removeOutputHandler(OutputHandler cb);
};

#define LOG  bpp::Log::ref()
#define MSG  bpp::Log::ref()(bpp::Log::MESSAGE)




class LogOut:public bpp::ulib::CStreamOps
{
public:
    LogOut(Log* Logger, Log::ELogLevel ll):mpLogger(Logger),mpLogLevel(ll){}

protected:
    virtual void doProcessLine(const char* line) { mpLogger->outLine(mpLogLevel, line);}
    virtual void doFlushOutput() {mpLogger->outLine(mpLogLevel, "", true);}

private:
    Log* mpLogger;
    Log::ELogLevel mpLogLevel;
};



}//namespace
