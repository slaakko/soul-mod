// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util.boost.uuid;

import std.core;

namespace boost::uuids {

struct uuid
{
    using value_type = uint8_t;
};

} // namespace boost::uuids
