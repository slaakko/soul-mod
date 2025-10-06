// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.value;

import std;

export namespace otava::assembly {

enum class ValueKind
{
    integerLiteral, floatLiteral, doubleLiteral, stringLiteral, symbol, macro, reg, binaryExpr, content, sizePrefix
};

class Value
{
public:
    Value(ValueKind kind_, const std::string& name_);
    virtual ~Value();
    inline ValueKind Kind() const { return kind; }
    inline bool IsIntegerLiteral() const { return kind == ValueKind::integerLiteral; }
    inline bool IsFloatLiteral() const { return kind == ValueKind::floatLiteral; }
    inline bool IsDoubletLiteral() const { return kind == ValueKind::doubleLiteral; }
    inline bool IsStringLiteral() const { return kind == ValueKind::stringLiteral; }
    inline bool IsSymbol() const { return kind == ValueKind::symbol; }
    inline bool IsMacro() const { return kind == ValueKind::macro; }
    inline bool IsRegister() const { return kind == ValueKind::reg; }
    inline const std::string& Name() const { return name; }
    void SetName(const std::string& name_);
    virtual std::string ToString() const { return Name(); }
    inline int Length() const { return ToString().length(); }
    virtual bool CanSplit() const { return false; }
    virtual Value* Split(int length) { return nullptr; }
    virtual bool IsEmpty() const { return false; }
private:
    ValueKind kind;
    std::string name;
};

} // namespace otava::assembly
