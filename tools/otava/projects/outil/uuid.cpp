// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util.uuid;

import util.error;
import util.text.util;

namespace util {

uuid::uuid()
{
    for (auto& byte : data)
    {
        byte = static_cast<std::uint8_t>(0);
    }
}

uuid::uuid(const uuid& that)
{
    for (int i = 0; i < uuid::static_size(); ++i)
    {
        data[i] = that.data[i];
    }
}

uuid::uuid(uuid&& that)
{
    for (int i = 0; i < uuid::static_size(); ++i)
    {
        data[i] = that.data[i];
    }
}

uuid& uuid::operator=(const uuid& that)
{
    for (int i = 0; i < uuid::static_size(); ++i)
    {
        data[i] = that.data[i];
    }
    return *this;
}

uuid& uuid::operator=(uuid&& that)
{
    for (int i = 0; i < uuid::static_size(); ++i)
    {
        data[i] = that.data[i];
    }
    return *this;
}

uuid uuid::random()
{
    uuid rand_uuid;
    for (int i = 0; i < uuid::static_size(); ++i)
    {
        rand_uuid.data[i] = ort_get_random_byte();
    }
    return rand_uuid;
}

bool uuid::is_nil() const
{
    for (const auto& x : data)
    {
        if (x != 0) return false;
    }
    return true;
}

bool operator==(const uuid& left, const uuid& right)
{
    for (int i = 0; i < uuid::static_size(); ++i)
    {
        if (left.data[i] != right.data[i]) return false;
    }
    return true;
}

bool operator<(const uuid& left, const uuid& right)
{
    for (int i = 0; i < uuid::static_size(); ++i)
    {
        if (left.data[i] < right.data[i]) return true;
        if (left.data[i] > right.data[i]) return false;
    }
    return false;
}

void UuidToInts(const uuid& id, std::uint64_t& int1, std::uint64_t& int2)
{
    const std::uint8_t* i = &id.data[0];
    const std::uint64_t* i64 = reinterpret_cast<const std::uint64_t*>(i);
    int1 = *i64++;
    int2 = *i64;
}

void IntsToUuid(std::uint64_t int1, std::uint64_t int2, uuid& id)
{
    std::uint8_t* i = &id.data[0];
    std::uint64_t* i64 = reinterpret_cast<std::uint64_t*>(i);
    *i64++ = int1;
    *i64 = int2;
}

void RandomUuid(uuid& id)
{
    id = uuid::random();
}

std::string ToString(const uuid& id)
{
    std::string s;
    int index = 0;
    for (std::uint8_t x : id)
    {
        s.append(ToLowerNarrow(ToHexString(x)));
        if (index == 3 || index == 5 || index == 7 || index == 9)
        {
            s.append(1, '-');
        }
        ++index;
    }
    return s;
}

std::expected<uuid, int> ParseUuid(const std::string& str)
{
    if (str.length() != 2 * uuid::static_size() + 4)
    {
        std::string msg("wrong number of hex bytes in uuid string '");
        msg.append(str).append("'.").append(std::to_string(uuid::static_size())).append(" hex bytes + 4 hyphens expected.");
        return std::unexpected<int>(AllocateError(msg));
    }
    uuid id;
    int index = 0;
    for (int i = 0; i < uuid::static_size(); ++i)
    {
        std::string hexByteStr = str.substr(index, 2);
        std::uint8_t hexByte = ParseHexByte(hexByteStr);
        id.data[i] = hexByte;
        ++index;
        ++index;
        if (i == 3 || i == 5 || i == 7 || i == 9)
        {
            ++index;
        }
    }
    return std::expected<uuid, int>(id);
}

} // namespace util
