#pragma once

#include "./str.h"
#include "./streamops.h"

namespace bpp
{
namespace ulib
{

class StrStream: public CStreamOps
{
public:
    StrStream(bpp::ulib::String* pStr):mpStr(pStr){}
    virtual ~StrStream(){}

protected:
    virtual void doProcessLine(const char* line){(*mpStr)+= line;}

private:
    bpp::ulib::String* mpStr;

};

}}
