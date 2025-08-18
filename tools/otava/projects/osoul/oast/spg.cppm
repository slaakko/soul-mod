// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.ast.spg;

import std;
import soul.ast.common;
import soul.ast.cpp;
import soul.ast.source.pos;

export namespace soul::ast::spg {

struct Range
{
    std::int32_t first;
    std::int32_t last;
};

enum class ParamVarKind
{
    parameter, variable
};

class ParamVar
{
public:
    ParamVar(const soul::ast::SourcePos& sourcePos_, ParamVarKind kind_, soul::ast::cpp::TypeIdNode* type_, const std::string& name_);
    virtual ~ParamVar();
    inline const soul::ast::SourcePos& GetSourcePos() const { return sourcePos; }
    inline ParamVarKind Kind() const { return kind; }
    inline soul::ast::cpp::TypeIdNode* Type() const { return type.get(); }
    inline const std::string& Name() const { return name; }
    virtual ParamVar* Clone() const = 0;
private:
    soul::ast::SourcePos sourcePos;
    ParamVarKind kind;
    std::unique_ptr<soul::ast::cpp::TypeIdNode> type;
    std::string name;
};

class Parameter : public ParamVar
{
public:
    Parameter(const soul::ast::SourcePos& sourcePos_, soul::ast::cpp::TypeIdNode* type_, const std::string& name_);
    ParamVar* Clone() const override;
};

class Variable : public ParamVar
{
public:
    Variable(const soul::ast::SourcePos& sourcePos_, soul::ast::cpp::TypeIdNode* type_, const std::string& name_);
    ParamVar* Clone() const override;
};

class CharSet
{
public:
    CharSet();
    CharSet* Clone() const;
    inline bool Inverse() const { return inverse; }
    inline void SetInverse() { inverse = true; }
    inline const std::vector<Range>& Ranges() const { return ranges; }
    void AddRange(const Range& range);
private:
    bool inverse;
    std::vector<Range> ranges;
};

class TokenSet
{
public:
    TokenSet();
    bool AddToken(const std::string& token);
    bool Merge(const TokenSet& that);
    bool Contains(const std::string& token) const;
    bool Intersects(const TokenSet& that) const;
    std::string ToString() const;
    inline const std::set<std::string>& Tokens() const { return tokens; }
private:
    std::set<std::string> tokens;
};

class Visitor;

enum class ParserKind
{
    alternativeParser, sequenceParser, differenceParser, listParser, lookaheadParser, kleeneParser, positiveParser, optionalParser, expectationParser, actionParser,
    nonterminalParser, emptyParser, anyParser, tokenParser, charParser, stringParser, charSetParser, groupParser, switchParser, caseParser, ruleParser, grammarParser
};

std::string ParserKindStr(ParserKind kind);

class Parser
{
public:
    Parser(const soul::ast::SourcePos& sourcePos_, ParserKind kind_);
    inline Parser* Parent() const { return parent; }
    inline void SetParent(Parser* parent_) { parent = parent_; }
    inline const soul::ast::SourcePos& GetSourcePos() const { return sourcePos; }
    virtual ~Parser();
    virtual Parser* Clone() const = 0;
    virtual void Accept(Visitor& visitor) = 0;
    virtual std::string Name() const = 0;
    virtual std::expected<bool, int> ComputeFirst(bool& changed, std::set<Parser*>& visited) = 0;
    inline ParserKind Kind() const { return kind; }
    inline bool IsNonterminalParser() const { return kind == ParserKind::nonterminalParser; }
    inline bool IsTokenParser() const { return kind == ParserKind::tokenParser; }
    inline bool IsListParser() const { return kind == ParserKind::listParser; }
    inline bool IsSwitchParser() const { return kind == ParserKind::switchParser; }
    inline bool IsDifferenceParser() const { return kind == ParserKind::differenceParser; }
    inline const TokenSet& First() const { return first; }
    inline TokenSet& First() { return first; }
private:
    Parser* parent;
    soul::ast::SourcePos sourcePos;
    ParserKind kind;
    TokenSet first;
};

class UnaryParser : public Parser
{
public:
    UnaryParser(const soul::ast::SourcePos& sourcePos_, ParserKind kind_, Parser* child_);
    inline Parser* Child() const { return child.get(); }
    std::expected<bool, int> ComputeFirst(bool& changed, std::set<Parser*>& visited) override;
private:
    std::unique_ptr<Parser> child;
};

class BinaryParser : public Parser
{
public:
    BinaryParser(const soul::ast::SourcePos& sourcePos_, ParserKind kind_, Parser* left_, Parser* right_);
    inline Parser* Left() const { return left.get(); }
    inline Parser* Right() const { return right.get(); }
private:
    std::unique_ptr<Parser> left;
    std::unique_ptr<Parser> right;
};

class ChoiceParser : public BinaryParser
{
public:
    ChoiceParser(const soul::ast::SourcePos& sourcePos_, Parser* left_, Parser* right_);
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "choice"; }
    std::expected<bool, int> ComputeFirst(bool& changed, std::set<Parser*>& visited) override;
    void SetOptimizationFlag(int& count);
    inline bool Optimize() const { return optimize; }
private:
    bool optimize;
};

class CaseParser : public UnaryParser
{
public:
    CaseParser(const soul::ast::SourcePos& sourcePos_, Parser* child_);
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "case"; }
};

class SwitchParser : public Parser
{
public:
    SwitchParser(const soul::ast::SourcePos& sourcePos_);
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "switch"; }
    std::expected<bool, int> ComputeFirst(bool& changed, std::set<Parser*>& visited) override;
    const std::vector<std::unique_ptr<CaseParser>>& CaseParsers() const { return caseParsers; }
    void AddCaseParser(CaseParser* caseParser);
private:
    std::vector<std::unique_ptr<CaseParser>> caseParsers;
};

class SequenceParser : public BinaryParser
{
public:
    SequenceParser(const soul::ast::SourcePos& sourcePos_, Parser* left_, Parser* right_);
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "sequence"; }
    std::expected<bool, int> ComputeFirst(bool& changed, std::set<Parser*>& visited) override;
};

class DifferenceParser : public BinaryParser
{
public:
    DifferenceParser(const soul::ast::SourcePos& sourcePos_, Parser* left_, Parser* right_);
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "difference"; }
    std::expected<bool, int> ComputeFirst(bool& changed, std::set<Parser*>& visited) override;
};

class ListParser : public UnaryParser
{
public:
    ListParser(const soul::ast::SourcePos& sourcePos_, Parser* left_, Parser* right_);
    Parser* Clone() const override;
    inline Parser* Left() const { return left; }
    inline Parser* Right() const { return right; }
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "list"; }
private:
    Parser* left;
    Parser* right;
};

class LookaheadParser : public UnaryParser
{
public:
    LookaheadParser(const soul::ast::SourcePos& sourcePos_, Parser* child_);
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "lookahead"; }
};

class KleeneParser : public UnaryParser
{
public:
    KleeneParser(const soul::ast::SourcePos& sourcePos_, Parser* child_);
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "kleene"; }
    std::expected<bool, int> ComputeFirst(bool& changed, std::set<Parser*>& visited) override;
};

class PositiveParser : public UnaryParser
{
public:
    PositiveParser(const soul::ast::SourcePos& sourcePos_, Parser* child_);
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "positive"; }
};

class OptionalParser : public UnaryParser
{
public:
    OptionalParser(const soul::ast::SourcePos& sourcePos_, Parser* child_);
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "optional"; }
    std::expected<bool, int> ComputeFirst(bool& changed, std::set<Parser*>& visited) override;
};

class ExpectationParser : public UnaryParser
{
public:
    ExpectationParser(const soul::ast::SourcePos& sourcePos_, Parser* child_);
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "expectation"; }
};

class ActionParser : public UnaryParser
{
public:
    ActionParser(const soul::ast::SourcePos& sourcePos_, Parser* child_,
        soul::ast::cpp::CompoundStatementNode* successCode_, soul::ast::cpp::CompoundStatementNode* failureCode_);
    inline soul::ast::cpp::CompoundStatementNode* SuccessCode() const { return successCode.get(); }
    inline soul::ast::cpp::CompoundStatementNode* FailureCode() const { return failureCode.get(); }
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "action"; }
private:
    std::unique_ptr<soul::ast::cpp::CompoundStatementNode> successCode;
    std::unique_ptr<soul::ast::cpp::CompoundStatementNode> failureCode;
};

class RuleParser;

class NonterminalParser : public Parser
{
public:
    NonterminalParser(const soul::ast::SourcePos& sourcePos_, const std::string& ruleName_, const std::string& instanceName_, soul::ast::cpp::ExprListNode* args_);
    inline const std::string& RuleName() const { return ruleName; }
    inline const std::string& InstanceName() const { return instanceName; }
    inline const std::unique_ptr<soul::ast::cpp::ExprListNode>& Arguments() const { return arguments; }
    inline void SetRule(RuleParser* rule_) { rule = rule_; }
    inline RuleParser* Rule() const { return rule; }
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "nonterminal"; }
    std::expected<bool, int> ComputeFirst(bool& changed, std::set<Parser*>& visited) override;
private:
    std::string ruleName;
    std::string instanceName;
    std::unique_ptr<soul::ast::cpp::ExprListNode> arguments;
    RuleParser* rule;
    bool recursive;
};

class EmptyParser : public Parser
{
public:
    EmptyParser(const soul::ast::SourcePos& sourcePos_);
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "empty"; }
    std::expected<bool, int> ComputeFirst(bool& changed, std::set<Parser*>& visited) override;
};

class AnyParser : public Parser
{
public:
    AnyParser(const soul::ast::SourcePos& sourcePos_);
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "any"; }
    std::expected<bool, int> ComputeFirst(bool& changed, std::set<Parser*>& visited) override;
};

class TokenParser : public Parser
{
public:
    TokenParser(const soul::ast::SourcePos& sourcePos_, const std::string& tokenName_);
    inline const std::string& TokenName() const { return tokenName; }
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "token"; }
    std::expected<bool, int> ComputeFirst(bool& changed, std::set<Parser*>& visited) override;
private:
    std::string tokenName;
};

class CharParser : public Parser
{
public:
    CharParser(const soul::ast::SourcePos& sourcePos_, char32_t chr_);
    inline char32_t Chr() const { return chr; }
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "char"; }
    std::expected<bool, int> ComputeFirst(bool& changed, std::set<Parser*>& visited) override;
private:
    char32_t chr;
};

class StringParser : public Parser
{
public:
    StringParser(const soul::ast::SourcePos& sourcePos_, const std::u32string& str_);
    inline const std::u32string& Str() const { return str; }
    inline const std::string& ArrayName() const { return arrayName; }
    void SetArrayName(const std::string& arrayName_);
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "string"; }
    std::expected<bool, int> ComputeFirst(bool& changed, std::set<Parser*>& visited) override;
private:
    std::u32string str;
    std::string arrayName;
};

class CharSetParser : public Parser
{
public:
    CharSetParser(const soul::ast::SourcePos& sourcePos_, CharSet* charSet_);
    inline CharSet* GetCharSet() const { return charSet.get(); }
    inline const std::string& ArrayName() const { return arrayName; }
    void SetArrayName(const std::string& arrayName_);
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "charSet"; }
    std::expected<bool, int> ComputeFirst(bool& changed, std::set<Parser*>& visited) override;
private:
    std::unique_ptr<CharSet> charSet;
    std::string arrayName;
};

class GroupParser : public UnaryParser
{
public:
    GroupParser(const soul::ast::SourcePos& sourcePos_, Parser* child_);
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::string Name() const override { return "group"; }
};

class GrammarParser;

class RuleParser : public Parser
{
public:
    RuleParser(const soul::ast::SourcePos& sourcePos_, const std::string& name_);
    std::string Name() const override { return name; }
    inline void SetIndex(std::int32_t index_) { index = index_; }
    inline std::int32_t Index() const { return index; }
    inline void SetId(std::int64_t id_) { id = id_; }
    inline std::int64_t Id() const { return id; }
    void SetInfo(const std::string& info_);
    inline const std::string& Info() const { return info; }
    void AddParamOrVariable(ParamVar* paramVar);
    inline const std::vector<std::unique_ptr<Parameter>>& Params() const { return params; }
    inline const std::vector<std::unique_ptr<Variable>>& Vars() const { return vars; }
    void SetDefinition(Parser* definition_);
    inline Parser* Definition() const { return definition.get(); }
    void SetReturnType(soul::ast::cpp::TypeIdNode* returnType_);
    inline soul::ast::cpp::TypeIdNode* ReturnType() const { return returnType.get(); }
    void AddNonterminal(NonterminalParser* nonterminal);
    inline const std::vector<NonterminalParser*>& Nonterminals() const { return nonterminals; }
    void SetGrammar(GrammarParser* grammar_);
    inline GrammarParser* Grammar() const { return grammar; }
    inline bool HasReturn() const { return hasReturn; }
    inline void SetHasReturn() { hasReturn = true; }
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> ComputeFirst(bool& changed, std::set<Parser*>& visited) override;
private:
    std::string name;
    std::int32_t index;
    std::int64_t id;
    std::string info;
    std::vector<std::unique_ptr<Parameter>> params;
    std::vector<std::unique_ptr<Variable>> vars;
    std::unique_ptr<Parser> definition;
    std::unique_ptr<soul::ast::cpp::TypeIdNode> returnType;
    std::vector<NonterminalParser*> nonterminals;
    GrammarParser* grammar;
    bool hasReturn;
    bool computingFirst;
};

struct Using
{
    Using(const soul::ast::SourcePos& sourcePos_, const std::string& parserRuleId_);
    soul::ast::SourcePos sourcePos;
    std::string parserRuleId;
};

class ParserFile;

class GrammarParser : public Parser
{
public:
    GrammarParser(const soul::ast::SourcePos& sourcePos_, const std::string& name_);
    std::string Name() const override { return name; }
    inline bool Main() const { return main; }
    inline void SetMain() { main = true; }
    inline std::int32_t Id() const { return id; }
    inline void SetId(std::int32_t id_) { id = id_; }
    inline ParserFile* GetParserFile() const { return parserFile; }
    inline void SetParserFile(ParserFile* parserFile_) { parserFile = parserFile_; }
    void AddLexer(soul::ast::cpp::TypeIdNode* lexerTypeId);
    inline const std::vector<std::unique_ptr<soul::ast::cpp::TypeIdNode>>& Lexers() const { return lexers; }
    void AddUsing(const soul::ast::SourcePos& sourcePos, const std::string& parserRuleId);
    inline const std::vector<Using>& Usings() const { return usings; }
    bool AddRule(RuleParser* rule);
    bool MapRule(RuleParser* rule);
    RuleParser* GetRule(const std::string& ruleName) const;
    inline const std::vector<std::unique_ptr<RuleParser>>& Rules() const { return rules; }
    Parser* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> ComputeFirst(bool& changed, std::set<Parser*>& visited) override;
private:
    std::string name;
    bool main;
    std::int32_t id;
    ParserFile* parserFile;
    std::vector<std::unique_ptr<soul::ast::cpp::TypeIdNode>> lexers;
    std::vector<Using> usings;
    std::vector<std::unique_ptr<RuleParser>> rules;
    std::map<std::string, RuleParser*> ruleMap;
};

enum class FileKind
{
    spgFile, parserFile
};

class File
{
public:
    File(FileKind kind_, const std::string& filePath_);
    inline FileKind Kind() const { return kind; }
    inline const std::string& FilePath() const { return filePath; }
    virtual void Accept(Visitor& visitor) = 0;
private:
    FileKind kind;
    std::string filePath;
};

class SpgFileDeclaration
{
public:
    SpgFileDeclaration(const soul::ast::SourcePos& sourcePos_, FileKind fileKind_, const std::string& filePath_);
    virtual ~SpgFileDeclaration();
    inline const soul::ast::SourcePos& GetSourcePos() const { return sourcePos; }
    inline FileKind GetFileKind() const { return fileKind; }
    inline const std::string& FilePath() const { return filePath; }
private:
    soul::ast::SourcePos sourcePos;
    FileKind fileKind;
    std::string filePath;
};

class ParserFileDeclaration : public SpgFileDeclaration
{
public:
    ParserFileDeclaration(const soul::ast::SourcePos& sourcePos_, const std::string& filePath_, bool external_);
    inline bool External() const { return external; }
private:
    bool external;
};

class ParserFile : public File
{
public:
    ParserFile(const std::string& filePath_);
    std::expected<bool, int> SetExportModule(soul::ast::common::ExportModule* exportModule_);
    inline soul::ast::common::ExportModule* ExportModule() const { return exportModule.get(); }
    void AddImport(soul::ast::common::Import* imprt);
    inline const std::vector<std::unique_ptr<soul::ast::common::Import>>& Imports() const { return imports; }
    void AddParser(soul::ast::spg::GrammarParser* parser);
    inline const std::vector<std::unique_ptr<soul::ast::spg::GrammarParser>>& Parsers() const { return parsers; }
    inline bool IsExternal() const { return external; }
    inline void SetExternal() { external = true; }
    void Accept(Visitor& visitor) override;
private:
    std::unique_ptr<soul::ast::common::ExportModule> exportModule;
    std::vector<std::unique_ptr<soul::ast::common::Import>> imports;
    std::vector<std::unique_ptr<soul::ast::spg::GrammarParser>> parsers;
    bool external;
};

class SpgFile : public File
{
public:
    SpgFile(const std::string& filePath_, const std::string& projectName_);
    inline const std::string& ProjectName() const { return projectName; }
    void AddDeclaration(SpgFileDeclaration* declaration);
    inline const std::vector<std::unique_ptr<SpgFileDeclaration>>& Declarations() const { return declarations; }
    void AddParserFile(ParserFile* parserFile);
    inline const std::vector<std::unique_ptr<ParserFile>>& ParserFiles() const { return parserFiles; }
    bool AddParser(GrammarParser* parser);
    GrammarParser* GetParser(const std::string& name) const;
    void AddRule(RuleParser* rule);
    inline const std::vector<RuleParser*>& Rules() const { return rules; }
    void Accept(Visitor& visitor) override;
private:
    std::string projectName;
    std::vector<std::unique_ptr<SpgFileDeclaration>> declarations;
    std::vector<std::unique_ptr<ParserFile>> parserFiles;
    std::map<std::string, GrammarParser*> parserMap;
    std::vector<RuleParser*> rules;
};

class Visitor
{
public:
    virtual void Visit(ChoiceParser& parser) {}
    virtual void Visit(SwitchParser& parser) {}
    virtual void Visit(CaseParser& parser) {}
    virtual void Visit(SequenceParser& parser) {}
    virtual void Visit(DifferenceParser& parser) {}
    virtual void Visit(ListParser& parser) {}
    virtual void Visit(LookaheadParser& parser) {}
    virtual void Visit(KleeneParser& parser) {}
    virtual void Visit(PositiveParser& parser) {}
    virtual void Visit(OptionalParser& parser) {}
    virtual void Visit(ExpectationParser& parser) {}
    virtual void Visit(ActionParser& parser) {}
    virtual void Visit(NonterminalParser& parser) {}
    virtual void Visit(EmptyParser& parser) {}
    virtual void Visit(AnyParser& parser) {}
    virtual void Visit(TokenParser& parser) {}
    virtual void Visit(CharParser& parser) {}
    virtual void Visit(StringParser& parser) {}
    virtual void Visit(CharSetParser& parser) {}
    virtual void Visit(GroupParser& parser) {}
    virtual void Visit(RuleParser& parser) {}
    virtual void Visit(GrammarParser& parser) {}
    virtual void Visit(ParserFile& parserFile) {}
    virtual void Visit(SpgFile& spgFile) {}
};

class DefaultVisitor : public Visitor
{
public:
    DefaultVisitor();
    void Visit(ChoiceParser& parser) override;
    void Visit(SwitchParser& parser) override;
    void Visit(CaseParser& parser) override;
    void Visit(SequenceParser& parser) override;
    void Visit(DifferenceParser& parser) override;
    void Visit(ListParser& parser) override;
    void Visit(LookaheadParser& parser) override;
    void Visit(KleeneParser& parser) override;
    void Visit(PositiveParser& parser) override;
    void Visit(OptionalParser& parser) override;
    void Visit(ExpectationParser& parser) override;
    void Visit(ActionParser& parser) override;
    void Visit(GroupParser& parser) override;
    void Visit(RuleParser& parser) override;
    void Visit(GrammarParser& parser) override;
    void Visit(ParserFile& parserFile) override;
    void Visit(SpgFile& spgFile) override;
    inline void SetError(int error_) { error = error_; }
    inline int Error() const { return error; }
    inline bool Valid() const { return error == 0; }
    inline explicit operator bool() const { return Valid(); }
private:
    int error;
};

} // namespace soul::ast::spg
