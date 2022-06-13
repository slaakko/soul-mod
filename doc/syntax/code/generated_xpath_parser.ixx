// generated xpath_parser.ixx:

template<typename Lexer>
struct XPathParser
{
    static std::unique_ptr<soul::xml::xpath::expr::Expr> Parse(Lexer& lexer);
    static soul::parser::Match Expr(Lexer& lexer);
	...
}
