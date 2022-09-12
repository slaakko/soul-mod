
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/optimized_parser/concept.parser' using soul parser generator spg version 4.1.0

export module soul.cpp20.parser.concepts;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;

using namespace soul::cpp20::symbols::context;

export namespace soul::cpp20::parser::concepts {

template<typename Lexer>
struct ConceptParser
{
    static soul::parser::Match ConceptDefinition(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ConceptName(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ConceptNameChecked(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ConstraintExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match RequiresClause(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ConstraintLogicalOrExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ConstraintLogicalAndExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match RequiresExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match RequirementParameterList(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match RequirementBody(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match RequirementSeq(Lexer& lexer, soul::cpp20::symbols::Context* context, soul::cpp20::ast::Node* requirementBody);
    static soul::parser::Match Requirement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match SimpleRequirement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TypeRequirement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match CompoundRequirement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ReturnTypeRequirement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NestedRequirement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TypeConstraint(Lexer& lexer, soul::cpp20::symbols::Context* context);
};

} // namespace soul::cpp20::parser::concepts
