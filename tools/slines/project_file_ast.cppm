export module project_file.ast;

import std.core;
import source_file.ast;

export namespace project_file::ast {

class Project
{
public:
    Project(const std::string& root_, const std::string& typeId_, const std::string& name_, const std::string& filePath_, const std::string& id_);
    bool IsCppProject() const;
    const std::string& Root() const { return root; }
    const std::string& TypeId() const { return typeId; }
    const std::string& Name() const { return name; }
    const std::string& FilePath() const { return filePath; }
    const std::string& Id() const { return id; }
    void AddSourceFile(source_file::ast::SourceFile* sourceFile);
    const std::vector<std::unique_ptr<source_file::ast::SourceFile>>& SourceFiles() const { return sourceFiles; }
    const Counters& GetCounters() const { return counters; }
    void ProcessSourceFiles();
private:
    std::string typeId;
    std::string name;
    std::string filePath;
    std::string id;
    std::string root;
    std::vector<std::unique_ptr<source_file::ast::SourceFile>> sourceFiles;
    Counters counters;
};

void ProcessProject(Project* project);

} // namespace project_file::ast

