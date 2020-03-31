#pragma once

#include "heapman.h"

// Supress warning on delete operator in new clang
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wimplicit-exception-spec-mismatch"
#endif

#ifndef _GLIBCXX_USE_NOEXCEPT
#define _GLIBCXX_USE_NOEXCEPT noexcept
#endif

void* operator new   (size_t size, bpp::ulib::IHeapManager* hm);
void* operator new[] (size_t size, bpp::ulib::IHeapManager* hm);
void operator delete(void* p) _GLIBCXX_USE_NOEXCEPT;
void operator delete[](void* p) _GLIBCXX_USE_NOEXCEPT;

namespace bpp
{
    bpp::ulib::IHeapManager *heapManager(void* p);
}

#define MY_HEAP_MANAGER (bpp::heapManager(this))
#define DEFAILT_HEAP_MANAGER (bpp::ulib::defaultHM())
#define NO_HEAP_MANAGER

#ifdef __clang__
#pragma clang diagnostic pop
#endif
