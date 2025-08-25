
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/xml/xpath_expected/xpath.parser' using soul parser generator espg version 5.0.0

export module soul_expected.xml.xpath.parser;

import std;
import soul_expected.lexer;
import soul_expected.parser;
import soul_expected.xml.xpath.expr;

export namespace soul_expected::xml::xpath::parser {

template<typename LexerT>
struct XPathParser
{
    static std::expected<std::unique_ptr<soul_expected::xml::xpath::expr::Expr>, int> Parse(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Expr(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> OrExpr(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> AndExpr(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> EqualityExpr(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> RelationalExpr(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> AdditiveExpr(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> MultiplicativeExpr(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> UnaryExpr(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> UnionExpr(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> PathExpr(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> LocationPath(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> AbsoluteLocationPath(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> AbbreviatedAbsoluteLocationPath(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> RelativeLocationPath(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Step(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> AxisSpecifier(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> AxisName(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> AbbreviatedAxisSpecifier(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> NodeTest(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Literal(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> NodeType(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> NameTest(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> NCName(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> QName(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> PrefixedName(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Prefix(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> UnprefixedName(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> LocalPart(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Predicate(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> AbbreviatedStep(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> FunctionCall(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> FunctionName(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Argument(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> FilterExpr(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> PrimaryExpr(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> VariableReference(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Number(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> EqualityOp(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> RelationalOp(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> AdditiveOp(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> MultiplicativeOp(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> CombinePathOp(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> OrKeyword(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> AndKeyword(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> DivKeyword(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> ModKeyword(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> ProcessingInstructionKeyword(LexerT& lexer);
};

} // namespace soul_expected::xml::xpath::parser
