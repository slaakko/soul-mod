// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================
module;
#include <stdio.h>

module ort;

void prints(const char* s)
{
    fwrite(s, strlen(s), 1, stdout);
}