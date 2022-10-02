module otava.command.ast;

namespace otava::command::ast {

Command::Command()
{
}

Command::~Command()
{
}

BuildCommand::BuildCommand(const std::string& filePath_) : filePath(filePath_)
{
}

void BuildCommand::Execute()
{
    std::cout << "build " << filePath << std::endl;
}

DumpCommand::DumpCommand(const std::string& filePath_) : filePath(filePath_)
{
}

void DumpCommand::Execute()
{
    std::cout << "dump " << filePath << std::endl;
}

AssembleCommand::AssembleCommand(const std::string& filePath_) : filePath(filePath_)
{
}

void AssembleCommand::Execute()
{
    std::cout << "assemble " << filePath << std::endl;
}

IntermediateCompileCommand::IntermediateCompileCommand(const std::string& filePath_) : filePath(filePath_)
{
}

void IntermediateCompileCommand::Execute()
{
    std::cout << "ic " << filePath << std::endl;
}

} // namespace otava::command::ast
