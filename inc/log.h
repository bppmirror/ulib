/* Copyright (c) 2019-2020 Yuriy Momotyuk
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

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

#ifdef BPP_ENABLE_LOG_SECRET
    #define BPP_LOG_SECRET(val) (val)
#else
    #define BPP_LOG_SECRET(val) "[*#@!]"
#endif

}//namespace
