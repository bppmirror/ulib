#pragma once

#include "../inc/asrt.h"
#include "../inc/new.h"
#include "../inc/log.h"
#include "../inc/stdfn/stdfn.h"

namespace bpp
{
namespace ulib
{
typedef struct _SuLibSettings
{
    _SuLibSettings():mASSERTCallback(nullptr), mOutputHandler(nullptr)
    {}
    AssertCallback     mASSERTCallback;  //< Callback for cusom ASSER handler
    Log::OutputHandler mOutputHandler;   //< Callback to custom logger output handler
    bpp::SStdFunc      mStdFn;           //< Pointers to cusom standard functions (like mamcpy)
}SuLibSettings;

bool init(const SuLibSettings* settings);

SuLibSettings* autoSettings();

}
}
