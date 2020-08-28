#pragma once
#include "./log.h"
#include "./list.h"
#include <stdlib.h>
#include <stdarg.h>

namespace bpp
{
namespace ulib
{
//! String class
class String;

typedef bpp::ulib::List<bpp::ulib::String> StringList;

class String
{
public:
    //! String size policy
    typedef struct _SSizePolicy
    {
        /** Constructor
         *
         * @param size - preferred initial size
         * @param increment - increment step
         */
        _SSizePolicy(size_t size=0, size_t increment=1):mInitialSize(size), mIncrement(increment)
        {}
        size_t mInitialSize;
        size_t mIncrement;
    }SSizePolicy;

    static const size_t npos;
    static const size_t actual;

    String(SSizePolicy sz = SSizePolicy());
    String(const char* pStr, SSizePolicy sz = SSizePolicy());
    String(const String& str);
    String(String& str, SSizePolicy sz = SSizePolicy());

    const char* c_str();
    void clear();
    size_t length() const;
    bool isEmpty() const;

    void toBuf(char* pBuf, size_t BuffSize);

    static String substr (const char* pStr, size_t pos = 0, size_t len = String::npos, SSizePolicy sz = SSizePolicy());
    static size_t find (const char* pStr, const char* pattern, size_t from = 0);
    static size_t find (const char* pStr, String pattern, size_t from = 0);
    static size_t find (const char* pStr, char pattern, size_t from = 0);
    static size_t rfind (const char* pStr, const char* pattern, size_t from = String::npos);
    static size_t rfind (const char* pStr, String pattern, size_t from = String::npos);
    static size_t rfind (const char* pStr, char pattern, size_t from = String::npos);
    static String upperCase(char* pStr);
    static String lowerCase(char* pStr);
    static void upperCaseMe(char* pStr);
    static void lowerCaseMe(char* pStr);
    static String trimmed(char* pStr);
    static StringList split(char* pStr, char delim);

    String substr(size_t pos = 0, size_t len = String::npos, SSizePolicy sz = SSizePolicy()) const;
    String right(size_t len);
    String left(size_t len);

    size_t find(const char* pattern, size_t from = 0);
    size_t find(String pattern, size_t from = 0);
    size_t find(char pattern, size_t from = 0);

    size_t rfind(const char* pattern, size_t from = String::npos);
    size_t rfind(String pattern, size_t from = String::npos);
    size_t rfind(char pattern, size_t from = String::npos);

    String upperCase();
    String& upperCaseMe();
    String lowerCase();
    String &lowerCaseMe();
    String trimmed();
    StringList split(char delim);

    size_t capacity();
    bool crop(size_t newBuffSize);
    void sprintf(const char* fmt, ...);

    String &operator= (const String& str);
    String& operator= (const char* pStr);
    char &operator[] (size_t pos);
    bool operator== (const String& str);
    bool operator== (const char* pStr);
    bool operator!= (const String& str);
    bool operator!= (const char* pStr);
    String &operator+= (const String& str);
    String& operator+= (const char* pStr);
    String &operator+= (const char ch);
    String operator+(const String& str);
    String operator+(const char* pStr);
    String operator+(const char ch);

    ~String();

#ifdef BPP_UNIT_TESTS
    static void outSizes();
#endif
private:
    char*   mpStr;
    size_t  mBuffSize;
    size_t  mIncrement;
    void resize(size_t new_size);
};

}}//namespace

bpp::ulib::CStreamOps& operator<<(bpp::ulib::CStreamOps& out, bpp::ulib::String val);



