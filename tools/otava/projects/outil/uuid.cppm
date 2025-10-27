// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util.uuid;

import std;

export namespace util {

struct uuid
{
    using value_type = std::uint8_t;
    uuid();
    uuid(const uuid& that);
    uuid& operator=(const uuid& that);
    uuid(uuid&& that);
    uuid& operator=(uuid&& that);
    static uuid random();
    static constexpr int static_size() { return 16; }
    inline const std::uint8_t* begin() const { return &data[0]; }
    inline const std::uint8_t* end() const { return &data[static_size()]; }
    inline std::uint8_t* begin() { return &data[0]; }
    inline std::uint8_t* end() { return &data[static_size()]; }
    bool is_nil() const;
    std::uint8_t data[16];
};

bool operator==(const uuid& left, const uuid& right);
inline bool operator!=(const uuid& left, const uuid& right) { return !(left == right); }
bool operator<(const uuid& left, const uuid& right);

void UuidToInts(const uuid& id, std::uint64_t& int1, std::uint64_t& int2);
void IntsToUuid(std::uint64_t int1, std::uint64_t int2, uuid& id);
void RandomUuid(uuid& id);
std::string ToString(const uuid& uuid);
std::expected<uuid, int> ParseUuid(const std::string& str);
uuid ToUuid(const std::u32string& str);

inline uuid nil_uuid()
{
    return uuid();
}

inline uuid random_uuid()
{
    return uuid::random();
}

void Rotate(uuid& id, int index);
void Xor(uuid& id, const uuid& that);

struct uuid_hash 
{
    size_t operator()(const uuid& id) const;
};

} // namespace util
