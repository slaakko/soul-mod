// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.common.module_map;

import std.core;

export namespace soul::common {

class ModuleMap
{
public:
    void SetRoot(const std::string& root_);
    void Read(const std::string& xmlFilePath);
    void Write(const std::string& xmlFilePath);
    void MapModule(const std::string& moduleName, const std::string& headerFilePath);
    std::string GetHeaderFilePath(const std::string& moduleName, const std::string& absoluteDirPath) const;
private:
    std::string root;
    std::map<std::string, std::string> map;
};

} // namespace soul::common
