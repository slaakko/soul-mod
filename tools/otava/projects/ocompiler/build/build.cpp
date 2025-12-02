// =================================
// Copyright (c) 2025 Seppo Laakko
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
import otava.parser.rules;
import otava.parser.module_dependency;
import otava.symbols.context;
import otava.symbols.bound.tree;
import otava.symbols.compound.type.symbol;
import otava.symbols.declarator;
import otava.symbols.namespaces;
import otava.symbols.conversion.table;
import otava.symbols.symbol.table;
import otava.symbols.error;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.classes;
import otava.symbols.function_definition_symbol_set;
import otava.symbols.function.templates;
import otava.symbols.inline_functions;
import otava.symbols.argument.conversion.table;
import otava.symbols.operation.repository;
import otava.symbols.emitter;
import otava.symbols.class_info_index;
import otava.pp;
import otava.pp.state;
import otava.codegen;
import otava.opt;
import soul.lexer.xml.parsing.log;
import util;

namespace otava::build {

std::expected<bool, int> WriteClassIndex(const std::string& classIndexFilePath, otava::symbols::class_index& index)
{
    util::FileStream fileStream(classIndexFilePath, util::OpenMode::write | util::OpenMode::binary);
    if (!fileStream) return std::unexpected<int>(util::AllocateError("could not create file '" + classIndexFilePath + "'"));
    util::BufferedStream bufferedStream(fileStream);
    util::BinaryStreamWriter writer(bufferedStream);
    auto rv = index.write(writer);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Visit(std::int32_t fileId, Project* project, std::vector<int>& topologicalOrder, std::set<int>& visited)
{
    std::expected<otava::symbols::Module*, int> m = project->GetModule(fileId);
    if (!m) return std::unexpected<int>(m.error());
    otava::symbols::Module* module = *m;
    for (otava::symbols::Module* dependsOnModule : module->DependsOnModules())
    {
        if (project->GetModule(dependsOnModule->Name()))
        {
            if (dependsOnModule->FileId() != -1)
            {
                if (visited.find(dependsOnModule->FileId()) == visited.cend())
                {
                    visited.insert(dependsOnModule->FileId());
                    auto rv = Visit(dependsOnModule->FileId(), project, topologicalOrder, visited);
                    if (!rv) return rv;
                }
            }
        }
    }
    visited.insert(fileId);
    topologicalOrder.push_back(fileId);
    return std::expected<bool, int>(true);
}

std::expected<std::vector<std::int32_t>, int> MakeTopologicalOrder(const std::vector<std::int32_t>& files, Project* project)
{
    std::set<std::int32_t> visited;
    std::vector<std::int32_t> topologicalOrder;
    for (std::int32_t file : files)
    {
        if (visited.find(file) == visited.cend())
        {
            auto rv = Visit(file, project, topologicalOrder, visited);
            if (!rv) return std::unexpected<int>(rv.error());
        }
    }
    return std::expected<std::vector<std::int32_t>, int>(topologicalOrder);
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
    if (!Valid()) return;
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
    if (!Valid()) return;
    module.reset(new otava::symbols::Module(project->Name() + "." + fileName));
    auto rv = module->Init();
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    module->SetFileId(file);
    if (node.Unit())
    {
        node.Unit()->Accept(*this);
        if (!Valid()) return;
    }
}

void ModuleDependencyVisitor::Visit(otava::ast::ExportDeclarationNode& node)
{
    if (!Valid()) return;
    if (node.Subject() && node.Subject()->IsImportDeclarationNode())
    {
        expimp = true;
        node.Subject()->Accept(*this);
        if (!Valid()) return;
        expimp = false;
    }
}

void ModuleDependencyVisitor::Visit(otava::ast::ImportDeclarationNode& node)
{
    if (!Valid()) return;
    if (!expimp)
    {
        imp = true;
    }
    node.Subject()->Accept(*this);
    if (!Valid()) return;
    imp = false;
}

void ModuleDependencyVisitor::Visit(otava::ast::ModuleNameNode& node)
{
    if (!Valid()) return;
    if (exp)
    {
        auto s = util::ToUtf8(node.Str());
        if (!s)
        {
            SetError(s.error());
            return;
        }
        std::string moduleName = std::move(*s);
        module.reset(new otava::symbols::Module(moduleName));
        if (moduleName != "std.type.fundamental")
        {
            module->AddImportModuleName("std.type.fundamental");
        }
        auto rv = module->Init();
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        module->SetFileId(file);
    }
    else if (expimp && module.get())
    {
        auto e = util::ToUtf8(node.Str());
        if (!e)
        {
            SetError(e.error());
            return;
        }
        module->AddExportModuleName(std::move(*e));
    }
    else if (imp && module.get())
    {
        auto i = util::ToUtf8(node.Str());
        if (!i)
        {
            SetError(i.error());
            return;
        }
        module->AddImportModuleName(std::move(*i));
    }
    else if (implementation)
    {
        auto s = util::ToUtf8(node.Str());
        if (!s)
        {
            SetError(s.error());
            return;
        }
        interfaceUnitName = std::move(*s);
        module.reset(new otava::symbols::Module(*s + ".cpp"));
        module->AddImportModuleName("std.type.fundamental");
        module->AddImportModuleName(*s);
    }
}

std::expected<bool, int> ScanDependencies(Project* project, std::int32_t fileId, bool implementationUnit, std::string& interfaceUnitName)
{
    std::string filePath = project->GetFileMap().GetFilePath(fileId);
    std::string fileName = util::Path::GetFileNameWithoutExtension(filePath);
    auto s = util::ReadFile(filePath);
    if (!s) return std::unexpected<int>(s.error());
    std::string fileContent = std::move(*s);
    auto u = util::ToUtf32(fileContent);
    if (!u) return std::unexpected<int>(u.error());
    std::u32string content = std::move(*u);
    auto lxr = otava::lexer::MakeLexer(content.c_str(), content.c_str() + content.length(), filePath);
    if (!lxr) return std::unexpected<int>(lxr.error());
    auto& lexer = *lxr;
    lexer.SetFile(fileId);
    lexer.SetRuleNameMapPtr(otava::parser::rules::GetRuleNameMapPtr());
    otava::symbols::Context context;
    context.SetLexer(&lexer);
    using LexerType = otava::lexer::OtavaLexer<char32_t>;
    std::expected<std::unique_ptr<otava::ast::Node>, int> n = otava::parser::module_dependency::ModuleDependencyParser<LexerType>::Parse(lexer, &context);
    if (!n) return std::unexpected<int>(n.error());
    std::unique_ptr<otava::ast::Node> node = std::move(*n);
    project->GetFileMap().AddFileContent(fileId, std::move(content), lexer.GetLineStartIndeces());
    ModuleDependencyVisitor visitor(fileId, project, fileName, implementationUnit);
    node->Accept(visitor);
    project->SetModule(fileId, visitor.GetModule());
    interfaceUnitName = visitor.InterfaceUnitName();
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ReadFilesFile(const std::string& projectFilesPath, soul::lexer::FileMap& fileMap)
{
    util::FileStream filesFile(projectFilesPath, util::OpenMode::read | util::OpenMode::binary);
    if (!filesFile) return std::unexpected<int>(util::AllocateError("could not open file '" + projectFilesPath + "'"));
    util::BufferedStream filesBufStream(filesFile);
    util::BinaryStreamReader filesReader(filesBufStream);
    std::expected<std::int32_t, int> i = filesReader.ReadInt();
    if (!i) return std::unexpected<int>(i.error());
    std::int32_t fileCount = *i;
    for (std::int32_t i = 0; i < fileCount; ++i)
    {
        std::expected<std::int32_t, int> f = filesReader.ReadInt();
        if (!f) return std::unexpected<int>(f.error());
        std::int32_t fileId = *f;
        std::expected<std::string, int> s = filesReader.ReadUtf8String();
        if (!s) return std::unexpected<int>(s.error());
        std::string filePath = std::move(*s);
        fileMap.MapFile(filePath, fileId);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> WriteFilesFile(const std::string& projectFilesPath, const std::vector<std::pair<std::int32_t, std::string>>& files)
{
    util::FileStream filesFile(projectFilesPath, util::OpenMode::write | util::OpenMode::binary);
    if (!filesFile) return std::unexpected<int>(util::AllocateError("could not create file '" + projectFilesPath + "'"));
    util::BufferedStream filesBufStream(filesFile);
    util::BinaryStreamWriter filesWriter(filesBufStream);
    std::int32_t fileCount = files.size();
    auto rv = filesWriter.Write(fileCount);
    if (!rv) return rv;
    for (const auto& file : files)
    {
        rv = filesWriter.Write(file.first);
        if (!rv) return rv;
        rv = filesWriter.Write(file.second);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BuildSequentially(Project* project, const std::string& config, int optLevel, BuildFlags flags)
{
    otava::symbols::SetProjectReady(false);
    std::expected<std::string, int> moduleDirPathRv = otava::symbols::MakeModuleDirPath(
        project->Root(), config, otava::symbols::GetOptLevel(optLevel, config == "release"));
    if (!moduleDirPathRv) return std::unexpected<int>(moduleDirPathRv.error());
    std::string moduleDirPath = *moduleDirPathRv;
    util::uuid projectId = otava::symbols::MakeProjectId(project->Name());
    if ((flags & BuildFlags::seed) != BuildFlags::none)
    {
        std::uint64_t seed = std::hash<std::string>()(project->FilePath());
        ort_reset_rng();
        ort_set_random_seed(seed);
    }
    otava::symbols::ModuleMapper* prevModuleMapper = otava::symbols::GetModuleMapper();
    otava::symbols::ModuleMapper moduleMapper;
    otava::symbols::SetModuleMapper(&moduleMapper);
    otava::symbols::InstantiationQueue instantiationQueue;
    std::string projectFilePath;
    std::string outputFilePath;
    if (config == "release")
    {
        auto fp = util::GetFullPath(util::Path::Combine(util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(project->FilePath()), config),
            std::to_string(otava::symbols::GetOptLevel(optLevel, true))), project->Name() + ".vcxproj"));
        if (!fp) return std::unexpected<int>(fp.error());
        projectFilePath = *fp;
        fp = util::GetFullPath(util::Path::Combine(util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(project->FilePath()), config),
            std::to_string(otava::symbols::GetOptLevel(optLevel, true))), project->Name()));
        if (!fp) return std::unexpected<int>(fp.error());
        outputFilePath = *fp;
    }
    else
    {
        auto fp = util::GetFullPath(util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(project->FilePath()), config),
            project->Name() + ".vcxproj"));
        if (!fp) return std::unexpected<int>(fp.error());
        projectFilePath = *fp;
        fp = util::GetFullPath(util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(project->FilePath()), config),
            project->Name()));
        if (!fp) return std::unexpected<int>(fp.error());
        outputFilePath = *fp;
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
    moduleMapper.SetFunctionDefinitionSymbolSet(project->GetFunctionDefinitionSymbolSet());
    std::string libraryDirs;
    std::string mainFunctionIrName;
    int mainFunctionParams = 0;
    std::string cppFileName = "__main__.cpp";
    if (project->GetTarget() == Target::program)
    {
        cppFileNames.push_back(cppFileName);
        auto sr = util::SoulRoot();
        if (!sr) return std::unexpected<int>(sr.error());
        std::string soulRoot = std::move(*sr);
        auto fp = util::GetFullPath(util::Path::Combine(soulRoot, "lib"));
        if (!fp) return std::unexpected<int>(fp.error());
        libraryDirs = *fp;
        if (config == "release")
        {
            fp = util::GetFullPath(util::Path::Combine(util::Path::Combine(util::Path::Combine(soulRoot, "tools/otava/std"), config),
                std::to_string(otava::symbols::GetOptLevel(optLevel, true))));
            if (!fp) return std::unexpected<int>(fp.error());
            libraryDirs.append(";").append(*fp);
            fp = util::GetFullPath(util::Path::Combine(soulRoot, "tools/otava/lib"));
            if (!fp) return std::unexpected<int>(fp.error());
            libraryDirs.append(";").append(*fp);
        }
        else
        {
            fp = util::GetFullPath(util::Path::Combine(util::Path::Combine(soulRoot, "tools/otava/std"), config));
            if (!fp) return std::unexpected<int>(fp.error());
            libraryDirs.append(";").append(*fp);
            fp = util::GetFullPath(util::Path::Combine(soulRoot, "tools/otava/lib"));
            if (!fp) return std::unexpected<int>(fp.error());
            libraryDirs.append(";").append(*fp);
        }
    }
    auto rv = project->AddRoots(moduleMapper);
    if (!rv) return rv;
    otava::symbols::Module projectModule(project->Name() + ".#project");
    projectModule.SetProjectId(projectId);
    projectModule.SetImportIndex(importIndex);
    otava::ast::SetNodeIdFactory(projectModule.GetNodeIdFactory());
    projectModule.GetSymbolTable()->SetSymbolMap(moduleMapper.GetSymbolMap());
    projectModule.GetNodeIdFactory()->SetModuleId(projectModule.Id());
    std::map<std::string, std::vector<std::string>> implementationNameMap;
    rv = project->InitModules();
    if (!rv) return rv;
    otava::symbols::SetCurrentModule(nullptr);
    if (!project->Scanned())
    {
        project->SetScanned();
        for (std::int32_t file : project->InterfaceFiles())
        {
            const std::string& filePath = project->GetFileMap().GetFilePath(file);
            std::string interfaceUnitName;
            auto rv = ScanDependencies(project, file, false, interfaceUnitName);
            if (!rv) return rv;
            auto m = project->GetModule(file);
            if (!m) return std::unexpected<int>(m.error());
            otava::symbols::Module* interfaceModule = *m;
            interfaceModule->SetFilePath(filePath);
            interfaceModule->SetKind(otava::symbols::ModuleKind::interfaceModule);
            interfaceModule->SetProjectId(projectId);
        }
        for (std::int32_t file : project->SourceFiles())
        {
            const std::string& filePath = project->GetFileMap().GetFilePath(file);
            std::string interfaceUnitName;
            auto rv = ScanDependencies(project, file, true, interfaceUnitName);
            if (!rv) return rv;
            auto m = project->GetModule(file);
            if (!m) return std::unexpected<int>(m.error());
            otava::symbols::Module* implementationModule = *m;
            implementationModule->SetFilePath(filePath);
            implementationModule->SetKind(otava::symbols::ModuleKind::implementationModule);
            implementationModule->SetProjectId(projectId);
            implementationNameMap[interfaceUnitName].push_back(implementationModule->Name());
        }
    }
    if (project->Name() != "std")
    {
        std::expected<std::string, int> p = moduleMapper.GetProjectFilePath("std");
        if (!p) return std::unexpected<int>(p.error());
        std::string stdProjectPath = *p;
        if (!stdProjectPath.empty())
        {
            project->AddReferenceFilePath(stdProjectPath);
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("'std.project' not found"));
        }
    }
    for (const auto& path : project->ReferenceFilePaths())
    {
        auto fp = util::GetFullPath(util::Path::Combine(project->Root(), path));
        if (!fp) return std::unexpected<int>(fp.error());
        std::string projectFilePath = *fp;
        std::expected<std::unique_ptr<Project>, int> pf = otava::build::ParseProjectFile(projectFilePath);
        if (!pf) return std::unexpected<int>(pf.error());
        std::unique_ptr<Project> projectReference = std::move(*pf);
        std::string outputFilePath;
        if (config == "release")
        {
            fp = util::GetFullPath(util::Path::Combine(util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(projectReference->FilePath()),
                config), std::to_string(otava::symbols::GetOptLevel(optLevel, true))), projectReference->Name()));
            if (!fp) return std::unexpected<int>(fp.error());
            outputFilePath = *fp;
        }
        else
        {
            fp = util::GetFullPath(util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(projectReference->FilePath()), config),
                projectReference->Name()));
            if (!fp) return std::unexpected<int>(fp.error());
            outputFilePath = *fp;
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
        int error = 0;
        if (project->UpToDate(config, optLevel, error))
        {
            if (error != 0)
            {
                return std::unexpected<int>(error);
            }
            if ((flags & BuildFlags::verbose) != BuildFlags::none)
            {
                std::cout << "> project '" << project->Name() << "' is up-to-date" << "\n";
            }
            return std::expected<bool, int>(true);
        }
        if (error != 0)
        {
            return std::unexpected<int>(error);
        }
    }
    if ((flags & BuildFlags::verbose) != BuildFlags::none)
    {
        std::cout << "> building project '" << project->Name() << "'..." << "\n";
    }
    rv = project->LoadModules(moduleMapper, config, optLevel);
    if (!rv) return rv;
    importIndex = moduleMapper.ModuleCount();
    if (project->GetTarget() == Target::program)
    {
        for (const auto& referenceFilePath : project->ReferenceFilePaths())
        {
            auto fp = util::GetFullPath(
                util::Path::Combine(project->Root(), util::Path::Combine(util::Path::GetDirectoryName(referenceFilePath), "cu.init")));
            if (!fp) return std::unexpected<int>(fp.error());
            std::string cuInitFileName = std::move(*fp);
            util::FileStream cuInitFile(cuInitFileName, util::OpenMode::read | util::OpenMode::binary);
            if (!cuInitFile) return std::unexpected<int>(util::AllocateError("could not open file '" + cuInitFileName + "'"));
            util::BinaryStreamReader reader(cuInitFile);
            auto i = reader.ReadInt();
            if (!i) return std::unexpected<int>(i.error());
            int n = *i;
            for (int i = 0; i < n; ++i)
            {
                auto s = reader.ReadUtf8String();
                if (!s) return std::unexpected<int>(s.error());
                std::string compileUnitInitFunctionName = std::move(*s);
                allCompileUnitInitFunctionNames.push_back(std::move(compileUnitInitFunctionName));
            }
        }
    }
    for (Project* reference : project->ReferencedProjects())
    {
        auto fp = util::GetFullPath(util::Path::Combine(reference->Root(), reference->Name() + ".files"));
        if (!fp) return std::unexpected<int>(fp.error());
        std::string referenceFilesPath = std::move(*fp);
        rv = ReadFilesFile(referenceFilesPath, project->GetFileMap());
        if (!rv) return rv;
    }
    std::vector<std::pair<std::int32_t, std::string>> files;
    std::expected<std::vector<std::int32_t>, int> tp = MakeTopologicalOrder(project->InterfaceFiles(), project);
    if (!tp) return std::unexpected<int>(tp.error());
    std::vector<std::int32_t> topologicalOrder = std::move(*tp);
    for (std::int32_t file : topologicalOrder)
    {
        const std::string& filePath = project->GetFileMap().GetFilePath(file);
        std::cout << "> " << filePath << "\n";
        files.push_back(std::make_pair(file, filePath));
        std::expected<std::pair<std::u32string, std::vector<int>>*, int> fc = project->GetFileMap().GetFileContent(file);
        if (!fc) return std::unexpected<int>(fc.error());
        auto* p = *fc;
        std::u32string fileContent = std::move(p->first);
        auto l = otava::lexer::MakeLexer(fileContent.c_str(), fileContent.c_str() + fileContent.length(), filePath);
        if (!l) return std::unexpected<int>(l.error());
        auto& lxr = *l;
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
        lxr.SetRuleNameMapPtr(otava::parser::rules::GetRuleNameMapPtr());
        otava::symbols::Context context;
        otava::symbols::Emitter emitter;
        context.SetEmitter(&emitter);
        if (config == "release")
        {
            context.SetReleaseConfig();
        }
        if (!context.ReleaseConfig())
        {
            context.SetTraceInfo(&project->GetTraceInfo());
        }
        context.SetOptLevel(optLevel);
        context.SetFileMap(&project->GetFileMap());
        context.SetInstantiationQueue(&instantiationQueue);
        context.SetFunctionDefinitionSymbolSet(moduleMapper.GetFunctionDefinitionSymbolSet());
        std::string compileUnitId = "compile_unit_" + util::GetSha1MessageDigest(filePath);
        context.GetBoundCompileUnit()->SetId(compileUnitId);
        std::expected<otava::symbols::Module*, int> m = project->GetModule(file);
        if (!m) return std::unexpected<int>(m.error());
        otava::symbols::Module* module = *m;
        module->SetImportIndex(importIndex++);
        module->GetNodeIdFactory()->SetModuleId(module->Id());
        module->SetFilePath(filePath);
        otava::symbols::SetCurrentModule(module);
        otava::ast::SetNodeIdFactory(module->GetNodeIdFactory());
        module->GetSymbolTable()->SetSymbolMap(moduleMapper.GetSymbolMap());
        auto rv = module->Import(moduleMapper, config, optLevel);
        if (!rv) return rv;
        module->GetSymbolTable()->ResolveForwardDeclarations();
        context.SetLexer(&lxr);
        context.SetSymbolTable(module->GetSymbolTable());
        using LexerType = soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>;
        std::expected<std::unique_ptr<otava::ast::Node>, int> n = otava::parser::translation::unit::TranslationUnitParser<LexerType>::Parse(lxr, &context);
        if (!n) return std::unexpected<int>(n.error());
        std::unique_ptr<otava::ast::Node> node = std::move(*n);
        rv = otava::symbols::GenerateDestructors(context.GetBoundCompileUnit(), &context);
        if (!rv) return rv;
        if ((flags & BuildFlags::xml) != BuildFlags::none)
        {
            std::string xmlFilePath = filePath + ".ast.xml";
            rv = otava::ast::WriteXml(node.get(), xmlFilePath);
            if (!rv) return rv;
        }
        module->SetFile(new otava::ast::File(util::Path::GetFileName(filePath), node.release()));
        module->SetImplementationUnitNames(implementationNameMap[module->Name()]);
        //projectModule.Import(module, moduleMapper, config, optLevel); TODO
        //project->Index().imp(module->GetSymbolTable()->ClassIndex(), true); TODO
        if ((flags & BuildFlags::symbolXml) != BuildFlags::none)
        {
            std::string dirPath;
            if (config == "release")
            {
                dirPath = util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(module->FilePath()), config),
                    std::to_string(otava::symbols::GetOptLevel(optLevel, true)));
            }
            else
            {
                dirPath = util::Path::Combine(util::Path::GetDirectoryName(module->FilePath()), config);
            }
            std::filesystem::path p(dirPath);
            std::filesystem::create_directories(p);
            std::string xmlFilePath;
            if (config == "release")
            {
                xmlFilePath = util::Path::Combine(util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(module->FilePath()), config),
                    std::to_string(otava::symbols::GetOptLevel(optLevel, true))), util::Path::GetFileName(module->FilePath()) + ".xml");
            }
            else
            {
                xmlFilePath = util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(module->FilePath()), config),
                    util::Path::GetFileName(module->FilePath()) + ".xml");
            }
            rv = module->ToXml(xmlFilePath);
            if (!rv) return rv;
        }
        m = project->ReleaseModule(file);
        if (!m) return std::unexpected<int>(m.error());
        otava::symbols::Module* mod = std::move(*m);
        moduleMapper.AddModule(mod);
        auto a = otava::codegen::GenerateCode(
            context, config, optLevel, (flags & BuildFlags::verbose) != BuildFlags::none, mainFunctionIrName, mainFunctionParams, false, std::vector<std::string>());
        if (!a) return std::unexpected<int>(a.error());
        std::string asmFileName = std::move(*a);
        project->Index().import(module->GetSymbolTable()->ClassIndex());
        rv = module->Write(project->Root(), config, optLevel, &context);
        if (!rv) return rv;
        if ((flags & BuildFlags::verbose) != BuildFlags::none)
        {
            std::expected<std::string, int> moduleFilePath = otava::symbols::MakeModuleFilePath(project->Root(), config, optLevel, module->Name());
            if (!moduleFilePath) return std::unexpected<int>(moduleFilePath.error());
            std::cout << filePath << " -> " << *moduleFilePath << std::endl;
        }
        asmFileNames.push_back(asmFileName);
        otava::symbols::BoundFunctionNode* initFn = context.GetBoundCompileUnit()->GetCompileUnitInitializationFunction();
        if (initFn)
        {
            auto irn = initFn->GetFunctionDefinitionSymbol()->IrName(&context);
            if (!irn) return std::unexpected<int>(irn.error());
            std::string irName = std::move(*irn);
            compileUnitInitFunctionNames.push_back(std::move(irName));
        }
        totalFunctionsCompiled += context.TotalFunctionsCompiled();
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
        auto rv = ScanDependencies(project, file, true, interfaceUnitName);
        if (!rv) return rv;;
        const std::string& filePath = project->GetFileMap().GetFilePath(file);
        std::cout << "> " << filePath << "\n";
        files.push_back(std::make_pair(file, filePath));
        std::expected<std::pair<std::u32string, std::vector<int>>*, int> fc = project->GetFileMap().GetFileContent(file);
        if (!fc) return std::unexpected<int>(fc.error());
        auto* p = *fc;
        std::u32string fileContent = std::move(p->first);
        auto l = otava::lexer::MakeLexer(fileContent.c_str(), fileContent.c_str() + fileContent.length(), filePath);
        if (!l) return std::unexpected<int>(l.error());
        auto& lxr = *l;
        lxr.SetPPHook(otava::pp::PreprocessPPLine);
        otava::pp::state::State* state = otava::pp::state::LexerStateMap::Instance().GetState(&lxr);
        for (const auto& define : project->Defines())
        {
            state->Define(define.symbol, define.value);
        }
        lxr.SetFile(file);
        lxr.SetRuleNameMapPtr(otava::parser::rules::GetRuleNameMapPtr());
        otava::symbols::Emitter emitter;
        otava::symbols::Context context;
        context.SetEmitter(&emitter);
        if (config == "release")
        {
            context.SetReleaseConfig();
        }
        if (!context.ReleaseConfig())
        {
            context.SetTraceInfo(&project->GetTraceInfo());
        }
        context.SetOptLevel(optLevel);
        context.SetFileMap(&project->GetFileMap());
        context.SetInstantiationQueue(&instantiationQueue);
        context.SetFunctionDefinitionSymbolSet(moduleMapper.GetFunctionDefinitionSymbolSet());
        std::string compileUnitId = "compile_unit_" + util::GetSha1MessageDigest(filePath);
        context.GetBoundCompileUnit()->SetId(compileUnitId);
        auto m = project->GetModule(file);
        if (!m) return std::unexpected<int>(m.error());
        otava::symbols::Module* module = *m;
        module->SetKind(otava::symbols::ModuleKind::implementationModule);
        module->SetImportIndex(importIndex++);
        module->GetNodeIdFactory()->SetModuleId(module->Id());
        module->SetFilePath(filePath);
        otava::symbols::SetCurrentModule(module);
        otava::ast::SetNodeIdFactory(module->GetNodeIdFactory());
        module->GetSymbolTable()->SetSymbolMap(moduleMapper.GetSymbolMap());
        rv = module->Import(moduleMapper, config, optLevel);
        if (!rv) return rv;
        module->GetSymbolTable()->ResolveForwardDeclarations();
        context.SetLexer(&lxr);
        context.SetSymbolTable(module->GetSymbolTable());
        using LexerType = soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>;
        std::expected<std::unique_ptr<otava::ast::Node>, int> n = otava::parser::translation::unit::TranslationUnitParser<LexerType>::Parse(lxr, &context);
        if (!n) return std::unexpected<int>(n.error());
        std::unique_ptr<otava::ast::Node> node = std::move(*n);
        rv = otava::symbols::GenerateDestructors(context.GetBoundCompileUnit(), &context);
        if (!rv) return rv;
        if ((flags & BuildFlags::xml) != BuildFlags::none)
        {
            std::string xmlFilePath = filePath + ".ast.xml";
            rv = otava::ast::WriteXml(node.get(), xmlFilePath);
            if (!rv) return rv;
        }
        module->SetFile(new otava::ast::File(util::Path::GetFileName(filePath), node.release()));
        if (!interfaceUnitName.empty())
        {
            m = moduleMapper.GetModule(interfaceUnitName, config, optLevel);
            if (!m) return std::unexpected<int>(m.error());
            otava::symbols::Module* interfaceUnitModule = *m;
            interfaceUnitModule->AddImplementationUnit(module);
            m = project->ReleaseModule(file);
            if (!m) return std::unexpected<int>(m.error());
            otava::symbols::Module* mod = *m;
            moduleMapper.AddModule(mod);
        }
        auto a = otava::codegen::GenerateCode(
            context, config, optLevel, (flags & BuildFlags::verbose) != BuildFlags::none, mainFunctionIrName, mainFunctionParams, false, std::vector<std::string>());
        if (!a) return std::unexpected<int>(a.error());
        std::string asmFileName = std::move(*a);
        asmFileNames.push_back(asmFileName);
        project->Index().import(module->GetSymbolTable()->ClassIndex());
        otava::symbols::BoundFunctionNode* initFn = context.GetBoundCompileUnit()->GetCompileUnitInitializationFunction();
        if (initFn)
        {
            auto irn = initFn->GetFunctionDefinitionSymbol()->IrName(&context);
            if (!irn) return std::unexpected<int>(irn.error());
            std::string irName = std::move(*irn);
            compileUnitInitFunctionNames.push_back(std::move(irName));
        }
        totalFunctionsCompiled += context.TotalFunctionsCompiled();
        if (context.ReleaseConfig() && otava::optimizer::HasOptimization(otava::optimizer::Optimizations::inlining))
        {
            inliningEnabled = true;
            functionsInlined += context.FunctionsInlined();
            functionCallsInlined += context.FunctionCallsInlined();
        }
    }
    projectModule.AddDerivedClasses();
    ProjectTarget projectTarget = ProjectTarget::library;
    std::string classIndexFilePath;
    std::string traceBinPath;
    if (project->GetTarget() == Target::program)
    {
        if (mainFunctionIrName.empty())
        {
            return std::unexpected<int>(util::AllocateError("program has no main function"));
        }
        for (const auto& fileName : compileUnitInitFunctionNames)
        {
            allCompileUnitInitFunctionNames.push_back(fileName);
        }
        std::expected<std::string, int> m = GenerateMainUnit(moduleMapper, util::Path::Combine(util::Path::GetDirectoryName(projectFilePath), cppFileName),
            mainFunctionIrName, mainFunctionParams, allCompileUnitInitFunctionNames, config, optLevel);
        if (!m) return std::unexpected<int>(m.error());
        std::string mainAsmFileName = std::move(*m);
        asmFileNames.push_back(std::move(mainAsmFileName));
        projectTarget = ProjectTarget::program;
        otava::symbols::TraceBin traceBin;
        for (Project* referencedProject : project->ReferencedProjects())
        {
            std::expected<std::string, int> srv = otava::symbols::MakeModuleDirPath(
                referencedProject->Root(), config, otava::symbols::GetOptLevel(optLevel, config == "release"));
            if (!srv) return std::unexpected<int>(srv.error());
            std::string moduleDirPath = *srv;
            rv = referencedProject->ReadTraceInfo(moduleDirPath);
            if (!rv) return rv;
            if (config != "release")
            {
                traceBin.Import(referencedProject->GetTraceInfo());
            }
            rv = referencedProject->ReadClassIndex(moduleDirPath);
            if (!rv) return rv;
            project->Index().import(referencedProject->Index());
        }
        if (config != "release")
        {
            traceBin.Import(project->GetTraceInfo());
            std::expected<std::string, int> srv = util::GetFullPath(util::Path::Combine(moduleDirPath, "trace.bin"));
            if (!srv) return std::unexpected<int>(srv.error());
            traceBinPath = *srv;
            rv = otava::symbols::WriteTraceBin(traceBin, traceBinPath);
            if (!rv) return rv;
        }
        std::expected<std::string, int> srv = util::GetFullPath(util::Path::Combine(moduleDirPath, "class_index.bin"));
        if (!srv) return std::unexpected<int>(srv.error());
        classIndexFilePath = *srv;
        rv = WriteClassIndex(classIndexFilePath, project->Index());
        if (!rv) return rv;
    }
    else
    {
        std::string compileUnitInitFileName = util::Path::Combine(project->Root(), "cu.init");
        util::FileStream compileUnitInitFile(compileUnitInitFileName, util::OpenMode::write | util::OpenMode::binary);
        if (!compileUnitInitFile) return std::unexpected<int>(util::AllocateError("could not create file '" + compileUnitInitFileName + "'"));
        util::BinaryStreamWriter writer(compileUnitInitFile);
        std::int32_t n = compileUnitInitFunctionNames.size();
        rv = writer.Write(n);
        if (!rv) return rv;
        for (const auto& fileName : compileUnitInitFunctionNames)
        {
            rv = writer.Write(fileName);
            if (!rv) return rv;
        }
    }
    for (const auto& resourceFilePath : project->ResourceFilePaths())
    {
        auto fp = util::GetFullPath(util::Path::Combine(project->Root(), resourceFilePath));
        if (!fp) return std::unexpected<int>(fp.error());
        std::string absoluteRCFilePath = std::move(*fp);
        resourceFileNames.push_back(std::move(absoluteRCFilePath));
    }
    if ((flags & BuildFlags::verbose) != BuildFlags::none)
    {
        std::cout << totalFunctionsCompiled << " functions compiled\n";
        if (inliningEnabled)
        {
            std::cout << functionCallsInlined << " function calls inlined in " << functionsInlined << " functions\n";
        }
    }
    rv = MakeProjectFile(project, projectFilePath, asmFileNames, cppFileNames, resourceFileNames,
        libraryDirs, project->ReferencedProjects(), config, optLevel, classIndexFilePath, traceBinPath, projectTarget, (flags & BuildFlags::verbose) != BuildFlags::none);
    if (!rv) return rv;
    rv = MSBuild(projectFilePath, config);
    if (!rv) return rv;
    auto fp = util::GetFullPath(util::Path::Combine(project->Root(), project->Name() + ".files"));
    if (!fp) return std::unexpected<int>(fp.error());
    std::string projectFilesPath = std::move(*fp);
    rv = WriteFilesFile(projectFilesPath, files);
    if (!rv) return rv;
    if ((flags & BuildFlags::verbose) != BuildFlags::none)
    {
        std::cout << "project '" << project->Name() << "' built successfully" << std::endl;
    }
    otava::symbols::SetModuleMapper(prevModuleMapper);
    otava::symbols::SetProjectReady(true);
    return std::expected<bool, int>(true);
}

std::expected<otava::symbols::Module*, int> GetModule(otava::symbols::ModuleMapper& moduleMapper, const std::string& moduleName, const std::string& config, int optLevel)
{
    return moduleMapper.GetModule(moduleName, config, optLevel);
}

std::expected<bool, int> Visit(Solution* solution, Project* project, std::vector<Project*>& topologicalOrder, std::set<Project*>& visited)
{
    for (const std::string& path : project->ReferenceFilePaths())
    {
        auto fp = util::GetFullPath(util::Path::Combine(project->Root(), path));
        if (!fp) return std::unexpected<int>(fp.error());
        std::string referenceFilePath = std::move(*fp);
        Project* dependsOnProject = solution->GetProject(referenceFilePath);
        if (dependsOnProject)
        {
            if (visited.find(dependsOnProject) == visited.cend())
            {
                visited.insert(dependsOnProject);
                auto rv = Visit(solution, dependsOnProject, topologicalOrder, visited);
                if (!rv) return rv;
            }
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("reference file path '" + referenceFilePath + "' in solution '" + solution->FilePath() + "' not found"));
        }
    }
    visited.insert(project);
    topologicalOrder.push_back(project);
    return std::expected<bool, int>(true);
}

std::expected<std::vector<Project*>, int> MakeTopologicalOrder(Solution* solution)
{
    std::set<Project*> visited;
    std::vector<Project*> topologicalOrder;
    for (Project* project : solution->Projects())
    {
        if (visited.find(project) == visited.cend())
        {
            auto rv = Visit(solution, project, topologicalOrder, visited);
            if (!rv) return std::unexpected<int>(rv.error());
        }
    }
    return std::expected<std::vector<Project*>, int>(std::move(topologicalOrder));
}

std::expected<bool, int> BuildSequentially(soul::lexer::FileMap& fileMap, Solution* solution, const std::string& config, int optLevel, BuildFlags flags,
    std::set<Project*, ProjectLess>& projectSet)
{
    if ((flags & BuildFlags::verbose) != BuildFlags::none)
    {
        if (solution->IsProjectSolution())
        {
            std::cout << "> building project '" << solution->Name() << "' with dependencies..." << std::endl;
        }
        else
        {
            std::cout << "> building solution '" << solution->Name() << "'..." << std::endl;
        }
    }
    if (!solution->IsProjectSolution())
    {
        std::string root = util::Path::GetDirectoryName(solution->FilePath());
        for (const auto& path : solution->ProjectFilePaths())
        {
            auto fp = util::GetFullPath(util::Path::Combine(root, path));
            if (!fp) return std::unexpected<int>(fp.error());
            std::string projectFilePath = std::move(*fp);
            std::expected<std::unique_ptr<Project>, int> pf = otava::build::ParseProjectFile(projectFilePath);
            if (!pf) return std::unexpected<int>(pf.error());
            std::unique_ptr<Project> project = std::move(*pf);
            project->SetFileMap(&fileMap);
            solution->AddProject(project.release());
        }
    }
    std::expected<std::vector<Project*>, int> tp = MakeTopologicalOrder(solution);
    if (!tp) return std::unexpected<int>(tp.error());
    std::vector<Project*> buildOrder = std::move(*tp);
    for (Project* project : buildOrder)
    {
        auto rv = Build(fileMap, project, config, optLevel, flags & ~BuildFlags::all, projectSet);
        if (!rv) return rv;
    }
    if ((flags & BuildFlags::verbose) != BuildFlags::none)
    {
        if (!solution->IsProjectSolution())
        {
            std::cout << "solution '" << solution->Name() << "' built successfully" << std::endl;
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ProjectClosure(soul::lexer::FileMap& fileMap, Project* project, Solution* solution, std::set<std::string>& projectFilePaths)
{
    std::string root = util::Path::GetDirectoryName(project->FilePath());
    for (const auto& referenceFilePath : project->ReferenceFilePaths())
    {
        auto fp = util::GetFullPath(util::Path::Combine(root, referenceFilePath));
        if (!fp) return std::unexpected<int>(fp.error());
        std::string projectFilePath = std::move(*fp);
        if (projectFilePaths.find(projectFilePath) != projectFilePaths.end()) continue;
        projectFilePaths.insert(projectFilePath);
        std::expected<std::unique_ptr<Project>, int> pf = otava::build::ParseProjectFile(projectFilePath);
        if (!pf) return std::unexpected<int>(pf.error());
        std::unique_ptr<Project> referencedProject = std::move(*pf);
        Project* reference = referencedProject.get();
        if (project->Name() != "std" && reference->Name() == "std") continue;
        reference->SetFileMap(&fileMap);
        project->AddReferencedProject(referencedProject.release());
        auto rv = ProjectClosure(fileMap, reference, solution, projectFilePaths);
        if (!rv) return rv;
    }
    solution->AddProject(project, false);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Build(soul::lexer::FileMap& fileMap, Project* project, const std::string& config, int optLevel, BuildFlags flags, 
    std::set<Project*, ProjectLess>& projectSet)
{
    if ((flags & BuildFlags::all) != BuildFlags::none)
    {
        Solution solution(project->FilePath(), project->Name());
        solution.SetProjectSolution();
        std::set<std::string> projectFilePaths;
        auto rv = ProjectClosure(fileMap, project, &solution, projectFilePaths);
        if (!rv) return rv;
        rv = Build(fileMap, &solution, config, optLevel, flags & ~BuildFlags::all, projectSet);
        if (!rv) return rv;
    }
    else
    {
        if (projectSet.find(project) != projectSet.end()) return std::expected<bool, int>(true);
        projectSet.insert(project);
        std::expected<bool, int> rv = BuildSequentially(project, config, optLevel, flags & ~BuildFlags::all);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Build(soul::lexer::FileMap& fileMap, Solution* solution, const std::string& config, int optLevel, BuildFlags flags, 
    std::set<Project*, ProjectLess>& projectSet)
{
    std::expected<bool, int> rv = BuildSequentially(fileMap, solution, config, optLevel, flags & ~BuildFlags::all, projectSet);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

} // namespace otava::build
