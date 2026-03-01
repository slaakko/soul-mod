// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.build.build;

import otava.build.parser;
import otava.build.project_file;
import otava.build.gen_main_unit;
import otava.build.msbuild;
import otava.build.config;
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
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.classes;
import otava.symbols.function_definition_symbol_set;
import otava.symbols.function.templates;
import otava.symbols.inline_functions;
import otava.symbols.argument.conversion.table;
import otava.symbols.operation.repository;
import otava.symbols.emitter;
import otava.pp;
import otava.pp.state;
import otava.codegen;
import otava.opt;
import soul.lexer.xml.parsing.log;
import class_info_index;
import util;

namespace otava::build {

void WriteClassIndex(const std::string& classIndexFilePath, info::class_index& index)
{
    util::FileStream fileStream(classIndexFilePath, util::OpenMode::write | util::OpenMode::binary);
    util::BufferedStream bufferedStream(fileStream);
    util::BinaryStreamWriter writer(bufferedStream);
    index.write(writer);
}

void Visit(std::int32_t fileId, Project* project, std::vector<int>& topologicalOrder, std::set<int>& visited)
{
    otava::symbols::Module* module = project->GetModule(fileId);
    for (otava::symbols::Module* dependsOnModule : module->DependsOnModules())
    {
        if (project->GetModule(dependsOnModule->Name()))
        {
            if (dependsOnModule->FileId() != -1)
            {
                if (visited.find(dependsOnModule->FileId()) == visited.cend())
                {
                    visited.insert(dependsOnModule->FileId());
                    Visit(dependsOnModule->FileId(), project, topologicalOrder, visited);
                }
            }
        }
    }
    visited.insert(fileId);
    topologicalOrder.push_back(fileId);
}

std::vector<std::int32_t> MakeTopologicalOrder(const std::vector<std::int32_t>& files, Project* project)
{
    std::set<std::int32_t> visited;
    std::vector<std::int32_t> topologicalOrder;
    for (std::int32_t file : files)
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
    ModuleDependencyVisitor(std::int32_t file_, Project* project_, const std::string& fileName_, bool implementationUnit_);
    otava::symbols::Module* GetModule() { return module.release(); }
    const std::string& InterfaceUnitName() const { return interfaceUnitName; }
    void Visit(otava::ast::ModuleDeclarationNode& node) override;
    void Visit(otava::ast::TranslationUnitNode& node) override;
    void Visit(otava::ast::ExportDeclarationNode& node) override;
    void Visit(otava::ast::ImportDeclarationNode& node) override;
    void Visit(otava::ast::ModuleNameNode& node) override;
private:
    Project* project;
    std::string fileName;
    std::int32_t file;
    bool implementationUnit;
    bool exp;
    bool expimp;
    bool imp;
    bool implementation;
    std::string interfaceUnitName;
    std::unique_ptr<otava::symbols::Module> module;
};

ModuleDependencyVisitor::ModuleDependencyVisitor(std::int32_t file_, Project* project_, const std::string& fileName_, bool implementationUnit_) :
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
    module->SetFileId(file);
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
        module->SetFileId(file);
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
        module.reset(new otava::symbols::Module(util::ToUtf8(node.Str()) + ".cpp"));
        module->AddImportModuleName("std.type.fundamental");
        module->AddImportModuleName(util::ToUtf8(node.Str()));
    }
}

void ScanDependencies(Project* project, std::int32_t fileId, bool implementationUnit, std::string& interfaceUnitName)
{
    std::string filePath = project->GetFileMap().GetFilePath(fileId);
    std::string fileName = util::Path::GetFileNameWithoutExtension(filePath);
    std::string fileContent = util::ReadFile(filePath);
    std::u32string content = util::ToUtf32(fileContent);
    auto lxr = otava::lexer::MakeLexer(content.c_str(), content.c_str() + content.length(), filePath);
    lxr.SetFile(fileId);
    lxr.SetRuleNameMapPtr(otava::parser::spg::rules::GetRuleNameMapPtr());
    otava::symbols::Context context;
    context.SetLexer(&lxr);
    context.SetCurrentProject(project);
    if (project->HasDefine("NOWARN"))
    {
        context.SetFlag(otava::symbols::ContextFlags::noWarnings);
    }
    using LexerType = decltype(lxr);
    std::unique_ptr<otava::ast::Node> node = otava::parser::module_dependency::ModuleDependencyParser<LexerType>::Parse(lxr, &context);
    project->GetFileMap().AddFileContent(fileId, std::move(content), lxr.GetLineStartIndeces());
    ModuleDependencyVisitor visitor(fileId, project, fileName, implementationUnit);
    node->Accept(visitor);
    project->SetModule(fileId, visitor.GetModule());
    interfaceUnitName = visitor.InterfaceUnitName();
}

void ReadFilesFile(const std::string& projectFilesPath, soul::lexer::FileMap& fileMap)
{
    util::FileStream filesFile(projectFilesPath, util::OpenMode::read | util::OpenMode::binary);
    util::BufferedStream filesBufStream(filesFile);
    util::BinaryStreamReader filesReader(filesBufStream);
    std::int32_t fileCount = filesReader.ReadInt();
    for (std::int32_t i = 0; i < fileCount; ++i)
    {
        std::int32_t fileId = filesReader.ReadInt();
        std::string filePath = filesReader.ReadUtf8String();
        fileMap.MapFile(filePath, fileId);
    }
}

void WriteFilesFile(const std::string& projectFilesPath, const std::vector<std::pair<std::int32_t, std::string>>& files)
{
    util::FileStream filesFile(projectFilesPath, util::OpenMode::write | util::OpenMode::binary);
    util::BufferedStream filesBufStream(filesFile);
    util::BinaryStreamWriter filesWriter(filesBufStream);
    std::int32_t fileCount = files.size();
    filesWriter.Write(fileCount);
    for (const auto& file : files)
    {
        filesWriter.Write(file.first);
        filesWriter.Write(file.second);
    }
}

void BuildSequentially(Project* project, const std::string& config, int optLevel, BuildFlags flags)
{
    otava::symbols::SetProjectReady(false);
    std::vector<std::string> buildSymbols = GetBuildSymbols();
    for (const auto& symbol : buildSymbols)
    {
        project->AddDefine(symbol, 1);
    }
    std::set<std::string> configurations;
    ConfigureProject(project, config, (flags & BuildFlags::verbose) != BuildFlags::none, configurations);
    std::string moduleDirPath = otava::symbols::MakeModuleDirPath(project->Root(), config, otava::symbols::GetOptLevel(optLevel,
        configurations.find("release") != configurations.end()), configurations);
    util::uuid projectId = otava::symbols::MakeProjectId(project->Name());
    if ((flags & BuildFlags::seed) != BuildFlags::none)
    {
        std::uint64_t seed = std::hash<std::string>()(project->FilePath());
        util::reset_rng();
        util::set_rand_seed(seed);
    }
    otava::symbols::ModuleMapper* prevModuleMapper = otava::symbols::GetModuleMapper();
    bool expected = project->HasDefine("EXPECTED");
    bool nowarnings = project->HasDefine("NOWARN");
    otava::symbols::ModuleMapper moduleMapper(expected);
    otava::symbols::SetModuleMapper(&moduleMapper);
    otava::symbols::InstantiationQueue instantiationQueue;
    std::string projectFilePath;
    std::string outputFilePath;
    if (configurations.find("release") != configurations.end())
    {
        projectFilePath = util::GetFullPath(util::Path::Combine(util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(project->FilePath()), config),
            std::to_string(otava::symbols::GetOptLevel(optLevel, true))), project->Name() + ".vcxproj"));
        outputFilePath = util::GetFullPath(util::Path::Combine(util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(project->FilePath()), config), 
            std::to_string(otava::symbols::GetOptLevel(optLevel, true))), project->Name()));
    }
    else
    {
        projectFilePath = util::GetFullPath(util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(
            project->FilePath()), config), project->Name() + ".vcxproj"));
        outputFilePath = util::GetFullPath(util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(project->FilePath()), config), project->Name()));
    }
    if (project->GetTarget() == otava::build::Target::program)
    {
        outputFilePath.append(".exe");
    }
    else if (project->GetTarget() == otava::build::Target::library)
    {
        outputFilePath.append(".lib");
    }
    project->SetOutputFilePath(outputFilePath);
    std::vector<std::string> asmFileNames;
    std::vector<std::string> cppFileNames;
    std::vector<std::string> resourceFileNames;
    std::vector<std::string> compileUnitInitFunctionNames;
    std::vector<std::string> allCompileUnitInitFunctionNames;
    bool inliningEnabled = false;
    int totalFunctionsCompiled = 0;
    int functionsInlined = 0;
    int functionCallsInlined = 0;
    int importIndex = 0;
    int invokes = 0;
    moduleMapper.SetFunctionDefinitionSymbolSet(project->GetFunctionDefinitionSymbolSet());
    std::string libraryDirs;
    std::string mainFunctionIrName;
    int mainFunctionParams = 0;
    std::string cppFileName = "__main__.cpp";
    if (project->GetTarget() == Target::program)
    {
        cppFileNames.push_back(cppFileName);
        libraryDirs = util::GetFullPath(util::Path::Combine(util::SoulRoot(), "lib"));
        if (configurations.find("release") != configurations.end())
        {
            if (project->HasDefine("EXPECTED"))
            {
                libraryDirs.append(";").append(util::GetFullPath(util::Path::Combine(util::Path::Combine(
                    util::Path::Combine(util::SoulRoot(), "tools/otava/expected/std"), config),
                    std::to_string(otava::symbols::GetOptLevel(optLevel, true)))));
            }
            else
            {
                libraryDirs.append(";").append(util::GetFullPath(util::Path::Combine(util::Path::Combine(
                    util::Path::Combine(util::SoulRoot(), "tools/otava/std"), config),
                    std::to_string(otava::symbols::GetOptLevel(optLevel, true)))));
            }
            libraryDirs.append(";").append(util::GetFullPath(util::Path::Combine(util::SoulRoot(), "tools/otava/lib")));
        }
        else
        {
            if (project->HasDefine("EXPECTED"))
            {
                libraryDirs.append(";").append(util::GetFullPath(util::Path::Combine(util::Path::Combine(util::SoulRoot(), 
                    "tools/otava/expected/std"), config)));
            }
            else
            {
                libraryDirs.append(";").append(util::GetFullPath(util::Path::Combine(util::Path::Combine(util::SoulRoot(), "tools/otava/std"), config)));
            }
            libraryDirs.append(";").append(util::GetFullPath(util::Path::Combine(util::SoulRoot(), "tools/otava/lib")));
        }
    }
    project->AddRoots(moduleMapper);
    otava::symbols::Module projectModule(project->Name() + ".#project");
    projectModule.SetProjectId(projectId);
    projectModule.SetImportIndex(importIndex);
    otava::ast::SetNodeIdFactory(projectModule.GetNodeIdFactory());
    projectModule.GetSymbolTable()->SetSymbolMap(moduleMapper.GetSymbolMap());
    projectModule.GetNodeIdFactory()->SetModuleId(projectModule.Id());
    std::map<std::string, std::vector<std::string>> implementationNameMap;
    project->InitModules();
    otava::symbols::SetCurrentModule(nullptr);
    if (!project->Scanned())
    {
        project->SetScanned();
        for (std::int32_t file : project->InterfaceFiles())
        {
            const std::string& filePath = project->GetFileMap().GetFilePath(file);
            std::string interfaceUnitName;
            ScanDependencies(project, file, false, interfaceUnitName);
            otava::symbols::Module* interfaceModule = project->GetModule(file);
            interfaceModule->SetFilePath(filePath);
            interfaceModule->SetKind(otava::symbols::ModuleKind::interfaceModule);
            interfaceModule->SetProjectId(projectId);
        }
        for (std::int32_t file : project->SourceFiles())
        {
            const std::string& filePath = project->GetFileMap().GetFilePath(file);
            std::string interfaceUnitName;
            ScanDependencies(project, file, true, interfaceUnitName);
            otava::symbols::Module* implementationModule = project->GetModule(file);
            implementationModule->SetFilePath(filePath);
            implementationModule->SetKind(otava::symbols::ModuleKind::implementationModule);
            implementationModule->SetProjectId(projectId);
            implementationNameMap[interfaceUnitName].push_back(implementationModule->Name());
        }
    }
    if (project->Name() != "std")
    {
        std::string stdProjectPath = moduleMapper.GetProjectFilePath("std");
        if (!stdProjectPath.empty())
        {
            project->AddReferenceFilePath(stdProjectPath);
        }
        else
        {
            otava::symbols::SetExceptionThrown();
            throw std::runtime_error("error: 'std.project' not found");
        }
    }
    for (const auto& path : project->ReferenceFilePaths())
    {
        std::string projectFilePath = util::GetFullPath(util::Path::Combine(project->Root(), path));
        std::unique_ptr<Project> projectReference = otava::build::ParseProjectFile(projectFilePath);
        std::string outputFilePath;
        if (configurations.find("release") != configurations.end())
        {
            outputFilePath = util::GetFullPath(util::Path::Combine(util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(projectReference->FilePath()), 
                config), std::to_string(otava::symbols::GetOptLevel(optLevel, true))), projectReference->Name()));
        }
        else
        {
            outputFilePath = util::GetFullPath(util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(projectReference->FilePath()), config),
                projectReference->Name()));
        }
        if (projectReference->GetTarget() == otava::build::Target::program)
        {
            outputFilePath.append(".exe");
        }
        else if (projectReference->GetTarget() == otava::build::Target::library)
        {
            outputFilePath.append(".lib");
        }
        projectReference->SetOutputFilePath(outputFilePath);
        projectReference->SetFileMap(&project->GetFileMap());
        project->AddReferencedProject(projectReference.release());
    }
    if ((flags & BuildFlags::rebuild) == BuildFlags::none)
    {
        if (project->UpToDate(config, optLevel, configurations))
        {
            std::cout << "> project '" << project->Name() << "' is up-to-date" << "\n";
            return;
        }
    }
    std::cout << "> building project '" << project->Name() << "'..." << "\n";
    otava::symbols::Context moduleContext;
    if (project->HasDefine("NOWARN"))
    {
        moduleContext.SetFlag(otava::symbols::ContextFlags::noWarnings);
    }
    project->LoadModules(moduleMapper, config, optLevel, configurations, &moduleContext);
    importIndex = moduleMapper.ModuleCount();
    if (project->GetTarget() == Target::program)
    {
        for (const auto& referenceFilePath : project->ReferenceFilePaths())
        {
            std::string cuInitFileName = util::GetFullPath(util::Path::Combine(project->Root(), 
                util::Path::Combine(util::Path::GetDirectoryName(referenceFilePath), "cu.init")));
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
    for (const auto& reference : project->ReferencedProjects())
    {
        std::string referenceFilesPath = util::GetFullPath(util::Path::Combine(reference->Root(), reference->Name() + ".files"));
        ReadFilesFile(referenceFilesPath, project->GetFileMap());
    }
    std::vector<std::pair<std::int32_t, std::string>> files;
    std::vector<std::int32_t> topologicalOrder = MakeTopologicalOrder(project->InterfaceFiles(), project);
    for (std::int32_t file : topologicalOrder)
    {
        const std::string& filePath = project->GetFileMap().GetFilePath(file);
        std::cout << "> " << filePath << "\n";
        files.push_back(std::make_pair(file, filePath));
        const auto& fileContent = project->GetFileMap().GetFileContent(file).first;
        soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t> lxr = otava::lexer::MakeLexer(
            fileContent.c_str(), fileContent.c_str() + fileContent.length(), filePath);
        lxr.SetPPHook(otava::pp::PreprocessPPLine);
        otava::pp::state::State* state = otava::pp::state::LexerStateMap::Instance().GetState(&lxr);
        for (const auto& define : project->Defines())
        {
            state->Define(define.symbol, define.value);
        }
        lxr.SetFile(file);
        std::unique_ptr<std::ofstream> logFile;
        std::unique_ptr<soul::lexer::XmlParsingLog> log;
        if ((flags & BuildFlags::debugParse) != BuildFlags::none)
        {
            logFile.reset(new std::ofstream("parse.log"));
            log.reset(new soul::lexer::XmlParsingLog(*logFile));
            lxr.SetLog(log.get());
        }
        lxr.SetRuleNameMapPtr(otava::parser::spg::rules::GetRuleNameMapPtr());
        otava::symbols::Context context;
        otava::symbols::Emitter emitter;
        context.SetEmitter(&emitter);
        context.SetCurrentProject(project);
        if (configurations.find("release") != configurations.end())
        {
            context.SetReleaseConfig();
        }
        if (!context.CurrentProject() && context.CurrentProject()->HasDefine("TRACE"))
        {
            context.SetTraceInfo(&project->GetTraceInfo());
        }
        if (context.CurrentProject() && context.CurrentProject()->HasDefine("EXPECTED"))
        {
            context.SetFlag(otava::symbols::ContextFlags::expected);
        }
        if (context.CurrentProject() && context.CurrentProject()->HasDefine("NOWARN"))
        {
            context.SetFlag(otava::symbols::ContextFlags::noWarnings);
        }
        context.SetOptLevel(optLevel);
        context.SetFileMap(&project->GetFileMap());
        context.SetInstantiationQueue(&instantiationQueue);
        context.SetFunctionDefinitionSymbolSet(moduleMapper.GetFunctionDefinitionSymbolSet());
        std::string compileUnitId = "compile_unit_" + util::GetSha1MessageDigest(filePath);
        context.GetBoundCompileUnit()->SetId(compileUnitId);
        otava::symbols::Module* module = project->GetModule(file);
        if (context.CurrentProject() && context.CurrentProject()->HasDefine("TRACE"))
        {
            project->GetTraceInfo().AddSourceFileInfo(module->Id(), filePath);
        }
        module->SetImportIndex(importIndex++);
        module->GetNodeIdFactory()->SetModuleId(module->Id());
        module->SetFilePath(filePath);
        otava::symbols::SetCurrentModule(module);
        otava::ast::SetNodeIdFactory(module->GetNodeIdFactory());
        module->GetSymbolTable()->SetSymbolMap(moduleMapper.GetSymbolMap());
        module->Import(moduleMapper, config, optLevel, configurations, &context);
        module->GetSymbolTable()->ResolveForwardDeclarations();
        context.SetLexer(&lxr);
        context.SetSymbolTable(module->GetSymbolTable());
        using LexerType = decltype(lxr);
        std::unique_ptr<otava::ast::Node> node = otava::parser::translation::unit::TranslationUnitParser<LexerType>::Parse(lxr, &context);
        otava::symbols::GenerateDestructors(context.GetBoundCompileUnit(), &context);
        if ((flags & BuildFlags::xml) != BuildFlags::none)
        {
            std::string xmlFilePath = filePath + ".ast.xml";
            otava::ast::WriteXml(node.get(), xmlFilePath);
        }
        module->SetFile(new otava::ast::File(util::Path::GetFileName(filePath), node.release()));
        module->SetImplementationUnitNames(implementationNameMap[module->Name()]);
        //projectModule.Import(module, moduleMapper, config, optLevel);
        if ((flags & BuildFlags::symbolXml) != BuildFlags::none)
        {
            std::string dirPath;
            if (configurations.find("release") != configurations.end())
            {
                dirPath = util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(module->FilePath()), config),
                    std::to_string(otava::symbols::GetOptLevel(optLevel, true)));
            }
            else
            {
                dirPath = util::Path::Combine(util::Path::GetDirectoryName(module->FilePath()), config);
            }
            util::CreateDirectories(dirPath);
            std::string xmlFilePath;
            if (configurations.find("release") != configurations.end())
            {
                xmlFilePath = util::Path::Combine(util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(module->FilePath()), config),
                    std::to_string(otava::symbols::GetOptLevel(optLevel, true))), util::Path::GetFileName(module->FilePath()) + ".xml");
            }
            else
            {
                xmlFilePath = util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(module->FilePath()), config),
                    util::Path::GetFileName(module->FilePath()) + ".xml");
            }
            module->ToXml(xmlFilePath);
        }
        moduleMapper.AddModule(project->ReleaseModule(file));
        std::string asmFileName = otava::codegen::GenerateCode(
            context, config, optLevel, (flags & BuildFlags::verbose) != BuildFlags::none, 
            mainFunctionIrName, mainFunctionParams, false, std::vector<std::string>(), configurations);
        project->Index().import(module->GetSymbolTable()->ClassIndex());
        module->Write(project->Root(), config, optLevel, &context, configurations);
        if ((flags & BuildFlags::verbose) != BuildFlags::none)
        {
            std::cout << filePath << " -> " << otava::symbols::MakeModuleFilePath(project->Root(), config, optLevel, module->Name(), configurations) << std::endl;
        }
        asmFileNames.push_back(asmFileName);
        otava::symbols::BoundFunctionNode* initFn = context.GetBoundCompileUnit()->GetCompileUnitInitializationFunction();
        if (initFn)
        {
            compileUnitInitFunctionNames.push_back(initFn->GetFunctionDefinitionSymbol()->IrName(&context));
        }
        totalFunctionsCompiled += context.TotalFunctionsCompiled();
        invokes += context.Invokes();
        if (context.ReleaseConfig() && otava::optimizer::HasOptimization(otava::optimizer::Optimizations::inlining))
        {
            inliningEnabled = true;
            functionsInlined += context.FunctionsInlined();
            functionCallsInlined += context.FunctionCallsInlined();
        }
    }
    for (std::int32_t file : project->SourceFiles())
    {
        std::string interfaceUnitName;
        ScanDependencies(project, file, true, interfaceUnitName);
        const std::string& filePath = project->GetFileMap().GetFilePath(file);
        std::cout << "> " << filePath << "\n";
        files.push_back(std::make_pair(file, filePath));
        const auto& fileContent = project->GetFileMap().GetFileContent(file).first;
        soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t> lxr = otava::lexer::MakeLexer(
            fileContent.c_str(), fileContent.c_str() + fileContent.length(), filePath);
        lxr.SetPPHook(otava::pp::PreprocessPPLine);
        otava::pp::state::State* state = otava::pp::state::LexerStateMap::Instance().GetState(&lxr);
        for (const auto& define : project->Defines())
        {
            state->Define(define.symbol, define.value);
        }
        lxr.SetFile(file);
        lxr.SetRuleNameMapPtr(otava::parser::spg::rules::GetRuleNameMapPtr());
        otava::symbols::Emitter emitter;
        otava::symbols::Context context;
        context.SetEmitter(&emitter);
        context.SetCurrentProject(project);
        if (configurations.find("release") != configurations.end())
        {
            context.SetReleaseConfig();
        }
        if (context.CurrentProject() && context.CurrentProject()->HasDefine("TRACE"))
        {
            context.SetTraceInfo(&project->GetTraceInfo());
        }
        if (context.CurrentProject() && context.CurrentProject()->HasDefine("EXPECTED"))
        {
            context.SetFlag(otava::symbols::ContextFlags::expected);
        }
        if (context.CurrentProject() && context.CurrentProject()->HasDefine("NOWARN"))
        {
            context.SetFlag(otava::symbols::ContextFlags::noWarnings);
        }
        context.SetOptLevel(optLevel);
        context.SetFileMap(&project->GetFileMap());
        context.SetInstantiationQueue(&instantiationQueue);
        context.SetFunctionDefinitionSymbolSet(moduleMapper.GetFunctionDefinitionSymbolSet());
        std::string compileUnitId = "compile_unit_" + util::GetSha1MessageDigest(filePath);
        context.GetBoundCompileUnit()->SetId(compileUnitId);
        otava::symbols::Module* module = project->GetModule(file);
        if (context.CurrentProject() && context.CurrentProject()->HasDefine("TRACE"))
        {
            project->GetTraceInfo().AddSourceFileInfo(module->Id(), filePath);
        }
        module->SetKind(otava::symbols::ModuleKind::implementationModule);
        module->SetImportIndex(importIndex++);
        module->GetNodeIdFactory()->SetModuleId(module->Id());
        module->SetFilePath(filePath);
        otava::symbols::SetCurrentModule(module);
        otava::ast::SetNodeIdFactory(module->GetNodeIdFactory());
        module->GetSymbolTable()->SetSymbolMap(moduleMapper.GetSymbolMap());
        module->Import(moduleMapper, config, optLevel, configurations, &context);
        module->GetSymbolTable()->ResolveForwardDeclarations();
        context.SetLexer(&lxr);
        context.SetSymbolTable(module->GetSymbolTable());
        using LexerType = decltype(lxr);
        std::unique_ptr<otava::ast::Node> node = otava::parser::translation::unit::TranslationUnitParser<LexerType>::Parse(lxr, &context);
        otava::symbols::GenerateDestructors(context.GetBoundCompileUnit(), &context);
        if ((flags & BuildFlags::xml) != BuildFlags::none)
        {
            std::string xmlFilePath = filePath + ".ast.xml";
            otava::ast::WriteXml(node.get(), xmlFilePath);
        }
        module->SetFile(new otava::ast::File(util::Path::GetFileName(filePath), node.release()));
        if (!interfaceUnitName.empty())
        {
            otava::symbols::Module* interfaceUnitModule = moduleMapper.GetModule(interfaceUnitName, config, optLevel, configurations, &context);
            interfaceUnitModule->AddImplementationUnit(module);
            moduleMapper.AddModule(project->ReleaseModule(file));
        }
        std::string asmFileName = otava::codegen::GenerateCode(
            context, config, optLevel, (flags& BuildFlags::verbose) != BuildFlags::none, mainFunctionIrName, mainFunctionParams, 
            false, std::vector<std::string>(), configurations);
        project->Index().import(module->GetSymbolTable()->ClassIndex());
        asmFileNames.push_back(asmFileName);
        otava::symbols::BoundFunctionNode* initFn = context.GetBoundCompileUnit()->GetCompileUnitInitializationFunction();
        if (initFn)
        {
            compileUnitInitFunctionNames.push_back(initFn->GetFunctionDefinitionSymbol()->IrName(&context));
        }
        totalFunctionsCompiled += context.TotalFunctionsCompiled();
        invokes += context.Invokes();
        if (context.ReleaseConfig() && otava::optimizer::HasOptimization(otava::optimizer::Optimizations::inlining))
        {
            inliningEnabled = true;
            functionsInlined += context.FunctionsInlined();
            functionCallsInlined += context.FunctionCallsInlined();
        }
    }
    projectModule.AddDerivedClasses();
    project->WriteTraceInfo(moduleDirPath);
    project->WriteClassIndex(moduleDirPath);
    ProjectTarget projectTarget = ProjectTarget::library;
    std::string classIndexFilePath;
    std::string traceBinPath;
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
        otava::symbols::Context mainUnitContext;
        if (project->HasDefine("NOWARN"))
        {
            mainUnitContext.SetFlag(otava::symbols::ContextFlags::noWarnings);
        }
        std::string mainAsmFileName = GenerateMainUnit(moduleMapper, util::Path::Combine(util::Path::GetDirectoryName(projectFilePath), cppFileName), 
            mainFunctionIrName, mainFunctionParams, allCompileUnitInitFunctionNames, config, optLevel, project, configurations, &mainUnitContext);
        asmFileNames.push_back(mainAsmFileName);
        projectTarget = ProjectTarget::program;
        otava::symbols::TraceBin traceBin;
        for (const auto& referencedProject : project->ReferencedProjects())
        {
            std::string moduleDirPath = otava::symbols::MakeModuleDirPath(referencedProject->Root(), config, 
                otava::symbols::GetOptLevel(optLevel, configurations.find("release") != configurations.end()), configurations);
            referencedProject->ReadTraceInfo(moduleDirPath);
            if (referencedProject->HasDefine("TRACE"))
            {
                traceBin.Import(referencedProject->GetTraceInfo());
            }
            referencedProject->ReadClassIndex(moduleDirPath);
            project->Index().import(referencedProject->Index());
        }
        if (project->HasDefine("TRACE"))
        {
            traceBin.Import(project->GetTraceInfo());
            traceBinPath = util::GetFullPath(util::Path::Combine(moduleDirPath, "trace.bin"));
            otava::symbols::WriteTraceBin(traceBin, traceBinPath);
        }
        classIndexFilePath = util::GetFullPath(util::Path::Combine(moduleDirPath, "class_index.bin"));
        WriteClassIndex(classIndexFilePath, project->Index());
    }
    else
    {
        std::string compileUnitInitFileName = util::Path::Combine(project->Root(), "cu.init");
        util::FileStream compileUnitInitFile(compileUnitInitFileName, util::OpenMode::write | util::OpenMode::binary);
        util::BinaryStreamWriter writer(compileUnitInitFile);
        std::int32_t n = compileUnitInitFunctionNames.size();
        writer.Write(n);
        for (const auto& fileName : compileUnitInitFunctionNames)
        {
            writer.Write(fileName);
        }
    }
    for (const auto& resourceFilePath : project->ResourceFilePaths())
    {
        std::string absoluteRCFilePath = util::GetFullPath(util::Path::Combine(project->Root(), resourceFilePath));
        resourceFileNames.push_back(absoluteRCFilePath);
    }
    if ((flags & BuildFlags::verbose) != BuildFlags::none)
    {
        std::cout << totalFunctionsCompiled << " functions compiled\n";
        if (inliningEnabled)
        {
            std::cout << functionCallsInlined << " function calls inlined in " << functionsInlined << " functions\n";
        }
        std::cout << invokes << " invokes generated\n";
    }
    MakeProjectFile(project, projectFilePath, asmFileNames, cppFileNames, resourceFileNames,
        libraryDirs, project->ReferencedProjects(), config, optLevel, classIndexFilePath, traceBinPath, projectTarget, (flags& BuildFlags::verbose) != BuildFlags::none,
        configurations);
    MSBuild(projectFilePath, config, configurations);
    std::string projectFilesPath = util::GetFullPath(util::Path::Combine(project->Root(), project->Name() + ".files"));
    WriteFilesFile(projectFilesPath, files);
    std::cout << "project '" << project->Name() << "' built successfully" << std::endl;
    otava::symbols::SetModuleMapper(prevModuleMapper);
    otava::symbols::SetProjectReady(true);
}

otava::symbols::Module* GetModule(otava::symbols::ModuleMapper& moduleMapper, const std::string& moduleName, const std::string& config, int optLevel, 
    const std::set<std::string>& configurations, otava::symbols::Context* context)
{
    return moduleMapper.GetModule(moduleName, config, optLevel, configurations, context);
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
            otava::symbols::SetExceptionThrown();
            throw std::runtime_error("reference file path '" + referenceFilePath + "' in solution '" + solution->FilePath() + "' not found");
        }
    }
    visited.insert(project);
    topologicalOrder.push_back(project);
}

std::vector<Project*> MakeTopologicalOrder(Solution* solution)
{
    std::set<Project*> visited;
    std::vector<Project*> topologicalOrder;
    for (Project* project : solution->Projects())
    {
        if (visited.find(project) == visited.cend())
        {
            Visit(solution, project, topologicalOrder, visited);
        }
    }
    return topologicalOrder;
}

void BuildSequentially(soul::lexer::FileMap& fileMap, Solution* solution, const std::string& config, int optLevel, BuildFlags flags, 
    std::set<Project*, ProjectLess>& projectSet)
{
    if (solution->IsProjectSolution())
    {
        std::cout << "> building project '" << solution->Name() << "' with dependencies..." << std::endl;
    }
    else
    {
        std::cout << "> building solution '" << solution->Name() << "'..." << std::endl;
    }
    if (!solution->IsProjectSolution())
    {
        std::string root = util::Path::GetDirectoryName(solution->FilePath());
        for (const auto& path : solution->ProjectFilePaths())
        {
            std::string projectFilePath = util::GetFullPath(util::Path::Combine(root, path));
            std::unique_ptr<Project> project = otava::build::ParseProjectFile(projectFilePath);
            project->SetFileMap(&fileMap);
            solution->AddProject(project.release());
        }
    }
    std::vector<Project*> buildOrder = MakeTopologicalOrder(solution);
    for (Project* project : buildOrder)
    {
        Build(fileMap, project, config, optLevel, flags & ~BuildFlags::all, projectSet);
    }
    if (!solution->IsProjectSolution())
    {
        std::cout << "solution '" << solution->Name() << "' built successfully" << std::endl;
    }
}

void ProjectClosure(soul::lexer::FileMap& fileMap, Project* project, Solution* solution, std::set<std::string>& projectFilePaths)
{
    std::string root = util::Path::GetDirectoryName(project->FilePath());
    for (const auto& referenceFilePath : project->ReferenceFilePaths())
    {
        std::string projectFilePath = util::GetFullPath(util::Path::Combine(root, referenceFilePath));
        if (projectFilePaths.find(projectFilePath) != projectFilePaths.end()) continue;
        projectFilePaths.insert(projectFilePath);
        std::unique_ptr<Project> referencedProject = otava::build::ParseProjectFile(projectFilePath);
        Project* reference = referencedProject.get();
        if (project->Name() != "std" && reference->Name() == "std") continue;
        reference->SetFileMap(&fileMap);
        project->AddReferencedProject(referencedProject.release());
        ProjectClosure(fileMap, reference, solution, projectFilePaths);
    }
    solution->AddProject(project, false);
}

void Build(soul::lexer::FileMap& fileMap, Project* project, const std::string& config, int optLevel, BuildFlags flags, std::set<Project*, ProjectLess>& projectSet)
{
    if ((flags & BuildFlags::all) != BuildFlags::none)
    {
        Solution solution(project->FilePath(), project->Name());
        solution.SetProjectSolution();
        std::set<std::string> projectFilePaths;
        ProjectClosure(fileMap, project, &solution, projectFilePaths);
        Build(fileMap, &solution, config, optLevel, flags & ~BuildFlags::all, projectSet);
    }
    else
    {
        if (projectSet.find(project) != projectSet.end()) return;
        projectSet.insert(project);
        BuildSequentially(project, config, optLevel, flags & ~BuildFlags::all);
    }
}

void Build(soul::lexer::FileMap& fileMap, Solution* solution, const std::string& config, int optLevel, BuildFlags flags, std::set<Project*, ProjectLess>& projectSet)
{
    BuildSequentially(fileMap, solution, config, optLevel, flags & ~BuildFlags::all, projectSet);
}

} // namespace otava::build
