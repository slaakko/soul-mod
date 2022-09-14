// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.pp;
import soul.cpp20.pp.lexer;
import soul.cpp20.pp.parser;
import soul.cpp20.pp.parser.spg.rules;
import soul.cpp20.pp.state;

namespace soul::cpp20::pp {

void PreprocessPPLine(Lexer& lexer, Token& token)
{
    soul::cpp20::pp::state::State* state = soul::cpp20::pp::state::LexerStateMap::Instance().GetState(&lexer);
    auto ppLexer = soul::cpp20::pp::lexer::MakeLexer(token.match.begin, token.match.end, lexer.FileName());
    lexer.SetRuleNameMapPtr(soul::cpp20::pp::parser::spg::rules::GetRuleNameMapPtr());
    soul::cpp20::pp::parser::PPParser<decltype(ppLexer)>::Parse(ppLexer, state);
}

} // namespace soul::cpp20::pp
