// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.declaration;

import std.core;
import util.code.formatter;

export namespace otava::assembly {

class Declaration
{
public:
    Declaration(const std::string& name_);
    virtual ~Declaration();
    const std::string& Name() const { return name; }
    virtual void Write(util::CodeFormatter& formatter) = 0;
private:
    std::string name;
};

} // namespace otava::assembly
