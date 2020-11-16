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
