
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/concept.parser' using soul parser generator ospg version 5.0.0

export module otava.parser.concepts;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;
import otava.ast;

export namespace otava::parser::concepts {

template<typename LexerT>
struct ConceptParser
{
    static std::expected<soul::parser::Match, int> ConceptDefinition(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ConceptName(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ConceptNameChecked(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ConstraintExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> RequiresClause(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ConstraintLogicalOrExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ConstraintLogicalAndExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> RequiresExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> RequirementParameterList(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> RequirementBody(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> RequirementSeq(LexerT& lexer, otava::symbols::Context* context, otava::ast::Node* requirementBody);
    static std::expected<soul::parser::Match, int> Requirement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> SimpleRequirement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> TypeRequirement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> CompoundRequirement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ReturnTypeRequirement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NestedRequirement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> TypeConstraint(LexerT& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::concepts
