// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.rex.symbol;

namespace soul_expected::rex::symbol {

Symbol::~Symbol()
{
}

Char::Char(char32_t chr_) : chr(chr_)
{
}

bool Char::Match(char32_t c)
{
    return c == chr;
}

bool Any::Match(char32_t c)
{
    return true;
}

Range::Range(char32_t start_, char32_t end_) : start(start_), end(end_)
{
}

bool Range::Match(char32_t c)
{
    return c >= start && c <= end;
}

Class::Class() : inverse(false)
{
}

bool Class::Match(char32_t c)
{
    bool match = false;
    for (Symbol* symbol : symbols)
    {
        if (symbol->Match(c))
        {
            match = true;
            break;
        }
    }
    return match != inverse;
}

void Class::AddSymbol(Symbol* symbol)
{
    symbols.push_back(symbol);
}

} // namespace soul_expected::rex::symbol
