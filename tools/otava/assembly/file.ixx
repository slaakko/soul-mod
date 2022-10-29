// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.file;

import std.core;
import util.code.formatter;

export namespace otava::assembly {

class Function;

class File
{
public:
    File(const std::string& filePath_);
    const std::string& FilePath() const { return filePath; }
    Function* CreateFunction(const std::string& name);
    void Write();
private:
    std::string filePath;
    std::ofstream file;
    util::CodeFormatter formatter;
    std::vector<std::unique_ptr<Function>> functions;
};

} // namespace otava::assembly
