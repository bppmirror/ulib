#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

namespace bpp
{
namespace ulib
{

class CStreamOps
{
protected:
    virtual void doProcessLine(const char* line) = 0;
    virtual void doFlushOutput() {}

public:
    virtual ~CStreamOps(){}

public:
    typedef enum
    {
        ENDL,
        TAB,
        FLUSH
    }SpecialSymbols;

    typedef struct _SHEXInt
    {
        int val;
        _SHEXInt(int _val):val(_val){}
    }HEXInt;

    void flush() {doFlushOutput();}

    CStreamOps& operator<< (char v)
        {
         char out[2] = {v,0};
         doProcessLine (out);
         return *this;
        }
    CStreamOps& operator<< (unsigned char v)
        {
            char out[2] = {static_cast<char>(v),0};
            doProcessLine(out);
            return *this;
        }

    CStreamOps& operator<< (const char* v)
        {
            doProcessLine(v);
            return *this;
        }

    CStreamOps& operator<< (char* v)
        {
            doProcessLine(v);
            return *this;
        }

    CStreamOps& operator<< (const HEXInt& v)
        {
            const size_t buff_size = (sizeof(int)*8+5);
            char out[buff_size];
            snprintf(out, buff_size, "0x%x", v.val);
            doProcessLine(out);
            return *this;
        }

    CStreamOps& operator<< (const SpecialSymbols ss)
        {
            if (FLUSH == ss)
            {
                doFlushOutput();
            }
            else
            {
                static char buf[2]={0,0};
                switch (ss)
                {
                    case ENDL: buf[0]='\n'; break;
                    case TAB:  buf[0]='\t'; break;
                    default: break;
                }
                doProcessLine(buf);
            }
            return *this;
        }
    CStreamOps& operator<< (void* val)
        {
            const size_t buff_size = (sizeof(size_t)*8+3);
            char out[buff_size];
            snprintf(out, buff_size, "%p", val);
            doProcessLine(out);
            return *this;
        }

    CStreamOps& operator<< (bool val)
        {
            if (val)
                doProcessLine("true");
            else
                doProcessLine("false");
            return *this;
        }

#define OPERATOR_FOR_INT(type , printf_format)\
    CStreamOps& operator<< (type v){\
        const size_t buff_size = (sizeof(type)*8+3);\
        char out[buff_size];\
        snprintf(out, buff_size, printf_format, v);\
        doProcessLine(out);\
        return *this;}


    OPERATOR_FOR_INT(int, "%d")
    OPERATOR_FOR_INT(unsigned int, "%u")
    OPERATOR_FOR_INT(long, "%ld")
    OPERATOR_FOR_INT(unsigned long, "%lu")
    OPERATOR_FOR_INT(long long,  "%lld")
    OPERATOR_FOR_INT(unsigned long long, "%llu")

#undef OPERATOR_FOR_INT

};

}}//namespace
