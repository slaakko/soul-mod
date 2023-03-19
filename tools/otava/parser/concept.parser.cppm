
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/concept.parser' using soul parser generator spg version 4.1.0

export module otava.parser.concepts;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

using namespace otava::symbols::context;

export namespace otava::parser::concepts {

template<typename Lexer>
struct ConceptParser
{
    static soul::parser::Match ConceptDefinition(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ConceptName(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ConceptNameChecked(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ConstraintExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match RequiresClause(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ConstraintLogicalOrExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ConstraintLogicalAndExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match RequiresExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match RequirementParameterList(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match RequirementBody(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match RequirementSeq(Lexer& lexer, otava::symbols::Context* context, otava::ast::Node* requirementBody);
    static soul::parser::Match Requirement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match SimpleRequirement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match TypeRequirement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match CompoundRequirement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ReturnTypeRequirement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NestedRequirement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match TypeConstraint(Lexer& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::concepts
