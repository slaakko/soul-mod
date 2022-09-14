// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.project.build;

import util;
import soul.lexer;
import soul.cpp20.project.parser;
import soul.cpp20.lexer;
import soul.cpp20.pp;
import soul.cpp20.pp.state;
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
        if (project->GetModule(dependsOnModule->Name()))
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
    ModuleDependencyVisitor(int file_, soul::cpp20::proj::ast::Project* project_, const std::string& fileName_, bool implementationUnit_);
    soul::cpp20::symbols::Module* GetModule() { return module.release(); }
    const std::string& InterfaceUnitName() const { return interfaceUnitName; }
    void Visit(soul::cpp20::ast::ModuleDeclarationNode& node);
    void Visit(soul::cpp20::ast::TranslationUnitNode& node);
    void Visit(soul::cpp20::ast::ExportDeclarationNode& node);
    void Visit(soul::cpp20::ast::ImportDeclarationNode& node);
    void Visit(soul::cpp20::ast::ModuleNameNode& node);
private:
    soul::cpp20::proj::ast::Project* project;
    std::string fileName;
    int file;
    bool implementationUnit;
    bool exp;
    bool expimp;
    bool imp;
    bool implementation;
    std::string interfaceUnitName;
    std::unique_ptr<soul::cpp20::symbols::Module> module;
};

ModuleDependencyVisitor::ModuleDependencyVisitor(int file_, soul::cpp20::proj::ast::Project* project_, const std::string& fileName_, bool implementationUnit_) :
    fileName(fileName_),
    file(file_),
    implementationUnit(implementationUnit_),
    exp(false),
    expimp(false), 
    imp(false), 
    implementation(false),
    project(project_)
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
    else if (implementationUnit)
    {
        implementation = true;
        node.ModuleName()->Accept(*this);
        implementation = false;
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
        std::string moduleName = util::ToUtf8(node.Str());
        module.reset(new soul::cpp20::symbols::Module(moduleName));
        if (moduleName != "std.type.fundamental")
        {
            module->AddImportModuleName("std.type.fundamental");
        }
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
    else if (implementation)
    {
        interfaceUnitName = util::ToUtf8(node.Str());
        module.reset(new soul::cpp20::symbols::Module(util::ToUtf8(node.Str()) + "." + fileName + ".cpp"));
        module->AddImportModuleName("std.type.fundamental");
        module->AddImportModuleName(util::ToUtf8(node.Str()));
    }
}

void ScanDependencies(soul::cpp20::proj::ast::Project* project, int file, bool implementationUnit, std::string& interfaceUnitName)
{
    std::string filePath = project->GetFileMap().GetFilePath(file);
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
    ModuleDependencyVisitor visitor(file, project, fileName, implementationUnit);
    node->Accept(visitor);
    project->SetModule(file, visitor.GetModule());
    interfaceUnitName = visitor.InterfaceUnitName();
}

void BuildSequentally(soul::cpp20::symbols::ModuleMapper& moduleMapper, soul::cpp20::proj::ast::Project* project, BuildFlags flags)
{
    if ((flags & BuildFlags::verbose) != BuildFlags::none)
    {
        std::cout << "> building project '" << project->Name() << "'..." << std::endl;
    }
    project->AddRoots(moduleMapper);
    soul::cpp20::symbols::Module projectModule(project->Name() + ".#project");
    soul::cpp20::ast::NodeIdFactory nodeIdFactory;
    soul::cpp20::ast::SetNodeIdFactory(&nodeIdFactory);
    soul::cpp20::symbols::Symbols symbols;
    std::map<std::string, std::vector<std::string>> implementationNameMap;
    project->InitModules();
    if (!project->Scanned())
    {
        project->SetScanned();
        for (int file : project->InterfaceFiles())
        {
            std::string interfaceUnitName;
            ScanDependencies(project, file, false, interfaceUnitName);
        }
        for (int file : project->SourceFiles())
        {
            std::string interfaceUnitName;
            ScanDependencies(project, file, true, interfaceUnitName);
            soul::cpp20::symbols::Module* implementationModule = project->GetModule(file);
            implementationNameMap[interfaceUnitName].push_back(implementationModule->Name());
        }
    }
    project->LoadModules(&nodeIdFactory, moduleMapper, &symbols);
    std::vector<int> topologicalOrder = MakeTopologicalOrder(project->InterfaceFiles(), project);
    for (int file : topologicalOrder)
    {
        const std::string& filePath = project->GetFileMap().GetFilePath(file);
        const auto& fileContent = project->GetFileMap().GetFileContent(file).first;
        auto lexer = soul::cpp20::lexer::MakeLexer(fileContent.c_str(), fileContent.c_str() + fileContent.length(), filePath);
        lexer.SetPPHook(soul::cpp20::pp::PreprocessPPLine);
        soul::cpp20::pp::state::State* state = soul::cpp20::pp::state::LexerStateMap::Instance().GetState(&lexer);
        for (const auto& define : project->Defines())
        {
            state->Define(define.symbol, define.value);
        }
        lexer.SetFile(file);
        std::unique_ptr<std::ofstream> logFile;
        std::unique_ptr<soul::lexer::XmlParsingLog> log;
        if ((flags & BuildFlags::debugParse) != BuildFlags::none)
        {
            logFile.reset(new std::ofstream("parse.log"));
            log.reset(new soul::lexer::XmlParsingLog(*logFile));
            lexer.SetLog(log.get());
        }
        lexer.SetRuleNameMapPtr(::cpp20::parser::spg::rules::GetRuleNameMapPtr());
        soul::cpp20::symbols::Context context;
        soul::cpp20::symbols::Module* module = project->GetModule(file);
        module->SetFilePath(filePath);
        soul::cpp20::symbols::SetCurrentModule(module);
        module->Import(moduleMapper);
        context.SetLexer(&lexer);
        context.SetSymbolTable(module->GetSymbolTable());
        std::unique_ptr<soul::cpp20::ast::Node> node = soul::cpp20::parser::translation::unit::TranslationUnitParser<decltype(lexer)>::Parse(lexer, &context);
        if ((flags & BuildFlags::xml) != BuildFlags::none)
        {
            std::string xmlFilePath = filePath + ".ast.xml";
            soul::cpp20::ast::WriteXml(node.get(), xmlFilePath);
        }
        module->SetFile(new soul::cpp20::ast::File(util::Path::GetFileName(filePath), node.release()));
        module->SetImplementationUnitNames(implementationNameMap[module->Name()]);
        projectModule.Import(module, moduleMapper);
        module->Write(project->Root());
        moduleMapper.AddModule(project->ReleaseModule(file));
        if ((flags & BuildFlags::verbose) != BuildFlags::none)
        {
            std::cout << filePath << " -> " << soul::cpp20::symbols::MakeModuleFilePath(project->Root(), module->Name()) << std::endl;
        }
    }
    for (int file : project->SourceFiles())
    {
        std::string interfaceUnitName;
        ScanDependencies(project, file, true, interfaceUnitName);
        const std::string& filePath = project->GetFileMap().GetFilePath(file);
        const auto& fileContent = project->GetFileMap().GetFileContent(file).first;
        auto lexer = soul::cpp20::lexer::MakeLexer(fileContent.c_str(), fileContent.c_str() + fileContent.length(), filePath);
        lexer.SetPPHook(soul::cpp20::pp::PreprocessPPLine);
        lexer.SetFile(file);
        lexer.SetRuleNameMapPtr(::cpp20::parser::spg::rules::GetRuleNameMapPtr());
        soul::cpp20::symbols::Context context;
        soul::cpp20::symbols::Module* module = project->GetModule(file);
        module->SetFilePath(filePath);
        soul::cpp20::symbols::SetCurrentModule(module);
        module->Import(moduleMapper);
        context.SetLexer(&lexer);
        context.SetSymbolTable(module->GetSymbolTable());
        std::unique_ptr<soul::cpp20::ast::Node> node = soul::cpp20::parser::translation::unit::TranslationUnitParser<decltype(lexer)>::Parse(lexer, &context);
        if ((flags & BuildFlags::xml) != BuildFlags::none)
        {
            std::string xmlFilePath = filePath + ".ast.xml";
            soul::cpp20::ast::WriteXml(node.get(), xmlFilePath);
        }
        module->SetFile(new soul::cpp20::ast::File(util::Path::GetFileName(filePath), node.release()));
        module->Write(project->Root());
        soul::cpp20::symbols::Module* interfaceUnitModule = moduleMapper.GetModule(interfaceUnitName);
        interfaceUnitModule->AddImplementationUnit(module);
        moduleMapper.AddModule(project->ReleaseModule(file));
        if ((flags & BuildFlags::verbose) != BuildFlags::none)
        {
            std::cout << filePath << " -> " << soul::cpp20::symbols::MakeModuleFilePath(project->Root(), module->Name()) << std::endl;
        }
    }
    projectModule.ResolveForwardDeclarations();
    projectModule.AddDerivedClasses();
    if ((flags & BuildFlags::verbose) != BuildFlags::none)
    {
        std::cout << "project '" << project->Name() << "' built successfully" << std::endl;
    }
}

soul::cpp20::symbols::Module* GetModule(soul::cpp20::symbols::ModuleMapper& moduleMapper, const std::string& moduleName)
{
    return moduleMapper.GetModule(moduleName);
}

void Visit(soul::cpp20::proj::ast::Solution* solution, 
    soul::cpp20::proj::ast::Project* project, 
    std::vector<soul::cpp20::proj::ast::Project*>& topologicalOrder,
    std::set<soul::cpp20::proj::ast::Project*>& visited)
{
    for (const std::string& path : project->ReferenceFilePaths())
    {
        std::string referenceFilePath = util::GetFullPath(util::Path::Combine(project->Root(), path));
        soul::cpp20::proj::ast::Project* dependsOnProject = solution->GetProject(referenceFilePath);
        if (dependsOnProject)
        {
            if (visited.find(dependsOnProject) == visited.cend())
            {
                visited.insert(dependsOnProject);
                Visit(solution, dependsOnProject, topologicalOrder, visited);
            }
        }
        else
        {
            soul::cpp20::ast::SetExceptionThrown();
            throw std::runtime_error("reference file path '" + referenceFilePath + "' in project '" + project->FilePath() + "' not found");
        }
    }
    visited.insert(project);
    topologicalOrder.push_back(project);
}

std::vector<soul::cpp20::proj::ast::Project*> MakeTopologicalOrder(soul::cpp20::proj::ast::Solution* solution)
{
    std::set<soul::cpp20::proj::ast::Project*> visited;
    std::vector<soul::cpp20::proj::ast::Project*> topologicalOrder;
    for (auto& project : solution->Projects())
    {
        if (visited.find(project.get()) == visited.cend())
        {
            Visit(solution, project.get(), topologicalOrder, visited);
        }
    }
    return topologicalOrder;
}

void BuildSequentally(soul::cpp20::symbols::ModuleMapper& moduleMapper, soul::cpp20::proj::ast::Solution* solution, BuildFlags flags)
{
    if ((flags & BuildFlags::verbose) != BuildFlags::none)
    {
        std::cout << "> building solution '" << solution->Name() << "'..." << std::endl;
    }
    std::string root = util::Path::GetDirectoryName(solution->FilePath());
    for (const auto& path : solution->ProjectFilePaths())
    {
        std::string projectFilePath = util::GetFullPath(util::Path::Combine(root, path));
        std::unique_ptr<soul::cpp20::proj::ast::Project> project = soul::cpp20::project::parser::ParseProjectFile(projectFilePath);
        solution->AddProject(project.release());
    }
    std::vector<soul::cpp20::proj::ast::Project*> buildOrder = MakeTopologicalOrder(solution);
    for (soul::cpp20::proj::ast::Project* project : buildOrder)
    {
        moduleMapper.AddRoot(project->Root());
        Build(moduleMapper, project, flags);
    }
    if ((flags & BuildFlags::verbose) != BuildFlags::none)
    {
        std::cout << "solution '" << solution->Name() << "' built successfully" << std::endl;
    }
}

void Build(soul::cpp20::symbols::ModuleMapper& moduleMapper, soul::cpp20::proj::ast::Project* project, BuildFlags flags)
{
    BuildSequentally(moduleMapper, project, flags);
}

void Build(soul::cpp20::symbols::ModuleMapper& moduleMapper, soul::cpp20::proj::ast::Solution* solution, BuildFlags flags)
{
    BuildSequentally(moduleMapper, solution, flags);
}

} // namespace soul::cpp20::project::build
