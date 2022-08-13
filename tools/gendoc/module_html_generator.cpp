// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module gendoc.module_html_generator;

import std.filesystem;
import util;
import soul.cpp20.symbols;
import soul.xml.dom;

namespace gendoc {

class ModuleHtmlGenerator : public soul::cpp20::symbols::DefaultVisitor
{
public:
    ModuleHtmlGenerator(const std::string& rootDir_);
    void BeginVisitExports() override;
    void EndVisitExports() override;
    void BeginVisitImports() override;
    void EndVisitImports() override;
    void Visit(soul::cpp20::symbols::Module& module) override;
private:
    std::string rootDir;
    std::string moduleDir;
    soul::xml::Document doc;
    std::string filePath;
    bool visitingExports;
    bool visitingImports;
};

ModuleHtmlGenerator::ModuleHtmlGenerator(const std::string& rootDir_) : rootDir(rootDir_), visitingExports(false), visitingImports(false)
{
}

void ModuleHtmlGenerator::BeginVisitExports()
{
    visitingExports = true;
}

void ModuleHtmlGenerator::EndVisitExports()
{
    visitingExports = false;
}

void ModuleHtmlGenerator::BeginVisitImports()
{
    visitingImports = true;
}

void ModuleHtmlGenerator::EndVisitImports()
{
    visitingImports = false;
}

void ModuleHtmlGenerator::Visit(soul::cpp20::symbols::Module& module)
{
    if (visitingExports)
    {
        int x = 0;
    }
    else if (visitingImports)
    {
        int y = 0;
    }
    else
    {
        moduleDir = util::GetFullPath(util::Path::Combine(util::Path::Combine(rootDir, "module"), module.Name()));
        std::filesystem::create_directories(moduleDir);
        filePath = util::Path::Combine(moduleDir, "index.html");
        DefaultVisitor::Visit(module);
    }
}

void GenerateModuleHtml(const std::string& rootDir, soul::cpp20::symbols::Module* module)
{
    ModuleHtmlGenerator generator(rootDir);
    module->Accept(generator);
}

} // namespace gendoc::module_html_generator
