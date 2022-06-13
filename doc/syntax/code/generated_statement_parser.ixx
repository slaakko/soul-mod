// generated statement_parser.ixx:
...
template<typename Lexer>
struct StatementParser
{
    static soul::parser::Match Statement(Lexer& lexer);
    static soul::parser::Match LabeledStatement(Lexer& lexer);
    static soul::parser::Match EmptyStatement(Lexer& lexer);
	...
}
...