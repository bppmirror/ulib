#pragma once

#include "./assert.h"

#include <stdio.h>
#include <stdlib.h>

namespace bpp
{
static void ASSERT_HALT_STDIO(char* formatted_msg, const char* file, int line, const char* msg)
{
    (void)file;
    (void)line;
    (void)msg;
    printf("%s", formatted_msg);
    static volatile bool flag = true;
    while(flag);
};
} //namespace
