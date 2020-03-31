#pragma once

#include "./assert.h"

#include <stdio.h>
#include <stdlib.h>

namespace bpp
{
static void ASSERT_PC_STDIO(char* formatted_msg, const char* file, int line, const char* msg)
{
    (void)file;
    (void)line;
    (void)msg;
    printf("%s", formatted_msg);
    exit(1);
};
} //namespace
