// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.pp;
import otava.pp.lexer;
import otava.pp.parser;
import otava.pp.parser.ospg.rules;
import otava.pp.state;
import util;

namespace otava::pp {

void PreprocessPPLine(soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>* lxr,
    const soul::lexer::Token<char32_t, soul::lexer::LexerBase<char32_t>>* token)
{
    otava::pp::state::State* state = otava::pp::state::LexerStateMap::Instance().GetState(lxr);
    auto ppl = otava::pp::lexer::MakeLexer(token->match.begin, token->match.end, lxr->FileName());
    if (!ppl)
    {
        std::cerr << util::GetErrorMessage(ppl.error()) << "\n";
        std::exit(1);
    }
    auto& ppLexer = *ppl;
    lxr->SetRuleNameMapPtr(otava::pp::parser::ospg::rules::GetRuleNameMapPtr());
    using LexerType = decltype(ppLexer);
    auto rv = otava::pp::parser::PPParser<LexerType>::Parse(ppLexer, state);
    if (!rv)
    {
        std::cerr << util::GetErrorMessage(rv.error()) << "\n";
        std::exit(1);
    }
}

} // namespace soul::cpp20::pp
