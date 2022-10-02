// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.match;

namespace otava::symbols {

bool ScoreLess::operator()(const std::pair<Symbol*, int>& left, const std::pair<Symbol*, int>& right) const
{
    return left.second < right.second;
}

} // namespace otava::symbols
