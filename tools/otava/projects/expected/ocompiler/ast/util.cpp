// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.util;

import util.unicode;
import util.text.util;

namespace otava::ast {

std::string UniversalCharacterName(char32_t c)
{
    std::string s;
    s.append("\\");
    if (static_cast<int>(c) >= 0 && static_cast<int>(c) <= 0xFFFF)
    {
        s.append("u").append(util::ToHexString(static_cast<std::uint16_t>(c)));
    }
    else
    {
        s.append("U").append(util::ToHexString(static_cast<std::uint32_t>(c)));
    }
    return s;
}

std::expected<std::u32string, int> ToUniversalId(const std::u32string& id)
{
    std::u32string s;
    for (char32_t c : id)
    {
        if (static_cast<int>(c) >= 32 && static_cast<int>(c) < 127)
        {
            s.append(1, c);
        }
        else
        {
            auto rv = util::ToUtf32(UniversalCharacterName(c));
            if (!rv) return std::unexpected<int>(rv.error());
            s.append(*rv);
        }
    }
    return std::expected<std::u32string, int>(s);
}

} // namespace otava::ast
