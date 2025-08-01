// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.ast.slg;

import std;
import soul.ast.common;
import soul.ast.cpp;

export namespace soul::ast::slg {

enum class FileKind
{
    tokenFile, keywordFile, expressionFile, lexerFile, slgFile
};

class File
{
public:
    File(FileKind kind_, const std::string& filePath_);
    virtual ~File();
    inline FileKind Kind() const { return kind; }
    inline const std::string& FilePath() const { return filePath; }
    inline bool IsExternal() const { return external; }
    inline void SetExternal() { external = true; }
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
private:
    std::unique_ptr<TokenCollection> tokenCollection;
};

class Keyword
{
public:
    Keyword(const std::string& str_, const std::string& tokenName_, std::int64_t tokenId_);
    Keyword(const std::string& str_, const std::string& tokenName_);
    inline void SetCollection(Collection* collection_) { collection = collection_; }
    inline Collection* GetCollection() const { return collection; }
    inline const std::string& Str() const { return str; }
    inline const std::string& TokenName() const { return tokenName; }
    inline std::int64_t TokenId() const { return tokenId; }
    inline void SetTokenId(std::int64_t tokenId_) { tokenId = tokenId_; }
private:
    std::string str;
    std::string tokenName;
    std::int64_t tokenId;
    Collection* collection;
};

class KeywordCollection : public Collection
{
public:
    KeywordCollection(const std::string& name_);
    void AddKeyword(Keyword* keyword);
    inline const std::vector<std::unique_ptr<Keyword>>& Keywords() const { return keywords; }
private:
    std::vector<std::unique_ptr<Keyword>> keywords;
};

class KeywordFile : public File
{
public:
    KeywordFile(const std::string& filePath_);
    void SetKeywordCollection(KeywordCollection* keywordCollection_);
    inline KeywordCollection* GetKeywordCollection() const { return keywordCollection.get(); }
    void AddImport(soul::ast::common::Import* imp);
    inline const std::vector<std::unique_ptr<soul::ast::common::Import>>& Imports() const { return imports; }
private:
    std::unique_ptr<KeywordCollection> keywordCollection;
    std::vector<std::unique_ptr<soul::ast::common::Import>> imports;
};

class Expression
{
public:
    Expression(const std::string& id_, const std::string& value_, int line_);
    inline void SetCollection(Collection* collection_) { collection = collection_; }
    inline Collection* GetCollection() const { return collection; }
    inline int Index() const { return index; }
    inline void SetIndex(int index_) { index = index_; }
    inline const std::string& Id() const { return id; }
    inline const std::string& Value() const { return value; }
    const std::string& FileName() const;
    inline int Line() const { return line; }
private:
    int index;
    std::string id;
    std::string value;
    int line;
    Collection* collection;
};

class ExpressionCollection : public Collection
{
public:
    ExpressionCollection(const std::string& name_);
    void AddExpression(Expression* expression);
    inline const std::vector<std::unique_ptr<Expression>>& Expressions() const { return expressions; }
private:
    std::vector<std::unique_ptr<Expression>> expressions;
};

class ExpressionFile : public File
{
public:
    ExpressionFile(const std::string& filePath_);
    void SetExpressionCollection(ExpressionCollection* expressionCollection_);
    inline ExpressionCollection* GetExpressionCollection() const { return expressionCollection.get(); }
private:
    std::unique_ptr<ExpressionCollection> expressionCollection;
};

class Rule
{
public:
    Rule(const std::string& expr_, soul::ast::cpp::CompoundStatementNode* code_, int action_, int line_);
    inline int Index() const { return index; }
    inline void SetIndex(int index_) { index = index_; }
    inline void SetCollection(Collection* collection_) { collection = collection_; }
    inline Collection* GetCollection() const { return collection; }
    inline const std::string& Expr() const { return expr; }
    inline soul::ast::cpp::CompoundStatementNode* Code() const { return code.get(); }
    inline int Action() const { return action; }
    inline int Line() const { return line; }
    inline int NfaIndex() const { return nfaIndex; }
    inline void SetNfaIndex(int nfaIndex_) { nfaIndex = nfaIndex_; }
private:
    int index;
    std::string expr;
    std::unique_ptr<soul::ast::cpp::CompoundStatementNode> code;
    int action;
    int line;
    Collection* collection;
    int nfaIndex;
};

class Variable
{
public:
    Variable(soul::ast::cpp::TypeIdNode* type_,  const std::string& name_);
    inline soul::ast::cpp::TypeIdNode* Type() const { return type.get(); }
    inline const std::string& Name() const { return name; }
private:
    std::unique_ptr<soul::ast::cpp::TypeIdNode> type;
    std::string name;
};

class Action
{
public:
    Action(int id_, soul::ast::cpp::CompoundStatementNode* code_);
    inline int Id() const { return id; }
    inline soul::ast::cpp::CompoundStatementNode* Code() const { return code.get(); }
private:
    int id;
    std::unique_ptr<soul::ast::cpp::CompoundStatementNode> code;
};

class Actions
{
public:
    void AddAction(Action* action);
    Action* GetAction(int id) const;
private:
    std::vector<std::unique_ptr<Action>> actions;
    std::map<int, Action*> actionMap;
};

class Lexer : public Collection
{
public:
    Lexer(const std::string& name_);
    void AddRule(Rule* rule);
    inline const std::vector<std::unique_ptr<Rule>>& Rules() const { return rules; }
    void AddVariable(Variable* variable);
    inline const std::vector<std::unique_ptr<Variable>>& Variables() const { return variables; }
    void AddAction(Action* action);
    inline const Actions& GetActions() const { return actions; }
    inline const std::string& VariableClassName() const { return variableClassName; }
    void SetVariableClassName(const std::string& variableClassName_);
private:
    std::vector<std::unique_ptr<Rule>> rules;
    std::vector<std::unique_ptr<Variable>> variables;
    Actions actions;
    std::string variableClassName;
};

class LexerFile : public File
{
public:
    LexerFile(const std::string& filePath_);
    void SetExportModule(soul::ast::common::ExportModule* exportModule_);
    inline soul::ast::common::ExportModule* GetExportModule() const { return exportModule.get(); }
    void AddImport(soul::ast::common::Import* imp);
    inline const std::vector<std::unique_ptr<soul::ast::common::Import>>& Imports() const { return imports; }
    void SetLexer(Lexer* lexer_);
    inline Lexer* GetLexer() const { return lexer.get(); }
private:
    std::unique_ptr<soul::ast::common::ExportModule> exportModule;
    std::vector<std::unique_ptr<soul::ast::common::Import>> imports;
    std::unique_ptr<Lexer> lexer;
};

enum class SlgFileDeclarationKind
{
    tokenFileDeclaration, keywordFileDeclaration, expressionFileDeclaration, lexerFileDeclararation
};

class SlgFileDeclaration
{
public:
    SlgFileDeclaration(SlgFileDeclarationKind kind_, const std::string& filePath_);
    virtual ~SlgFileDeclaration();
    inline SlgFileDeclarationKind Kind() const { return kind; }
    inline const std::string& FilePath() const { return filePath; }
private:
    SlgFileDeclarationKind kind;
    std::string filePath;
};

class TokenFileDeclaration : public SlgFileDeclaration
{
public:
    TokenFileDeclaration(const std::string& filePath_, bool external_);
    inline bool External() const { return external; }
private:
    bool external;
};

class KeywordFileDeclaration : public SlgFileDeclaration
{
public:
    KeywordFileDeclaration(const std::string& filePath_);
};

class ExpressionFileDeclaration : public SlgFileDeclaration
{
public:
    ExpressionFileDeclaration(const std::string& filePath_);
};

class LexerFileDeclaration : public SlgFileDeclaration
{
public:
    LexerFileDeclaration(const std::string& filePath_);
};

class SlgFile : public File
{
public:
    SlgFile(const std::string& filePath_, const std::string& projectName_);
    inline const std::string& ProjectName() const { return projectName; }
    void AddDeclaration(SlgFileDeclaration* declaration);
    inline const std::vector<std::unique_ptr<SlgFileDeclaration>>& Declarations() const { return declarations; }
    void AddTokenFile(TokenFile* tokenFile);
    inline const std::vector<std::unique_ptr<TokenFile>>& TokenFiles() const { return tokenFiles; }
    void AddKeywordFile(KeywordFile* keywordFile);
    inline const std::vector<std::unique_ptr<KeywordFile>>& KeywordFiles() const { return keywordFiles; }
    void AddExpressionFile(ExpressionFile* expressionFile);
    inline const std::vector<std::unique_ptr<ExpressionFile>>& ExpressionFiles() const { return expressionFiles; }
    void AddLexerFile(LexerFile* lexerFile);
    inline const std::vector<std::unique_ptr<LexerFile>>& LexerFiles() const { return lexerFiles; }
    inline const std::vector<Collection*>& Collections() const { return collections; }
    Collection* GetCollection(const std::string& name) const;
private:
    std::string projectName;
    std::vector<std::unique_ptr<SlgFileDeclaration>> declarations;
    std::vector<std::unique_ptr<TokenFile>> tokenFiles;
    std::vector<std::unique_ptr<KeywordFile>> keywordFiles;
    std::vector<std::unique_ptr<ExpressionFile>> expressionFiles;
    std::vector<std::unique_ptr<LexerFile>> lexerFiles;
    std::vector<Collection*> collections;
    std::map<std::string, Collection*> collectionMap;
};

class Tokens
{
public:
    Tokens();
    void AddToken(Token* token);
    inline const std::vector<Token*>& GetTokens() const { return tokens; }
private:
    std::vector<Token*> tokens;
};

class Keywords
{
public:
    Keywords();
    void AddKeyword(Keyword* keyword);
    inline const std::vector<Keyword*>& GetKeywords() const { return keywords; }
private:
    std::vector<Keyword*> keywords;
};

class Expressions
{
public:
    Expressions();
    void AddExpression(Expression* expression);
    Expression* GetExpression(const std::string& id) const;
private:
    std::vector<Expression*> expressions;
    std::map<std::string, Expression*> expressionMap;
};

} // namespace soul::ast::slg
