#pragma once

#include <string.h>
#include <stdlib.h>

namespace bpp
{

typedef void*  (*memcpy_fn)( void * destination, const void * source, size_t num );
typedef int    (*memcmp_fn) ( const void * ptr1, const void * ptr2, size_t num );
typedef void*  (*memset_fn) ( void * ptr, int value, size_t num );
typedef char*  (*strncpy_fn)( char * destination, const char * source, size_t num );
typedef size_t (*strlen_fn)(const char* str);
typedef int    (*strcmp_fn) ( const char * str1, const char * str2 );

typedef struct _SStdFunc
{
    _SStdFunc():memcpy(::memcpy),memcmp(::memcmp),memset(::memset), strncpy(::strncpy),strlen(::strlen), strcmp(::strcmp)
    {}
    memcpy_fn  memcpy;
    memcmp_fn  memcmp;
    memset_fn  memset;
    strncpy_fn strncpy;
    strlen_fn  strlen;
    strcmp_fn  strcmp;
}SStdFunc;

const SStdFunc& stdfFn();

void setStdFn(const SStdFunc& stdfn);

}
