export module otava.command.ast;

import std.core;

export namespace otava::command::ast {

class Command
{
public:
    Command();
    virtual ~Command();
    virtual void Execute() = 0;
};

class BuildCommand : public Command
{
public:
    BuildCommand(const std::string& filePath_);
    const std::string& FilePath() const { return filePath; }
    void Execute() override;
private:
    std::string filePath;
};

class DumpCommand : public Command
{
public:
    DumpCommand(const std::string& filePath_);
    const std::string& FilePath() const { return filePath; }
    void Execute() override;
private:
    std::string filePath;
};

class AssembleCommand : public Command
{
public:
    AssembleCommand(const std::string& filePath_);
    const std::string& FilePath() const { return filePath; }
    void Execute() override;
private:
    std::string filePath;
};

class IntermediateCompileCommand : public Command
{
public:
    IntermediateCompileCommand(const std::string& filePath_);
    const std::string& FilePath() const { return filePath; }
    void Execute() override;
private:
    std::string filePath;
};

} // namespace otava::command::ast

