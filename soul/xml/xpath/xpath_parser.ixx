
// this file has been automatically generated from 'C:/work/soul-mod/soul/xml/xpath/xpath_parser.parser' using soul parser generator spg version 4.0.0

export module soul.xml.xpath.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.xml.xpath.expr;

using namespace soul::xml::xpath::expr;

export namespace soul::xml::xpath::parser {

template<typename Lexer>
struct XPathParser
{
    static std::unique_ptr<soul::xml::xpath::expr::Expr> Parse(Lexer& lexer);
    static soul::parser::Match Expr(Lexer& lexer);
    static soul::parser::Match OrExpr(Lexer& lexer);
    static soul::parser::Match AndExpr(Lexer& lexer);
    static soul::parser::Match EqualityExpr(Lexer& lexer);
    static soul::parser::Match RelationalExpr(Lexer& lexer);
    static soul::parser::Match AdditiveExpr(Lexer& lexer);
    static soul::parser::Match MultiplicativeExpr(Lexer& lexer);
    static soul::parser::Match UnaryExpr(Lexer& lexer);
    static soul::parser::Match UnionExpr(Lexer& lexer);
    static soul::parser::Match PathExpr(Lexer& lexer);
    static soul::parser::Match LocationPath(Lexer& lexer);
    static soul::parser::Match AbsoluteLocationPath(Lexer& lexer);
    static soul::parser::Match AbbreviatedAbsoluteLocationPath(Lexer& lexer);
    static soul::parser::Match RelativeLocationPath(Lexer& lexer);
    static soul::parser::Match Step(Lexer& lexer);
    static soul::parser::Match AxisSpecifier(Lexer& lexer);
    static soul::parser::Match AxisName(Lexer& lexer);
    static soul::parser::Match AbbreviatedAxisSpecifier(Lexer& lexer);
    static soul::parser::Match NodeTest(Lexer& lexer);
    static soul::parser::Match Literal(Lexer& lexer);
    static soul::parser::Match NodeType(Lexer& lexer);
    static soul::parser::Match NameTest(Lexer& lexer);
    static soul::parser::Match NCName(Lexer& lexer);
    static soul::parser::Match QName(Lexer& lexer);
    static soul::parser::Match PrefixedName(Lexer& lexer);
    static soul::parser::Match Prefix(Lexer& lexer);
    static soul::parser::Match UnprefixedName(Lexer& lexer);
    static soul::parser::Match LocalPart(Lexer& lexer);
    static soul::parser::Match Predicate(Lexer& lexer);
    static soul::parser::Match AbbreviatedStep(Lexer& lexer);
    static soul::parser::Match FunctionCall(Lexer& lexer);
    static soul::parser::Match FilterExpr(Lexer& lexer);
    static soul::parser::Match EqualityOp(Lexer& lexer);
    static soul::parser::Match RelationalOp(Lexer& lexer);
    static soul::parser::Match AdditiveOp(Lexer& lexer);
    static soul::parser::Match MultiplicativeOp(Lexer& lexer);
    static soul::parser::Match CombinePathOp(Lexer& lexer);
    static soul::parser::Match OrKeyword(Lexer& lexer);
    static soul::parser::Match AndKeyword(Lexer& lexer);
    static soul::parser::Match DivKeyword(Lexer& lexer);
    static soul::parser::Match ModKeyword(Lexer& lexer);
    static soul::parser::Match ProcessingInstructionKeyword(Lexer& lexer);
};

} // namespace soul::xml::xpath::parser
