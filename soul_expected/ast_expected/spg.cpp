// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.ast.spg;

import util_expected;

namespace soul_expected::ast::spg {

std::string ParserKindStr(ParserKind kind)
{
    switch (kind)
    {
        case ParserKind::alternativeParser:
        {
            return "alternativeParser";
        }
        case ParserKind::sequenceParser:
        {
            return "sequenceParser";
        }
        case ParserKind::differenceParser:
        {
            return "differenceParser";
        }
        case ParserKind::listParser:
        {
            return "listParser";
        }
        case ParserKind::lookaheadParser:
        {
            return "lookaheadParser";
        }
        case ParserKind::kleeneParser:
        {
            return "kleeneParser";
        }
        case ParserKind::positiveParser:
        {
            return "positiveParser";
        }
        case ParserKind::optionalParser:
        {
            return "optionalParser";
        }
        case ParserKind::expectationParser:
        {
            return "expectationParser";
        }
        case ParserKind::actionParser:
        {
            return "actionParser";
        }
        case ParserKind::nonterminalParser:
        {
            return "nonterminalParser";
        }
        case ParserKind::emptyParser:
        {
            return "emptyParser";
        }
        case ParserKind::anyParser:
        {
            return "anyParser";
        }
        case ParserKind::tokenParser:
        {
            return "tokenParser";
        }
        case ParserKind::charParser:
        {
            return "charParser";
        }
        case ParserKind::stringParser:
        {
            return "stringParser";
        }
        case ParserKind::charSetParser:
        {
            return "charSetParser";
        }
        case ParserKind::groupParser:
        {
            return "groupParser";
        }
        case ParserKind::switchParser:
        {
            return "switchParser";
        }
        case ParserKind::caseParser:
        {
            return "caseParser";
        }
        case ParserKind::ruleParser:
        {
            return "ruleParser";
        }
        case ParserKind::grammarParser:
        {
            return "grammarParser";
        }
    }
    return "<unknown parser kind>";
}

std::unexpected<int> CannotBeOptimized()
{
    return std::unexpected<int>(util::AllocateError("grammars that contain character, string or character set parsers cannot be optimized currently"));
}

ParamVar::ParamVar(const soul_expected::ast::SourcePos& sourcePos_, ParamVarKind kind_, soul_expected::ast::cpp::TypeIdNode* type_, const std::string& name_) :
    sourcePos(sourcePos_), kind(kind_), type(type_), name(name_)
{
}

ParamVar::~ParamVar()
{
}

Parameter::Parameter(const soul_expected::ast::SourcePos& sourcePos_, soul_expected::ast::cpp::TypeIdNode* type_, const std::string& name_) :
    ParamVar(sourcePos_, ParamVarKind::parameter, type_, name_)
{
}

ParamVar* Parameter::Clone() const
{
    return new Parameter(GetSourcePos(), static_cast<soul_expected::ast::cpp::TypeIdNode*>(Type()->Clone()), Name());
}

Variable::Variable(const soul_expected::ast::SourcePos& sourcePos_, soul_expected::ast::cpp::TypeIdNode* type_, const std::string& name_) :
    ParamVar(sourcePos_, ParamVarKind::variable, type_, name_)
{
}

ParamVar* Variable::Clone() const
{
    return new Variable(GetSourcePos(), static_cast<soul_expected::ast::cpp::TypeIdNode*>(Type()->Clone()), Name());
}

CharSet::CharSet() : inverse(false)
{
}

void CharSet::AddRange(const Range& range)
{
    ranges.push_back(range);
}

CharSet* CharSet::Clone() const
{
    CharSet* clone = new CharSet();
    if (inverse)
    {
        clone->SetInverse();
    }
    for (const auto& range : ranges)
    {
        clone->AddRange(range);
    }
    return clone;
}

TokenSet::TokenSet()
{
}

bool TokenSet::AddToken(const soul_expected::ast::common::Token* token)
{
    auto it = tokens.find(token);
    if (it != tokens.cend())
    {
        return false;
    }
    else
    {
        tokens.insert(token);
        return true;
    }
}

bool TokenSet::Merge(const TokenSet& that)
{
    bool changed = false;
    for (const auto& token : that.tokens)
    {
        if (AddToken(token))
        {
            changed = true;
        }
    }
    return changed;
}

bool TokenSet::Contains(const soul_expected::ast::common::Token* token) const
{
    return tokens.find(token) != tokens.cend();
}

bool TokenSet::Intersects(const TokenSet& that) const
{
    for (const auto& token : that.tokens)
    {
        if (Contains(token))
        {
            return true;
        }
    }
    return false;
}

std::string TokenSet::ToString() const
{
    std::string set("{");
    bool first = true;
    for (const auto& token : tokens)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            set.append(", ");
        }
        set.append(token->Name());
    }
    set.append("}");
    return set;
}

Parser::Parser(const soul_expected::ast::SourcePos& sourcePos_, ParserKind kind_) : parent(nullptr), sourcePos(sourcePos_), kind(kind_)
{
}

Parser::~Parser()
{
}

soul_expected::ast::common::TokenMap* Parser::GetTokenMap()
{
    if (IsGrammarParser())
    {
        const GrammarParser* grammar = static_cast<const GrammarParser*>(this);
        ParserFile* parserFile = grammar->GetParserFile();
        return parserFile->GetTokenMap();
    }
    else if (parent)
    {
        return parent->GetTokenMap();
    }
    else
    {
        return nullptr;
    }
}

UnaryParser::UnaryParser(const soul_expected::ast::SourcePos& sourcePos_, ParserKind kind_, Parser* child_) : Parser(sourcePos_, kind_), child(child_)
{
    child->SetParent(this);
}

std::expected<bool, int> UnaryParser::ComputeFirst(bool& changed, std::set<Parser*>& visited)
{
    if (visited.find(this) == visited.cend())
    {
        visited.insert(this);
        std::expected<bool, int> rv = child->ComputeFirst(changed, visited);
        if (!rv) return rv;
        if (First().Merge(child->First()))
        {
            changed = true;
        }
    }
    return std::expected<bool, int>(true);
}

BinaryParser::BinaryParser(const soul_expected::ast::SourcePos& sourcePos_, ParserKind kind_, Parser* left_, Parser* right_) : Parser(sourcePos_, kind_), left(left_), right(right_)
{
    left->SetParent(this);
    right->SetParent(this);
}

ChoiceParser::ChoiceParser(const soul_expected::ast::SourcePos& sourcePos_, Parser* left_, Parser* right_) :
    BinaryParser(sourcePos_, ParserKind::alternativeParser, left_, right_), optimize(false)
{
}

Parser* ChoiceParser::Clone() const
{
    return new ChoiceParser(GetSourcePos(), Left()->Clone(), Right()->Clone());
}

void ChoiceParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ChoiceParser::ComputeFirst(bool& changed, std::set<Parser*>& visited)
{
    if (visited.find(this) == visited.cend())
    {
        visited.insert(this);
        std::expected<bool, int> rv = Left()->ComputeFirst(changed, visited);
        if (!rv) return rv;
        rv = Right()->ComputeFirst(changed, visited);
        if (!rv) return rv;
        if (First().Merge(Left()->First()))
        {
            changed = true;
        }
        if (First().Merge(Right()->First()))
        {
            changed = true;
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ChoiceParser::SetOptimizationFlag(int& count)
{
    Parser* parent = Parent();
    while (parent)
    {
        if (parent->IsDifferenceParser())
        {
            return std::expected<bool, int>(false);
        }
        parent = parent->Parent();
    }
    soul_expected::ast::common::TokenMap* tokenMap = GetTokenMap();
    if (tokenMap)
    {
        if (!First().Contains(tokenMap->Any()))
        {
            if (!Left()->First().Contains(tokenMap->Epsilon()) && !Right()->First().Contains(tokenMap->Epsilon()) && !Left()->First().Contains(tokenMap->Any()) &&
                !Right()->First().Contains(tokenMap->Any()))
            {
                if (!Left()->First().Intersects(Right()->First()))
                {
                    optimize = true;
                    ++count;
                }
            }
        }
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("token map not found"));
    }
    return std::expected<bool, int>(true);
}

CaseParser::CaseParser(const soul_expected::ast::SourcePos& sourcePos_, Parser* child_) : UnaryParser(sourcePos_, ParserKind::caseParser, child_)
{
}

Parser* CaseParser::Clone() const
{
    CaseParser* clone = new CaseParser(GetSourcePos(), Child()->Clone());
    return clone;
}

void CaseParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

SwitchParser::SwitchParser(const soul_expected::ast::SourcePos& sourcePos_) : Parser(sourcePos_, ParserKind::switchParser)
{
}

Parser* SwitchParser::Clone() const
{
    SwitchParser* clone = new SwitchParser(GetSourcePos());
    for (const auto& caseParser : caseParsers)
    {
        clone->AddCaseParser(static_cast<CaseParser*>(caseParser->Clone()));
    }
    return clone;
}

void SwitchParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> SwitchParser::ComputeFirst(bool& changed, std::set<Parser*>& visited)
{
    if (visited.find(this) == visited.cend())
    {
        visited.insert(this);
        for (const auto& caseParser : caseParsers)
        {
            std::expected<bool, int> rv = caseParser->ComputeFirst(changed, visited);
            if (!rv) return rv;
            if (First().Merge(caseParser->First()))
            {
                changed = true;
            }
        }
    }
    return std::expected<bool, int>(true);
}

void SwitchParser::AddCaseParser(CaseParser* caseParser)
{
    caseParsers.push_back(std::unique_ptr<CaseParser>(caseParser));
    caseParser->SetParent(this);
}

SequenceParser::SequenceParser(const soul_expected::ast::SourcePos& sourcePos_, Parser* left_, Parser* right_) : BinaryParser(sourcePos_, ParserKind::sequenceParser, left_, right_)
{
}

Parser* SequenceParser::Clone() const
{
    return new SequenceParser(GetSourcePos(), Left()->Clone(), Right()->Clone());
}

void SequenceParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> SequenceParser::ComputeFirst(bool& changed, std::set<Parser*>& visited)
{
    if (visited.find(this) == visited.cend())
    {
        visited.insert(this);
        std::expected<bool, int> rv = Left()->ComputeFirst(changed, visited);
        if (!rv) return rv;
        rv = Right()->ComputeFirst(changed, visited);
        if (!rv) return rv;
        if (First().Merge(Left()->First()))
        {
            changed = true;
        }
        soul_expected::ast::common::TokenMap* tokenMap = GetTokenMap();
        if (tokenMap)
        {
            if (First().Contains(tokenMap->Epsilon()))
            {
                if (First().Merge(Right()->First()))
                {
                    changed = true;
                }
            }
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("token map not found"));
        }

    }
    return std::expected<bool, int>(true);
}

DifferenceParser::DifferenceParser(const soul_expected::ast::SourcePos& sourcePos_, Parser* left_, Parser* right_) : BinaryParser(sourcePos_, ParserKind::differenceParser, left_, right_)
{
}

Parser* DifferenceParser::Clone() const
{
    return new DifferenceParser(GetSourcePos(), Left()->Clone(), Right()->Clone());
}

void DifferenceParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> DifferenceParser::ComputeFirst(bool& changed, std::set<Parser*>& visited)
{
    if (visited.find(this) == visited.cend())
    {
        visited.insert(this);
        std::expected<bool, int> rv = Left()->ComputeFirst(changed, visited);
        if (!rv) return rv;
        if (First().Merge(Left()->First()))
        {
            changed = true;
        }
    }
    return std::expected<bool, int>(true);
}

ListParser::ListParser(const soul_expected::ast::SourcePos& sourcePos_, Parser* left_, Parser* right_) :
    UnaryParser(sourcePos_, ParserKind::listParser,
        new SequenceParser(sourcePos_, left_,
            new KleeneParser(sourcePos_,
                new SequenceParser(sourcePos_, right_, left_->Clone())))),
    left(left_), right(right_)
{
}

Parser* ListParser::Clone() const
{
    return new ListParser(GetSourcePos(), left->Clone(), right->Clone());
}

void ListParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LookaheadParser::LookaheadParser(const soul_expected::ast::SourcePos& sourcePos_, Parser* child_) : UnaryParser(sourcePos_, ParserKind::lookaheadParser, child_)
{
}

Parser* LookaheadParser::Clone() const
{
    return new LookaheadParser(GetSourcePos(), Child()->Clone());
}

void LookaheadParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

KleeneParser::KleeneParser(const soul_expected::ast::SourcePos& sourcePos_, Parser* child_) : UnaryParser(sourcePos_, ParserKind::kleeneParser, child_)
{
}

Parser* KleeneParser::Clone() const
{
    return new KleeneParser(GetSourcePos(), Child()->Clone());
}

void KleeneParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> KleeneParser::ComputeFirst(bool& changed, std::set<Parser*>& visited)
{
    if (visited.find(this) == visited.cend())
    {
        visited.insert(this);
        std::expected<bool, int> rv = Child()->ComputeFirst(changed, visited);
        if (!rv) return rv;
        if (First().Merge(Child()->First()))
        {
            changed = true;
        }
        soul_expected::ast::common::TokenMap* tokenMap = GetTokenMap();
        if (tokenMap)
        {
            bool epsilonAdded = First().AddToken(tokenMap->Epsilon());
            if (epsilonAdded)
            {
                changed = true;
            }
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("token map not found"));
        }
    }
    return std::expected<bool, int>(true);
}

PositiveParser::PositiveParser(const soul_expected::ast::SourcePos& sourcePos_, Parser* child_) : UnaryParser(sourcePos_, ParserKind::positiveParser, child_)
{
}

Parser* PositiveParser::Clone() const
{
    return new PositiveParser(GetSourcePos(), Child()->Clone());
}

void PositiveParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

OptionalParser::OptionalParser(const soul_expected::ast::SourcePos& sourcePos_, Parser* child_) : UnaryParser(sourcePos_, ParserKind::optionalParser, child_)
{
}

Parser* OptionalParser::Clone() const
{
    return new OptionalParser(GetSourcePos(), Child()->Clone());
}

void OptionalParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> OptionalParser::ComputeFirst(bool& changed, std::set<Parser*>& visited)
{
    if (visited.find(this) == visited.cend())
    {
        visited.insert(this);
        std::expected<bool, int> rv = Child()->ComputeFirst(changed, visited);
        if (!rv) return rv;
        if (First().Merge(Child()->First()))
        {
            changed = true;
        }
        soul_expected::ast::common::TokenMap* tokenMap = GetTokenMap();
        if (tokenMap)
        {
            bool epsilonAdded = First().AddToken(tokenMap->Epsilon());
            if (epsilonAdded)
            {
                changed = true;
            }
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("token map not found"));
        }
    }
    return std::expected<bool, int>(true);
}

ExpectationParser::ExpectationParser(const soul_expected::ast::SourcePos& sourcePos_, Parser* child_) : UnaryParser(sourcePos_, ParserKind::expectationParser, child_)
{
}

Parser* ExpectationParser::Clone() const
{
    return new ExpectationParser(GetSourcePos(), Child()->Clone());
}

void ExpectationParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ActionParser::ActionParser(const soul_expected::ast::SourcePos& sourcePos_, Parser* child_, soul_expected::ast::cpp::CompoundStatementNode* successCode_, soul_expected::ast::cpp::CompoundStatementNode* failureCode_) :
    UnaryParser(sourcePos_, ParserKind::actionParser, child_), successCode(successCode_), failureCode(failureCode_)
{
}

Parser* ActionParser::Clone() const
{
    soul_expected::ast::cpp::CompoundStatementNode* clonedSuccessCode = static_cast<soul_expected::ast::cpp::CompoundStatementNode*>(successCode->Clone());
    soul_expected::ast::cpp::CompoundStatementNode* clonedFailureCode = nullptr;
    if (failureCode)
    {
        clonedFailureCode = static_cast<soul_expected::ast::cpp::CompoundStatementNode*>(failureCode->Clone());
    }
    return new ActionParser(GetSourcePos(), Child()->Clone(), clonedSuccessCode, clonedFailureCode);
}

void ActionParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

NonterminalParser::NonterminalParser(const soul_expected::ast::SourcePos& sourcePos_, const std::string& ruleName_, const std::string& instanceName_, soul_expected::ast::cpp::ExprListNode* args_) :
    Parser(sourcePos_, ParserKind::nonterminalParser), ruleName(ruleName_), instanceName(instanceName_), arguments(args_), rule(nullptr), recursive(false)
{
}

Parser* NonterminalParser::Clone() const
{
    soul_expected::ast::cpp::ExprListNode* clonedArgs = nullptr;
    if (arguments)
    {
        clonedArgs = static_cast<soul_expected::ast::cpp::ExprListNode*>(arguments->Clone());
    }
    return new NonterminalParser(GetSourcePos(), ruleName, instanceName, clonedArgs);
}

void NonterminalParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> NonterminalParser::ComputeFirst(bool& changed, std::set<Parser*>& visited)
{
    if (visited.find(this) == visited.cend())
    {
        visited.insert(this);
        std::expected<bool, int> rv = rule->ComputeFirst(changed, visited);
        if (!rv) return rv;
        if (First().Merge(rule->First()))
        {
            changed = true;
        }
    }
    return std::expected<bool, int>(true);
}

EmptyParser::EmptyParser(const soul_expected::ast::SourcePos& sourcePos_) : Parser(sourcePos_, ParserKind::emptyParser)
{
}

Parser* EmptyParser::Clone() const
{
    return new EmptyParser(GetSourcePos());
}

void EmptyParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> EmptyParser::ComputeFirst(bool& changed, std::set<Parser*>& visited)
{
    if (visited.find(this) == visited.cend())
    {
        visited.insert(this);
        soul_expected::ast::common::TokenMap* tokenMap = GetTokenMap();
        if (tokenMap)
        {
            if (First().AddToken(tokenMap->Epsilon()))
            {
                changed = true;
            }
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("token map not found"));
        }
    }
    return std::expected<bool, int>(true);
}

AnyParser::AnyParser(const soul_expected::ast::SourcePos& sourcePos_) : Parser(sourcePos_, ParserKind::anyParser)
{
}

Parser* AnyParser::Clone() const
{
    return new AnyParser(GetSourcePos());
}

void AnyParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> AnyParser::ComputeFirst(bool& changed, std::set<Parser*>& visited)
{
    if (visited.find(this) == visited.cend())
    {
        visited.insert(this);
        soul_expected::ast::common::TokenMap* tokenMap = GetTokenMap();
        if (tokenMap)
        {
            if (First().AddToken(tokenMap->Any()))
            {
                changed = true;
            }
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("token map not found"));
        }
    }
    return std::expected<bool, int>(true);
}

TokenParser::TokenParser(const soul_expected::ast::SourcePos& sourcePos_, const std::string& tokenName_) : 
    Parser(sourcePos_, ParserKind::tokenParser), tokenName(tokenName_), token(nullptr)
{
}

Parser* TokenParser::Clone() const
{
    return new TokenParser(GetSourcePos(), tokenName);
}

void TokenParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> TokenParser::ComputeFirst(bool& changed, std::set<Parser*>& visited)
{
    if (visited.find(this) == visited.cend())
    {
        visited.insert(this);
        if (First().AddToken(token))
        {
            changed = true;
        }
    }
    return std::expected<bool, int>(true);
}

CharParser::CharParser(const soul_expected::ast::SourcePos& sourcePos_, char32_t chr_) : Parser(sourcePos_, ParserKind::charParser), chr(chr_)
{
}

Parser* CharParser::Clone() const
{
    return new CharParser(GetSourcePos(), chr);
}

void CharParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> CharParser::ComputeFirst(bool& changed, std::set<Parser*>& visited)
{
    return CannotBeOptimized();
}

StringParser::StringParser(const soul_expected::ast::SourcePos& sourcePos_, const std::u32string& str_) : Parser(sourcePos_, ParserKind::stringParser), str(str_)
{
}

void StringParser::SetArrayName(const std::string& arrayName_)
{
    arrayName = arrayName_;
}

Parser* StringParser::Clone() const
{
    return new StringParser(GetSourcePos(), str);
}

void StringParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> StringParser::ComputeFirst(bool& changed, std::set<Parser*>& visited)
{
    return CannotBeOptimized();
}

CharSetParser::CharSetParser(const soul_expected::ast::SourcePos& sourcePos_, CharSet* charSet_) : Parser(sourcePos_, ParserKind::charSetParser), charSet(charSet_)
{
}

void CharSetParser::SetArrayName(const std::string& arrayName_)
{
    arrayName = arrayName_;
}

Parser* CharSetParser::Clone() const
{
    return new CharSetParser(GetSourcePos(), charSet->Clone());
}

std::expected<bool, int> CharSetParser::ComputeFirst(bool& changed, std::set<Parser*>& visited)
{
    return CannotBeOptimized();
}

void CharSetParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

GroupParser::GroupParser(const soul_expected::ast::SourcePos& sourcePos_, Parser* child_) : UnaryParser(sourcePos_, ParserKind::groupParser, child_)
{
}

Parser* GroupParser::Clone() const
{
    return new GroupParser(GetSourcePos(), Child()->Clone());
}

void GroupParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

RuleParser::RuleParser(const soul_expected::ast::SourcePos& sourcePos_, const std::string& name_) :
    Parser(sourcePos_, ParserKind::ruleParser), name(name_), id(-1), index(-1), grammar(nullptr), hasReturn(false), computingFirst(false)
{
}

void RuleParser::SetInfo(const std::string& info_)
{
    info = info_;
}

void RuleParser::AddParamOrVariable(ParamVar* paramVar)
{
    if (paramVar->Kind() == ParamVarKind::parameter)
    {
        params.push_back(std::unique_ptr<Parameter>(static_cast<Parameter*>(paramVar)));
    }
    else if (paramVar->Kind() == ParamVarKind::variable)
    {
        vars.push_back(std::unique_ptr<Variable>(static_cast<Variable*>(paramVar)));
    }
}

void RuleParser::SetDefinition(Parser* definition_)
{
    definition.reset(definition_);
    definition->SetParent(this);
}

void RuleParser::SetReturnType(soul_expected::ast::cpp::TypeIdNode* returnType_)
{
    returnType.reset(returnType_);
}

void RuleParser::AddNonterminal(NonterminalParser* nonterminal)
{
    nonterminals.push_back(nonterminal);
}

void RuleParser::SetGrammar(GrammarParser* grammar_)
{
    grammar = grammar_;
}

Parser* RuleParser::Clone() const
{
    RuleParser* clone = new RuleParser(GetSourcePos(), name);
    clone->SetId(id);
    clone->SetInfo(info);
    for (const auto& param : params)
    {
        ParamVar* clonedParamVar = static_cast<ParamVar*>(param->Clone());
        clone->AddParamOrVariable(clonedParamVar);
    }
    for (const auto& var : vars)
    {
        ParamVar* clonedParamVar = static_cast<ParamVar*>(var->Clone());
        clone->AddParamOrVariable(clonedParamVar);
    }
    clone->SetDefinition(definition->Clone());
    if (returnType)
    {
        clone->SetReturnType(static_cast<soul_expected::ast::cpp::TypeIdNode*>(returnType->Clone()));
    }
    for (auto nonterminal : nonterminals)
    {
        clone->AddNonterminal(static_cast<NonterminalParser*>(nonterminal->Clone()));
    }
    if (hasReturn)
    {
        clone->SetHasReturn();
    }
    return clone;
}

void RuleParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> RuleParser::ComputeFirst(bool& changed, std::set<Parser*>& visited)
{
    if (visited.find(this) == visited.cend())
    {
        visited.insert(this);
        std::expected<bool, int> rv = definition->ComputeFirst(changed, visited);
        if (!rv) return rv;
        if (First().Merge(definition->First()))
        {
            changed = true;
        }
    }
    return std::expected<bool, int>(true);
}

Using::Using(const soul_expected::ast::SourcePos& sourcePos_, const std::string& parserRuleId_) : sourcePos(sourcePos_), parserRuleId(parserRuleId_)
{
}

GrammarParser::GrammarParser(const soul_expected::ast::SourcePos& sourcePos_, const std::string& name_) :
    Parser(sourcePos_, ParserKind::grammarParser), name(name_), main(false), id(-1), parserFile(nullptr)
{
}

void GrammarParser::AddLexer(soul_expected::ast::cpp::TypeIdNode* lexerTypeId)
{
    lexers.push_back(std::unique_ptr< soul_expected::ast::cpp::TypeIdNode>(lexerTypeId));
}

void GrammarParser::AddUsing(const soul_expected::ast::SourcePos& sourcePos, const std::string& parserRuleId)
{
    usings.push_back(Using(sourcePos, parserRuleId));
}

bool GrammarParser::AddRule(RuleParser* rule)
{
    rule->SetGrammar(this);
    rule->SetParent(this);
    rule->SetIndex(static_cast<int>(rules.size()));
    rules.push_back(std::unique_ptr<RuleParser>(rule));
    return MapRule(rule);
}

bool GrammarParser::MapRule(RuleParser* rule)
{
    auto it = ruleMap.find(rule->Name());
    if (it != ruleMap.cend())
    {
        return false;
    }
    ruleMap[rule->Name()] = rule;
    return true;
}

RuleParser* GrammarParser::GetRule(const std::string& ruleName) const
{
    auto it = ruleMap.find(ruleName);
    if (it != ruleMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

Parser* GrammarParser::Clone() const
{
    std::cerr << "grammar cannot be cloned" << "\n";
    std::exit(1);
}

void GrammarParser::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> GrammarParser::ComputeFirst(bool& changed, std::set<Parser*>& visited)
{
    if (visited.find(this) == visited.cend())
    {
        visited.insert(this);
        for (const auto& rule : rules)
        {
            std::expected<bool, int> rv = rule->ComputeFirst(changed, visited);
            if (!rv) return rv;
        }
    }
    return std::expected<bool, int>(true);
}

SpgFileDeclaration::SpgFileDeclaration(const soul_expected::ast::SourcePos& sourcePos_, soul_expected::ast::common::FileKind fileKind_, const std::string& filePath_) :
    sourcePos(sourcePos_), fileKind(fileKind_), filePath(filePath_)
{
}

SpgFileDeclaration::~SpgFileDeclaration()
{
}

ParserFileDeclaration::ParserFileDeclaration(const soul_expected::ast::SourcePos& sourcePos_, const std::string& filePath_, bool external_) :
    SpgFileDeclaration(sourcePos_, soul_expected::ast::common::FileKind::parserFile, filePath_), external(external_)
{
}

TokenFileDeclaration::TokenFileDeclaration(const soul_expected::ast::SourcePos& sourcePos_, const std::string& filePath_, bool external_) :
    SpgFileDeclaration(sourcePos_, soul_expected::ast::common::FileKind::tokenFile, filePath_), external(external_)
{
}

ParserFile::ParserFile(const std::string& filePath_) : soul_expected::ast::common::File(soul_expected::ast::common::FileKind::parserFile, filePath_), external(false)
{
}

void ParserFile::Accept(soul_expected::ast::common::Visitor& visitor)
{
    if (Visitor* spgVisitor = dynamic_cast<Visitor*>(&visitor))
    {
        spgVisitor->Visit(*this);
    }
}

std::expected<bool, int> ParserFile::SetExportModule(soul_expected::ast::common::ExportModule* exportModule_)
{
    if (exportModule)
    {
        return std::unexpected<int>(util::AllocateError("parser file '" + FilePath() + "' already has export module declaration"));
    }
    exportModule.reset(exportModule_);
    return std::expected<bool, int>(true);
}

void ParserFile::AddImport(soul_expected::ast::common::Import* imprt)
{
    imports.push_back(std::unique_ptr<soul_expected::ast::common::Import>(imprt));
}

void ParserFile::AddParser(soul_expected::ast::spg::GrammarParser* parser)
{
    parser->SetParserFile(this);
    parsers.push_back(std::unique_ptr<soul_expected::ast::spg::GrammarParser>(parser));
}

SpgFile::SpgFile(const std::string& filePath_, const std::string& projectName_) : File(soul_expected::ast::common::FileKind::spgFile, filePath_), projectName(projectName_)
{
}

soul_expected::ast::common::TokenCollection* SpgFile::GetTokenCollection(const std::string& tokenCollectionName) const
{
    auto it = tokenCollectionMap.find(tokenCollectionName);
    if (it != tokenCollectionMap.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void SpgFile::AddDeclaration(SpgFileDeclaration* declaration)
{
    declarations.push_back(std::unique_ptr<SpgFileDeclaration>(declaration));
}

void SpgFile::AddParserFile(ParserFile* parserFile)
{
    parserFiles.push_back(std::unique_ptr<ParserFile>(parserFile));
}

void SpgFile::AddTokenFile(soul_expected::ast::common::TokenFile* tokenFile)
{
    tokenFiles.push_back(std::unique_ptr<soul_expected::ast::common::TokenFile>(tokenFile));
    tokenCollectionMap[tokenFile->GetTokenCollection()->Name()] = tokenFile->GetTokenCollection();
}

void SpgFile::AddRule(RuleParser* rule)
{
    rules.push_back(rule);
}

void SpgFile::Accept(soul_expected::ast::common::Visitor& visitor)
{
    if (Visitor* spgVisitor = dynamic_cast<Visitor*>(&visitor))
    {
        spgVisitor->Visit(*this);
    }
}

bool SpgFile::AddParser(GrammarParser* parser)
{
    auto it = parserMap.find(parser->Name());
    if (it != parserMap.cend())
    {
        return false;
    }
    parserMap[parser->Name()] = parser;
    return true;
}

GrammarParser* SpgFile::GetParser(const std::string& name) const
{
    auto it = parserMap.find(name);
    if (it != parserMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

DefaultVisitor::DefaultVisitor() : error(0)
{
}

void DefaultVisitor::Visit(ChoiceParser& parser)
{
    if (!Valid()) return;
    parser.Left()->Accept(*this);
    if (!Valid()) return;
    parser.Right()->Accept(*this);
}

void DefaultVisitor::Visit(SwitchParser& parser)
{
    if (!Valid()) return;
    for (const auto& caseParser : parser.CaseParsers())
    {
        caseParser->Accept(*this);
        if (!Valid()) return;
    }
}

void DefaultVisitor::Visit(CaseParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
}

void DefaultVisitor::Visit(SequenceParser& parser)
{
    if (!Valid()) return;
    parser.Left()->Accept(*this);
    if (!Valid()) return;
    parser.Right()->Accept(*this);
}

void DefaultVisitor::Visit(DifferenceParser& parser)
{
    if (!Valid()) return;
    parser.Left()->Accept(*this);
    if (!Valid()) return;
    parser.Right()->Accept(*this);
}

void DefaultVisitor::Visit(ListParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
}

void DefaultVisitor::Visit(LookaheadParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
}

void DefaultVisitor::Visit(KleeneParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
}

void DefaultVisitor::Visit(PositiveParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
}

void DefaultVisitor::Visit(OptionalParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
}

void DefaultVisitor::Visit(ExpectationParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
}

void DefaultVisitor::Visit(ActionParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
}

void DefaultVisitor::Visit(GroupParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
}

void DefaultVisitor::Visit(RuleParser& parser)
{
    if (!Valid()) return;
    parser.Definition()->Accept(*this);
}

void DefaultVisitor::Visit(GrammarParser& parser)
{
    if (!Valid()) return;
    for (const auto& rule : parser.Rules())
    {
        rule->Accept(*this);
        if (!Valid()) return;
    }
}

void DefaultVisitor::Visit(ParserFile& parserFile)
{
    if (!Valid()) return;
    for (const auto& parser : parserFile.Parsers())
    {
        parser->Accept(*this);
        if (!Valid()) return;
    }
}

void DefaultVisitor::Visit(SpgFile& spgFile)
{
    if (!Valid()) return;
    for (const auto& parserFile : spgFile.ParserFiles())
    {
        parserFile->Accept(*this);
        if (!Valid()) return;
    }
}

} // namespace soul_expected::ast::spg
