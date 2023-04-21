import std.core;

export namespace soul::ast::common {

enum class ImportPrefix
{
    interfacePrefix, implementationPrefix
};

class Import
{
public:
    Import(const std::string& moduleName_, ImportPrefix prefix_);
    const std::string& ModuleName() const { return moduleName; }
    ImportPrefix Prefix() const { return prefix; }
private:
    std::string moduleName;
    ImportPrefix prefix;
};

}

class ParserFile
{
public:
    const std::vector<std::unique_ptr<soul::ast::common::Import>>& Imports() const { return imports; }
private:
    std::vector<std::unique_ptr<soul::ast::common::Import>> imports;
};

void test(ParserFile& parserFile)
{
    for (const auto& imprt : parserFile.Imports())
    {

    }
}

int main()
{ 
    return 0;
}
