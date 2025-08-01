// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.ast.common;

import std;

export namespace soul::ast::common {

std::string ToNamespaceName(const std::string& qualifiedId);

class ExportModule
{
public:
    ExportModule(const std::string& moduleName_);
    inline const std::string& ModuleName() const { return moduleName; }
private:
    std::string moduleName;
};

enum class ImportPrefix
{
    interfacePrefix, implementationPrefix
};

class Import
{
public:
    Import(const std::string& moduleName_, ImportPrefix prefix_);
    inline const std::string& ModuleName() const { return moduleName; }
    inline ImportPrefix Prefix() const { return prefix; }
private:
    std::string moduleName;
    ImportPrefix prefix;
};

} // namespace soul::ast::common
