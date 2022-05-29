// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.nonterminal.info;

import std.core;

export namespace soul::spg {

struct NonterminalInfo
{
    NonterminalInfo(const std::string& name_, bool ptrType_);
    std::string name;
    bool ptrType;
    int count;
};

} // namespace soul::spg
