module soul.lex.instantiate;

import soul.lexer;
import soul.lex.re;
import soul.lex.slg;
import soul.lex.spg;

template class soul::lexer::Lexer<soul::lex::re::RegExLexer<char32_t>, char32_t>;
template class soul::lexer::Lexer<soul::lex::slg::SlgLexer<char32_t>, char32_t>;
template class soul::lexer::Lexer<soul::lex::spg::SpgLexer<char32_t>, char32_t>;
