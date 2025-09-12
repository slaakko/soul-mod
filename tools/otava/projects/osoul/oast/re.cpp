// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.ast.re;

import soul.ast.slg;
import util;

namespace soul::ast::re {

Symbol::Symbol(SymbolKind kind_) : name(), kind(kind_), contained(false), dontSetContained(false)
{
}

Symbol::~Symbol()
{
}

void Symbol::SetName(const std::string& name_)
{
    name = name_;
}

CharSymbol::CharSymbol(char32_t chr_) : Symbol(SymbolKind::charSymbol), chr(chr_), error(0)
{
    std::expected<std::string, int> rv = util::ToUtf8(std::u32string(1, chr));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    SetName("(" + *rv + ")");
}

bool CharSymbol::Match(char32_t c)
{
    return chr == c;
}

void CharSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> CharSymbol::Print(CodeFormatter& formatter)
{
    if (chr == eps)
    {
        std::expected<bool, int> rv = formatter.Write("EPS");
        if (!rv) return rv;
    }
    else
    {
        std::expected<std::u32string, int> rv = util::CharStr(chr);
        if (!rv) return std::unexpected<int>(rv.error());
        std::expected<std::string, int> urv = util::ToUtf8(*rv);
        if (!urv) return std::unexpected<int>(urv.error());
        std::expected<bool, int> frv = formatter.Write(*urv);
        if (!frv) return frv;
    }
    return std::expected<bool, int>(true);
}

Any::Any() : Symbol(SymbolKind::anySymbol)
{
    SetName("(*)");
}

bool Any::Match(char32_t c)
{
    return true;
}

void Any::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> Any::Print(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write(".");
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

Range::Range() : Symbol(SymbolKind::rangeSymbol), start(), end()
{
}

Range::Range(char32_t start_, char32_t end_) : Symbol(SymbolKind::rangeSymbol), start(start_), end(end_), error(0)
{
    std::expected<std::string, int> rv = util::ToUtf8(std::u32string(1, start));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    std::expected<std::string, int> rv2 = util::ToUtf8(std::u32string(1, end));
    if (!rv2)
    {
        error = rv.error();
        return;
    }
    SetName("(" + *rv + "-" + *rv2 + ")");
}

bool Range::Match(char32_t c)
{
    return c >= start && c <= end;
}

void Range::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> Range::Print(CodeFormatter& formatter)
{
    std::expected<std::u32string, int> rv = util::CharStr(start);
    if (!rv) return std::unexpected<int>(rv.error());
    std::expected<std::string, int> u = util::ToUtf8(*rv);
    if (!u) return std::unexpected<int>(u.error());
    std::expected<bool, int> frv = formatter.Write(*u);
    if (!frv) return frv;
    frv = formatter.Write("-");
    if (!frv) return frv;
    rv = util::CharStr(end);
    if (!rv) return std::unexpected<int>(rv.error());
    u = util::ToUtf8(*rv);
    if (!u) return std::unexpected<int>(u.error());
    frv = formatter.Write(*u);
    if (!frv) return frv;
    return std::expected<bool, int>(true);
}

bool Intersect(const Range& left, const Range& right)
{
    if (left.IsEmpty() || right.IsEmpty()) return false;
    if (left.Start() <= right.Start())
    {
        return right.Start() >= left.Start() && right.Start() <= left.End();
    }
    else
    {
        return left.Start() >= right.Start() && left.Start() <= right.End();
    }
}

Range operator&(const Range& left, const Range& right)
{
    if (Intersect(left, right))
    {
        Range intersection(std::max(left.Start(), right.Start()), std::min(left.End(), right.End()));
        return intersection;
    }
    return Range(static_cast<char32_t>(1), static_cast<char32_t>(0));
}

std::vector<Range> operator-(const Range& left, const Range& right)
{
    std::vector<Range> ranges;
    if (right.Start() <= left.Start() && right.End() >= left.End())
    {
        return ranges;
    }
    else if (right.Start() > left.End() || right.End() < left.Start())
    {
        ranges.push_back(left);
    }
    else
    {
        if (right.Start() >= left.Start() && right.Start() <= left.End())
        {
            if (left.Start() <= static_cast<char32_t>(static_cast<int>(right.Start()) - 1))
            {
                ranges.push_back(Range(left.Start(), static_cast<char32_t>(static_cast<int>(right.Start()) - 1)));
            }
        }
        if (right.End() >= left.Start() && right.End() <= left.End())
        {
            if (static_cast<char32_t>(static_cast<int>(right.End()) + 1) <= left.End())
            {
                ranges.push_back(Range(static_cast<char32_t>(static_cast<int>(right.End()) + 1), left.End()));
            }
        }
    }
    return ranges;
}

std::vector<Range> operator~(const Range& that)
{
    std::vector<Range> result;
    if (that.Start() > char32_t(1))
    {
        result.push_back(Range(static_cast<char32_t>(1), static_cast<char32_t>(static_cast<int>(that.Start()) - 1)));
    }
    if (static_cast<int>(that.End()) < static_cast<int>(0x110000))
    {
        result.push_back(Range(static_cast<char32_t>(static_cast<int>(that.End()) + 1), static_cast<char32_t>(0x10FFFF)));
    }
    return result;
}

Class::Class(int index_) : Symbol(SymbolKind::classSymbol), index(index_), inverse(false)
{
    SetName("[" + std::to_string(index) + "]");
}

void Class::SetIndex(int index_)
{
    index = index_;
    SetName("[" + std::to_string(index) + "]");
}

std::expected<Class*, int> Class::MakeCanonical(LexerContext& lexerContext)
{
    std::vector<Range> rangeVec;
    Class* canonicalClass = new Class(-1);
    for (Symbol* symbol : symbols)
    {
        if (symbol->Kind() == SymbolKind::charSymbol)
        {
            CharSymbol* chr = static_cast<CharSymbol*>(symbol);
            rangeVec.push_back(Range(chr->Chr(), chr->Chr()));
        }
        else if (symbol->Kind() == SymbolKind::rangeSymbol)
        {
            Range* range = static_cast<Range*>(symbol);
            rangeVec.push_back(*range);
        }
        else if (symbol->Kind() == SymbolKind::anySymbol)
        {
            return std::unexpected<int>(util::AllocateError("class contains any"));
        }
        else if (symbol->Kind() == SymbolKind::classSymbol)
        {
            return std::unexpected<int>(util::AllocateError("class contains class"));
        }
    }
    for (const Range& range : rangeVec)
    {
        canonicalClass->ranges.push_back(range);
    }
    if (inverse)
    {
        canonicalClass->MakeInverse(lexerContext);
    }
    return std::expected<Class*, int>(canonicalClass);
}

void Class::MakeMinimal(LexerContext& lexerContext)
{
    std::vector<Range> rangeVec;
    for (const Range& range : ranges)
    {
        rangeVec.push_back(range);
    }
    ranges.clear();
    std::sort(rangeVec.begin(), rangeVec.end());
    std::vector<Range>::iterator e = std::unique(rangeVec.begin(), rangeVec.end());
    rangeVec.erase(e, rangeVec.end());
    bool changed = true;
    while (changed)
    {
        changed = false;
        std::vector<Range> combinedRanges;
        for (int i = 0; i < rangeVec.size(); ++i)
        {
            bool combined = false;
            Range current = rangeVec[i];
            if (i > 0)
            {
                Range left = rangeVec[i - 1];
                if (static_cast<char32_t>(static_cast<int>(left.End()) + 1) == current.Start())
                {
                    combinedRanges.push_back(Range(left.Start(), current.End()));
                    combined = true;
                }
            }
            if (i < rangeVec.size() - 1)
            {
                Range right = rangeVec[i + 1];
                if (static_cast<char32_t>(static_cast<int>(current.End()) + 1) == right.Start())
                {
                    combinedRanges.push_back(Range(current.Start(), right.End()));
                    combined = true;
                }
            }
            if (combined)
            {
                changed = true;
            }
            else
            {
                combinedRanges.push_back(current);
            }
        }
        std::sort(combinedRanges.begin(), combinedRanges.end());
        std::vector<Range>::iterator e = std::unique(combinedRanges.begin(), combinedRanges.end());
        combinedRanges.erase(e, combinedRanges.end());
        std::swap(rangeVec, combinedRanges);
    }
    symbols.clear();
    chars.clear();
    for (const Range& range : rangeVec)
    {
        if (range.IsEmpty()) continue;
        ranges.push_back(range);
        if (chars.empty())
        {
            AddChar(range.Start());
        }
    }
}

void Class::MakeInverse(LexerContext& lexerContext)
{
    std::vector<Range> rangeVec;
    for (const Range& range : ranges)
    {
        rangeVec.push_back(range);
    }
    ranges.clear();
    std::vector<Range> inverseRanges;
    inverseRanges.push_back(Range(1, 0x10FFFF));
    for (const Range& range : rangeVec)
    {
        std::vector<Range> newInverse;
        for (const Range& i : inverseRanges)
        {
            if (Intersect(range, i))
            {
                Range intersection = range & i;
                Range left = Range(i.Start(), static_cast<char32_t>(static_cast<int>(intersection.Start()) - 1));
                if (!left.IsEmpty())
                {
                    newInverse.push_back(left);
                }
                Range right = Range(static_cast<char32_t>(static_cast<int>(intersection.End()) + 1), i.End());
                if (!right.IsEmpty())
                {
                    newInverse.push_back(right);
                }
            }
            else
            {
                newInverse.push_back(i);
            }
        }
        std::swap(inverseRanges, newInverse);
    }
    symbols.clear();
    chars.clear();
    for (const Range& range : inverseRanges)
    {
        ranges.push_back(range);
        if (chars.empty())
        {
            AddChar(range.Start());
        }
    }
    MakeMinimal(lexerContext);
    inverse = false;
}

Class* Class::Clone()
{
    Class* cls = new Class(-1);
    for (Symbol* symbol : symbols)
    {
        cls->AddSymbol(symbol);
    }
    for (char32_t c : chars)
    {
        cls->AddChar(c);
    }
    return cls;
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

void Class::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void Class::AddSymbol(Symbol* symbol)
{
    symbol->SetContained();
    symbols.push_back(symbol);
}

void Class::AddChar(char32_t c)
{
    chars.push_back(c);
}

std::expected<bool, int> Class::Print(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("CLASS " + Name() + ": ");
    if (!rv) return rv;
    if (ranges.empty())
    {
        rv = formatter.Write("[");
        if (!rv) return rv;
        if (inverse)
        {
            rv = formatter.Write("^");
            if (!rv) return rv;
        }
        bool first = true;
        for (Symbol* symbol : symbols)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                rv = formatter.Write(", ");
                if (!rv) return rv;
            }
            rv = symbol->Print(formatter);
            if (!rv) return rv;
        }
        rv = formatter.WriteLine("]");
        if (!rv) return rv;
    }
    else
    {
        rv = formatter.Write("{");
        if (!rv) return rv;
        bool first = true;
        for (auto& range : ranges)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                rv = formatter.Write(", ");
                if (!rv) return rv;
            }
            rv = range.Print(formatter);
            if (!rv) return rv;
        }
        rv = formatter.WriteLine("}");
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

bool operator==(const Class& left, const Class& right)
{
    if (left.Symbols().size() != right.Symbols().size()) return false;
    int n = static_cast<int>(left.Symbols().size());
    for (int i = 0; i < n; ++i)
    {
        Symbol* leftSymbol = left.Symbols()[i];
        Symbol* rightSymbol = right.Symbols()[i];
        if (leftSymbol->Kind() == SymbolKind::rangeSymbol && rightSymbol->Kind() == SymbolKind::rangeSymbol)
        {
            const Range* leftRange = static_cast<const Range*>(leftSymbol);
            const Range* rightRange = static_cast<const Range*>(rightSymbol);
            if (!(*leftRange == *rightRange))
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}

struct RangeEndLess
{
    bool operator()(const Range& left, const Range& right) const
    {
        if (left.End() < right.End()) return true;
        if (left.End() > right.End()) return false;
        return left.Start() < right.Start();
    }
};

bool Intersect(const Class& left, const Class& right)
{
    for (Symbol* leftSymbol : left.Symbols())
    {
        if (leftSymbol->Kind() == SymbolKind::rangeSymbol)
        {
            Range* leftRange = static_cast<Range*>(leftSymbol);
            for (Symbol* rightSymbol : right.Symbols())
            {
                if (rightSymbol->Kind() == SymbolKind::rangeSymbol)
                {
                    Range* rightRange = static_cast<Range*>(rightSymbol);
                    if (Intersect(*leftRange, *rightRange))
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

std::expected<Class*, int> MakeIntertersection(const Class& left, const Class& right, LexerContext& lexerContext)
{
    std::vector<Range> leftRanges;
    for (Symbol* leftSymbol : left.Symbols())
    {
        if (leftSymbol->Kind() == SymbolKind::rangeSymbol)
        {
            Range* leftRange = static_cast<Range*>(leftSymbol);
            leftRanges.push_back(*leftRange);
        }
    }
    std::vector<Range> rightRanges;
    for (Symbol* rightSymbol : right.Symbols())
    {
        if (rightSymbol->Kind() == SymbolKind::rangeSymbol)
        {
            Range* rightRange = static_cast<Range*>(rightSymbol);
            rightRanges.push_back(*rightRange);
        }
    }
    std::vector<Range> intersection;
    for (const Range& left : leftRanges)
    {
        std::vector<Range>::iterator start = std::lower_bound(rightRanges.begin(), rightRanges.end(), left);
        std::vector<Range>::iterator end = std::upper_bound(rightRanges.begin(), rightRanges.end(), left, RangeEndLess());
        if (start != rightRanges.begin()) --start;
        if (end < rightRanges.end()) ++end;
        for (std::vector<Range>::iterator i = start; i != end; ++i)
        {
            const Range& right = *i;
            if (left == right)
            {
                intersection.push_back(left);
                break;
            }
            else if (Intersect(left, right))
            {
                intersection.push_back(left & right);
            }
        }
    }
    std::sort(intersection.begin(), intersection.end());
    std::vector<Range>::iterator e = std::unique(intersection.begin(), intersection.end());
    intersection.erase(e, intersection.end());
    Class* cls = lexerContext.MakeClass();
    for (const Range& i : intersection)
    {
        std::expected<Symbol*, int> rv = lexerContext.MakeRange(i.Start(), i.End());
        if (!rv) return std::unexpected<int>(rv.error());
        cls->AddSymbol(*rv);
        if (cls->Chars().empty())
        {
            cls->AddChar(i.Start());
        }
    }
    return std::expected<Class*, int>(cls);
}

std::expected<Class*, int> MakeDifference(const Class& left, const Class& right, LexerContext& lexerContext)
{
    std::vector<Range> leftRanges;
    for (Symbol* leftSymbol : left.Symbols())
    {
        if (leftSymbol->Kind() == SymbolKind::rangeSymbol)
        {
            Range* leftRange = static_cast<Range*>(leftSymbol);
            leftRanges.push_back(*leftRange);
        }
    }
    std::vector<Range> rightRanges;
    for (Symbol* rightSymbol : right.Symbols())
    {
        if (rightSymbol->Kind() == SymbolKind::rangeSymbol)
        {
            Range* rightRange = static_cast<Range*>(rightSymbol);
            rightRanges.push_back(*rightRange);
        }
    }
    std::vector<Range> difference;
    for (const Range& left : leftRanges)
    {
        bool found = false;
        std::vector<Range> diffs;
        std::vector<Range>::iterator start = std::lower_bound(rightRanges.begin(), rightRanges.end(), left);
        std::vector<Range>::iterator end = std::upper_bound(rightRanges.begin(), rightRanges.end(), left, RangeEndLess());
        if (start != rightRanges.begin()) --start;
        if (end < rightRanges.end()) ++end;
        for (std::vector<Range>::iterator i = start; i != end; ++i)
        {
            const Range& right = *i;
            if (left == right)
            {
                found = true;
                break;
            }
            else
            {
                if (Intersect(left, right))
                {
                    Range intersection = left & right;
                    Range l = Range(left.Start(), static_cast<char32_t>(static_cast<int>(intersection.Start()) - 1));
                    if (!l.IsEmpty())
                    {
                        diffs.push_back(l);
                    }
                    Range r = Range(static_cast<char32_t>(static_cast<int>(intersection.End()) + 1), left.End());
                    if (!r.IsEmpty())
                    {
                        diffs.push_back(r);
                    }
                }
            }
        }
        if (!found)
        {
            if (diffs.empty())
            {
                difference.push_back(left);
            }
            else
            {
                for (const Range& diff : diffs)
                {
                    difference.push_back(diff);
                }
            }
        }
    }
    Class* d = lexerContext.MakeClass();
    for (const Range& r : difference)
    {
        std::expected<Symbol*, int> rv = lexerContext.MakeRange(r.Start(), r.End());
        if (!rv) return std::unexpected<int>(rv.error());
        d->AddSymbol(*rv);
        if (d->Chars().empty())
        {
            d->AddChar(r.Start());
        }
    }
    d->MakeMinimal(lexerContext);
    return std::expected<Class*, int>(d);
}

NfaEdge::NfaEdge(Symbol* symbol_, NfaState* next_) : symbol(symbol_), next(next_)
{
}

std::expected<bool, int> NfaEdge::Print(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = symbol->Print(formatter);
    if (!rv) return rv;
    return formatter.WriteLine("-> " + std::to_string(next->Id()));
}

NfaState::NfaState(int id_, int ruleIndex_) : id(id_), ruleIndex(ruleIndex_), accept(false)
{
}

void NfaState::SetEdges(const std::vector<NfaEdge>& edges_)
{
    edges = edges_;
    for (NfaEdge& edge : edges)
    {
        edge.Next()->AddPrev(this);
    }
}

void NfaState::AddEdge(const NfaEdge& edge)
{
    edges.push_back(edge);
    edge.Next()->AddPrev(this);
}

void NfaState::AddPrev(NfaState* prev_)
{
    prev.insert(prev_);
}

std::vector<NfaState*> NfaState::Next(char32_t c) const
{
    std::vector<NfaState*> next;
    for (const auto& edge : edges)
    {
        Symbol* symbol = edge.GetSymbol();
        if (symbol->Match(c))
        {
            next.push_back(edge.Next());
        }
    }
    return next;
}

std::expected<bool, int> NfaState::Print(CodeFormatter& formatter)
{
    std::string str = std::to_string(id);
    if (ruleIndex != -1)
    {
        str.append(" : RULE=").append(std::to_string(ruleIndex));
    }
    if (accept)
    {
        str.append(" : ACCEPT");
    }
    if (!prev.empty())
    {
        str.append(" : prev:");
        for (NfaState* p : prev)
        {
            str.append(" ").append(std::to_string(p->Id()));
        }
    }
    std::expected<bool, int> rv = formatter.WriteLine(str);
    if (!rv) return rv;
    formatter.IncIndent();
    for (NfaEdge& edge : edges)
    {
        rv = edge.Print(formatter);
        if (!rv) return rv;
    }
    formatter.DecIndent();
    return std::expected<bool, int>(true);
}

Nfa::Nfa() : start(nullptr), end(nullptr)
{
}

Nfa::Nfa(NfaState* start_, NfaState* end_) : start(start_), end(end_)
{
}

Nfa MakeNfa(LexerContext& lexerContext, Symbol* symbol)
{
    NfaState* start = lexerContext.MakeNfaState();
    NfaState* end = lexerContext.MakeNfaState();
    end->SetAccept(true);
    start->AddEdge(NfaEdge(symbol, end));
    Nfa nfa(start, end);
    return nfa;
}

Nfa Cat(const Nfa& left, const Nfa& right)
{
    Nfa cat(left);
    NfaState* leftEnd = cat.End();
    leftEnd->SetAccept(false);
    NfaState* rightStart = right.Start();
    rightStart->SetRuleIndex(-1);
    leftEnd->SetEdges(rightStart->Edges());
    cat.SetEnd(right.End());
    return cat;
}

Nfa Alt(LexerContext& lexerContext, const Nfa& left, const Nfa& right)
{
    NfaState* leftStart = left.Start();
    NfaState* leftEnd = left.End();
    NfaState* rightStart = right.Start();
    NfaState* rightEnd = right.End();
    NfaState* start = lexerContext.MakeNfaState();
    NfaState* end = lexerContext.MakeNfaState();
    end->SetAccept(true);
    start->AddEdge(NfaEdge(lexerContext.MakeEpsilon(), leftStart));
    start->AddEdge(NfaEdge(lexerContext.MakeEpsilon(), rightStart));
    Nfa alt;
    alt.SetStart(start);
    leftEnd->SetAccept(false);
    leftEnd->AddEdge(NfaEdge(lexerContext.MakeEpsilon(), end));
    rightEnd->SetAccept(false);
    rightEnd->AddEdge(NfaEdge(lexerContext.MakeEpsilon(), end));
    alt.SetEnd(end);
    return alt;
}

Nfa Kleene(LexerContext& lexerContext, const Nfa& nfa)
{
    Nfa kleene;
    NfaState* start = lexerContext.MakeNfaState();
    NfaState* end = lexerContext.MakeNfaState();
    end->SetAccept(true);
    start->AddEdge(NfaEdge(lexerContext.MakeEpsilon(), end));
    kleene.SetStart(start);
    NfaState* nfaStart = nfa.Start();
    start->AddEdge(NfaEdge(lexerContext.MakeEpsilon(), nfaStart));
    NfaState* nfaEnd = nfa.End();
    nfaEnd->SetAccept(false);
    nfaEnd->AddEdge(NfaEdge(lexerContext.MakeEpsilon(), end));
    nfaEnd->AddEdge(NfaEdge(lexerContext.MakeEpsilon(), nfaStart));
    kleene.SetEnd(end);
    return kleene;
}

Nfa Pos(LexerContext& lexerContext, const Nfa& nfa)
{
    Nfa pos;
    NfaState* start = lexerContext.MakeNfaState();
    NfaState* end = lexerContext.MakeNfaState();
    end->SetAccept(true);
    pos.SetStart(start);
    NfaState* nfaStart = nfa.Start();
    start->AddEdge(NfaEdge(lexerContext.MakeEpsilon(), nfaStart));
    NfaState* nfaEnd = nfa.End();
    nfaEnd->SetAccept(false);
    nfaEnd->AddEdge(NfaEdge(lexerContext.MakeEpsilon(), end));
    nfaEnd->AddEdge(NfaEdge(lexerContext.MakeEpsilon(), nfaStart));
    pos.SetEnd(end);
    return pos;
}

Nfa Opt(LexerContext& lexerContext, const Nfa& nfa)
{
    Nfa opt(nfa);
    opt.Start()->AddEdge(NfaEdge(lexerContext.MakeEpsilon(), opt.End()));
    return opt;
}

DfaState::DfaState(int id_, const std::vector<int>& nfaStateIds_) : id(id_), nfaStateIds(nfaStateIds_), next(), marked(false), accept(false), ruleIndex(-1)
{
}

void DfaState::AddNext(DfaState* n)
{
    next.push_back(n);
}

DfaState* DfaState::Next(int i) const
{
    if (i >= 0 && i < next.size())
    {
        return next[i];
    }
    else
    {
        return nullptr;
    }
}

std::expected<bool, int> DfaState::Print(LexerContext& context, CodeFormatter& formatter)
{
    std::string str = std::to_string(id);
    str.append("[");
    bool first = true;
    for (int nfaStateId : nfaStateIds)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            str.append(", ");
        }
        str.append(std::to_string(nfaStateId));
    }
    str.append("]");
    if (accept)
    {
        str.append(" : ACCEPT");
    }
    if (ruleIndex != -1)
    {
        str.append(" : RULE=" + std::to_string(ruleIndex));
    }
    std::expected<bool, int> rv = formatter.WriteLine(str);
    if (!rv) return rv;
    formatter.IncIndent();
    int n = static_cast<int>(next.size());
    for (int i = 0; i < n; ++i)
    {
        if (next[i])
        {
            rv = context.Partition()[i]->Print(formatter);
            if (!rv) return rv;
            rv = formatter.WriteLine("-> " + std::to_string(next[i]->Id()));
            if (!rv) return rv;
        }
    }
    formatter.DecIndent();
    return std::expected<bool, int>(true);
}

void Dfa::AddState(DfaState* state)
{
    states.push_back(state);
}

std::expected<bool, int> Dfa::Finalize(LexerContext& lexerContext)
{
    for (auto state : states)
    {
        for (auto nfaStateId : state->NfaStateIds())
        {
            std::expected<NfaState*, int> rv = lexerContext.GetNfaState(nfaStateId);
            if (!rv) return std::unexpected<int>(rv.error());
            NfaState* nfaState = *rv;
            if (nfaState->Accept())
            {
                state->SetAccept(true);
                if (state->RuleIndex() == -1 || (nfaState->RuleIndex() != -1 && nfaState->RuleIndex() < state->RuleIndex()))
                {
                    state->SetRuleIndex(nfaState->RuleIndex());
                }
            }
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Dfa::Print(LexerContext& lexerContext, CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.WriteLine("DFA:");
    if (!rv) return rv;
    for (DfaState* state : states)
    {
        rv = state->Print(lexerContext, formatter);
        if (!rv) return rv;
    }
    formatter.WriteLine();
    return std::expected<bool, int>(true);
}

std::expected<std::vector<int>, int> EpsilonClosure(LexerContext& lexerContext, const std::vector<int>& stateIds)
{
    std::vector<int> stack;
    for (int state : stateIds)
    {
        stack.push_back(state);
    }
    std::vector<int> epsilonClosure = stateIds;
    while (!stack.empty())
    {
        int s = stack.back();
        stack.pop_back();
        std::expected<NfaState*, int> rv = lexerContext.GetNfaState(s);
        if (!rv) return std::unexpected<int>(rv.error());
        NfaState* state = *rv;
        std::vector<NfaState*> u = state->Next(eps);
        for (NfaState* vs : u)
        {
            int v = vs->Id();
            if (std::find(epsilonClosure.cbegin(), epsilonClosure.cend(), v) == epsilonClosure.cend())
            {
                epsilonClosure.push_back(v);
                stack.push_back(v);
            }
        }
    }
    return std::expected<std::vector<int>, int>(epsilonClosure);
}

std::expected<std::vector<int>, int> EpsilonClosure(LexerContext& lexerContext, int stateId)
{
    std::vector<int> states(1, stateId);
    return EpsilonClosure(lexerContext, states);
}

std::expected<std::vector<int>, int> Move(LexerContext& lexerContext, const std::vector<int>& stateIds, char32_t c)
{
    std::vector<int> next;
    for (int stateId : stateIds)
    {
        std::expected<NfaState*, int> rv = lexerContext.GetNfaState(stateId);
        if (!rv) return std::unexpected<int>(rv.error());
        NfaState* state = *rv;
        std::vector<NfaState*> n = state->Next(c);
        for (NfaState* sn : n)
        {
            int s = sn->Id();
            if (std::find(next.cbegin(), next.cend(), s) == next.cend())
            {
                next.push_back(s);
            }
        }
    }
    return std::expected<std::vector<int>, int>(next);
}

std::expected<Dfa, int> Compile(LexerContext& lexerContext, Nfa& nfa)
{
    Dfa dfa;
    std::expected<std::vector<int>, int> rv = EpsilonClosure(lexerContext, nfa.Start()->Id());
    if (!rv) return std::unexpected<int>(rv.error());
    std::vector<int> start = *rv;
    DfaState* s = lexerContext.MakeDfaState(start);
    s->Mark();
    std::vector<DfaState*> stack;
    stack.push_back(s);
    while (!stack.empty())
    {
        DfaState* state = stack.back();
        stack.pop_back();
        dfa.AddState(state);
        for (Class* cls : lexerContext.Partition())
        {
            if (!cls->Chars().empty())
            {
                char32_t c = cls->Chars().front();
                std::expected<std::vector<int>, int> mrv = Move(lexerContext, state->NfaStateIds(), c);
                if (!mrv) return std::unexpected<int>(mrv.error());
                rv = EpsilonClosure(lexerContext, *mrv);
                std::vector<int> next = *rv;
                if (next.empty())
                {
                    state->AddNext(nullptr);
                }
                else
                {
                    DfaState* n = lexerContext.MakeDfaState(next);
                    state->AddNext(n);
                    if (!n->IsMarked())
                    {
                        n->Mark();
                        stack.push_back(n);
                    }
                }
            }
        }
    }
    std::expected<bool, int> drv = dfa.Finalize(lexerContext);
    if (!rv) return std::unexpected<int>(drv.error());
    return std::expected<Dfa, int>(std::move(dfa));
}

ExprParser::~ExprParser()
{
}

LexerContext::LexerContext() :
    nextNfaStateId(0), nextDfaStateId(0), ruleIndex(-1), classIndex(0), any(), epsilon(eps),
    asciiIdStart(new Class(classIndex)), asciiIdCont(new Class(classIndex + 1)), unicodeIdStart(new Class(classIndex + 2)), unicodeIdCont(new Class(classIndex + 3)),
    tokens(nullptr), keywords(nullptr), expressions(nullptr), lxr(nullptr), currentExpression(nullptr), exprParser(nullptr), masterNfaIndex(-1), error(0),
    verbose(false), debug(false)
{
    classIndex += 4;
    symbols.push_back(asciiIdStart);
    symbols.push_back(asciiIdCont);
    symbols.push_back(unicodeIdStart);
    symbols.push_back(unicodeIdCont);

    asciiIdStart->SetName("{ascii_id_start}");
    std::expected<Symbol*, int> rv = MakeRange('A', 'Z');
    if (!rv)
    {
        error = rv.error();
        return;
    }
    asciiIdStart->AddSymbol(*rv);
    rv = MakeRange('a', 'z');
    if (!rv)
    {
        error = rv.error();
        return;
    }
    asciiIdStart->AddSymbol(*rv);
    rv = MakeChar('_');
    if (!rv)
    {
        error = rv.error();
        return;
    }
    asciiIdStart->AddSymbol(*rv);
    asciiIdCont->SetName("{ascii_id_cont}");
    rv = MakeRange('A', 'Z');
    if (!rv)
    {
        error = rv.error();
        return;
    }
    asciiIdCont->AddSymbol(*rv);
    rv = MakeRange('a', 'z');
    if (!rv)
    {
        error = rv.error();
        return;
    }
    asciiIdCont->AddSymbol(*rv);
    rv = MakeRange('0', '9');
    if (!rv)
    {
        error = rv.error();
        return;
    }
    asciiIdCont->AddSymbol(*rv);
    rv = MakeChar('_');
    if (!rv)
    {
        error = rv.error();
        return;
    }
    asciiIdCont->AddSymbol(*rv);

    unicodeIdStart->SetName("{unicode_id_start}");
    rv = MakeRange(static_cast<char32_t>(65), static_cast<char32_t>(90));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(95), static_cast<char32_t>(95));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(97), static_cast<char32_t>(122));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(170), static_cast<char32_t>(170));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(181), static_cast<char32_t>(181));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(186), static_cast<char32_t>(186));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(192), static_cast<char32_t>(214));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(216), static_cast<char32_t>(246));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(248), static_cast<char32_t>(705));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(710), static_cast<char32_t>(721));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(736), static_cast<char32_t>(740));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(748), static_cast<char32_t>(748));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(750), static_cast<char32_t>(750));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(880), static_cast<char32_t>(884));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(886), static_cast<char32_t>(887));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(890), static_cast<char32_t>(893));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(895), static_cast<char32_t>(895));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(902), static_cast<char32_t>(902));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(904), static_cast<char32_t>(906));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(908), static_cast<char32_t>(908));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(910), static_cast<char32_t>(929));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(931), static_cast<char32_t>(1013));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1015), static_cast<char32_t>(1153));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1162), static_cast<char32_t>(1327));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1329), static_cast<char32_t>(1366));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1369), static_cast<char32_t>(1369));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1376), static_cast<char32_t>(1416));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1488), static_cast<char32_t>(1514));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1519), static_cast<char32_t>(1522));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1568), static_cast<char32_t>(1610));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1646), static_cast<char32_t>(1647));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1649), static_cast<char32_t>(1747));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1749), static_cast<char32_t>(1749));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1765), static_cast<char32_t>(1766));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1774), static_cast<char32_t>(1775));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1786), static_cast<char32_t>(1788));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1791), static_cast<char32_t>(1791));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1808), static_cast<char32_t>(1808));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1810), static_cast<char32_t>(1839));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1869), static_cast<char32_t>(1957));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1969), static_cast<char32_t>(1969));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1994), static_cast<char32_t>(2026));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2036), static_cast<char32_t>(2037));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2042), static_cast<char32_t>(2042));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2048), static_cast<char32_t>(2069));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2074), static_cast<char32_t>(2074));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2084), static_cast<char32_t>(2084));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2088), static_cast<char32_t>(2088));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2112), static_cast<char32_t>(2136));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2144), static_cast<char32_t>(2154));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2208), static_cast<char32_t>(2228));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2230), static_cast<char32_t>(2237));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2308), static_cast<char32_t>(2361));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2365), static_cast<char32_t>(2365));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2384), static_cast<char32_t>(2384));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2392), static_cast<char32_t>(2401));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2417), static_cast<char32_t>(2432));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2437), static_cast<char32_t>(2444));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2447), static_cast<char32_t>(2448));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2451), static_cast<char32_t>(2472));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2474), static_cast<char32_t>(2480));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2482), static_cast<char32_t>(2482));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2486), static_cast<char32_t>(2489));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2493), static_cast<char32_t>(2493));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2510), static_cast<char32_t>(2510));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2524), static_cast<char32_t>(2525));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2527), static_cast<char32_t>(2529));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2544), static_cast<char32_t>(2545));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2556), static_cast<char32_t>(2556));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2565), static_cast<char32_t>(2570));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2575), static_cast<char32_t>(2576));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2579), static_cast<char32_t>(2600));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2602), static_cast<char32_t>(2608));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2610), static_cast<char32_t>(2611));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2613), static_cast<char32_t>(2614));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2616), static_cast<char32_t>(2617));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2649), static_cast<char32_t>(2652));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2654), static_cast<char32_t>(2654));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2674), static_cast<char32_t>(2676));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2693), static_cast<char32_t>(2701));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2703), static_cast<char32_t>(2705));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2707), static_cast<char32_t>(2728));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2730), static_cast<char32_t>(2736));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2738), static_cast<char32_t>(2739));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2741), static_cast<char32_t>(2745));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2749), static_cast<char32_t>(2749));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2768), static_cast<char32_t>(2768));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2784), static_cast<char32_t>(2785));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2809), static_cast<char32_t>(2809));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2821), static_cast<char32_t>(2828));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2831), static_cast<char32_t>(2832));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2835), static_cast<char32_t>(2856));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2858), static_cast<char32_t>(2864));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2866), static_cast<char32_t>(2867));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2869), static_cast<char32_t>(2873));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2877), static_cast<char32_t>(2877));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2908), static_cast<char32_t>(2909));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2911), static_cast<char32_t>(2913));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2929), static_cast<char32_t>(2929));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2947), static_cast<char32_t>(2947));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2949), static_cast<char32_t>(2954));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2958), static_cast<char32_t>(2960));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2962), static_cast<char32_t>(2965));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2969), static_cast<char32_t>(2970));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2972), static_cast<char32_t>(2972));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2974), static_cast<char32_t>(2975));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2979), static_cast<char32_t>(2980));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2984), static_cast<char32_t>(2986));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2990), static_cast<char32_t>(3001));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3024), static_cast<char32_t>(3024));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3077), static_cast<char32_t>(3084));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3086), static_cast<char32_t>(3088));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3090), static_cast<char32_t>(3112));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3114), static_cast<char32_t>(3129));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3133), static_cast<char32_t>(3133));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3160), static_cast<char32_t>(3162));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3168), static_cast<char32_t>(3169));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3200), static_cast<char32_t>(3200));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3205), static_cast<char32_t>(3212));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3214), static_cast<char32_t>(3216));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3218), static_cast<char32_t>(3240));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3242), static_cast<char32_t>(3251));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3253), static_cast<char32_t>(3257));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3261), static_cast<char32_t>(3261));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3294), static_cast<char32_t>(3294));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3296), static_cast<char32_t>(3297));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3313), static_cast<char32_t>(3314));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3333), static_cast<char32_t>(3340));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3342), static_cast<char32_t>(3344));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3346), static_cast<char32_t>(3386));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3389), static_cast<char32_t>(3389));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3406), static_cast<char32_t>(3406));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3412), static_cast<char32_t>(3414));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3423), static_cast<char32_t>(3425));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3450), static_cast<char32_t>(3455));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3461), static_cast<char32_t>(3478));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3482), static_cast<char32_t>(3505));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3507), static_cast<char32_t>(3515));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3517), static_cast<char32_t>(3517));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3520), static_cast<char32_t>(3526));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3585), static_cast<char32_t>(3632));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3634), static_cast<char32_t>(3635));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3648), static_cast<char32_t>(3654));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3713), static_cast<char32_t>(3714));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3716), static_cast<char32_t>(3716));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3718), static_cast<char32_t>(3722));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3724), static_cast<char32_t>(3747));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3749), static_cast<char32_t>(3749));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3751), static_cast<char32_t>(3760));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3762), static_cast<char32_t>(3763));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3773), static_cast<char32_t>(3773));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3776), static_cast<char32_t>(3780));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3782), static_cast<char32_t>(3782));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3804), static_cast<char32_t>(3807));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3840), static_cast<char32_t>(3840));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3904), static_cast<char32_t>(3911));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3913), static_cast<char32_t>(3948));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3976), static_cast<char32_t>(3980));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4096), static_cast<char32_t>(4138));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4159), static_cast<char32_t>(4159));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4176), static_cast<char32_t>(4181));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4186), static_cast<char32_t>(4189));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4193), static_cast<char32_t>(4193));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4197), static_cast<char32_t>(4198));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4206), static_cast<char32_t>(4208));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4213), static_cast<char32_t>(4225));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4238), static_cast<char32_t>(4238));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4256), static_cast<char32_t>(4293));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4295), static_cast<char32_t>(4295));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4301), static_cast<char32_t>(4301));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4304), static_cast<char32_t>(4346));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4348), static_cast<char32_t>(4680));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4682), static_cast<char32_t>(4685));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4688), static_cast<char32_t>(4694));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4696), static_cast<char32_t>(4696));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4698), static_cast<char32_t>(4701));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4704), static_cast<char32_t>(4744));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4746), static_cast<char32_t>(4749));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4752), static_cast<char32_t>(4784));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4786), static_cast<char32_t>(4789));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4792), static_cast<char32_t>(4798));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4800), static_cast<char32_t>(4800));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4802), static_cast<char32_t>(4805));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4808), static_cast<char32_t>(4822));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4824), static_cast<char32_t>(4880));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4882), static_cast<char32_t>(4885));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4888), static_cast<char32_t>(4954));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4992), static_cast<char32_t>(5007));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5024), static_cast<char32_t>(5109));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5112), static_cast<char32_t>(5117));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5121), static_cast<char32_t>(5740));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5743), static_cast<char32_t>(5759));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5761), static_cast<char32_t>(5786));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5792), static_cast<char32_t>(5866));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5870), static_cast<char32_t>(5880));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5888), static_cast<char32_t>(5900));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5902), static_cast<char32_t>(5905));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5920), static_cast<char32_t>(5937));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5952), static_cast<char32_t>(5969));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5984), static_cast<char32_t>(5996));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5998), static_cast<char32_t>(6000));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6016), static_cast<char32_t>(6067));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6103), static_cast<char32_t>(6103));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6108), static_cast<char32_t>(6108));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6176), static_cast<char32_t>(6264));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6272), static_cast<char32_t>(6312));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6314), static_cast<char32_t>(6314));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6320), static_cast<char32_t>(6389));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6400), static_cast<char32_t>(6430));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6480), static_cast<char32_t>(6509));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6512), static_cast<char32_t>(6516));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6528), static_cast<char32_t>(6571));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6576), static_cast<char32_t>(6601));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6656), static_cast<char32_t>(6678));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6688), static_cast<char32_t>(6740));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6823), static_cast<char32_t>(6823));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6917), static_cast<char32_t>(6963));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6981), static_cast<char32_t>(6987));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7043), static_cast<char32_t>(7072));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7086), static_cast<char32_t>(7087));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7098), static_cast<char32_t>(7141));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7168), static_cast<char32_t>(7203));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7245), static_cast<char32_t>(7247));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7258), static_cast<char32_t>(7293));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7296), static_cast<char32_t>(7304));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7312), static_cast<char32_t>(7354));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7357), static_cast<char32_t>(7359));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7401), static_cast<char32_t>(7404));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7406), static_cast<char32_t>(7411));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7413), static_cast<char32_t>(7414));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7418), static_cast<char32_t>(7418));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7424), static_cast<char32_t>(7615));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7680), static_cast<char32_t>(7957));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7960), static_cast<char32_t>(7965));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7968), static_cast<char32_t>(8005));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8008), static_cast<char32_t>(8013));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8016), static_cast<char32_t>(8023));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8025), static_cast<char32_t>(8025));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8027), static_cast<char32_t>(8027));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8029), static_cast<char32_t>(8029));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8031), static_cast<char32_t>(8061));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8064), static_cast<char32_t>(8116));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8118), static_cast<char32_t>(8124));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8126), static_cast<char32_t>(8126));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8130), static_cast<char32_t>(8132));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8134), static_cast<char32_t>(8140));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8144), static_cast<char32_t>(8147));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8150), static_cast<char32_t>(8155));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8160), static_cast<char32_t>(8172));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8178), static_cast<char32_t>(8180));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8182), static_cast<char32_t>(8188));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8305), static_cast<char32_t>(8305));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8319), static_cast<char32_t>(8319));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8336), static_cast<char32_t>(8348));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8450), static_cast<char32_t>(8450));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8455), static_cast<char32_t>(8455));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8458), static_cast<char32_t>(8467));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8469), static_cast<char32_t>(8469));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8472), static_cast<char32_t>(8477));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8484), static_cast<char32_t>(8484));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8486), static_cast<char32_t>(8486));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8488), static_cast<char32_t>(8488));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8490), static_cast<char32_t>(8505));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8508), static_cast<char32_t>(8511));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8517), static_cast<char32_t>(8521));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8526), static_cast<char32_t>(8526));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8544), static_cast<char32_t>(8584));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11264), static_cast<char32_t>(11310));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11312), static_cast<char32_t>(11358));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11360), static_cast<char32_t>(11492));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11499), static_cast<char32_t>(11502));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11506), static_cast<char32_t>(11507));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11520), static_cast<char32_t>(11557));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11559), static_cast<char32_t>(11559));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11565), static_cast<char32_t>(11565));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11568), static_cast<char32_t>(11623));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11631), static_cast<char32_t>(11631));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11648), static_cast<char32_t>(11670));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11680), static_cast<char32_t>(11686));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11688), static_cast<char32_t>(11694));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11696), static_cast<char32_t>(11702));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11704), static_cast<char32_t>(11710));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11712), static_cast<char32_t>(11718));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11720), static_cast<char32_t>(11726));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11728), static_cast<char32_t>(11734));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11736), static_cast<char32_t>(11742));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12293), static_cast<char32_t>(12295));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12321), static_cast<char32_t>(12329));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12337), static_cast<char32_t>(12341));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12344), static_cast<char32_t>(12348));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12353), static_cast<char32_t>(12438));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12443), static_cast<char32_t>(12447));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12449), static_cast<char32_t>(12538));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12540), static_cast<char32_t>(12543));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12549), static_cast<char32_t>(12591));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12593), static_cast<char32_t>(12686));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12704), static_cast<char32_t>(12730));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12784), static_cast<char32_t>(12799));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(13312), static_cast<char32_t>(19893));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(19968), static_cast<char32_t>(40943));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(40960), static_cast<char32_t>(42124));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42192), static_cast<char32_t>(42237));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42240), static_cast<char32_t>(42508));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42512), static_cast<char32_t>(42527));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42538), static_cast<char32_t>(42539));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42560), static_cast<char32_t>(42606));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42623), static_cast<char32_t>(42653));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42656), static_cast<char32_t>(42735));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42775), static_cast<char32_t>(42783));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42786), static_cast<char32_t>(42888));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42891), static_cast<char32_t>(42943));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42946), static_cast<char32_t>(42950));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42999), static_cast<char32_t>(43009));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43011), static_cast<char32_t>(43013));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43015), static_cast<char32_t>(43018));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43020), static_cast<char32_t>(43042));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43072), static_cast<char32_t>(43123));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43138), static_cast<char32_t>(43187));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43250), static_cast<char32_t>(43255));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43259), static_cast<char32_t>(43259));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43261), static_cast<char32_t>(43262));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43274), static_cast<char32_t>(43301));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43312), static_cast<char32_t>(43334));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43360), static_cast<char32_t>(43388));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43396), static_cast<char32_t>(43442));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43471), static_cast<char32_t>(43471));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43488), static_cast<char32_t>(43492));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43494), static_cast<char32_t>(43503));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43514), static_cast<char32_t>(43518));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43520), static_cast<char32_t>(43560));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43584), static_cast<char32_t>(43586));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43588), static_cast<char32_t>(43595));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43616), static_cast<char32_t>(43638));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43642), static_cast<char32_t>(43642));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43646), static_cast<char32_t>(43695));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43697), static_cast<char32_t>(43697));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43701), static_cast<char32_t>(43702));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43705), static_cast<char32_t>(43709));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43712), static_cast<char32_t>(43712));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43714), static_cast<char32_t>(43714));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43739), static_cast<char32_t>(43741));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43744), static_cast<char32_t>(43754));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43762), static_cast<char32_t>(43764));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43777), static_cast<char32_t>(43782));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43785), static_cast<char32_t>(43790));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43793), static_cast<char32_t>(43798));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43808), static_cast<char32_t>(43814));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43816), static_cast<char32_t>(43822));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43824), static_cast<char32_t>(43866));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43868), static_cast<char32_t>(43879));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43888), static_cast<char32_t>(44002));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(44032), static_cast<char32_t>(55203));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(55216), static_cast<char32_t>(55238));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(55243), static_cast<char32_t>(55291));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(63744), static_cast<char32_t>(64109));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64112), static_cast<char32_t>(64217));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64256), static_cast<char32_t>(64262));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64275), static_cast<char32_t>(64279));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64285), static_cast<char32_t>(64285));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64287), static_cast<char32_t>(64296));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64298), static_cast<char32_t>(64310));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64312), static_cast<char32_t>(64316));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64318), static_cast<char32_t>(64318));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64320), static_cast<char32_t>(64321));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64323), static_cast<char32_t>(64324));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64326), static_cast<char32_t>(64433));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64467), static_cast<char32_t>(64829));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64848), static_cast<char32_t>(64911));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64914), static_cast<char32_t>(64967));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65008), static_cast<char32_t>(65019));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65136), static_cast<char32_t>(65140));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65142), static_cast<char32_t>(65276));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65313), static_cast<char32_t>(65338));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65345), static_cast<char32_t>(65370));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65382), static_cast<char32_t>(65470));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65474), static_cast<char32_t>(65479));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65482), static_cast<char32_t>(65487));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65490), static_cast<char32_t>(65495));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65498), static_cast<char32_t>(65500));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdStart->AddSymbol(*rv);

    unicodeIdCont->SetName("{unicode_id_cont}");
    rv = MakeRange(static_cast<char32_t>(48), static_cast<char32_t>(57));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65), static_cast<char32_t>(90));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(95), static_cast<char32_t>(95));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(97), static_cast<char32_t>(122));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(170), static_cast<char32_t>(170));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(181), static_cast<char32_t>(181));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(183), static_cast<char32_t>(183));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(186), static_cast<char32_t>(186));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(192), static_cast<char32_t>(214));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(216), static_cast<char32_t>(246));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(248), static_cast<char32_t>(705));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(710), static_cast<char32_t>(721));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(736), static_cast<char32_t>(740));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(748), static_cast<char32_t>(748));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(750), static_cast<char32_t>(750));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(768), static_cast<char32_t>(884));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(886), static_cast<char32_t>(887));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(890), static_cast<char32_t>(893));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(895), static_cast<char32_t>(895));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(902), static_cast<char32_t>(906));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(908), static_cast<char32_t>(908));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(910), static_cast<char32_t>(929));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(931), static_cast<char32_t>(1013));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1015), static_cast<char32_t>(1153));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1155), static_cast<char32_t>(1159));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1162), static_cast<char32_t>(1327));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1329), static_cast<char32_t>(1366));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1369), static_cast<char32_t>(1369));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1376), static_cast<char32_t>(1416));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1425), static_cast<char32_t>(1469));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1471), static_cast<char32_t>(1471));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1473), static_cast<char32_t>(1474));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1476), static_cast<char32_t>(1477));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1479), static_cast<char32_t>(1479));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1488), static_cast<char32_t>(1514));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1519), static_cast<char32_t>(1522));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1552), static_cast<char32_t>(1562));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1568), static_cast<char32_t>(1641));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1646), static_cast<char32_t>(1747));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1749), static_cast<char32_t>(1756));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1759), static_cast<char32_t>(1768));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1770), static_cast<char32_t>(1788));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1791), static_cast<char32_t>(1791));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1808), static_cast<char32_t>(1866));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1869), static_cast<char32_t>(1969));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(1984), static_cast<char32_t>(2037));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2042), static_cast<char32_t>(2042));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2045), static_cast<char32_t>(2045));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2048), static_cast<char32_t>(2093));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2112), static_cast<char32_t>(2139));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2144), static_cast<char32_t>(2154));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2208), static_cast<char32_t>(2228));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2230), static_cast<char32_t>(2237));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2259), static_cast<char32_t>(2273));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2275), static_cast<char32_t>(2403));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2406), static_cast<char32_t>(2415));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2417), static_cast<char32_t>(2435));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2437), static_cast<char32_t>(2444));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2447), static_cast<char32_t>(2448));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2451), static_cast<char32_t>(2472));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2474), static_cast<char32_t>(2480));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2482), static_cast<char32_t>(2482));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2486), static_cast<char32_t>(2489));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2492), static_cast<char32_t>(2500));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2503), static_cast<char32_t>(2504));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2507), static_cast<char32_t>(2510));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2519), static_cast<char32_t>(2519));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2524), static_cast<char32_t>(2525));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2527), static_cast<char32_t>(2531));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2534), static_cast<char32_t>(2545));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2556), static_cast<char32_t>(2556));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2558), static_cast<char32_t>(2558));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2561), static_cast<char32_t>(2563));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2565), static_cast<char32_t>(2570));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2575), static_cast<char32_t>(2576));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2579), static_cast<char32_t>(2600));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2602), static_cast<char32_t>(2608));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2610), static_cast<char32_t>(2611));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2613), static_cast<char32_t>(2614));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2616), static_cast<char32_t>(2617));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2620), static_cast<char32_t>(2620));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2622), static_cast<char32_t>(2626));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2631), static_cast<char32_t>(2632));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2635), static_cast<char32_t>(2637));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2641), static_cast<char32_t>(2641));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2649), static_cast<char32_t>(2652));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2654), static_cast<char32_t>(2654));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2662), static_cast<char32_t>(2677));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2689), static_cast<char32_t>(2691));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2693), static_cast<char32_t>(2701));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2703), static_cast<char32_t>(2705));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2707), static_cast<char32_t>(2728));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2730), static_cast<char32_t>(2736));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2738), static_cast<char32_t>(2739));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2741), static_cast<char32_t>(2745));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2748), static_cast<char32_t>(2757));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2759), static_cast<char32_t>(2761));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2763), static_cast<char32_t>(2765));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2768), static_cast<char32_t>(2768));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2784), static_cast<char32_t>(2787));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2790), static_cast<char32_t>(2799));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2809), static_cast<char32_t>(2815));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2817), static_cast<char32_t>(2819));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2821), static_cast<char32_t>(2828));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2831), static_cast<char32_t>(2832));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2835), static_cast<char32_t>(2856));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2858), static_cast<char32_t>(2864));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2866), static_cast<char32_t>(2867));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2869), static_cast<char32_t>(2873));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2876), static_cast<char32_t>(2884));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2887), static_cast<char32_t>(2888));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2891), static_cast<char32_t>(2893));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2902), static_cast<char32_t>(2903));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2908), static_cast<char32_t>(2909));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2911), static_cast<char32_t>(2915));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2918), static_cast<char32_t>(2927));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2929), static_cast<char32_t>(2929));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2946), static_cast<char32_t>(2947));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2949), static_cast<char32_t>(2954));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2958), static_cast<char32_t>(2960));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2962), static_cast<char32_t>(2965));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2969), static_cast<char32_t>(2970));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2972), static_cast<char32_t>(2972));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2974), static_cast<char32_t>(2975));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2979), static_cast<char32_t>(2980));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2984), static_cast<char32_t>(2986));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(2990), static_cast<char32_t>(3001));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3006), static_cast<char32_t>(3010));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3014), static_cast<char32_t>(3016));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3018), static_cast<char32_t>(3021));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3024), static_cast<char32_t>(3024));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3031), static_cast<char32_t>(3031));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3046), static_cast<char32_t>(3055));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3072), static_cast<char32_t>(3084));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3086), static_cast<char32_t>(3088));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3090), static_cast<char32_t>(3112));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3114), static_cast<char32_t>(3129));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3133), static_cast<char32_t>(3140));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3142), static_cast<char32_t>(3144));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3146), static_cast<char32_t>(3149));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3157), static_cast<char32_t>(3158));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3160), static_cast<char32_t>(3162));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3168), static_cast<char32_t>(3171));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3174), static_cast<char32_t>(3183));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3200), static_cast<char32_t>(3203));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3205), static_cast<char32_t>(3212));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3214), static_cast<char32_t>(3216));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3218), static_cast<char32_t>(3240));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3242), static_cast<char32_t>(3251));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3253), static_cast<char32_t>(3257));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3260), static_cast<char32_t>(3268));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3270), static_cast<char32_t>(3272));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3274), static_cast<char32_t>(3277));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3285), static_cast<char32_t>(3286));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3294), static_cast<char32_t>(3294));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3296), static_cast<char32_t>(3299));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3302), static_cast<char32_t>(3311));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3313), static_cast<char32_t>(3314));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3328), static_cast<char32_t>(3331));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3333), static_cast<char32_t>(3340));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3342), static_cast<char32_t>(3344));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3346), static_cast<char32_t>(3396));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3398), static_cast<char32_t>(3400));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3402), static_cast<char32_t>(3406));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3412), static_cast<char32_t>(3415));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3423), static_cast<char32_t>(3427));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3430), static_cast<char32_t>(3439));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3450), static_cast<char32_t>(3455));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3458), static_cast<char32_t>(3459));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3461), static_cast<char32_t>(3478));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3482), static_cast<char32_t>(3505));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3507), static_cast<char32_t>(3515));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3517), static_cast<char32_t>(3517));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3520), static_cast<char32_t>(3526));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3530), static_cast<char32_t>(3530));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3535), static_cast<char32_t>(3540));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3542), static_cast<char32_t>(3542));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3544), static_cast<char32_t>(3551));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3558), static_cast<char32_t>(3567));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3570), static_cast<char32_t>(3571));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3585), static_cast<char32_t>(3642));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3648), static_cast<char32_t>(3662));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3664), static_cast<char32_t>(3673));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3713), static_cast<char32_t>(3714));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3716), static_cast<char32_t>(3716));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3718), static_cast<char32_t>(3722));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3724), static_cast<char32_t>(3747));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3749), static_cast<char32_t>(3749));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3751), static_cast<char32_t>(3773));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3776), static_cast<char32_t>(3780));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3782), static_cast<char32_t>(3782));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3784), static_cast<char32_t>(3789));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3792), static_cast<char32_t>(3801));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3804), static_cast<char32_t>(3807));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3840), static_cast<char32_t>(3840));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3864), static_cast<char32_t>(3865));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3872), static_cast<char32_t>(3881));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3893), static_cast<char32_t>(3893));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3895), static_cast<char32_t>(3895));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3897), static_cast<char32_t>(3897));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3902), static_cast<char32_t>(3911));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3913), static_cast<char32_t>(3948));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3953), static_cast<char32_t>(3972));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3974), static_cast<char32_t>(3991));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(3993), static_cast<char32_t>(4028));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4038), static_cast<char32_t>(4038));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4096), static_cast<char32_t>(4169));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4176), static_cast<char32_t>(4253));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4256), static_cast<char32_t>(4293));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4295), static_cast<char32_t>(4295));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4301), static_cast<char32_t>(4301));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4304), static_cast<char32_t>(4346));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4348), static_cast<char32_t>(4680));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4682), static_cast<char32_t>(4685));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4688), static_cast<char32_t>(4694));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4696), static_cast<char32_t>(4696));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4698), static_cast<char32_t>(4701));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4704), static_cast<char32_t>(4744));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4746), static_cast<char32_t>(4749));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4752), static_cast<char32_t>(4784));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4786), static_cast<char32_t>(4789));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4792), static_cast<char32_t>(4798));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4800), static_cast<char32_t>(4800));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4802), static_cast<char32_t>(4805));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4808), static_cast<char32_t>(4822));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4824), static_cast<char32_t>(4880));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4882), static_cast<char32_t>(4885));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4888), static_cast<char32_t>(4954));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4957), static_cast<char32_t>(4959));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4969), static_cast<char32_t>(4977));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(4992), static_cast<char32_t>(5007));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5024), static_cast<char32_t>(5109));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5112), static_cast<char32_t>(5117));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5121), static_cast<char32_t>(5740));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5743), static_cast<char32_t>(5759));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5761), static_cast<char32_t>(5786));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5792), static_cast<char32_t>(5866));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5870), static_cast<char32_t>(5880));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5888), static_cast<char32_t>(5900));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5902), static_cast<char32_t>(5908));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5920), static_cast<char32_t>(5940));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5952), static_cast<char32_t>(5971));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5984), static_cast<char32_t>(5996));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(5998), static_cast<char32_t>(6000));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6002), static_cast<char32_t>(6003));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6016), static_cast<char32_t>(6099));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6103), static_cast<char32_t>(6103));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6108), static_cast<char32_t>(6109));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6112), static_cast<char32_t>(6121));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6155), static_cast<char32_t>(6157));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6160), static_cast<char32_t>(6169));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6176), static_cast<char32_t>(6264));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6272), static_cast<char32_t>(6314));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6320), static_cast<char32_t>(6389));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6400), static_cast<char32_t>(6430));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6432), static_cast<char32_t>(6443));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6448), static_cast<char32_t>(6459));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6470), static_cast<char32_t>(6509));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6512), static_cast<char32_t>(6516));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6528), static_cast<char32_t>(6571));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6576), static_cast<char32_t>(6601));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6608), static_cast<char32_t>(6618));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6656), static_cast<char32_t>(6683));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6688), static_cast<char32_t>(6750));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6752), static_cast<char32_t>(6780));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6783), static_cast<char32_t>(6793));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6800), static_cast<char32_t>(6809));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6823), static_cast<char32_t>(6823));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6832), static_cast<char32_t>(6845));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6912), static_cast<char32_t>(6987));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(6992), static_cast<char32_t>(7001));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7019), static_cast<char32_t>(7027));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7040), static_cast<char32_t>(7155));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7168), static_cast<char32_t>(7223));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7232), static_cast<char32_t>(7241));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7245), static_cast<char32_t>(7293));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7296), static_cast<char32_t>(7304));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7312), static_cast<char32_t>(7354));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7357), static_cast<char32_t>(7359));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7376), static_cast<char32_t>(7378));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7380), static_cast<char32_t>(7418));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7424), static_cast<char32_t>(7673));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7675), static_cast<char32_t>(7957));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7960), static_cast<char32_t>(7965));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(7968), static_cast<char32_t>(8005));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8008), static_cast<char32_t>(8013));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8016), static_cast<char32_t>(8023));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8025), static_cast<char32_t>(8025));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8027), static_cast<char32_t>(8027));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8029), static_cast<char32_t>(8029));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8031), static_cast<char32_t>(8061));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8064), static_cast<char32_t>(8116));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8118), static_cast<char32_t>(8124));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8126), static_cast<char32_t>(8126));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8130), static_cast<char32_t>(8132));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8134), static_cast<char32_t>(8140));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8144), static_cast<char32_t>(8147));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8150), static_cast<char32_t>(8155));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8160), static_cast<char32_t>(8172));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8178), static_cast<char32_t>(8180));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8182), static_cast<char32_t>(8188));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8255), static_cast<char32_t>(8256));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8276), static_cast<char32_t>(8276));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8305), static_cast<char32_t>(8305));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8319), static_cast<char32_t>(8319));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8336), static_cast<char32_t>(8348));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8400), static_cast<char32_t>(8412));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8417), static_cast<char32_t>(8417));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8421), static_cast<char32_t>(8432));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8450), static_cast<char32_t>(8450));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8455), static_cast<char32_t>(8455));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8458), static_cast<char32_t>(8467));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8469), static_cast<char32_t>(8469));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8472), static_cast<char32_t>(8477));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8484), static_cast<char32_t>(8484));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8486), static_cast<char32_t>(8486));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8488), static_cast<char32_t>(8488));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8490), static_cast<char32_t>(8505));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8508), static_cast<char32_t>(8511));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8517), static_cast<char32_t>(8521));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8526), static_cast<char32_t>(8526));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(8544), static_cast<char32_t>(8584));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11264), static_cast<char32_t>(11310));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11312), static_cast<char32_t>(11358));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11360), static_cast<char32_t>(11492));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11499), static_cast<char32_t>(11507));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11520), static_cast<char32_t>(11557));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11559), static_cast<char32_t>(11559));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11565), static_cast<char32_t>(11565));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11568), static_cast<char32_t>(11623));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11631), static_cast<char32_t>(11631));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11647), static_cast<char32_t>(11670));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11680), static_cast<char32_t>(11686));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11688), static_cast<char32_t>(11694));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11696), static_cast<char32_t>(11702));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11704), static_cast<char32_t>(11710));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11712), static_cast<char32_t>(11718));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11720), static_cast<char32_t>(11726));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11728), static_cast<char32_t>(11734));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11736), static_cast<char32_t>(11742));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(11744), static_cast<char32_t>(11775));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12293), static_cast<char32_t>(12295));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12321), static_cast<char32_t>(12335));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12337), static_cast<char32_t>(12341));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12344), static_cast<char32_t>(12348));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12353), static_cast<char32_t>(12438));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12441), static_cast<char32_t>(12447));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12449), static_cast<char32_t>(12538));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12540), static_cast<char32_t>(12543));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12549), static_cast<char32_t>(12591));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12593), static_cast<char32_t>(12686));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12704), static_cast<char32_t>(12730));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(12784), static_cast<char32_t>(12799));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(13312), static_cast<char32_t>(19893));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(19968), static_cast<char32_t>(40943));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(40960), static_cast<char32_t>(42124));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42192), static_cast<char32_t>(42237));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42240), static_cast<char32_t>(42508));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42512), static_cast<char32_t>(42539));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42560), static_cast<char32_t>(42607));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42612), static_cast<char32_t>(42621));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42623), static_cast<char32_t>(42737));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42775), static_cast<char32_t>(42783));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42786), static_cast<char32_t>(42888));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42891), static_cast<char32_t>(42943));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42946), static_cast<char32_t>(42950));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(42999), static_cast<char32_t>(43047));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43072), static_cast<char32_t>(43123));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43136), static_cast<char32_t>(43205));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43216), static_cast<char32_t>(43225));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43232), static_cast<char32_t>(43255));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43259), static_cast<char32_t>(43259));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43261), static_cast<char32_t>(43309));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43312), static_cast<char32_t>(43347));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43360), static_cast<char32_t>(43388));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43392), static_cast<char32_t>(43456));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43471), static_cast<char32_t>(43481));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43488), static_cast<char32_t>(43518));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43520), static_cast<char32_t>(43574));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43584), static_cast<char32_t>(43597));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43600), static_cast<char32_t>(43609));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43616), static_cast<char32_t>(43638));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43642), static_cast<char32_t>(43714));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43739), static_cast<char32_t>(43741));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43744), static_cast<char32_t>(43759));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43762), static_cast<char32_t>(43766));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43777), static_cast<char32_t>(43782));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43785), static_cast<char32_t>(43790));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43793), static_cast<char32_t>(43798));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43808), static_cast<char32_t>(43814));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43816), static_cast<char32_t>(43822));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43824), static_cast<char32_t>(43866));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43868), static_cast<char32_t>(43879));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(43888), static_cast<char32_t>(44010));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(44012), static_cast<char32_t>(44013));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(44016), static_cast<char32_t>(44025));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(44032), static_cast<char32_t>(55203));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(55216), static_cast<char32_t>(55238));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(55243), static_cast<char32_t>(55291));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(63744), static_cast<char32_t>(64109));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64112), static_cast<char32_t>(64217));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64256), static_cast<char32_t>(64262));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64275), static_cast<char32_t>(64279));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64285), static_cast<char32_t>(64296));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64298), static_cast<char32_t>(64310));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64312), static_cast<char32_t>(64316));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64318), static_cast<char32_t>(64318));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64320), static_cast<char32_t>(64321));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64323), static_cast<char32_t>(64324));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64326), static_cast<char32_t>(64433));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64467), static_cast<char32_t>(64829));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64848), static_cast<char32_t>(64911));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(64914), static_cast<char32_t>(64967));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65008), static_cast<char32_t>(65019));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65024), static_cast<char32_t>(65039));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65056), static_cast<char32_t>(65071));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65075), static_cast<char32_t>(65076));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65101), static_cast<char32_t>(65103));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65136), static_cast<char32_t>(65140));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65142), static_cast<char32_t>(65276));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65296), static_cast<char32_t>(65305));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65313), static_cast<char32_t>(65338));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65343), static_cast<char32_t>(65343));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65345), static_cast<char32_t>(65370));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65382), static_cast<char32_t>(65470));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65474), static_cast<char32_t>(65479));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65482), static_cast<char32_t>(65487));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65490), static_cast<char32_t>(65495));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
    rv = MakeRange(static_cast<char32_t>(65498), static_cast<char32_t>(65500));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    unicodeIdCont->AddSymbol(*rv);
}

LexerContext::~LexerContext()
{
    for (NfaState* state : nfaStates)
    {
        delete state;
    }
    for (DfaState* state : dfaStates)
    {
        delete state;
    }
    for (Symbol* symbol : symbols)
    {
        delete symbol;
    }
    for (Class* cls : canonicalClasses)
    {
        delete cls;
    }
}

void LexerContext::SetFileName(const std::string& fileName_)
{
    fileName = fileName_;
}

void LexerContext::SetBase(const std::string& base_)
{
    base = base_;
}

NfaState* LexerContext::MakeNfaState()
{
    NfaState* state = new NfaState(nextNfaStateId++, ruleIndex);
    nfaStates.push_back(state);
    nfaStateMap[state->Id()] = state;
    return state;
}

std::expected<NfaState*, int> LexerContext::GetNfaState(int id) const
{
    auto it = nfaStateMap.find(id);
    if (it != nfaStateMap.cend())
    {
        return std::expected<NfaState*, int>(it->second);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("NFA state " + std::to_string(id) + " not found"));
    }
}

DfaState* LexerContext::MakeDfaState(const std::vector<int>& nfaStates)
{
    std::vector<int> s(nfaStates);
    std::sort(s.begin(), s.end());
    for (DfaState* state : dfaStates)
    {
        if (state->NfaStateIds() == s)
        {
            return state;
        }
    }
    DfaState* state = new DfaState(nextDfaStateId++, s);
    dfaStates.push_back(state);
    return state;
}

std::expected<Symbol*, int> LexerContext::MakeChar(char32_t c)
{
    auto it = charSymbols.find(c);
    if (it != charSymbols.cend())
    {
        return std::expected<Symbol*, int>(it->second);
    }
    CharSymbol* symbol = new CharSymbol(c);
    if (!*symbol) return std::unexpected<int>(symbol->Error());
    symbol->DontSetContained();
    symbols.push_back(symbol);
    Symbol* s = symbol;
    charSymbols[c] = s;
    return symbol;
}

std::expected<Symbol*, int> LexerContext::MakeRange(char32_t start, char32_t end)
{
    Range range(start, end);
    auto it = rangeSymbols.find(range);
    if (it != rangeSymbols.cend())
    {
        return std::expected<Symbol*, int>(it->second);
    }
    Range* symbol = new Range(start, end);
    if (!*symbol) return std::unexpected<int>(symbol->Error());
    symbols.push_back(symbol);
    Symbol* s = symbol;
    rangeSymbols[range] = s;
    return std::expected<Symbol*, int>(s);
}

Class* LexerContext::MakeClass()
{
    Class* cls = new Class(classIndex++);
    symbols.push_back(cls);
    return cls;
}

void LexerContext::AddToSymbols(Symbol* symbol)
{
    symbols.push_back(symbol);
}

void LexerContext::AddCanonicalClass(Class* cls)
{
    canonicalClasses.push_back(cls);
}

void LexerContext::AddToPartition(Class* cls)
{
    partition.push_back(cls);
}

std::expected<Nfa, int> LexerContext::MakeExpr(const std::string& id)
{
    if (id == "ascii_id_start")
    {
        return std::expected<Nfa, int>(MakeNfa(*this, MakeAsciiIdStart()));
    }
    else if (id == "ascii_id_cont")
    {
        return std::expected<Nfa, int>(MakeNfa(*this, MakeAsciiIdCont()));
    }
    else if (id == "unicode_id_start")
    {
        return std::expected<Nfa, int>(MakeNfa(*this, MakeUnicodeIdStart()));
    }
    else if (id == "unicode_id_cont")
    {
        return std::expected<Nfa, int>(MakeNfa(*this, MakeUnicodeIdCont()));
    }
    if (expressions)
    {
        soul::ast::slg::Expression* expr = expressions->GetExpression(id);
        if (expr)
        {
            if (currentExpression)
            {
                if (expr->Index() >= currentExpression->Index())
                {
                    return std::unexpected<int>(util::AllocateError("error: expression '" + currentExpression->Id() +
                        "' depends on forward reference '" + expr->Id() + "'"));
                }
            }
            if (exprParser)
            {
                soul::ast::slg::Expression* prevExpression = currentExpression;
                currentExpression = expr;
                std::expected<Nfa, int> rv = exprParser->Parse(expr->Value(), this, expr->FileName(), expr->Line());
                if (!rv) return rv;
                Nfa nfa = std::move(*rv);
                currentExpression = prevExpression;
                return std::expected<Nfa, int>(std::move(nfa));
            }
            else
            {
                return std::unexpected<int>(util::AllocateError("parser not set"));
            }
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("error: expression '" + id + "' not found"));
        }
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("expressions not set"));
    }
}

int LexerContext::AddNfa(Nfa* nfa)
{
    int index = static_cast<int>(nfas.size());
    nfas.push_back(std::unique_ptr<Nfa>(nfa));
    nfaMap[index] = nfa;
    return index;
}

std::expected<Nfa*, int> LexerContext::GetNfa(int index) const
{
    auto it = nfaMap.find(index);
    if (it != nfaMap.cend())
    {
        return std::expected<Nfa*, int>(it->second);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("NFA " + std::to_string(index) + " not found"));
    }
}

void LexerContext::SetDfa(Dfa&& dfa_)
{
    dfa = std::move(dfa_);
}

} // namespace soul::ast::re
