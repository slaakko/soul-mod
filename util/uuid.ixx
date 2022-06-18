module;
#include <boost/uuid/uuid.hpp>

export module util.uuid;

import std.core;

export namespace util {

using uuid = boost::uuids::uuid;

void UuidToInts(const uuid& id, uint64_t& int1, uint64_t& int2);
void IntsToUuid(uint64_t int1, uint64_t int2, uuid& id);
void RandomUuid(uuid& id);
std::string ToString(const uuid& uuid);
uuid ParseUuid(const std::string& str);

} // namespace util

export namespace util::uuids {

struct nil_generator 
{
    using result_type = uuid;

    uuid operator()() const 
    {
        uuid u = { {0} };
        return u;
    }
};

} // namespace util::uuid

export namespace util {

inline uuid nil_uuid() 
{
    return util::uuids::nil_generator()();
}

inline uuid random_uuid()
{
    uuid id;
    RandomUuid(id);
    return id;
}

} // namespace util
