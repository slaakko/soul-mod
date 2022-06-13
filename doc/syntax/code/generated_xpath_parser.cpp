// generated xpath_parser.cpp:

namespace soul::xml::xpath::parser {

template<typename Lexer>
std::unique_ptr<soul::xml::xpath::expr::Expr> XPathParser<Lexer>::Parse(Lexer& lexer)
{
	...
	++lexer;
	soul::parser::Match match = XPathParser<Lexer>::Expr(lexer);
	...
}
...
