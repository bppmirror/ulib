#include "../inc/ulib.h"

#ifdef __unix__
#include "../inc/assert/asrt_pc_stdio.h"
#endif

bool bpp::ulib::init(const bpp::ulib::SuLibSettings *settings)
{
   if (nullptr == settings) return false;

    bpp::setAssertHandler(settings->mASSERTCallback);

    return true;
}

bpp::ulib::SuLibSettings *bpp::ulib::autoSettings()
{
#ifdef __unix__
    static bpp::ulib::SuLibSettings settings;
    settings.mASSERTCallback = ASSERT_PC_STDIO;
    return &settings;
#else
    return nullptr;
#endif
}
