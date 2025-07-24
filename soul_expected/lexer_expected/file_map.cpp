// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.lexer.file.map;

namespace soul_expected::lexer {

FileMap::FileMap() : nextFileId(0)
{
}

std::int32_t FileMap::MapFile(const std::string& filePath)
{
    std::lock_guard<std::recursive_mutex> lock(mtx);
    std::int32_t fileId = nextFileId++;
    MapFile(filePath, fileId);
    return fileId;
}

void FileMap::MapFile(const std::string& filePath, std::int32_t fileId)
{
    std::lock_guard<std::recursive_mutex> lock(mtx);
    filePathMap[fileId] = filePath;
}

const std::string& FileMap::GetFilePath(std::int32_t fileId)
{
    std::lock_guard<std::recursive_mutex> lock(mtx);
    auto it = filePathMap.find(fileId);
    if (it != filePathMap.end())
    {
        return it->second;
    }
    else
    {
        static std::string empty;
        return empty;
    }
}

void FileMap::AddFileContent(std::int32_t fileId, std::u32string&& fileContent, std::vector<int>&& lineStartIndeces)
{
    std::lock_guard<std::recursive_mutex> lock(mtx);
    fileContentsMap[fileId] = std::make_pair(std::move(fileContent), std::move(lineStartIndeces));
}

bool FileMap::HasFileContent(std::int32_t fileId)
{
    std::lock_guard<std::recursive_mutex> lock(mtx);
    return fileContentsMap.find(fileId) != fileContentsMap.end();
}

std::expected<std::pair<std::u32string, std::vector<int>>*, int> FileMap::GetFileContent(std::int32_t fileId)
{
    std::lock_guard<std::recursive_mutex> lock(mtx);
    auto it = fileContentsMap.find(fileId);
    if (it != fileContentsMap.end())
    {
        return std::expected<std::pair<std::u32string, std::vector<int>>*, int>(&it->second);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("file contents for file id " + std::to_string(fileId) + " not found from file map"));
    }
}

std::vector<int> ComputeLineStartIndeces(const std::u32string& content)
{
    std::vector<int> indeces;
    indeces.push_back(0);
    const char32_t* start = content.c_str();
    const char32_t* end = content.c_str() + content.size();
    const char32_t* pos = start;
    bool startOfLine = true;
    while (pos != end)
    {
        if (startOfLine)
        {
            indeces.push_back(static_cast<int>(pos - start));
        }
        startOfLine = *pos == '\n';
        ++pos;
    }
    indeces.push_back(static_cast<int>(end - start));
    return indeces;
}

std::expected<bool, int> FileMap::ReadFile(std::int32_t fileId)
{
    std::lock_guard<std::recursive_mutex> lock(mtx);
    std::string filePath = GetFilePath(fileId);
    if (filePath.empty()) return std::unexpected<int>(util::AllocateError("file path is empty"));
    std::expected<std::string, int> frv = util::ReadFile(filePath);
    if (!frv) return std::unexpected<int>(frv.error());
    std::string fileContent = std::move(*frv);
    std::expected<std::u32string, int> rv = util::ToUtf32(fileContent);
    if (!rv) return std::unexpected<int>(rv.error());
    std::u32string ucontent = std::move(*rv);
    std::vector<int> lineStartIndeces = ComputeLineStartIndeces(ucontent);
    AddFileContent(fileId, std::move(ucontent), std::move(lineStartIndeces));
    return std::expected<bool, int>(true);
}

std::expected<std::u32string, int> FileMap::GetFileLine(std::int32_t fileId, int line)
{
    std::lock_guard<std::recursive_mutex> lock(mtx);
    if (fileId == -1) return std::u32string();
    if (!HasFileContent(fileId))
    {
        std::expected<bool, int> rv = ReadFile(fileId);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    std::expected<std::pair<std::u32string, std::vector<int>>*, int> rv = GetFileContent(fileId);
    if (!rv) return std::unexpected<int>(rv.error());
    std::pair<std::u32string, std::vector<int>>* contents = *rv;
    if (line < 1 || line >= contents->second.size()) throw std::runtime_error("invalid line");
    std::u32string::size_type lineStart = contents->second[line];
    std::u32string::size_type lineLength = std::u32string::npos;
    if (line < contents->second.size() - 1)
    {
        lineLength = contents->second[line + 1] - lineStart;
    }
    std::u32string lineStr = contents->first.substr(lineStart, lineLength);
    int n = static_cast<int>(lineStr.length());
    int i = n - 1;
    while (i >= 0)
    {
        if (lineStr[i] != '\r' && lineStr[i] != '\n')
        {
            break;
        }
        --i;
    }
    std::u32string trimmedLine = lineStr.substr(0, i + 1);
    return std::expected<std::u32string, int>(std::move(trimmedLine));
}

const std::vector<int>* FileMap::LineStartIndeces(std::int32_t fileId)
{
    std::lock_guard<std::recursive_mutex> lock(mtx);
    auto it = fileContentsMap.find(fileId);
    if (it != fileContentsMap.end())
    {
        return &it->second.second;
    }
    else
    {
        return nullptr;
    }
}

FileMap* globalFileMap = nullptr;

FileMap* GetGlobalFileMap()
{
    return globalFileMap;
}

void SetGlobalFileMap(FileMap* fileMap)
{
    globalFileMap = fileMap;
}

} // namespace soul_expected::lexer
