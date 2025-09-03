// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.ast.common;

import std;

export namespace soul::ast::common {

std::string ToNamespaceName(const std::string& qualifiedId);

class ExportModule
{
public:
    ExportModule(const std::string& moduleName_);
    inline const std::string& ModuleName() const { return moduleName; }
    std::string NamespaceName() const;
private:
    std::string moduleName;
};

enum class ImportPrefix
{
    interfacePrefix, implementationPrefix
};

class Import
{
public:
    Import(const std::string& moduleName_, ImportPrefix prefix_);
    inline const std::string& ModuleName() const { return moduleName; }
    inline ImportPrefix Prefix() const { return prefix; }
private:
    std::string moduleName;
    ImportPrefix prefix;
};

enum class FileKind
{
    tokenFile, keywordFile, expressionFile, lexerFile, slgFile, parserFile, spgFile
};

class Visitor;

class File
{
public:
    File(FileKind kind_, const std::string& filePath_);
    virtual ~File();
    inline FileKind Kind() const { return kind; }
    inline const std::string& FilePath() const { return filePath; }
    inline bool IsExternal() const { return external; }
    inline void SetExternal() { external = true; }
    virtual void Accept(Visitor& visitor);
private:
    FileKind kind;
    std::string filePath;
    bool external;
};

enum class CollectionKind
{
    tokenCollection, keywordCollection, expressionCollection, lexer
};

class Collection
{
public:
    Collection(CollectionKind kind_, const std::string& name_);
    virtual ~Collection();
    inline CollectionKind Kind() const { return kind; }
    inline const std::string& Name() const { return name; }
    inline void SetFile(File* file_) { file = file_; }
    inline File* GetFile() const { return file; }
private:
    CollectionKind kind;
    std::string name;
    File* file;
};

class Token
{
public:
    Token(std::int64_t id_, const std::string& name_, const std::string& info_);
    Token(const std::string& name_, const std::string& info_);
    inline void SetCollection(Collection* collection_) { collection = collection_; }
    inline Collection* GetCollection() const { return collection; }
    inline std::int64_t Id() const { return id; }
    inline void SetId(std::int64_t id_) { id = id_; }
    inline const std::string& Name() const { return name; }
    inline const std::string& Info() const { return info; }
    inline bool IsAny() const { return id == -1; }
    inline bool IsEpsilon() const { return id == -2; }
    std::string FullName() const;
    std::string FullCppId() const;
    Token* Clone() const;
private:
    std::int64_t id;
    std::string name;
    std::string info;
    Collection* collection;
};

class TokenCollection : public Collection
{
public:
    TokenCollection(const std::string& name_);
    inline bool Initialized() const { return initialized; }
    inline void SetInitialized() { initialized = true; }
    void AddToken(Token* token);
    inline const std::vector<std::unique_ptr<Token>>& Tokens() const { return tokens; }
    inline std::int32_t Id() const { return id; }
    Token* GetToken(std::int64_t id) const;
    TokenCollection* Clone() const;
private:
    bool initialized;
    std::int32_t id;
    std::vector<std::unique_ptr<Token>> tokens;
    std::map<std::int64_t, Token*> tokenMap;
};

class TokenFile : public File
{
public:
    TokenFile(const std::string& filePath_);
    void SetTokenCollection(TokenCollection* tokenCollection_);
    inline TokenCollection* GetTokenCollection() const { return tokenCollection.get(); }
    void Accept(Visitor& visitor) override;
    TokenFile* Clone() const;
private:
    std::unique_ptr<TokenCollection> tokenCollection;
};

class TokenMap
{
public:
    TokenMap();
    void AddUsingToken(Token* usingToken);
    std::expected<bool, int> AddToken(Token* token);
    std::vector<Token*> GetTokens(const std::string& tokenName) const;
    Token* GetToken(const std::string& tokenFullName) const;
    const Token* Any() const { return &any; }
    const Token* Epsilon() const { return &epsilon; }
private:
    std::map<std::string, Token*> usingTokenMap;
    std::map<std::string, std::vector<Token*>> tokenMap;
    std::map<std::string, Token*> tokenFullNameMap;
    Token any;
    Token epsilon;
};

enum class VisitorKind : int
{
    commonVisitor, spgVisitor
}

class Visitor
{
public:
    Visitor(VisitorKind kind_);
    virtual ~Visitor();
    virtual void Visit(TokenFile& tokenFile) {}
    inline bool IsSpgVisitor() const { return kind == VisitorKind::spgVisitor; }
private:
    VisitorKind kind;
};

} // namespace soul::ast::common
