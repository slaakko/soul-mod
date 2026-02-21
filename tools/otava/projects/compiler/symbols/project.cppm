// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.project;

import std;

export namespace otava::symbols {

class Project
{
public:
    virtual bool HasDefine(const std::string& symbol) const noexcept = 0;
};

} // otava::symbols
