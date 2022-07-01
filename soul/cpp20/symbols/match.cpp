// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.match;

namespace soul::cpp20::symbols {

bool ScoreLess::operator()(const std::pair<Symbol*, int>& left, const std::pair<Symbol*, int>& right) const
{
    return left.second < right.second;
}

} // namespace soul::cpp20::symbols
