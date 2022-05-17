// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.ast.slg;

namespace soul::ast::slg {

File::File(FileKind kind_, const std::string& filePath_) : kind(kind_), filePath(filePath_)
{
}

File::~File()
{
}

Collection::Collection(CollectionKind kind_, const std::string& name_) : kind(kind_), name(name_), file(nullptr)
{
}

Collection::~Collection()
{
}

Token::Token(int64_t id_, const std::string& name_, const std::string& info_) : id(id_), name(name_), info(info_), collection(nullptr)
{
}

Token::Token(const std::string& name_, const std::string& info_) : id(-1), name(name_), info(info_), collection(nullptr)
{
}

TokenCollection::TokenCollection(const std::string& name_) : Collection(CollectionKind::tokenCollection, name_), id(std::hash<std::string>{}(Name()) & 0x7FFFFFFF)
{
}

void TokenCollection::AddToken(Token* token)
{
    if (token->Id() == -1)
    {
        int64_t tokenId = (int64_t(Id()) << 32) | (int64_t(tokens.size()) + 1);
        token->SetId(tokenId);
    }
    tokens.push_back(std::unique_ptr<Token>(token));
    tokenMap[token->Id()] = token;
    token->SetCollection(this);
}

Token* TokenCollection::GetToken(int64_t id) const
{
    auto it = tokenMap.find(id);
    if (it != tokenMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

TokenFile::TokenFile(const std::string& filePath_) : File(FileKind::tokenFile, filePath_)
{
}

void TokenFile::SetTokenCollection(TokenCollection* tokenCollection_)
{
    tokenCollection.reset(tokenCollection_);
    tokenCollection->SetFile(this);
}

Keyword::Keyword(const std::string str_, const std::string& tokenName_, int64_t tokenId_) : str(str_), tokenName(tokenName_), tokenId(tokenId_), collection(nullptr)
{
}

Keyword::Keyword(const std::string str_, const std::string& tokenName_) : str(str_), tokenName(tokenName_), tokenId(-1), collection(nullptr)
{
}

KeywordCollection::KeywordCollection(const std::string& name_) : Collection(CollectionKind::keywordCollection, name_)
{
}

void KeywordCollection::AddKeyword(Keyword* keyword)
{
    keywords.push_back(std::unique_ptr<Keyword>(keyword));
    keyword->SetCollection(this);
}

KeywordFile::KeywordFile(const std::string& filePath_) : File(FileKind::keywordFile, filePath_)
{
}

void KeywordFile::SetKeywordCollection(KeywordCollection* keywordCollection_)
{
    keywordCollection.reset(keywordCollection_);
    keywordCollection->SetFile(this);
}

void KeywordFile::AddImport(soul::ast::spg::Import* imp)
{
    imports.push_back(std::unique_ptr<soul::ast::spg::Import>(imp));
}

Expression::Expression(const std::string& id_, const std::string& value_, int line_) : index(-1), id(id_), value(value_), line(line_), collection(nullptr)
{
}

ExpressionCollection::ExpressionCollection(const std::string& name_) : Collection(CollectionKind::expressionCollection, name_)
{
}

void ExpressionCollection::AddExpression(Expression* expression)
{
    expressions.push_back(std::unique_ptr<Expression>(expression));
    expression->SetCollection(this);
}

ExpressionFile::ExpressionFile(const std::string& filePath_) : File(FileKind::expressionFile, filePath_)
{
}

void ExpressionFile::SetExpressionCollection(ExpressionCollection* expressionCollection_)
{
    expressionCollection.reset(expressionCollection_);
    expressionCollection->SetFile(this);
}

Rule::Rule(const std::string& expr_, soul::ast::cpp::CompoundStatementNode* code_, int action_, int line_) : expr(expr_), code(code_), action(action_), line(line_)
{
}

Variable::Variable(soul::ast::cpp::TypeIdNode* type_, const std::string& name_) : type(type_), name(name_)
{
}

Action::Action(int id_, soul::ast::cpp::CompoundStatementNode* stmt_) : id(id_), stmt(stmt_)
{
}

void Actions::AddAction(Action* action)
{
    actions.push_back(std::unique_ptr<Action>(action));
}

Action* Actions::GetAction(int id) const
{
    auto it = actionMap.find(id);
    if (it != actionMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

Lexer::Lexer(const std::string& name_) : name(name_)
{
}

void Lexer::AddRule(Rule* rule)
{
    rules.push_back(std::unique_ptr<Rule>(rule));
}

void Lexer::AddVariable(Variable* variable)
{
    variables.push_back(std::unique_ptr<Variable>(variable));
}

void Lexer::AddAction(Action* action)
{
    actions.AddAction(action);
}

LexerFile::LexerFile(const std::string& filePath_) : File(FileKind::lexerFile, filePath_)
{
}

void LexerFile::SetExportModule(soul::ast::spg::ExportModule* exportModule_)
{
    exportModule.reset(exportModule_);
}

void LexerFile::AddImport(soul::ast::spg::Import* imp)
{
    imports.push_back(std::unique_ptr<soul::ast::spg::Import>(imp));
}

void LexerFile::SetLexer(Lexer* lexer_)
{
    lexer.reset(lexer_);
}

} // namespace soul::ast::slg
