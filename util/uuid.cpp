// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#ifdef _WIN32
#include <rpc.h>
#pragma comment(lib, "rpcrt4.lib")
#endif

module util.uuid;

import util.text.util;

namespace util {

void UuidToInts(const boost::uuids::uuid& id, uint64_t& int1, uint64_t& int2)
{
#ifndef NDEBUG
    static_assert(boost::uuids::uuid::static_size() == 2 * sizeof(uint64_t), "16 bytes expected");
#endif
    const uint8_t* i = id.begin();
    const uint64_t* i64 = reinterpret_cast<const uint64_t*>(i);
    int1 = *i64++;
    int2 = *i64;
}

void IntsToUuid(uint64_t int1, uint64_t int2, boost::uuids::uuid& id)
{
#ifndef NDEBUG
    static_assert(boost::uuids::uuid::static_size() == 2 * sizeof(uint64_t), "16 bytes expected");
#endif
    uint8_t* i = id.begin();
    uint64_t* i64 = reinterpret_cast<uint64_t*>(i);
    *i64++ = int1;
    *i64 = int2;
}

void RandomUuid(boost::uuids::uuid& id)
{
    UUID u;
    UuidCreate(&u);
    id = *static_cast<boost::uuids::uuid*>(static_cast<void*>(&u));
}

std::string ToString(const boost::uuids::uuid& uuid)
{
    std::string s;
    int index = 0;
    for (uint8_t x : uuid)
    {
        s.append(ToLower(ToHexString(x)));
        if (index == 3 || index == 5 || index == 7 || index == 9)
        {
            s.append(1, '-');
        }
        ++index;
    }
    return s;
}

boost::uuids::uuid ParseUuid(const std::string& str)
{
    if (str.length() != 2 * boost::uuids::uuid::static_size() + 4)
    {
        throw std::runtime_error("wrong number of hex bytes in uuid string '" + str + "'." + std::to_string(boost::uuids::uuid::static_size()) + " hex bytes + 4 hyphens expected.");
    }
    boost::uuids::uuid uuid;
    int index = 0;
    for (long i = 0; i < boost::uuids::uuid::static_size(); ++i)
    {
        std::string hexByteStr = str.substr(index, 2);
        uint8_t hexByte = ParseHexByte(hexByteStr);
        uuid.data[i] = hexByte;
        ++index;
        ++index;
        if (i == 3 || i == 5 || i == 7 || i == 9)
        {
            ++index;
        }
    }
    return uuid;
}

} // namespace util
