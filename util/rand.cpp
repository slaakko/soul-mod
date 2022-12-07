// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module util.rand;

#ifdef OTAVA

extern "C" uint8_t get_random_byte();

#endif

namespace util {

#ifdef OTAVA

uint8_t get_random_byte()
{
    return ::get_random_byte();
}

#else

uint8_t get_random_byte()
{
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_int_distribution<> dist(0, 255);
    return dist(mt);
}

#endif

} // namespace util
