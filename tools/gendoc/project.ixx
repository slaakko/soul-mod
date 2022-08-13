// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.project;

import std.core;
import soul.cpp20.project.init;
import soul.cpp20.proj.ast;

export namespace gendoc {

class Project
{
public:
    Project(const std::string& path_, bool verbose_, bool force_, bool multithreaded_, soul::cpp20::project::init::Init& init_);
    void SetParent(Project* parent_) { parent = parent_; }
    void Build();
    std::string FullName() const;
private:
    void BuildCppProject();
    void GenerateDocs();
    void GenerateModuleDocs();
    void GenerateModuleDoc(const std::string& moduleName);
    Project* parent;
    std::string path;
    soul::cpp20::project::init::Init& init;
    std::string name;
    std::string rootDir;
    std::string cppProjectFilePath;
    bool verbose;
    bool force;
    bool multithreaded;
    std::vector<std::unique_ptr<Project>> subProjects;
    std::unique_ptr<soul::cpp20::proj::ast::Project> project;
};

void BuildProject(const std::string& path, bool verbose, bool force, bool multithreaded);

} // namespace gendoc
