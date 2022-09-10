// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module gendoc.project;

import util;
import soul.xml.dom.parser;
import soul.xml.dom;
import soul.xml.xpath.evaluate;
import soul.xml.xpath.object;
import soul.cpp20.symbols;
import soul.cpp20.project.build;
import soul.cpp20.project.parser;
import soul.cpp20.project.build;
import gendoc.module_html_generator;
import gendoc.type_element_generator;
import gendoc.namespace_html_generator;
import gendoc.style;

namespace gendoc {

Project::Project(const std::string& path_, bool verbose_, bool force_, bool multithreaded_, soul::cpp20::project::init::Init& init_) : 
    parent(nullptr), path(path_), verbose(verbose_), force(force_), multithreaded(multithreaded_), generateNamespaceDocs(false), init(init_)
{
    std::string filePath;
    if (path.ends_with(".xml"))
    {
        filePath = util::GetFullPath(path);
    }
    else if (!path.empty())
    {
        filePath = util::GetFullPath(util::Path::Combine(path, "gendoc.xml"));
    }
    else
    {
        filePath = util::GetFullPath("gendoc.xml");
    }
    if (verbose)
    {
        std::cout << "> " << filePath << std::endl;
    }
    std::unique_ptr<soul::xml::Document> doc = soul::xml::ParseXmlFile(filePath);
    std::unique_ptr<soul::xml::xpath::NodeSet> project = soul::xml::xpath::EvaluateToNodeSet("/gendoc/project", doc.get());
    int np = project->Count();
    for (int i = 0; i < np; ++i)
    {
        soul::xml::Node* node = project->GetNode(i);
        if (node->IsElementNode())
        {
            soul::xml::Element* element = static_cast<soul::xml::Element*>(node);
            std::string nameAttr = element->GetAttribute("name");
            if (!nameAttr.empty())
            {
                name = nameAttr;
            }
            else
            {
                throw std::runtime_error("'project' element has no 'name' attribute in '" + filePath + "' at line " + std::to_string(element->GetSourcePos().line));
            }
        }
    }
    std::unique_ptr<soul::xml::xpath::NodeSet> subproject = soul::xml::xpath::EvaluateToNodeSet("/gendoc/subproject", doc.get());
    int ns = subproject->Count();
    for (int i = 0; i < ns; ++i)
    {
        soul::xml::Node* node = subproject->GetNode(i);
        if (node->IsElementNode())
        {
            soul::xml::Element* element = static_cast<soul::xml::Element*>(node);
            std::string pathAttr = element->GetAttribute("path");
            if (!pathAttr.empty())
            {
                std::unique_ptr<Project> subProject(new Project(util::Path::Combine(util::Path::GetDirectoryName(filePath), pathAttr), verbose, force, multithreaded, init));
                subProject->SetParent(this);
                subProjects.push_back(std::move(subProject));
            }
            else
            {
                throw std::runtime_error("'subproject' element has no 'path' attribute in '" + filePath + "' at line " + std::to_string(element->GetSourcePos().line));
            }
        }
    }
    std::unique_ptr<soul::xml::xpath::NodeSet> root = soul::xml::xpath::EvaluateToNodeSet("/gendoc/root", doc.get());
    int nr = root->Count();
    for (int i = 0; i < nr; ++i)
    {
        soul::xml::Node* node = root->GetNode(i);
        if (node->IsElementNode())
        {
            soul::xml::Element* element = static_cast<soul::xml::Element*>(node);
            std::string dirAttr = element->GetAttribute("dir");
            if (!dirAttr.empty())
            {
                rootDir = util::GetFullPath(util::Path::Combine(util::Path::GetDirectoryName(filePath), dirAttr));
            }
            else
            {
                throw std::runtime_error("'root' element has no 'dir' attribute in '" + filePath + "' at line " + std::to_string(element->GetSourcePos().line));
            }
        }
    }
    std::unique_ptr<soul::xml::xpath::NodeSet> cppProject = soul::xml::xpath::EvaluateToNodeSet("/gendoc/cppProject", doc.get());
    int nc = cppProject->Count();
    for (int i = 0; i < nc; ++i)
    {
        soul::xml::Node* node = cppProject->GetNode(i);
        if (node->IsElementNode())
        {
            soul::xml::Element* element = static_cast<soul::xml::Element*>(node);
            std::string filePathAttr = element->GetAttribute("filePath");
            if (!filePathAttr.empty())
            {
                cppProjectFilePath = util::GetFullPath(util::Path::Combine(util::Path::GetDirectoryName(filePath), filePathAttr));
            }
            else
            {
                throw std::runtime_error("'cppProject' element has no 'filePath' attribute in '" + filePath + "' at line " + std::to_string(element->GetSourcePos().line));
            }
        }
    }
    std::unique_ptr<soul::xml::xpath::NodeSet> generateNamespaceDocsResult = soul::xml::xpath::EvaluateToNodeSet("/gendoc/generateNamespaceDocs", doc.get());
    int nnsc = generateNamespaceDocsResult->Count();
    for (int i = 0; i < nnsc; ++i)
    {
        soul::xml::Node* node = generateNamespaceDocsResult->GetNode(i);
        if (node->IsElementNode())
        {
            soul::xml::Element* element = static_cast<soul::xml::Element*>(node);
            std::string valueAttr = element->GetAttribute("value");
            if (valueAttr == "true")
            {
                generateNamespaceDocs = true;
            }
        }
    }
}

std::string Project::FullName() const
{
    std::string fullName;
    if (parent)
    {
        fullName = parent->FullName();
        fullName.append(".").append(name);
    }
    else
    {
        fullName = name;
    }
    return fullName;
}

void Project::Build(Project* nsProject)
{
    if (generateNamespaceDocs)
    {
        nsProject = this;
    }
    for (const auto& subproject : subProjects)
    {
        subproject->Build(nsProject);
    }
    if (verbose)
    {
        std::cout << "> " << FullName() << std::endl;
    }
    BuildCppProject();
    GenerateDocs(nsProject);
    GenerateNamespaceDocs();
    if (verbose)
    {
        std::cout << "documentation generated for project '" + FullName() << "'" << std::endl;
    }
}

void Project::BuildCppProject()
{
    if (cppProjectFilePath.empty()) return;
    project = soul::cpp20::project::parser::ParseProjectFile(cppProjectFilePath);
    init.moduleMapper.AddRoot(project->Root());
    project->AddRoots(init.moduleMapper);
    project->InitModules();
    for (int file : project->InterfaceFiles())
    {
        std::string interfaceUnitName;
        soul::cpp20::project::build::ScanDependencies(project.get(), file, false, interfaceUnitName);
    }
    project->SetScanned();
    project->LoadModules(init.nodeIdFactory, init.moduleMapper, init.symbols);
    bool build = force || !project->UpToDate();
    if (!build)
    {
        project->ResolveForwardDeclarationsAndAddDerivedClasses(init.moduleMapper);
        return;
    }
    soul::cpp20::project::build::BuildFlags flags = soul::cpp20::project::build::BuildFlags::none;
    if (verbose)
    {
        flags = flags | soul::cpp20::project::build::BuildFlags::verbose;
    }
    if (multithreaded)
    {
        flags = flags | soul::cpp20::project::build::BuildFlags::multithreadedBuild;
    }
    soul::cpp20::project::build::Build(init.moduleMapper, project.get(), flags);
}

NamespaceSymbols* Project::GetOrInsertNamespaceSymbols(const std::string& nsDocName, const std::string& namespaceName)
{
    auto it = nsSymbolMap.find(nsDocName);
    if (it != nsSymbolMap.cend())
    {
        return it->second;
    }
    else
    {
        NamespaceSymbols* nss = new NamespaceSymbols(namespaceName);
        nsSymbols.push_back(std::unique_ptr<NamespaceSymbols>(nss));
        nsSymbolMap[nsDocName] = nss;
        return nss;
    }
}

void Project::AddToNamespace(soul::cpp20::symbols::NamespaceSymbol* ns, soul::cpp20::symbols::Symbol* symbol)
{
    NamespaceSymbols* nns = GetOrInsertNamespaceSymbols(ns->DocName(), MakeNsText(ns));
    switch (symbol->Kind())
    {
        case soul::cpp20::symbols::SymbolKind::conceptSymbol:
        {
            nns->concepts.push_back(static_cast<soul::cpp20::symbols::ConceptSymbol*>(symbol));
            break;
        }
        case soul::cpp20::symbols::SymbolKind::aliasTypeSymbol:
        {
            nns->typeAliases.push_back(static_cast<soul::cpp20::symbols::AliasTypeSymbol*>(symbol));
            break;
        }
        case soul::cpp20::symbols::SymbolKind::classTypeSymbol:
        {
            nns->classes.push_back(static_cast<soul::cpp20::symbols::ClassTypeSymbol*>(symbol));
            break;
        }
        case soul::cpp20::symbols::SymbolKind::enumTypeSymbol:
        {
            nns->enumerations.push_back(static_cast<soul::cpp20::symbols::EnumeratedTypeSymbol*>(symbol));
            break;
        }
        case soul::cpp20::symbols::SymbolKind::functionSymbol:
        {
            nns->functions.push_back(static_cast<soul::cpp20::symbols::FunctionSymbol*>(symbol));
            break;
        }
        case soul::cpp20::symbols::SymbolKind::variableSymbol:
        {
            nns->variables.push_back(static_cast<soul::cpp20::symbols::VariableSymbol*>(symbol));
            break;
        }
    }
}

void Project::GenerateDocs(Project* nsProject)
{
    GenerateModuleDocs(nsProject);
}

void Project::GenerateModuleDocs(Project* nsProject)
{
    if (!project) return;;
    for (const auto& moduleName : project->ModuleNames())
    {
        GenerateModuleDoc(moduleName, nsProject);
    }
}

void Project::GenerateModuleDoc(const std::string& moduleName, Project* nsProject)
{
    soul::cpp20::symbols::Module* module = soul::cpp20::project::build::GetModule(init.moduleMapper, moduleName);
    GenerateModuleHtml(rootDir, module, init.moduleMapper, nsProject);
}

void Project::GenerateNamespaceDocs()
{
    if (!generateNamespaceDocs) return;
    for (const auto& p : nsSymbolMap)
    {
        const std::string& nsDocName = p.first;
        NamespaceSymbols* nsSymbols = p.second;
        GenerateNamespaceHtml(rootDir, nsDocName, nsSymbols);
    }
}

void BuildProject(const std::string& path, bool verbose, bool force, bool multithreaded)
{
    soul::cpp20::symbols::Symbols symbols;
    soul::cpp20::symbols::SetSymbols(&symbols);
    soul::cpp20::ast::NodeIdFactory nodeIdFactory;
    soul::cpp20::ast::SetNodeIdFactory(&nodeIdFactory);
    soul::cpp20::project::init::Init init;
    init.SetSymbols(&symbols);
    init.SetNodeIdFactory(&nodeIdFactory);
    Project project(path, verbose, force, multithreaded, init);
    MakeStyleFile(project.RootDir());
    project.Build(nullptr);
}

} // namespace gendoc
