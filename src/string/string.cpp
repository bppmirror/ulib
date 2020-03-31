#include "../../inc/str.h"
#include "../../inc/new.h"
#include "../../inc/stdfn/stdfn.h"
#include "../../inc/asrt.h"


static char zero_string[2] = {0,0};
const size_t bpp::ulib::String::npos = -1;
const size_t bpp::ulib::String::actual = -1;

bpp::ulib::String::String(bpp::ulib::String::SSizePolicy sz)
{
    mIncrement = sz.mIncrement;
    mpStr = nullptr;
    mBuffSize = 0;
    if (sz.mInitialSize != 0)
    {
        resize(sz.mInitialSize + 1);
    }
}

bpp::ulib::String::String(const char *pStr, bpp::ulib::String::SSizePolicy sz)
{
    size_t input_size= bpp::stdfFn().strlen(pStr);
    size_t size = (input_size > sz.mInitialSize)? input_size : sz.mInitialSize;
    mIncrement = sz.mIncrement;
    mpStr = nullptr;
    mBuffSize = 0;
    if (size != 0)
    {
        resize(size + 1);
        bpp::stdfFn().strncpy(mpStr, pStr, mBuffSize -1);
        mpStr[size] = '\0';
    }
}

bpp::ulib::String::String(const String &str)
{
    size_t input_size= str.length();
    mIncrement = str.mIncrement;
    mpStr = nullptr;
    mBuffSize = 0;
    if (input_size)
    {
        resize(input_size + 1);
        bpp::stdfFn().strncpy(mpStr, str.mpStr, mBuffSize -1);
        mpStr[input_size] = '\0';
    }
}

bpp::ulib::String::String(bpp::ulib::String &str, bpp::ulib::String::SSizePolicy sz)
{
    size_t input_size= str.length();
    size_t size = (input_size > sz.mInitialSize)? input_size : sz.mInitialSize;
    mIncrement = sz.mIncrement;
    mpStr = nullptr;
    mBuffSize = 0;
    if (size != 0)
    {
        resize(size + 1);
        bpp::stdfFn().strncpy(mpStr, str.c_str(), mBuffSize -1);
        mpStr[size] = '\0';
    }
}

const char *bpp::ulib::String::c_str()
{
    return (mpStr)?mpStr:zero_string;
}

void bpp::ulib::String::clear()
{
    if (mpStr)
    {
        mpStr[0] = '\0';
    }
}

size_t bpp::ulib::String::length() const
{
    return (mpStr)?bpp::stdfFn().strlen(mpStr):0;
}

bool bpp::ulib::String::isEmpty() const
{
    if (nullptr == mpStr) return true;
    return mpStr[0] == '\0';
}

void bpp::ulib::String::toBuf(char* pBuf, size_t BuffSize)
{
    size_t my_length = length();
    strncpy(pBuf, c_str(), BuffSize - 1);
    pBuf[ (my_length<(BuffSize - 1))? my_length:BuffSize-1] = '\0';
}

bpp::ulib::String bpp::ulib::String::substr(const char *pStr, size_t pos, size_t len, bpp::ulib::String::SSizePolicy sz)
{
    String out(sz);
    size_t size = bpp::stdfFn().strlen(pStr);


    if (pos>size)
    {
        pos = size;
    }
    if (bpp::ulib::String::npos == len)
    {
        len = size - pos;
    }
    if (!len)
    {
        return out;
    }
    out.resize(len + 1);
    bpp::stdfFn().memcpy(out.mpStr, pStr+pos, len);
    out.mpStr[len+1]='\0';

    return out;
}

size_t bpp::ulib::String::find(const char *pStr, const char *pattern, size_t from)
{
    BPP_ASSERT(pStr)
    BPP_ASSERT(pattern)
    size_t len = bpp::stdfFn().strlen(pStr);
    size_t pattern_len = bpp::stdfFn().strlen(pattern);
    //check length
    if ((from >= len) || ((len - from) < pattern_len))
    {
        return npos;
    }

    for(size_t i=from; i<=(len - pattern_len); i++)
    {
        if (0 == bpp::stdfFn().memcmp(&pStr[i], pattern, pattern_len))
        {
            return i;
        }
    }
    return npos;
}

size_t bpp::ulib::String::find(const char *pStr, bpp::ulib::String pattern, size_t from)
{
    return find(pStr, pattern.c_str(), from);
}

size_t bpp::ulib::String::find(const char *pStr, char pattern, size_t from)
{
    BPP_ASSERT(pStr)
    size_t len = bpp::stdfFn().strlen(pStr);
    if (from >= len)
    {
        return npos;
    }
    for(size_t i=from; i<len; i++)
    {
        if (pStr[i] == pattern)
        {
            return i;
        }
    }//for
    return npos;
}

size_t bpp::ulib::String::rfind(const char *pStr, const char *pattern, size_t from)
{
    BPP_ASSERT(pattern)
    BPP_ASSERT(pStr)
    size_t length = bpp::stdfFn().strlen(pStr);
    from= (from == String::npos)?length:from;
    size_t pattern_length = bpp::stdfFn().strlen(pattern);
    if (from > bpp::stdfFn().strlen(pStr))
    {
        from = bpp::stdfFn().strlen(pStr);
    }

    int start = static_cast<int>(from - pattern_length);
    if (start < 0)
    {
        return String::npos;
    }
    for (int i = start; i>=0; i--)
    {
        if (0 == bpp::stdfFn().memcmp(pStr + i, pattern, pattern_length))
        {
            return static_cast<size_t>(i);
        }
    }
    return String::npos;
}

size_t bpp::ulib::String::rfind(const char *pStr, bpp::ulib::String pattern, size_t from)
{
    return rfind(pStr, pattern.c_str(), from);
}

size_t bpp::ulib::String::rfind(const char *pStr, char pattern, size_t from)
{
    BPP_ASSERT(pStr)
    from= (from == String::npos)?bpp::stdfFn().strlen(pStr):from;
    if (from > bpp::stdfFn().strlen(pStr))
    {
        from = bpp::stdfFn().strlen(pStr);
    }
    for (int i= static_cast<int>(from); i>=0; i--)
    {
        if (pStr[i] == pattern)
            return static_cast<size_t>(i);
    }
    return String::npos;
}

void bpp::ulib::String::upperCaseMe(char *pStr)
{
    BPP_ASSERT(pStr)
    while (*pStr != '\0')
    {
        if ((*pStr>='a') && (*pStr<='z'))
        {
            *pStr -= ('a' - 'A');
        }
        pStr++;
    }
}

void bpp::ulib::String::lowerCaseMe(char *pStr)
{
    BPP_ASSERT(pStr)
    while (*pStr != '\0')
    {
        if ((*pStr>='A') && (*pStr<='Z'))
        {
            *pStr += ('a' - 'A');
        }
        pStr++;
    }
}

bpp::ulib::String bpp::ulib::String::substr(size_t pos, size_t len, bpp::ulib::String::SSizePolicy sz) const
{
    return bpp::ulib::String::substr(mpStr, pos, len, sz);
}

bpp::ulib::String bpp::ulib::String::right(size_t len)
{
    size_t my_len = length();
    if (!my_len) return String();
    if (my_len < len) len = my_len;
    String out(SSizePolicy(len, mIncrement));
    stdfFn().memcpy(out.mpStr, mpStr+(my_len - len), len);
    out.mpStr[len] = '\0';
    return out;
}

bpp::ulib::String bpp::ulib::String::left(size_t len)
{
    size_t my_len = length();
    if (!my_len) return String();
    if (my_len < len) len = my_len;
    String out(SSizePolicy(len, mIncrement));
    stdfFn().memcpy(out.mpStr, mpStr, len);
    out.mpStr[len] = '\0';
    return out;
}

size_t bpp::ulib::String::find(const char *pattern, size_t from)
{
    return find(c_str(), pattern, from);
}

size_t bpp::ulib::String::find(bpp::ulib::String pattern, size_t from)
{
    if (mpStr == nullptr)
    {
        return (pattern.length() && (from ==0))?npos: 0;
    }
    return find(mpStr, pattern, from);
}

size_t bpp::ulib::String::rfind(const char *pattern, size_t from)
{
    return rfind(c_str(), pattern, from);
}

size_t bpp::ulib::String::rfind(bpp::ulib::String pattern, size_t from)
{
    return rfind(c_str(), pattern, from);
}

size_t bpp::ulib::String::rfind(char pattern, size_t from)
{
    return rfind(c_str(), pattern, from);
}

bpp::ulib::String bpp::ulib::String::upperCase()
{
    if (mpStr == nullptr)
    {
        return String();
    }
    String out(SSizePolicy(length(), mIncrement));
    char* dst =out.mpStr;
    char* src = mpStr;
    while (*src != '\0')
    {
        if ((*src>='a') && (*src<='z'))
        {
            *dst = *src - ('a' - 'A');
        }
        else
        {
            *dst = *src;
        }
        dst++; src++;
    }// for all symbols
    *dst='\0';
    return out;
}

bpp::ulib::String &bpp::ulib::String::upperCaseMe()
{
    if (mpStr != nullptr)
        upperCaseMe(mpStr);
    return *this;
}

bpp::ulib::String bpp::ulib::String::lowerCase()
{
    if (mpStr == nullptr)
    {
        return String();
    }
    String out(SSizePolicy(length(), mIncrement));
    char* dst =out.mpStr;
    char* src = mpStr;
    while (*src != '\0')
    {
        if ((*src>='A') && (*src<='Z'))
        {
            *dst = *src + ('a' - 'A');
        }
        else
        {
            *dst = *src;
        }
        dst++; src++;
    }// for all symbols
    *dst='\0';
    return out;
}

bpp::ulib::String &bpp::ulib::String::lowerCaseMe()
{
    if (mpStr != nullptr)
        lowerCaseMe(mpStr);
    return *this;
}

size_t bpp::ulib::String::capacity()
{
    return mBuffSize;
}

bpp::ulib::String &bpp::ulib::String::operator=(const bpp::ulib::String &str)
{
    size_t len = str.length();
    if (!len)
    {
        clear();
        return *this;
    }
    resize(len+1);
    bpp::stdfFn().strncpy(mpStr, str.mpStr, len);
    mpStr[len] = '\0';
    return *this;
}

bpp::ulib::String &bpp::ulib::String::operator=(const char *pStr)
{
    BPP_ASSERT(pStr != nullptr)
    size_t len = bpp::stdfFn().strlen(pStr);
    if (!len)
    {
        clear();
        return *this;
    }
    resize(len+1);
    bpp::stdfFn().strncpy(mpStr, pStr, len);
    mpStr[len] = '\0';
    return *this;
}

char &bpp::ulib::String::operator[](size_t pos)
{
    BPP_ASSERT(pos>=length())
    return mpStr[pos];
}

bool bpp::ulib::String::operator==(const bpp::ulib::String &str)
{
    if ((mpStr == nullptr) || (str.mpStr == nullptr))
    {
        return mpStr == str.mpStr;
    }
    return (stdfFn().strcmp(str.mpStr, mpStr) == 0)?true:false;
}

bool bpp::ulib::String::operator==(const char *pStr)
{
    BPP_ASSERT(pStr)
    if (mpStr == nullptr)
    {
        return *pStr == 0;
    }
    return (stdfFn().strcmp(pStr, mpStr) == 0)?true:false;
}

bool bpp::ulib::String::operator!=(const bpp::ulib::String &str)
{
    return ! (this->operator==(str));
}

bool bpp::ulib::String::operator!=(const char *pStr)
{
    return ! (this->operator==(pStr));
}

bpp::ulib::String &bpp::ulib::String::operator+=(const bpp::ulib::String &str)
{
    size_t len = str.length();
    if (len)
    {
        size_t my_len = length();
        resize(my_len + len + 1);
        bpp::stdfFn().memcpy(&mpStr[my_len], str.mpStr, len);
        mpStr[my_len + len] = '\0';
    }
    return *this;
}

bpp::ulib::String &bpp::ulib::String::operator+=(const char *pStr)
{
    BPP_ASSERT(pStr)
    size_t len = bpp::stdfFn().strlen(pStr);
    if (len)
    {
        size_t my_len = length();
        resize(my_len + len + 1);
        bpp::stdfFn().memcpy(&mpStr[my_len], pStr, len);
        mpStr[my_len + len] = '\0';
    }
    return *this;
}

bpp::ulib::String &bpp::ulib::String::operator+=(const char ch)
{
    size_t my_len = length();
    resize(my_len + 2);
    mpStr[my_len] = ch;
    mpStr[my_len + 1] = '\0';
    return *this;
}

bpp::ulib::String bpp::ulib::String::operator+(const bpp::ulib::String &str)
{
    bpp::ulib::String out(*this);
    out+= str;
    return out;
}

bpp::ulib::String bpp::ulib::String::operator+(const char *pStr)
{
    bpp::ulib::String out(*this);
    out+= pStr;
    return out;
}

bpp::ulib::String bpp::ulib::String::operator+(const char ch)
{
    bpp::ulib::String out(*this);
    out+= ch;
    return out;
}

bpp::ulib::String::~String()
{
    if (mpStr)
    {
        //delete [] mpStr;
        bpp::ulib::IHeapManager* hm = MY_HEAP_MANAGER;
        ((hm)?hm->free(mpStr):free(mpStr));
        mpStr = nullptr;
    }
}

#ifdef BPP_UNIT_TESTS
void bpp::ulib::String::outSizes()
{
    MSG<<"String instance  : "<<sizeof(bpp::ulib::String)<<"\n";
}
#endif

void bpp::ulib::String::resize(size_t new_size)
{
    if (new_size == 0)
    {
        return;
    }
    if (!mpStr)
    {
        bpp::ulib::IHeapManager* hm = MY_HEAP_MANAGER;
        mpStr = static_cast<char*>((hm)?hm->malloc(new_size):malloc(new_size));
        BPP_ASSERT(mpStr)
        mBuffSize = new_size;
    }

    if (mBuffSize<(new_size))
    {
        bpp::ulib::IHeapManager* hm = MY_HEAP_MANAGER;
        mpStr = static_cast<char*>((hm)?hm->realloc(mpStr, new_size + new_size % mIncrement)
                                       :realloc(mpStr, new_size + new_size % mIncrement));
        BPP_ASSERT(mpStr)
        mBuffSize = new_size;
    }
}

bpp::ulib::CStreamOps& operator<<(bpp::ulib::CStreamOps& out, bpp::ulib::String val)
{
    out<<val.c_str();
    return out;
}
