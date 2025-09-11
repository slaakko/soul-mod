// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.ast.slg;

import util;

namespace soul::ast::slg {

Keyword::Keyword(const soul::ast::SourcePos& sourcePos_, const std::string& str_, const std::string& tokenName_, std::int64_t tokenId_) : 
    sourcePos(sourcePos_), str(str_), tokenName(tokenName_), tokenId(tokenId_), collection(nullptr)
{
}

Keyword::Keyword(const soul::ast::SourcePos& sourcePos_, const std::string& str_, const std::string& tokenName_) : 
    sourcePos(sourcePos_), str(str_), tokenName(tokenName_), tokenId(-1), collection(nullptr)
{
}

KeywordCollection::KeywordCollection(const std::string& name_) : soul::ast::common::Collection(CollectionKind::keywordCollection, name_)
{
}

void KeywordCollection::AddKeyword(Keyword* keyword)
{
    keywords.push_back(std::unique_ptr<Keyword>(keyword));
    keyword->SetCollection(this);
}

KeywordFile::KeywordFile(const std::string& filePath_) : soul::ast::common::File(soul::ast::common::FileKind::keywordFile, filePath_)
{
}

void KeywordFile::SetKeywordCollection(KeywordCollection* keywordCollection_)
{
    keywordCollection.reset(keywordCollection_);
    keywordCollection->SetFile(this);
}

void KeywordFile::AddImport(soul::ast::common::Import* imp)
{
    imports.push_back(std::unique_ptr<soul::ast::common::Import>(imp));
}

Expression::Expression(const std::string& id_, const std::string& value_, int line_) : index(-1), id(id_), value(value_), line(line_), collection(nullptr)
{
}

const std::string& Expression::FileName() const
{
    soul::ast::common::Collection* collection = GetCollection();
    soul::ast::common::File* file = collection->GetFile();
    return file->FilePath();
}

ExpressionCollection::ExpressionCollection(const std::string& name_) : soul::ast::common::Collection(CollectionKind::expressionCollection, name_)
{
}

void ExpressionCollection::AddExpression(Expression* expression)
{
    expressions.push_back(std::unique_ptr<Expression>(expression));
    expression->SetCollection(this);
}

ExpressionFile::ExpressionFile(const std::string& filePath_) : soul::ast::common::File(soul::ast::common::FileKind::expressionFile, filePath_)
{
}

void ExpressionFile::SetExpressionCollection(ExpressionCollection* expressionCollection_)
{
    expressionCollection.reset(expressionCollection_);
    expressionCollection->SetFile(this);
}

Rule::Rule(const std::string& expr_, soul::ast::cpp::CompoundStatementNode* code_, int action_, int line_) :
    index(-1), expr(expr_), code(code_), action(action_), line(line_), collection(nullptr), nfaIndex(-1)
{
}

Variable::Variable(soul::ast::cpp::TypeIdNode* type_, const std::string& name_) : type(type_), name(name_)
{
}

Action::Action(int id_, soul::ast::cpp::CompoundStatementNode* code_) : id(id_), code(code_)
{
}

void Actions::AddAction(Action* action)
{
    actions.push_back(std::unique_ptr<Action>(action));
    actionMap[action->Id()] = action;
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

Lexer::Lexer(const std::string& name_) : soul::ast::common::Collection(CollectionKind::lexer, name_)
{
}

void Lexer::AddRule(Rule* rule)
{
    rule->SetIndex(static_cast<int>(rules.size()));
    rule->SetCollection(this);
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

void Lexer::SetVariableClassName(const std::string& variableClassName_)
{
    variableClassName = variableClassName_;
}

LexerFile::LexerFile(const std::string& filePath_) : soul::ast::common::File(soul::ast::common::FileKind::lexerFile, filePath_)
{
}

void LexerFile::SetExportModule(soul::ast::common::ExportModule* exportModule_)
{
    exportModule.reset(exportModule_);
}

void LexerFile::AddImport(soul::ast::common::Import* imp)
{
    imports.push_back(std::unique_ptr<soul::ast::common::Import>(imp));
}

void LexerFile::SetLexer(Lexer* lexer_)
{
    lexer.reset(lexer_);
    lexer->SetFile(this);
}

SlgFileDeclaration::SlgFileDeclaration(SlgFileDeclarationKind kind_, const std::string& filePath_) : kind(kind_), filePath(filePath_)
{
}

SlgFileDeclaration::~SlgFileDeclaration()
{
}

TokenFileDeclaration::TokenFileDeclaration(const std::string& filePath_, bool external_) :
    SlgFileDeclaration(SlgFileDeclarationKind::tokenFileDeclaration, filePath_), external(external_)
{
}

KeywordFileDeclaration::KeywordFileDeclaration(const std::string& filePath_) : SlgFileDeclaration(SlgFileDeclarationKind::keywordFileDeclaration, filePath_)
{
}

ExpressionFileDeclaration::ExpressionFileDeclaration(const std::string& filePath_) : SlgFileDeclaration(SlgFileDeclarationKind::expressionFileDeclaration, filePath_)
{
}

LexerFileDeclaration::LexerFileDeclaration(const std::string& filePath_) : SlgFileDeclaration(SlgFileDeclarationKind::lexerFileDeclararation, filePath_)
{
}

SlgFile::SlgFile(const std::string& filePath_, const std::string& projectName_) : 
    soul::ast::common::File(soul::ast::common::FileKind::slgFile, filePath_), projectName(projectName_)
{
}

void SlgFile::AddDeclaration(SlgFileDeclaration* declaration)
{
    declarations.push_back(std::unique_ptr<SlgFileDeclaration>(declaration));
}

std::expected<bool, int> SlgFile::AddTokenFile(soul::ast::common::TokenFile* tokenFile)
{
    tokenFiles.push_back(std::unique_ptr<soul::ast::common::TokenFile>(tokenFile));
    auto it = collectionMap.find(tokenFile->GetTokenCollection()->Name());
    if (it != collectionMap.cend())
    {
        return std::unexpected<int>(util::AllocateError("token collection '" + tokenFile->GetTokenCollection()->Name() + "' already added to SLG file '" + FilePath() + "'"));
    }
    collectionMap[tokenFile->GetTokenCollection()->Name()] = static_cast<soul::ast::common::Collection*>(tokenFile->GetTokenCollection());
    collections.push_back(tokenFile->GetTokenCollection());
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SlgFile::AddKeywordFile(KeywordFile* keywordFile)
{
    keywordFiles.push_back(std::unique_ptr<KeywordFile>(keywordFile));
    auto it = collectionMap.find(keywordFile->GetKeywordCollection()->Name());
    if (it != collectionMap.cend())
    {
        return std::unexpected<int>(util::AllocateError("keyword collection '" + keywordFile->GetKeywordCollection()->Name() + "' already added to SLG file '" +
            FilePath() + "'"));
    }
    collectionMap[keywordFile->GetKeywordCollection()->Name()] = static_cast<soul::ast::common::Collection*>(keywordFile->GetKeywordCollection());
    collections.push_back(keywordFile->GetKeywordCollection());
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SlgFile::AddExpressionFile(ExpressionFile* expressionFile)
{
    expressionFiles.push_back(std::unique_ptr<ExpressionFile>(expressionFile));
    auto it = collectionMap.find(expressionFile->GetExpressionCollection()->Name());
    if (it != collectionMap.cend())
    {
        return std::unexpected<int>(util::AllocateError("expression collection '" + expressionFile->GetExpressionCollection()->Name() + "' already added to SLG file '" +
            FilePath() + "'"));
    }
    collectionMap[expressionFile->GetExpressionCollection()->Name()] = static_cast<soul::ast::common::Collection*>(expressionFile->GetExpressionCollection());
    collections.push_back(expressionFile->GetExpressionCollection());
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SlgFile::AddLexerFile(LexerFile* lexerFile)
{
    lexerFiles.push_back(std::unique_ptr<LexerFile>(lexerFile));
    auto it = collectionMap.find(lexerFile->GetLexer()->Name());
    if (it != collectionMap.cend())
    {
        return std::unexpected<int>(util::AllocateError("lexer '" + lexerFile->GetLexer()->Name() + "' already added to SLG file '" + FilePath() + "'"));
    }
    collectionMap[lexerFile->GetLexer()->Name()] = static_cast<soul::ast::common::Collection*>(lexerFile->GetLexer());
    collections.push_back(lexerFile->GetLexer());
    return std::expected<bool, int>(true);
}

soul::ast::common::Collection* SlgFile::GetCollection(const std::string& name) const
{
    auto it = collectionMap.find(name);
    if (it != collectionMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

Tokens::Tokens()
{
}

void Tokens::AddToken(soul::ast::common::Token* token)
{
    tokens.push_back(token);
}

Keywords::Keywords()
{
}

void Keywords::AddKeyword(Keyword* keyword)
{
    keywords.push_back(keyword);
}

Expressions::Expressions()
{
}

std::expected<bool, int> Expressions::AddExpression(Expression* expression)
{
    expression->SetIndex(static_cast<int>(expressions.size()));
    expressions.push_back(expression);
    Expression* prevExpr = GetExpression(expression->Id());
    if (prevExpr)
    {
        return std::unexpected<int>(util::AllocateError("expression '" + expression->Id() + "' already defined"));
    }
    expressionMap[expression->Id()] = expression;
    return std::expected<bool, int>(true);
}

Expression* Expressions::GetExpression(const std::string& id) const
{
    auto it = expressionMap.find(id);
    if (it != expressionMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

} // namespace soul::ast::slg
