// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.lexer.file.map;

import soul.lexer.base;
import soul.lexer.token;
import std;

export namespace soul::lexer {

using TokenVec = std::vector<soul::lexer::Token<char32_t, LexerBase<char32_t>>>;

class FileMap
{
public:
    FileMap();
    std::int32_t MapFile(const std::string& filePath);
    void MapFile(const std::string& filePath, std::int32_t fileId);
    const std::string& GetFilePath(std::int32_t fileId) const;
    void AddFileContent(std::int32_t fileId, std::u32string&& fileContent, std::vector<int>&& lineStartIndeces);
    bool HasFileContent(std::int32_t fileId) const;
    void ReadFile(std::int32_t fileId);
    const std::pair<std::u32string, std::vector<int>>& GetFileContent(std::int32_t file) const;
    std::u32string GetFileLine(std::int32_t fileId, int line);
    void SetTokens(std::int32_t fileId, TokenVec&& tokens);
    const TokenVec& GetTokens(std::int32_t fileId) const;
    std::int32_t NextFileId() const { return nextFileId; }
private:
    std::int32_t nextFileId;
    std::map<std::int32_t, std::string> filePathMap;
    std::map<std::int32_t, std::pair<std::u32string, std::vector<int>>> fileContentsMap;
    std::map<std::int32_t, TokenVec> tokenMap;
};

FileMap* GetGlobalFileMap();
void SetGlobalFileMap(soul::lexer::FileMap* fileMap_);

} // namespace soul::lexer
