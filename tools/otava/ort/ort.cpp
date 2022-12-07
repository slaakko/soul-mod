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

uint8_t get_random_byte()
{
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_int_distribution<> dist(0, 255);
    return dist(mt);
}
