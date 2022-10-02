// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.pp;
import otava.pp.lexer;
import otava.pp.parser;
import otava.pp.parser.spg.rules;
import otava.pp.state;

namespace otava::pp {

void PreprocessPPLine(Lexer& lexer, Token& token)
{
    otava::pp::state::State* state = otava::pp::state::LexerStateMap::Instance().GetState(&lexer);
    auto ppLexer = otava::pp::lexer::MakeLexer(token.match.begin, token.match.end, lexer.FileName());
    lexer.SetRuleNameMapPtr(otava::pp::parser::spg::rules::GetRuleNameMapPtr());
    otava::pp::parser::PPParser<decltype(ppLexer)>::Parse(ppLexer, state);
}

} // namespace soul::cpp20::pp
