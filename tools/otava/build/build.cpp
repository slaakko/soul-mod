// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.build.build;

import otava.build_project;
import otava.build_solution;
import otava.build.parser;
import otava.build.project_file;
import otava.build.gen_main_unit;
import otava.build.msbuild;
import otava.ast;
import otava.lexer;
import otava.parser.translation.unit;
import otava.parser.spg.rules;
import otava.parser.module_dependency;
import otava.symbols.context;
import otava.symbols.bound.tree;
import otava.symbols.compound.type.symbol;
import otava.symbols.declarator;
import otava.symbols.namespaces;
import otava.symbols.conversion.table;
import otava.symbols.symbol.table;
import otava.symbols.exception;
import otava.symbols.function.symbol;
import otava.pp;
import otava.pp.state;
import otava.codegen;
import soul.lexer.xml.parsing.log;
import class_info_index;
import util.path;
import util.unicode;
import util.file.stream;
import util.sha1;
import util.buffered.stream;

namespace otava::build {

void WriteClassIndex(const std::string& classIndexFilePath, info::class_index& index)
{
    util::FileStream fileStream(classIndexFilePath, util::OpenMode::write | util::OpenMode::binary);
    util::BufferedStream bufferedStream(fileStream);
    util::BinaryStreamWriter writer(bufferedStream);
    index.write(writer, true);
}

void Visit(int file, Project* project, std::vector<int>& topologicalOrder, std::set<int>& visited)
{
    otava::symbols::Module* module = project->GetModule(file);
    for (otava::symbols::Module* dependsOnModule : module->DependsOnModules())
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

std::vector<int32_t> MakeTopologicalOrder(const std::vector<int32_t>& files, Project* project)
{
    std::set<int32_t> visited;
    std::vector<int32_t> topologicalOrder;
    for (int32_t file : files)
    {
        if (visited.find(file) == visited.cend())
        {
            Visit(file, project, topologicalOrder, visited);
        }
    }
    return topologicalOrder;
}

class ModuleDependencyVisitor : public otava::ast::DefaultVisitor
{
public:
    ModuleDependencyVisitor(int32_t file_, Project* project_, const std::string& fileName_, bool implementationUnit_);
    otava::symbols::Module* GetModule() { return module.release(); }
    const std::string& InterfaceUnitName() const { return interfaceUnitName; }
    void Visit(otava::ast::ModuleDeclarationNode& node);
    void Visit(otava::ast::TranslationUnitNode& node);
    void Visit(otava::ast::ExportDeclarationNode& node);
    void Visit(otava::ast::ImportDeclarationNode& node);
    void Visit(otava::ast::ModuleNameNode& node);
private:
    Project* project;
    std::string fileName;
    int32_t file;
    bool implementationUnit;
    bool exp;
    bool expimp;
    bool imp;
    bool implementation;
    std::string interfaceUnitName;
    std::unique_ptr<otava::symbols::Module> module;
};

ModuleDependencyVisitor::ModuleDependencyVisitor(int32_t file_, Project* project_, const std::string& fileName_, bool implementationUnit_) :
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

void ModuleDependencyVisitor::Visit(otava::ast::ModuleDeclarationNode& node)
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

void ModuleDependencyVisitor::Visit(otava::ast::TranslationUnitNode& node)
{
    module.reset(new otava::symbols::Module(project->Name() + "." + fileName));
    module->Init();
    module->SetFile(file);
    if (node.Unit())
    {
        node.Unit()->Accept(*this);
    }
}

void ModuleDependencyVisitor::Visit(otava::ast::ExportDeclarationNode& node)
{
    if (node.Subject() && node.Subject()->IsImportDeclarationNode())
    {
        expimp = true;
        node.Subject()->Accept(*this);
        expimp = false;
    }
}

void ModuleDependencyVisitor::Visit(otava::ast::ImportDeclarationNode& node)
{
    if (!expimp)
    {
        imp = true;
    }
    node.Subject()->Accept(*this);
    imp = false;
}

void ModuleDependencyVisitor::Visit(otava::ast::ModuleNameNode& node)
{
    if (exp)
    {
        std::string moduleName = util::ToUtf8(node.Str());
        module.reset(new otava::symbols::Module(moduleName));
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
        module.reset(new otava::symbols::Module(util::ToUtf8(node.Str()) + "." + fileName + ".cpp"));
        module->AddImportModuleName("std.type.fundamental");
        module->AddImportModuleName(util::ToUtf8(node.Str()));
    }
}

void ScanDependencies(Project* project, int32_t file, bool implementationUnit, std::string& interfaceUnitName)
{
    std::string filePath = project->GetFileMap().GetFilePath(file);
    std::string fileName = util::Path::GetFileNameWithoutExtension(filePath);
    std::string fileContent = util::ReadFile(filePath);
    std::u32string content = util::ToUtf32(fileContent);
    auto lexer = otava::lexer::MakeLexer(content.c_str(), content.c_str() + content.length(), filePath);
    lexer.SetFile(file);
    lexer.SetRuleNameMapPtr(otava::parser::spg::rules::GetRuleNameMapPtr());
    otava::symbols::Context context;
    context.SetLexer(&lexer);
    std::unique_ptr<otava::ast::Node> node = otava::parser::module_dependency::ModuleDependencyParser<decltype(lexer)>::Parse(lexer, &context);
    project->GetFileMap().AddFileContent(file, std::move(content), lexer.GetLineStartIndeces());
    ModuleDependencyVisitor visitor(file, project, fileName, implementationUnit);
    node->Accept(visitor);
    project->SetModule(file, visitor.GetModule());
    interfaceUnitName = visitor.InterfaceUnitName();
}

void BuildSequentially(otava::symbols::ModuleMapper& moduleMapper, Project* project, const std::string& config, BuildFlags flags)
{
    otava::symbols::SetProjectReady(false);
    if ((flags & BuildFlags::verbose) != BuildFlags::none)
    {
        std::cout << "> building project '" << project->Name() << "'..." << std::endl;
    }
    std::string projectFilePath = util::GetFullPath(util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(project->FilePath()), config), project->Name() + ".vcxproj"));
    std::vector<std::string> asmFileNames;
    std::vector<std::string> cppFileNames;
    std::vector<std::string> compileUnitInitFunctionNames;
    std::vector<std::string> allCompileUnitInitFunctionNames;
    std::string libraryDirs;
    std::string mainFunctionIrName;
    int mainFunctionParams = 0;
    std::string cppFileName = "__main__.cpp";
    if (project->GetTarget() == Target::program)
    {
        cppFileNames.push_back(cppFileName);
        libraryDirs = util::GetFullPath(util::Path::Combine(util::SoulRoot(), "lib"));
        libraryDirs.append(";").append(util::GetFullPath(util::Path::Combine(util::Path::Combine(util::SoulRoot(), "tools/otava/std"), config)));
        libraryDirs.append(";").append(util::GetFullPath(util::Path::Combine(util::SoulRoot(), "tools/otava/lib")));
    }
    project->AddRoots(moduleMapper);
    otava::symbols::Module projectModule(project->Name() + ".#project");
    otava::ast::SetNodeIdFactory(projectModule.GetNodeIdFactory());
    projectModule.GetNodeIdFactory()->SetModuleId(projectModule.Id());
    std::map<std::string, std::vector<std::string>> implementationNameMap;
    project->InitModules();
    if (!project->Scanned())
    {
        project->SetScanned();
        for (int32_t file : project->InterfaceFiles())
        {
            std::string interfaceUnitName;
            ScanDependencies(project, file, false, interfaceUnitName);
        }
        for (int32_t file : project->SourceFiles())
        {
            std::string interfaceUnitName;
            ScanDependencies(project, file, true, interfaceUnitName);
            otava::symbols::Module* implementationModule = project->GetModule(file);
            implementationNameMap[interfaceUnitName].push_back(implementationModule->Name());
        }
    }
    project->LoadModules(moduleMapper);
    if (project->GetTarget() == Target::program)
    {
        std::vector<std::string> referenceFilePaths;
        otava::symbols::Module* stdModule = moduleMapper.GetModule("std");
        referenceFilePaths.push_back(stdModule->FilePath());
        for (const auto& referenceFilePath : project->ReferenceFilePaths())
        {
            referenceFilePaths.push_back(referenceFilePath);
        }
        for (const auto& referenceFilePath : referenceFilePaths)
        {
            std::string cuInitFileName = util::Path::Combine(util::Path::GetDirectoryName(referenceFilePath), "cu.init");
            util::FileStream cuInitFile(cuInitFileName, util::OpenMode::read | util::OpenMode::binary);
            util::BinaryStreamReader reader(cuInitFile);
            int n = reader.ReadInt();
            for (int i = 0; i < n; ++i)
            {
                std::string compileUnitInitFunctionName = reader.ReadUtf8String();
                allCompileUnitInitFunctionNames.push_back(compileUnitInitFunctionName);
            }
        }
    }
    std::vector<int32_t> topologicalOrder = MakeTopologicalOrder(project->InterfaceFiles(), project);
    for (int32_t file : topologicalOrder)
    {
        const std::string& filePath = project->GetFileMap().GetFilePath(file);
        const auto& fileContent = project->GetFileMap().GetFileContent(file).first;
        auto lexer = otava::lexer::MakeLexer(fileContent.c_str(), fileContent.c_str() + fileContent.length(), filePath);
        lexer.SetPPHook(otava::pp::PreprocessPPLine);
        otava::pp::state::State* state = otava::pp::state::LexerStateMap::Instance().GetState(&lexer);
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
        lexer.SetRuleNameMapPtr(otava::parser::spg::rules::GetRuleNameMapPtr());
        otava::symbols::Context context;
        context.SetFileMap(&project->GetFileMap());
        std::string compileUnitId = "compile_unit_" + util::GetSha1MessageDigest(filePath);
        context.GetBoundCompileUnit()->SetId(compileUnitId);
        otava::symbols::Module* module = project->GetModule(file);
        module->GetNodeIdFactory()->SetModuleId(module->Id());
        module->SetFilePath(filePath);
        otava::symbols::SetCurrentModule(module);
        otava::ast::SetNodeIdFactory(module->GetNodeIdFactory());
        module->Import(moduleMapper);
        context.SetLexer(&lexer);
        context.SetSymbolTable(module->GetSymbolTable());
        std::unique_ptr<otava::ast::Node> node = otava::parser::translation::unit::TranslationUnitParser<decltype(lexer)>::Parse(lexer, &context);
        if ((flags & BuildFlags::xml) != BuildFlags::none)
        {
            std::string xmlFilePath = filePath + ".ast.xml";
            otava::ast::WriteXml(node.get(), xmlFilePath);
        }
        module->SetFile(new otava::ast::File(util::Path::GetFileName(filePath), node.release()));
        module->SetImplementationUnitNames(implementationNameMap[module->Name()]);
        projectModule.Import(module, moduleMapper);
        project->Index().imp(module->GetSymbolTable()->ClassIndex(), true);
        moduleMapper.AddModule(project->ReleaseModule(file));
        std::string asmFileName = otava::codegen::GenerateCode(context, config, (flags & BuildFlags::verbose) != BuildFlags::none, mainFunctionIrName, mainFunctionParams, false,
            std::vector<std::string>()); 
        module->Write(project->Root());
        if ((flags & BuildFlags::verbose) != BuildFlags::none)
        {
            std::cout << filePath << " -> " << otava::symbols::MakeModuleFilePath(project->Root(), module->Name()) << std::endl;
        }
        asmFileNames.push_back(asmFileName);
        otava::symbols::BoundFunctionNode* initFn = context.GetBoundCompileUnit()->GetCompileUnitInitializationFunction();
        if (initFn)
        {
            compileUnitInitFunctionNames.push_back(initFn->GetFunctionDefinitionSymbol()->IrName(&context));
        }
    }
    for (int32_t file : project->SourceFiles())
    {
        std::string interfaceUnitName;
        ScanDependencies(project, file, true, interfaceUnitName);
        const std::string& filePath = project->GetFileMap().GetFilePath(file);
        const auto& fileContent = project->GetFileMap().GetFileContent(file).first;
        auto lexer = otava::lexer::MakeLexer(fileContent.c_str(), fileContent.c_str() + fileContent.length(), filePath);
        lexer.SetPPHook(otava::pp::PreprocessPPLine);
        otava::pp::state::State* state = otava::pp::state::LexerStateMap::Instance().GetState(&lexer);
        for (const auto& define : project->Defines())
        {
            state->Define(define.symbol, define.value);
        }
        lexer.SetFile(file);
        lexer.SetRuleNameMapPtr(otava::parser::spg::rules::GetRuleNameMapPtr());
        otava::symbols::Context context;
        context.SetFileMap(&project->GetFileMap());
        std::string compileUnitId = "compile_unit_" + util::GetSha1MessageDigest(filePath);
        context.GetBoundCompileUnit()->SetId(compileUnitId);
        otava::symbols::Module* module = project->GetModule(file);
        module->GetNodeIdFactory()->SetModuleId(module->Id());
        module->SetFilePath(filePath);
        otava::symbols::SetCurrentModule(module);
        otava::ast::SetNodeIdFactory(module->GetNodeIdFactory());
        module->Import(moduleMapper);
        context.SetLexer(&lexer);
        context.SetSymbolTable(module->GetSymbolTable());
        // module->ResolveForwardDeclarations();
        std::unique_ptr<otava::ast::Node> node = otava::parser::translation::unit::TranslationUnitParser<decltype(lexer)>::Parse(lexer, &context);
        if ((flags & BuildFlags::xml) != BuildFlags::none)
        {
            std::string xmlFilePath = filePath + ".ast.xml";
            otava::ast::WriteXml(node.get(), xmlFilePath);
        }
        module->SetFile(new otava::ast::File(util::Path::GetFileName(filePath), node.release()));
        project->Index().imp(module->GetSymbolTable()->ClassIndex(), true);
        if (!interfaceUnitName.empty())
        {
            otava::symbols::Module* interfaceUnitModule = moduleMapper.GetModule(interfaceUnitName);
            interfaceUnitModule->AddImplementationUnit(module);
            moduleMapper.AddModule(project->ReleaseModule(file));
        }
        std::string asmFileName = otava::codegen::GenerateCode(context, config, (flags& BuildFlags::verbose) != BuildFlags::none, mainFunctionIrName, mainFunctionParams, false, 
            std::vector<std::string>());
        module->Write(project->Root());
        if ((flags & BuildFlags::verbose) != BuildFlags::none)
        {
            std::cout << filePath << " -> " << otava::symbols::MakeModuleFilePath(project->Root(), module->Name()) << std::endl;
        }
        asmFileNames.push_back(asmFileName);
        otava::symbols::BoundFunctionNode* initFn = context.GetBoundCompileUnit()->GetCompileUnitInitializationFunction();
        if (initFn)
        {
            compileUnitInitFunctionNames.push_back(initFn->GetFunctionDefinitionSymbol()->IrName(&context));
        }
    }
    // projectModule.ResolveForwardDeclarations();
    projectModule.AddDerivedClasses();
    ProjectTarget projectTarget = ProjectTarget::library;
    std::string classIndexFilePath;
    if (project->GetTarget() == Target::program)
    {
        if (mainFunctionIrName.empty())
        {
            otava::symbols::SetExceptionThrown(); 
            throw std::runtime_error("program has no main function");
        }
        for (const auto& fileName : compileUnitInitFunctionNames)
        {
            allCompileUnitInitFunctionNames.push_back(fileName);
        }
        std::string mainAsmFileName = GenerateMainUnit(moduleMapper, util::Path::Combine(util::Path::GetDirectoryName(projectFilePath), cppFileName), 
            mainFunctionIrName, mainFunctionParams, allCompileUnitInitFunctionNames, config);
        asmFileNames.push_back(mainAsmFileName);
        projectTarget = ProjectTarget::program;
        classIndexFilePath = util::Path::Combine(util::Path::GetDirectoryName(projectFilePath), "class_index.bin");
        WriteClassIndex(classIndexFilePath, project->Index());
    }
    else
    {
        std::string compileUnitInitFileName = util::Path::Combine(project->Root(), "cu.init");
        util::FileStream compileUnitInitFile(compileUnitInitFileName, util::OpenMode::write | util::OpenMode::binary);
        util::BinaryStreamWriter writer(compileUnitInitFile);
        int32_t n = compileUnitInitFunctionNames.size();
        writer.Write(n);
        for (const auto& fileName : compileUnitInitFunctionNames)
        {
            writer.Write(fileName);
        }
    }
    MakeProjectFile(projectFilePath, project->Name(), asmFileNames, cppFileNames, libraryDirs, classIndexFilePath, projectTarget, (flags & BuildFlags::verbose) != BuildFlags::none);
    MSBuild(projectFilePath, config);
    if ((flags & BuildFlags::verbose) != BuildFlags::none)
    {
        std::cout << "project '" << project->Name() << "' built successfully" << std::endl;
    }
    otava::symbols::SetProjectReady(true);
}

otava::symbols::Module* GetModule(otava::symbols::ModuleMapper& moduleMapper, const std::string& moduleName)
{
    return moduleMapper.GetModule(moduleName);
}

void Visit(Solution* solution, Project* project, std::vector<Project*>& topologicalOrder, std::set<Project*>& visited)
{
    for (const std::string& path : project->ReferenceFilePaths())
    {
        std::string referenceFilePath = util::GetFullPath(util::Path::Combine(project->Root(), path));
        Project* dependsOnProject = solution->GetProject(referenceFilePath);
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
            otava::ast::SetExceptionThrown();
            throw std::runtime_error("reference file path '" + referenceFilePath + "' in project '" + project->FilePath() + "' not found");
        }
    }
    visited.insert(project);
    topologicalOrder.push_back(project);
}

std::vector<Project*> MakeTopologicalOrder(Solution* solution)
{
    std::set<Project*> visited;
    std::vector<Project*> topologicalOrder;
    for (auto& project : solution->Projects())
    {
        if (visited.find(project.get()) == visited.cend())
        {
            Visit(solution, project.get(), topologicalOrder, visited);
        }
    }
    return topologicalOrder;
}

void BuildSequentially(otava::symbols::ModuleMapper& moduleMapper, Solution* solution, const std::string& config, BuildFlags flags)
{
    if ((flags & BuildFlags::verbose) != BuildFlags::none)
    {
        std::cout << "> building solution '" << solution->Name() << "'..." << std::endl;
    }
    std::string root = util::Path::GetDirectoryName(solution->FilePath());
    for (const auto& path : solution->ProjectFilePaths())
    {
        std::string projectFilePath = util::GetFullPath(util::Path::Combine(root, path));
        std::unique_ptr<Project> project = otava::build::ParseProjectFile(projectFilePath);
        solution->AddProject(project.release());
    }
    std::vector<Project*> buildOrder = MakeTopologicalOrder(solution);
    for (Project* project : buildOrder)
    {
        moduleMapper.AddRoot(project->Root());
        Build(moduleMapper, project, config, flags);
    }
    if ((flags & BuildFlags::verbose) != BuildFlags::none)
    {
        std::cout << "solution '" << solution->Name() << "' built successfully" << std::endl;
    }
}

void Build(otava::symbols::ModuleMapper& moduleMapper, Project* project, const std::string& config, BuildFlags flags)
{
    BuildSequentially(moduleMapper, project, config, flags);
}

void Build(otava::symbols::ModuleMapper& moduleMapper, Solution* solution, const std::string& config, BuildFlags flags)
{
    BuildSequentially(moduleMapper, solution, config, flags);
}

} // namespace otava::build
