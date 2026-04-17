// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module gendoc.project;

import util;
import soul.xml.dom.parser;
import soul.xml.xpath.evaluate;
import soul.xml.xpath.object;
import otava.ast;
import otava.build;
import gendoc.project_html_generator;
import gendoc.module_html_generator;
import gendoc.type_element_generator;
import gendoc.namespace_html_generator;
import gendoc.style;

namespace gendoc {

void WriteProjectLink(Project* project, soul::xml::Element* tableElement)
{
    if (project->BuildProject())
    {
        soul::xml::Element* trElement = soul::xml::MakeElement("tr");
        tableElement->AppendChild(trElement);
        soul::xml::Element* tdElement = soul::xml::MakeElement("td");
        trElement->AppendChild(tdElement);
        soul::xml::Element* linkElement = soul::xml::MakeElement("a");
        tdElement->AppendChild(linkElement);
        linkElement->SetAttribute("href", "project/" + project->BuildProject()->Name() + "/index.html");
        soul::xml::Text* linkText = soul::xml::MakeText(project->BuildProject()->Name());
        linkElement->AppendChild(linkText);
    }
    for (const auto& subProject : project->SubProjects())
    {
        WriteProjectLink(subProject.get(), tableElement);
    }
}

Project::Project(const std::string& path_, bool verbose_, bool force_, bool multithreaded_, otava::build::Project& init_) : 
    parent(nullptr), path(path_), verbose(verbose_), force(force_), multithreaded(multithreaded_), generateNamespaceDocs(false), init(init_), buildProject(nullptr)
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
    std::unique_ptr<otava::build::Solution> solution(MakeSolution());
    BuildSolution(solution.get());
    GenerateDocs(nsProject);
    GenerateNamespaceDocs();
    if (!parent)
    {
        std::cout << "generating main index..." << "\n";
        GenerateMainIndex();
    }
    std::cout << "documentation generated" << "\n";
}

void AddToSolution(otava::build::Solution* solution, Project* project, soul::lexer::FileMap* fileMap)
{
    if (!project->CppProjectFilePath().empty())
    {
        std::unique_ptr<otava::build::Project> buildProject = otava::build::ParseProjectFile(project->CppProjectFilePath());
        buildProject->SetFileMap(fileMap);
        project->SetBuildProject(buildProject.get());
        solution->AddProject(buildProject.release());
    }
    for (const auto& subproject : project->SubProjects())
    {
        AddToSolution(solution, subproject.get(), fileMap);
    }
}

otava::build::Solution* Project::MakeSolution()
{
    otava::build::Solution* solution = new otava::build::Solution("reference", "reference");
    solution->SetProjectSolution();
    AddToSolution(solution, this, &fileMap);
    return solution;
}

void Project::BuildSolution(otava::build::Solution* solution)
{
    otava::symbols::Context* prevContext = otava::symbols::CurrentContext();
    otava::symbols::Context context;
    otava::symbols::SetCurrentContext(&context);
    context.SetFlag(otava::symbols::ContextFlags::noWarnings);
    context.SetFlag(otava::symbols::ContextFlags::gendoc);
    otava::build::BuildFlags flags = otava::build::BuildFlags::none;
    if (force)
    {
        flags = flags | otava::build::BuildFlags::rebuild;
    }
    flags = flags | otava::build::BuildFlags::gendoc;
    if (verbose)
    {
        flags = flags | otava::build::BuildFlags::verbose;
    }
    if (multithreaded)
    {
        flags = flags | otava::build::BuildFlags::multithreadedBuild;
    }
    otava::build::Build(fileMap, solution, "gendoc", 0, flags, projectSet, &std::cout);
    otava::symbols::SetCurrentContext(prevContext);
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

void Project::AddToNamespace(otava::symbols::NamespaceSymbol* ns, otava::symbols::Symbol* symbol)
{
    NamespaceSymbols* nns = GetOrInsertNamespaceSymbols(ns->DocName(), MakeNsText(ns));
    switch (symbol->Kind())
    {
        case otava::symbols::SymbolKind::conceptSymbol:
        {
            nns->concepts.push_back(static_cast<otava::symbols::ConceptSymbol*>(symbol));
            break;
        }
        case otava::symbols::SymbolKind::aliasTypeSymbol:
        {
            nns->typeAliases.push_back(static_cast<otava::symbols::AliasTypeSymbol*>(symbol));
            break;
        }
        case otava::symbols::SymbolKind::classTypeSymbol:
        {
            nns->classes.push_back(static_cast<otava::symbols::ClassTypeSymbol*>(symbol));
            break;
        }
        case otava::symbols::SymbolKind::enumTypeSymbol:
        {
            nns->enumerations.push_back(static_cast<otava::symbols::EnumeratedTypeSymbol*>(symbol));
            break;
        }
        case otava::symbols::SymbolKind::functionSymbol:
        {
            nns->functions.push_back(static_cast<otava::symbols::FunctionSymbol*>(symbol));
            break;
        }
        case otava::symbols::SymbolKind::variableSymbol:
        {
            nns->variables.push_back(static_cast<otava::symbols::VariableSymbol*>(symbol));
            break;
        }
    }
}

void AddRoots(Project* project)
{
    otava::build::Project* buildProject = project->BuildProject();
    if (buildProject)
    {
        otava::symbols::GetModuleMapper()->AddRoot(buildProject->Root());
    }
    for (const auto& subproject : project->SubProjects())
    {
        AddRoots(subproject.get());
    }
}

void Project::GenerateDocs(Project* nsProject)
{
    AddRoots(this);
    std::cout << "generating project documentation..." << "\n";
    GenerateProjectDocs();
    std::cout << "generating module documentation..." << "\n";
    GenerateModuleDocs(nsProject);
}

void Project::GenerateProjectDocs()
{
    if (buildProject)
    {
        std::cout << "> " << buildProject->Name() << "\n";
        std::vector<otava::symbols::Module*> modules;
        otava::symbols::Context context;
        context.SetFlag(otava::symbols::ContextFlags::gendoc);
        context.SetFlag(otava::symbols::ContextFlags::noWarnings);
        context.SetFunctionDefinitionSymbolSet(buildProject->GetFunctionDefinitionSymbolSet());
        otava::symbols::Context* prevContext = otava::symbols::CurrentContext();
        otava::symbols::SetCurrentContext(&context);
        otava::symbols::GetModuleMapper()->SetFunctionDefinitionSymbolSet(buildProject->GetFunctionDefinitionSymbolSet());
        for (const auto& moduleName : buildProject->ModuleNames())
        {
            otava::symbols::Module* module = otava::symbols::GetModuleMapper()->GetModule(moduleName, "gendoc", 0, configurations, &context);
            if (module->Kind() == otava::symbols::ModuleKind::implementationModule) continue;
            modules.push_back(module);
        }
        std::sort(modules.begin(), modules.end(), otava::symbols::ModuleNameLess());
        GenerateProjectHtml(this, rootDir, modules);
        otava::symbols::SetCurrentContext(prevContext);
    }
    for (const auto& subProject : subProjects)
    {
        subProject->GenerateProjectDocs();
    }
}

void Project::GenerateModuleDocs(Project* nsProject)
{
    if (buildProject)
    {
        std::cout << "> " << buildProject->Name() << "\n";
        for (const auto& moduleName : buildProject->ModuleNames())
        {
            GenerateModuleDoc(moduleName, nsProject);
        }
    }
    for (const auto& subProject : subProjects)
    {
        subProject->GenerateModuleDocs(nsProject);
    }
}

void Project::GenerateModuleDoc(const std::string& moduleName, Project* nsProject)
{
    otava::symbols::Context context;
    context.SetFlag(otava::symbols::ContextFlags::gendoc);
    context.SetFlag(otava::symbols::ContextFlags::noWarnings);
    context.SetFunctionDefinitionSymbolSet(buildProject->GetFunctionDefinitionSymbolSet());
    otava::symbols::Context* prevContext = otava::symbols::CurrentContext();
    otava::symbols::SetCurrentContext(&context);
    otava::symbols::GetModuleMapper()->SetFunctionDefinitionSymbolSet(buildProject->GetFunctionDefinitionSymbolSet());
    otava::symbols::Module* module = otava::symbols::GetModuleMapper()->GetModule(moduleName, "gendoc", 0, configurations, &context);
    if (module->IsMain())
    {
        otava::symbols::SetCurrentContext(prevContext);
        return;
    }
    context.SetSymbolTable(module->GetSymbolTable());
    GenerateModuleHtml(this, rootDir, module, *otava::symbols::GetModuleMapper(), nsProject);
    otava::symbols::SetCurrentContext(prevContext);
}

void Project::GenerateNamespaceDocs()
{
    if (!generateNamespaceDocs) return;
    std::cout << "generating namespace documentation..." << "\n";
    for (const auto& p : nsSymbolMap)
    {
        const std::string& nsDocName = p.first;
        NamespaceSymbols* nsSymbols = p.second;
        GenerateNamespaceHtml(rootDir, nsDocName, nsSymbols);
    }
}

void Project::GenerateMainIndex()
{
    std::string filePath = util::Path::Combine(rootDir, "index.html");
    soul::xml::Element* htmlElement = soul::xml::MakeElement("html");
    soul::xml::Document doc;
    doc.AppendChild(htmlElement);
    soul::xml::Element* headElement = soul::xml::MakeElement("head");
    htmlElement->AppendChild(headElement);
    soul::xml::Element* metaElement = soul::xml::MakeElement("meta");
    metaElement->SetAttribute("charset", "utf-8");
    headElement->AppendChild(metaElement);
    soul::xml::Element* titleElement = soul::xml::MakeElement("title");
    std::string title = "Reference";
    if (buildProject)
    {
        title = buildProject->Name() + " Reference";
    }
    soul::xml::Text* titleText = soul::xml::MakeText(title);
    titleElement->AppendChild(titleText);
    headElement->AppendChild(titleElement);
    soul::xml::Element* linkElement = soul::xml::MakeElement("link");
    std::string styleFilePath = "style/style.css";
    linkElement->SetAttribute("href", styleFilePath);
    linkElement->SetAttribute("rel", "stylesheet");
    linkElement->SetAttribute("type", "text/css");
    headElement->AppendChild(linkElement);
    soul::xml::Element* bodyElement = soul::xml::MakeElement("body");
    htmlElement->AppendChild(bodyElement);
    soul::xml::Element* h1Element = soul::xml::MakeElement("h1");
    soul::xml::Text* h1Text = soul::xml::MakeText(title);
    h1Element->AppendChild(h1Text);
    bodyElement->AppendChild(h1Element);

    soul::xml::Element* projectsElement = soul::xml::MakeElement("h2");
    soul::xml::Text* projectsText = soul::xml::MakeText("Projects");
    projectsElement->AppendChild(projectsText);
    bodyElement->AppendChild(projectsElement);
    soul::xml::Element* tableElement = soul::xml::MakeElement("table");
    tableElement->SetAttribute("class", "doc");
    bodyElement->AppendChild(tableElement);
    soul::xml::Element* trElement = soul::xml::MakeElement("tr");
    soul::xml::Element* thElement = soul::xml::MakeElement("th");
    soul::xml::Text* projectText = soul::xml::MakeText("project");
    thElement->AppendChild(projectText);
    trElement->AppendChild(thElement);
    tableElement->AppendChild(trElement);

    WriteProjectLink(this, tableElement);

    std::ofstream file(filePath);
    if (!file)
    {
        otava::symbols::SetExceptionThrown();
        throw std::runtime_error("could not create file '" + filePath + "'");
    }
    util::CodeFormatter formatter(file);
    formatter.SetIndentSize(1);
    doc.Write(formatter);
}

void BuildProject(const std::string& path, bool verbose, bool force, bool multithreaded)
{
    otava::symbols::ModuleMapper moduleMapper(false);
    otava::symbols::SetModuleMapper(&moduleMapper);
    otava::ast::NodeIdFactory nodeIdFactory;
    otava::ast::SetNodeIdFactory(&nodeIdFactory);
    otava::build::Project init(path, "#project");
    Project project(path, verbose, force, multithreaded, init);
    MakeStyleFile(project.RootDir());
    project.Build(nullptr);
}

} // namespace gendoc
