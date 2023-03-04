module project_file.ast;

import util.path;
import soul.xml.dom;
import soul.xml.dom.parser;
import soul.xml.xpath;

namespace project_file::ast {

const std::string vcxprojectTypeId = "{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}";

Project::Project(const std::string& root_, const std::string& typeId_, const std::string& name_, const std::string& filePath_, const std::string& id_) :
    typeId(typeId_), name(name_), filePath(util::GetFullPath(util::Path::Combine(root_, filePath_))), id(id_), 
    root(util::GetFullPath(util::Path::GetDirectoryName(filePath)))
{
    ++counters.nprojects;
    if (IsCppProject())
    {
        ++counters.ncpp_projects;
    }
}

bool Project::IsCppProject() const
{
    return typeId == vcxprojectTypeId;
}

void Project::ProcessSourceFiles()
{
    for (const auto& sourceFile : sourceFiles)
    {
        source_file::ast::ProcessSourceFile(sourceFile.get());
        counters += sourceFile->GetCounters();
    }
}

void Project::AddSourceFile(source_file::ast::SourceFile* sourceFile)
{
    sourceFiles.push_back(std::unique_ptr<source_file::ast::SourceFile>(sourceFile));
}

void ProcessProject(Project* project)
{
    std::unique_ptr<soul::xml::Document> doc = soul::xml::ParseXmlFile(project->FilePath());
    std::unique_ptr<soul::xml::xpath::NodeSet> compileItems = soul::xml::xpath::EvaluateToNodeSet("/Project/ItemGroup/ClCompile", doc.get());
    int n = compileItems->Count();
    for (int i = 0; i < n; ++i)
    {
        soul::xml::Node* node = compileItems->GetNode(i);
        if (node->IsElementNode())
        {
            soul::xml::Element* element = static_cast<soul::xml::Element*>(node);
            std::string includeAttribute = element->GetAttribute("Include");
            if (!includeAttribute.empty())
            {
                source_file::ast::SourceFile* sourceFile = new source_file::ast::SourceFile(util::Path::Combine(project->Root(), includeAttribute));
                project->AddSourceFile(sourceFile);
            }
        }
    }
    project->ProcessSourceFiles();
}

} // namespace project_file::ast
