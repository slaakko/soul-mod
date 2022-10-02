// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.match;

import std.core;

export namespace otava::symbols {

class Symbol;

enum class MatchKind
{
    exact, partial
};

struct ScoreLess
{
    bool operator()(const std::pair<Symbol*, int>& left, const std::pair<Symbol*, int>& right) const;
};

} // namespace otava::symbols
