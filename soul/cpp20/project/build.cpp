// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.project.build;

import util;
import soul.cpp20.project.parser;
import soul.cpp20.lexer;
import cpp20.parser.spg.rules;
import soul.cpp20.parser.module_dependency;
import soul.cpp20.ast;
import soul.cpp20.symbols;
import soul.cpp20.parser.translation.unit;

namespace soul::cpp20::project::build {

void Visit(int file, soul::cpp20::proj::ast::Project* project, std::vector<int>& topologicalOrder, std::set<int>& visited)
{
    soul::cpp20::symbols::Module* module = project->GetModule(file);
    for (soul::cpp20::symbols::Module* dependsOnModule : module->DependsOnModules())
    {
        if (dependsOnModule->File() != -1)
        {
            if (visited.find(dependsOnModule->File()) == visited.cend())
            {
                visited.insert(dependsOnModule->File());
                Visit(dependsOnModule->File(), project, topologicalOrder, visited);
            }
        }
    }
    visited.insert(file);
    topologicalOrder.push_back(file);
}

std::vector<int> MakeTopologicalOrder(const std::vector<int>& files, soul::cpp20::proj::ast::Project* project)
{
    std::set<int> visited;
    std::vector<int> topologicalOrder;
    for (int file : files)
    {
        if (visited.find(file) == visited.cend())
        {
            Visit(file, project, topologicalOrder, visited);
        }
    }
    return topologicalOrder;
}

class ModuleDependencyVisitor : public soul::cpp20::ast::DefaultVisitor
{
public:
    ModuleDependencyVisitor(int file_, soul::cpp20::proj::ast::Project* project_, const std::string& fileName_);
    soul::cpp20::symbols::Module* GetModule() { return module.release(); }
    void Visit(soul::cpp20::ast::ModuleDeclarationNode& node);
    void Visit(soul::cpp20::ast::TranslationUnitNode& node);
    void Visit(soul::cpp20::ast::ExportDeclarationNode& node);
    void Visit(soul::cpp20::ast::ImportDeclarationNode& node);
    void Visit(soul::cpp20::ast::ModuleNameNode& node);
private:
    soul::cpp20::proj::ast::Project* project;
    std::string fileName;
    int file;
    bool exp;
    bool expimp;
    bool imp;
    std::unique_ptr<soul::cpp20::symbols::Module> module;
};

ModuleDependencyVisitor::ModuleDependencyVisitor(int file_, soul::cpp20::proj::ast::Project* project_, const std::string& fileName_) : 
    exp(false), 
    expimp(false), 
    imp(false), 
    file(file_), 
    project(project_),
    fileName(fileName_)
{
}

void ModuleDependencyVisitor::Visit(soul::cpp20::ast::ModuleDeclarationNode& node)
{
    if (node.Export())
    {
        exp = true;
        node.ModuleName()->Accept(*this);
        exp = false;
    }
}

void ModuleDependencyVisitor::Visit(soul::cpp20::ast::TranslationUnitNode& node)
{
    module.reset(new soul::cpp20::symbols::Module(project->Name() + "." + fileName));
    module->Init();
    module->SetFile(file);
    if (node.Unit())
    {
        node.Unit()->Accept(*this);
    }
}

void ModuleDependencyVisitor::Visit(soul::cpp20::ast::ExportDeclarationNode& node)
{
    if (node.Subject() && node.Subject()->IsImportDeclarationNode())
    {
        expimp = true;
        node.Subject()->Accept(*this);
        expimp = false;
    }
}

void ModuleDependencyVisitor::Visit(soul::cpp20::ast::ImportDeclarationNode& node)
{
    if (!expimp)
    {
        imp = true;
    }
    node.Subject()->Accept(*this);
    imp = false;
}

void ModuleDependencyVisitor::Visit(soul::cpp20::ast::ModuleNameNode& node)
{
    if (exp)
    { 
        module.reset(new soul::cpp20::symbols::Module(util::ToUtf8(node.Str())));
        module->Init();
        module->SetFile(file);
    }
    else if (expimp && module)
    {
        module->AddExportModuleName(util::ToUtf8(node.Str()));
    }
    else if (imp && module)
    {
        module->AddImportModuleName(util::ToUtf8(node.Str()));
    }
}

void ScanDependencies(soul::cpp20::proj::ast::Project* project, int file)
{
    const std::string& filePath = project->GetFileMap().GetFilePath(file);
    std::string fileName = util::Path::GetFileNameWithoutExtension(filePath);
    std::string fileContent = util::ReadFile(filePath);
    std::u32string content = util::ToUtf32(fileContent);
    auto lexer = soul::cpp20::lexer::MakeLexer(content.c_str(), content.c_str() + content.length(), filePath);
    lexer.SetFile(file);
    lexer.SetRuleNameMapPtr(::cpp20::parser::spg::rules::GetRuleNameMapPtr());
    soul::cpp20::symbols::Context context;
    context.SetLexer(&lexer);
    std::unique_ptr<soul::cpp20::ast::Node> node = soul::cpp20::parser::module_dependency::ModuleDependencyParser<decltype(lexer)>::Parse(lexer, &context);
    project->GetFileMap().AddFileContent(file, std::move(content), lexer.GetLineStartIndeces());
    ModuleDependencyVisitor visitor(file, project, fileName);
    node->Accept(visitor);
    project->SetModule(file, visitor.GetModule());
}

void Build(soul::cpp20::symbols::ModuleMapper& moduleMapper, soul::cpp20::proj::ast::Project* project, BuildFlags flags)
{
    soul::cpp20::ast::NodeIdFactory nodeIdFactory;
    soul::cpp20::ast::SetNodeIdFactory(&nodeIdFactory);
    soul::cpp20::symbols::Symbols symbols;
    project->InitModules();
    if (!project->Scanned())
    {
        project->SetScanned();
        for (int file : project->InterfaceFiles())
        {
            ScanDependencies(project, file);
        }
    }
    project->LoadModules(&nodeIdFactory, moduleMapper, &symbols);
    std::vector<int> topologicalOrder = MakeTopologicalOrder(project->InterfaceFiles(), project);
    for (int file : topologicalOrder)
    {
        const std::string& filePath = project->GetFileMap().GetFilePath(file);
        const auto& fileContent = project->GetFileMap().GetFileContent(file).first;
        auto lexer = soul::cpp20::lexer::MakeLexer(fileContent.c_str(), fileContent.c_str() + fileContent.length(), filePath);
        lexer.SetFile(file);
        lexer.SetRuleNameMapPtr(::cpp20::parser::spg::rules::GetRuleNameMapPtr());
        soul::cpp20::symbols::Context context;
        soul::cpp20::symbols::Module* module = project->GetModule(file);
        soul::cpp20::symbols::SetCurrentModule(module);
        module->Import(moduleMapper);
        context.SetLexer(&lexer);
        context.SetSymbolTable(module->GetSymbolTable());
        std::unique_ptr<soul::cpp20::ast::Node> node = soul::cpp20::parser::translation::unit::TranslationUnitParser<decltype(lexer)>::Parse(lexer, &context);
        module->Files().AddFile(new soul::cpp20::ast::File(util::Path::GetFileName(filePath), node.release()));
        module->Write(project->Root());
        moduleMapper.AddModule(project->ReleaseModule(file));
        if ((flags & BuildFlags::verbose) != BuildFlags::none)
        {
            std::cout << filePath << " -> " << soul::cpp20::symbols::MakeModuleFilePath(project->Root(), module->Name()) << std::endl;
        }
    }
}

soul::cpp20::symbols::Module* GetModule(soul::cpp20::symbols::ModuleMapper& moduleMapper, const std::string& moduleName)
{
    return moduleMapper.GetModule(moduleName);
}

} // namespace soul::cpp20::project::build
