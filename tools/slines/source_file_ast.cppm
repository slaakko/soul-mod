export module source_file.ast;

import std;
import counters;

export namespace source_file::ast {

class SourceFile
{
public:
    SourceFile(const std::string& filePath_);
    const std::string& FilePath() const { return filePath; }
    void ProcessContent();
    const Counters& GetCounters() const { return counters; }
private:
    std::string filePath;
    std::string content;
    Counters counters;
};

void ProcessSourceFile(SourceFile* sourceFile);

} // namespace sourced_file::ast
