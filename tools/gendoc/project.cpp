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
import soul.cpp20.symbols.namespaces;
import soul.cpp20.symbols.compound.type.symbol;
import soul.cpp20.symbols.writer;
import soul.cpp20.project.build;
import soul.cpp20.project.parser;
import soul.cpp20.project.build;
import gendoc.module_html_generator;

namespace gendoc {

Project::Project(const std::string& path_, bool verbose_, bool force_, bool multithreaded_, soul::cpp20::project::init::Init& init_) : 
    parent(nullptr), path(path_), verbose(verbose_), force(force_), multithreaded(multithreaded_), init(init_)
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

void Project::Build()
{
    for (const auto& subproject : subProjects)
    {
        subproject->Build();
    }
    if (verbose)
    {
        std::cout << "> " << FullName() << std::endl;
    }
    BuildCppProject();
    GenerateDocs();
}

void Project::BuildCppProject()
{
    if (cppProjectFilePath.empty()) return;
    project = soul::cpp20::project::parser::ParseProjectFile(cppProjectFilePath);
    project->InitModules();
    for (int file : project->InterfaceFiles())
    {
        soul::cpp20::project::build::ScanDependencies(project.get(), file);
    }
    project->SetScanned();
    project->LoadModules(init.nodeIdFactory, init.moduleMapper, init.symbols, init.evaluationContext);
    bool build = force || !project->UpToDate();
    if (!build) return;
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

void Project::GenerateDocs()
{
    GenerateModuleDocs();
}

void Project::GenerateModuleDocs()
{
    if (!project) return;;
    for (const auto& module : project->Modules())
    {
        GenerateModuleDoc(module->Name());
    }
}

void Project::GenerateModuleDoc(const std::string& moduleName)
{
    soul::cpp20::symbols::Module* module = soul::cpp20::project::build::GetModule(init.moduleMapper, moduleName);
    GenerateModuleHtml(rootDir, module);
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
    project.Build();
}

} // namespace gendoc
