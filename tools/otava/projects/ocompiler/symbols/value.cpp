// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.value;

import util.unicode;
import otava.symbols.error;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.context;
import otava.symbols.emitter;
import otava.symbols.enums;
import otava.symbols.modules;
import otava.symbols.symbol.table;
import otava.symbols.symbol_map;
import otava.symbols.type.symbol;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.visitor;
import otava.symbols.variable.symbol;
import otava.symbols.classes;

namespace otava::symbols {

ValueKind CommonValueKind(ValueKind left, ValueKind right)
{
    switch (left)
    {
        case ValueKind::boolValue:
        {
            return ValueKind::boolValue;
        }
        case ValueKind::integerValue:
        {
            switch (right)
            {
                case ValueKind::integerValue:
                {
                    return ValueKind::integerValue;
                }
                case ValueKind::floatingValue:
                {
                    return ValueKind::floatingValue;
                }
                case ValueKind::boolValue:
                {
                    return ValueKind::boolValue;
                }
                default:
                {
                    return ValueKind::none;
                }
            }
            break;
        }
        case ValueKind::floatingValue:
        {
            switch (right)
            {
                case ValueKind::integerValue:
                case ValueKind::floatingValue:
                {
                    return ValueKind::floatingValue;
                }
                case ValueKind::boolValue:
                {
                    return ValueKind::boolValue;
                }
            }
        }
    }
    return ValueKind::none;
}

Value::Value(SymbolKind symbolKind_, const std::u32string& rep_, TypeSymbol* type_) : Symbol(symbolKind_, rep_), type(type_)
{
}

std::expected<bool, int> Value::Write(Writer& writer)
{
    std::expected<bool, int> rv = Symbol::Write(writer);
    if (!rv) return rv;
    if (type)
    {
        rv = writer.GetBinaryStreamWriter().Write(type->Id());
        if (!rv) return rv;
    }
    else
    {
        rv = writer.GetBinaryStreamWriter().Write(util::nil_uuid());
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Value::Read(Reader& reader)
{
    std::expected<bool, int> rv = Symbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(typeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Value::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = Symbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    if (typeId != util::nil_uuid())
    {
        type = symbolTable.GetType(typeId);
        if (!type)
        {
            std::expected<std::u32string, int> fname = FullName();
            if (!fname) return std::unexpected<int>(fname.error());
            std::expected<std::string, int> sfname = util::ToUtf8(*fname);
            if (!sfname) return std::unexpected<int>(sfname.error());
            std::cout << "Value::Resolve(): warning: type of '" + *sfname + "' not resolved" << "\n";
            return std::expected<bool, int>(false);
        }
    }
    return std::expected<bool, int>(true);
}

ValueKind Value::GetValueKind() const
{
    switch (Kind())
    {
        case SymbolKind::boolValueSymbol:
        {
            return ValueKind::boolValue;
        }
        case SymbolKind::integerValueSymbol:
        {
            return ValueKind::integerValue;
        }
        case SymbolKind::floatingValueSymbol:
        {
            return ValueKind::floatingValue;
        }
        case SymbolKind::nullPtrValueSymbol:
        {
            return ValueKind::nullPtrValue;
        }
        case SymbolKind::stringValueSymbol:
        {
            return ValueKind::stringValue;
        }
        case SymbolKind::charValueSymbol:
        {
            return ValueKind::charValue;
        }
        case SymbolKind::symbolValueSymbol:
        {
            return ValueKind::symbolValue;
        }
        case SymbolKind::invokeValueSymbol:
        {
            return ValueKind::invokeValue;
        }
    }
    return ValueKind::none;
}

std::expected<otava::intermediate::Value*, int> Value::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return Error("cannot evaluate statically", sourcePos, context);
}

BoolValue::BoolValue(TypeSymbol* type_) : Value(SymbolKind::boolValueSymbol, std::u32string(U"false"), type_), value(false)
{
}

BoolValue::BoolValue(const std::u32string& rep_, TypeSymbol* type_) : Value(SymbolKind::boolValueSymbol, rep_, type_), value(false)
{
}

BoolValue::BoolValue(bool value_, const std::u32string& rep_, TypeSymbol* type_) : Value(SymbolKind::boolValueSymbol, rep_, type_), value(value_)
{
}

std::expected<Value*, int> BoolValue::Convert(ValueKind kind, EvaluationContext& context)
{
    switch (kind)
    {
        case ValueKind::boolValue: return std::expected<Value*, int>(this);
        case ValueKind::integerValue:
        {
            std::expected<std::u32string, int> s = util::ToUtf32(std::to_string(static_cast<int>(value)));
            if (!s) return std::unexpected<int>(s.error());
            std::expected<TypeSymbol*, int> f = context.GetSymbolTable().GetFundamentalTypeSymbol(FundamentalTypeKind::intType);
            if (!f) return std::unexpected<int>(f.error());
            TypeSymbol* intType = *f;
            return std::expected<Value*, int>(context.GetIntegerValue(static_cast<std::int64_t>(value), *s, intType));
        }
        case ValueKind::floatingValue:
        {
            std::expected<std::u32string, int> s = util::ToUtf32(std::to_string(static_cast<int>(value)));
            if (!s) return std::unexpected<int>(s.error());
            std::expected<TypeSymbol*, int> d = context.GetSymbolTable().GetFundamentalTypeSymbol(FundamentalTypeKind::doubleType);
            if (!d) return std::unexpected<int>(d.error());
            TypeSymbol* doubleType = *d;
            return std::expected<Value*, int>(context.GetFloatingValue(static_cast<double>(static_cast<int>(value)), *s, doubleType));
        }
    }
    return std::expected<Value*, int>(this);
}

std::expected<bool, int> BoolValue::Write(Writer& writer)
{
    std::expected<bool, int> rv = Value::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(value);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BoolValue::Read(Reader& reader)
{
    std::expected<bool, int> rv = Value::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadBool();
    if (!rv) return rv;
    value = *rv;
    return std::expected<bool, int>(true);
}

void BoolValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<otava::intermediate::Value*, int> BoolValue::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return std::expected<otava::intermediate::Value*, int>(emitter.EmitBool(value));
}

IntegerValue::IntegerValue(TypeSymbol* type_) : Value(SymbolKind::integerValueSymbol, std::u32string(U"0"), type_), value(0)
{
}

IntegerValue::IntegerValue(const std::u32string& rep_, TypeSymbol* type_) : Value(SymbolKind::integerValueSymbol, rep_, type_), value(0)
{
}

IntegerValue::IntegerValue(std::int64_t value_, const std::u32string& rep_, TypeSymbol* type_) : Value(SymbolKind::integerValueSymbol, rep_, type_), value(value_)
{
}

BoolValue* IntegerValue::ToBoolValue(EvaluationContext& context)
{
    if (value) return context.GetBoolValue(true); else return context.GetBoolValue(false);
}

std::expected<Value*, int> IntegerValue::Convert(ValueKind kind, EvaluationContext& context)
{
    switch (kind)
    {
        case ValueKind::boolValue: return ToBoolValue(context);
        case ValueKind::integerValue: return std::expected<Value*, int>(this);
        case ValueKind::floatingValue:
        {
            std::expected<std::u32string, int> s = util::ToUtf32(std::to_string(value));
            if (!s) return std::unexpected<int>(s.error());
            std::expected<TypeSymbol*, int> dt = context.GetSymbolTable().GetFundamentalTypeSymbol(FundamentalTypeKind::doubleType);
            if (!dt) return std::unexpected<int>(dt.error());
            TypeSymbol* doubleType = *dt;
            return std::expected<Value*, int>(context.GetFloatingValue(static_cast<double>(value), *s, doubleType));
        }
    }
    return std::expected<Value*, int>(this);
}

std::expected<bool, int> IntegerValue::Write(Writer& writer)
{
    std::expected<bool, int> rv = Value::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(value);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> IntegerValue::Read(Reader& reader)
{
    std::expected<bool, int> rv = Value::Read(reader);
    if (!rv) return rv;
    std::expected<std::int64_t, int> lrv = reader.GetBinaryStreamReader().ReadLong();
    if (!lrv) return std::unexpected<int>(lrv.error());
    value = *lrv;
    return std::expected<bool, int>(true);
}

void IntegerValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<otava::intermediate::Value*, int> IntegerValue::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<otava::intermediate::Type*, int> irt = GetType()->IrType(emitter, sourcePos, context);
    if (irt) return std::unexpected<int>(irt.error());
    otava::intermediate::Type* irType = *irt;
    return std::expected<otava::intermediate::Value*, int>(emitter.EmitIntegerValue(irType, value));
}

FloatingValue::FloatingValue(TypeSymbol* type_) : Value(SymbolKind::floatingValueSymbol, std::u32string(U"0.0"), type_), value(0.0)
{
}

FloatingValue::FloatingValue(const std::u32string& rep_, TypeSymbol* type_) : Value(SymbolKind::floatingValueSymbol, rep_, type_), value(0.0)
{
}

FloatingValue::FloatingValue(double value_, const std::u32string& rep_, TypeSymbol* type_) : Value(SymbolKind::floatingValueSymbol, rep_, type_), value(value_)
{
}

BoolValue* FloatingValue::ToBoolValue(EvaluationContext& context)
{
    if (value) return context.GetBoolValue(true); else return context.GetBoolValue(false);
}

std::expected<Value*, int> FloatingValue::Convert(ValueKind kind, EvaluationContext& context)
{
    switch (kind)
    {
        case ValueKind::boolValue: return ToBoolValue(context);
        case ValueKind::integerValue:
        {
            std::expected<std::u32string, int> s = util::ToUtf32(std::to_string(value));
            if (!s) return std::unexpected<int>(s.error());
            std::expected<TypeSymbol*, int> it = context.GetSymbolTable().GetFundamentalTypeSymbol(FundamentalTypeKind::intType);
            if (!it) return std::unexpected<int>(it.error());
            TypeSymbol* intType = *it;
            return std::expected<Value*, int>(context.GetIntegerValue(static_cast<std::int64_t>(value), *s, intType));
        }
        case ValueKind::floatingValue: return std::expected<Value*, int>(this);
    }
    return std::expected<Value*, int>(this);
}

std::expected<bool, int> FloatingValue::Write(Writer& writer)
{
    std::expected<bool, int> rv = Value::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(value);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FloatingValue::Read(Reader& reader)
{
    std::expected<bool, int> rv = Value::Read(reader);
    if (!rv) return rv;
    std::expected<double, int> drv = reader.GetBinaryStreamReader().ReadDouble();
    if (!drv) return std::unexpected<int>(drv.error());
    value = *drv;
    return std::expected<bool, int>(true);
}

void FloatingValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<otava::intermediate::Value*, int> FloatingValue::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<otava::intermediate::Type*, int> irt = GetType()->IrType(emitter, sourcePos, context);
    if (!irt) return std::unexpected<int>(irt.error());
    otava::intermediate::Type* irType = *irt;
    return std::expected<otava::intermediate::Value*, int>(emitter.EmitFloatingValue(irType, value));
}

NullPtrValue::NullPtrValue(TypeSymbol* type_) : Value(SymbolKind::nullPtrValueSymbol, U"nullptr", type_)
{
}

BoolValue* NullPtrValue::ToBoolValue(EvaluationContext& context)
{
    return context.GetBoolValue(false);
}

std::expected<Value*, int> NullPtrValue::Convert(ValueKind kind, EvaluationContext& context)
{
    switch (kind)
    {
        case ValueKind::boolValue: return ToBoolValue(context);
    }
    return std::expected<Value*, int>(this);
}

std::expected<bool, int> NullPtrValue::Write(Writer& writer)
{
    return Value::Write(writer);
}

std::expected<bool, int> NullPtrValue::Read(Reader& reader)
{
    return Value::Read(reader);
}

void NullPtrValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<otava::intermediate::Value*, int> NullPtrValue::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<otava::intermediate::Type*, int> irt = GetType()->IrType(emitter, sourcePos, context);
    if (!irt) return std::unexpected<int>(irt.error());
    otava::intermediate::Type* irType = *irt;
    return std::expected<otava::intermediate::Value*, int>(irType->DefaultValue());
}

StringValue::StringValue(TypeSymbol* type_) : Value(SymbolKind::stringValueSymbol, U"", type_), value()
{
}

StringValue::StringValue(const std::string& value_, TypeSymbol* type_) : Value(SymbolKind::stringValueSymbol, U"", type_), value(value_)
{
}

BoolValue* StringValue::ToBoolValue(EvaluationContext& context)
{
    return context.GetBoolValue(false);
}

std::expected<Value*, int> StringValue::Convert(ValueKind kind, EvaluationContext& context)
{
    return std::expected<Value*, int>(this);
}

std::expected<bool, int>  StringValue::Write(Writer& writer)
{
    std::expected<bool, int> rv = Value::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(value);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> StringValue::Read(Reader& reader)
{
    std::expected<bool, int> rv = Value::Read(reader);
    if (!rv) return rv;
    std::expected<std::string, int> s = reader.GetBinaryStreamReader().ReadUtf8String();
    if (!s) return std::unexpected<int>(s.error());
    value = *s;
    return std::expected<bool, int>(true);
}

void StringValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<otava::intermediate::Value*, int> StringValue::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<TypeSymbol*, int> dt = GetType()->DirectType(context);
    if (!dt) return std::unexpected<int>(dt.error());
    TypeSymbol* directType = *dt;
    std::expected<TypeSymbol*, int> ft = directType->FinalType(sourcePos, context);
    if (!ft) return std::unexpected<int>(ft.error());
    TypeSymbol* type = *ft;
    if (type->IsConstCharPtrType() || type->IsBasicStringCharType(context))
    {
        return emitter.EmitStringValue(value);
    }
    else if (type->IsConstChar16PtrType() || type->IsBasicStringChar16Type(context))
    {
        return emitter.EmitString16Value(value);
    }
    else if (type->IsConstChar32PtrType() || type->IsBasicStringChar32Type(context))
    {
        return emitter.EmitString32Value(value);
    }
    else
    {
        std::expected<std::u32string, int> fname = type->FullName();
        if (!fname) return std::unexpected<int>(fname.error());
        std::expected<std::string, int> sfname = util::ToUtf8(*fname);
        if (!sfname) return std::unexpected<int>(sfname.error());
        return std::unexpected<int>(util::AllocateError("unknown base type for string type '" + *sfname + "'"));
    }
}

CharValue::CharValue(TypeSymbol* type_) : Value(SymbolKind::charValueSymbol, U"", type_), value()
{
}

CharValue::CharValue(char32_t value_, TypeSymbol* type_) : Value(SymbolKind::charValueSymbol, U"", type_), value(value_)
{
}

BoolValue* CharValue::ToBoolValue(EvaluationContext& context)
{
    return context.GetBoolValue(false);
}

std::expected<Value*, int> CharValue::Convert(ValueKind kind, EvaluationContext& context)
{
    return std::expected<Value*, int>(this);
}

std::expected<bool, int> CharValue::Write(Writer& writer)
{
    std::expected<bool, int> rv = Value::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(value);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CharValue::Read(Reader& reader)
{
    std::expected<bool, int> rv = Value::Read(reader);
    if (!rv) return rv;
    std::expected<char32_t, int> crv = reader.GetBinaryStreamReader().ReadUChar();
    if (!crv) return std::unexpected<int>(crv.error());
    value = *crv;
    return std::expected<bool, int>(true);
}

void CharValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<otava::intermediate::Value*, int> CharValue::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<otava::intermediate::Type*, int> irt = GetType()->IrType(emitter, sourcePos, context);
    if (!irt) return std::unexpected<int>(irt.error());
    otava::intermediate::Type* irType = *irt;
    return std::expected<otava::intermediate::Value*, int>(emitter.EmitIntegerValue(irType, value));
}

SymbolValue::SymbolValue() : Value(SymbolKind::symbolValueSymbol, std::u32string(), nullptr), symbol(nullptr)
{
}

SymbolValue::SymbolValue(Symbol* symbol_) : Value(SymbolKind::symbolValueSymbol, std::u32string(), nullptr), symbol(symbol_)
{
}

std::expected<Value*, int> SymbolValue::Convert(ValueKind kind, EvaluationContext& context)
{
    switch (kind)
    {
        case ValueKind::integerValue:
        {
            switch (symbol->Kind())
            {
                case SymbolKind::enumConstantSymbol:
                {
                    EnumConstantSymbol* enumConstantSymbol = static_cast<EnumConstantSymbol*>(symbol);
                    Value* value = enumConstantSymbol->GetValue();
                    switch (value->GetValueKind())
                    {
                        case ValueKind::integerValue:
                        {
                            IntegerValue* integerValue = static_cast<IntegerValue*>(value);
                            return std::expected<Value*, int>(context.GetIntegerValue(integerValue->GetValue(), enumConstantSymbol->Name(), value->GetType()));
                        }
                        case ValueKind::boolValue:
                        {
                            BoolValue* boolValue = static_cast<BoolValue*>(value);
                            return std::expected<Value*, int>(
                                context.GetIntegerValue(static_cast<std::int64_t>(boolValue->GetValue()), enumConstantSymbol->Name(), value->GetType()));
                        }
                    }
                    break;
                }
            }
            break;
        }
    }
    return this;
}

BoolValue* SymbolValue::ToBoolValue(EvaluationContext& context)
{
    return context.GetBoolValue(false);
}

bool SymbolValue::IsExportSymbol(Context* context) const
{
    return false;
}

std::expected<bool, int> SymbolValue::Write(Writer& writer)
{
    std::expected<bool, int> rv = Value::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(symbol->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolValue::Read(Reader& reader)
{
    std::expected<bool, int> rv = Value::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(symbolId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

void SymbolValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> SymbolValue::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = Value::Resolve(symbolTable, context);
    if (!rv) return rv;
    std::expected<Symbol*, int> s = symbolTable.GetSymbolMap()->GetSymbol(symbolTable.GetModule(), SymbolKind::null, symbolId);
    if (!s) return std::unexpected<int>(s.error());
    symbol = *s;
    return std::expected<bool, int>(true);
}

std::u32string SymbolValue::ToString() const
{
    return symbol->Name();
}

std::expected<otava::intermediate::Value*, int> SymbolValue::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (symbol->IsVariableSymbol())
    {
        VariableSymbol* variableSymbol = static_cast<VariableSymbol*>(symbol);
        Value* value = variableSymbol->GetValue();
        if (value)
        {
            return std::expected<otava::intermediate::Value*, int>(value->IrValue(emitter, sourcePos, context));
        }
    }
    return Error("cannot evaluate statically", sourcePos, context);
}

InvokeValue::InvokeValue() : Value(SymbolKind::invokeValueSymbol, std::u32string(), nullptr), subject(nullptr)
{
}

InvokeValue::InvokeValue(Value* subject_) : Value(SymbolKind::invokeValueSymbol, std::u32string(), nullptr), subject(subject_)
{
}

std::expected<Value*, int> InvokeValue::Convert(ValueKind kind, EvaluationContext& context)
{
    return std::expected<Value*, int>(this);
}

BoolValue* InvokeValue::ToBoolValue(EvaluationContext& context)
{
    return context.GetBoolValue(false);
}

bool InvokeValue::IsExportSymbol(Context* context) const
{
    return false;
}

std::expected<bool, int> InvokeValue::Write(Writer& writer)
{
    std::expected<bool, int> rv = Value::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(subject->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> InvokeValue::Read(Reader& reader)
{
    std::expected<bool, int> rv = Value::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(subjectId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

void InvokeValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> InvokeValue::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = Value::Resolve(symbolTable, context);
    if (!rv) return rv;
    EvaluationContext* evaluationContext = symbolTable.GetModule()->GetEvaluationContext();
    subject = evaluationContext->GetValue(subjectId);
    return std::expected<bool, int>(true);
}

std::u32string InvokeValue::ToString() const
{
    return subject->ToString() + U"()";
}

ArrayValue::ArrayValue(TypeSymbol* type_) : Value(SymbolKind::arrayValueSymbol, std::u32string(), type_)
{
}

void ArrayValue::AddElementValue(Value* elementValue)
{
    elementValues.push_back(elementValue);
}

std::expected<bool, int> ArrayValue::Write(Writer& writer)
{
    std::expected<bool, int> rv = Value::Write(writer);
    if (!rv) return rv;
    std::uint32_t count = elementValues.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    if (!rv) return rv;
    for (Value* elementValue : elementValues)
    {
        rv = writer.Write(elementValue);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayValue::Read(Reader& reader)
{
    std::expected<bool, int> rv = Value::Read(reader);
    if (!rv) return rv;
    std::expected<std::uint32_t, int> urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t count = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(count); ++i)
    {
        std::expected<Symbol*, int> s = reader.ReadSymbol();
        if (!s) return std::unexpected<int>(s.error());
        Symbol* symbol = *s;
        SymbolTable* symbolTable = reader.GetSymbolTable();
        EvaluationContext* evaluationContext = symbolTable->GetModule()->GetEvaluationContext();
        evaluationContext->AddValue(static_cast<Value*>(symbol));
        elementValues.push_back(static_cast<Value*>(symbol));
    }
    return std::expected<bool, int>(true);
}

BoolValue* ArrayValue::ToBoolValue(EvaluationContext& context)
{
    return context.GetBoolValue(false);
}

std::expected<Value*, int> ArrayValue::Convert(ValueKind kind, EvaluationContext& context)
{
    return std::expected<Value*, int>(this);
}

void ArrayValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<otava::intermediate::Value*, int> ArrayValue::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<otava::intermediate::Type*, int> irt = GetType()->IrType(emitter, sourcePos, context);
    if (!irt) return std::unexpected<int>(irt.error());
    otava::intermediate::ArrayType* arrayType = static_cast<otava::intermediate::ArrayType*>(*irt);
    std::vector<otava::intermediate::Value*> elements;
    for (Value* elementValue : elementValues)
    {
        std::expected<otava::intermediate::Value*, int> irv = elementValue->IrValue(emitter, sourcePos, context);
        if (!irv) return irv;
        otava::intermediate::Value* irValue = *irv;
        elements.push_back(irValue);
    }
    return std::expected<otava::intermediate::Value*, int>(emitter.EmitArrayValue(elements, arrayType));
}

Value* ArrayValue::Clone() const
{
    cloning = true;
    ArrayValue* clone = new ArrayValue(GetType());
    for (Value* elementValue : elementValues)
    {
        clone->AddElementValue(elementValue->Clone());
    }
    cloning = false;
    return clone;
}

StructureValue::StructureValue(TypeSymbol* type_) : Value(SymbolKind::structureValueSymbol, std::u32string(), type_)
{
}

void StructureValue::AddFieldValue(Value* fieldValue)
{
    fieldValues.push_back(fieldValue);
}

std::expected<bool, int> StructureValue::Write(Writer& writer)
{
    std::expected<bool, int> rv = Value::Write(writer);
    if (!rv) return rv;
    std::uint32_t count = fieldValues.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    if (!rv) return rv;
    for (Value* fieldValue : fieldValues)
    {
        rv = writer.Write(fieldValue);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> StructureValue::Read(Reader& reader)
{
    std::expected<bool, int> rv = Value::Read(reader);
    if (!rv) return rv;
    std::expected<std::uint32_t, int> urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t count = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(count); ++i)
    {
        std::expected<Symbol*, int> s = reader.ReadSymbol();
        if (!s) return std::unexpected<int>(s.error());
        Symbol* symbol = *s;
        SymbolTable* symbolTable = reader.GetSymbolTable();
        EvaluationContext* evaluationContext = symbolTable->GetModule()->GetEvaluationContext();
        evaluationContext->AddValue(static_cast<Value*>(symbol));
        fieldValues.push_back(static_cast<Value*>(symbol));
    }
    return std::expected<bool, int>(true);
}

void StructureValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

BoolValue* StructureValue::ToBoolValue(EvaluationContext& context)
{
    return context.GetBoolValue(false);
}

std::expected<Value*, int> StructureValue::Convert(ValueKind kind, EvaluationContext& context)
{
    return std::expected<Value*, int>(this);
}

std::expected<otava::intermediate::Value*, int> StructureValue::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<otava::intermediate::Type*, int> irt = GetType()->IrType(emitter, sourcePos, context);
    if (!irt) return std::unexpected<int>(irt.error());
    otava::intermediate::StructureType* structureType = static_cast<otava::intermediate::StructureType*>(*irt);
    std::vector<otava::intermediate::Value*> fields;
    for (Value* fieldValue : fieldValues)
    {
        std::expected<otava::intermediate::Value*, int> irv = fieldValue->IrValue(emitter, sourcePos, context);
        if (!irv) return irv;
        fields.push_back(*irv);
    }
    return std::expected<otava::intermediate::Value*, int>(emitter.EmitStructureValue(fields, structureType));
}

Value* StructureValue::Clone() const
{
    StructureValue* clone = new StructureValue(GetType());
    for (Value* fieldValue : fieldValues)
    {
        clone->AddFieldValue(fieldValue->Clone());
    }
    return clone;
}

EvaluationContext::EvaluationContext(SymbolTable& symbolTable_) :
    initialized(false),
    symbolTable(symbolTable_),
    trueValue(true, U"true", nullptr),
    falseValue(false, U"false", nullptr),
    nullPtrValue(nullptr)
{
    MapValue(&nullPtrValue);
    MapValue(&trueValue);
    MapValue(&falseValue);
}

void EvaluationContext::Init()
{
    if (initialized) return;
    initialized = true;
    trueValue.SetType(symbolTable.GetFundamentalType(FundamentalTypeKind::boolType));
    falseValue.SetType(symbolTable.GetFundamentalType(FundamentalTypeKind::boolType));
    nullPtrValue.SetType(symbolTable.GetFundamentalType(FundamentalTypeKind::nullPtrType));
}

BoolValue* EvaluationContext::GetBoolValue(bool value)
{
    if (value) return &trueValue; else return &falseValue;
}

IntegerValue* EvaluationContext::GetIntegerValue(std::int64_t value, const std::u32string& rep, TypeSymbol* type)
{
    auto it = integerValueMap.find(std::make_pair(std::make_pair(value, rep), type));
    if (it != integerValueMap.cend())
    {
        return it->second;
    }
    else
    {
        IntegerValue* integerValue = new IntegerValue(value, rep, type);
        integerValueMap[std::make_pair(std::make_pair(value, rep), type)] = integerValue;
        values.push_back(std::unique_ptr<Value>(integerValue));
        MapValue(integerValue);
        return integerValue;
    }
}

FloatingValue* EvaluationContext::GetFloatingValue(double value, const std::u32string& rep, TypeSymbol* type)
{
    auto it = floatingValueMap.find(std::make_pair(std::make_pair(value, rep), type));
    if (it != floatingValueMap.cend())
    {
        return it->second;
    }
    else
    {
        FloatingValue* floatingValue = new FloatingValue(value, rep, type);
        floatingValueMap[std::make_pair(std::make_pair(value, rep), type)] = floatingValue;
        values.push_back(std::unique_ptr<Value>(floatingValue));
        MapValue(floatingValue);
        return floatingValue;
    }
}

StringValue* EvaluationContext::GetStringValue(const std::string& value, TypeSymbol* type)
{
    auto it = stringValueMap.find(std::make_pair(value, type));
    if (it != stringValueMap.cend())
    {
        return it->second;
    }
    else
    {
        StringValue* stringValue = new StringValue(value, type);
        stringValueMap[std::make_pair(value, type)] = stringValue;
        values.push_back(std::unique_ptr<Value>(stringValue));
        MapValue(stringValue);
        return stringValue;
    }
}

CharValue* EvaluationContext::GetCharValue(char32_t value, TypeSymbol* type)
{
    auto it = charValueMap.find(std::make_pair(value, type));
    if (it != charValueMap.cend())
    {
        return it->second;
    }
    else
    {
        CharValue* charValue = new CharValue(value, type);
        charValueMap[std::make_pair(value, type)] = charValue;
        values.push_back(std::unique_ptr<Value>(charValue));
        MapValue(charValue);
        return charValue;
    }
}

SymbolValue* EvaluationContext::GetSymbolValue(Symbol* symbol)
{
    auto it = symbolValueMap.find(symbol);
    if (it != symbolValueMap.cend())
    {
        return it->second;
    }
    else
    {
        SymbolValue* symbolValue = new SymbolValue(symbol);
        symbolValueMap[symbol] = symbolValue;
        values.push_back(std::unique_ptr<Value>(symbolValue));
        MapValue(symbolValue);
        return symbolValue;
    }
}

InvokeValue* EvaluationContext::GetInvokeValue(Value* subject)
{
    auto it = invokeMap.find(subject);
    if (it != invokeMap.cend())
    {
        return it->second;
    }
    else
    {
        InvokeValue* invokeValue = new InvokeValue(subject);
        invokeMap[subject] = invokeValue;
        values.push_back(std::unique_ptr<Value>(invokeValue));
        MapValue(invokeValue);
        return invokeValue;
    }
}

ArrayValue* EvaluationContext::GetArrayValue(TypeSymbol* type)
{
    ArrayValue* arrayValue = new ArrayValue(type);
    values.push_back(std::unique_ptr<Value>(arrayValue));
    return arrayValue;
}

StructureValue* EvaluationContext::GetStructureValue(TypeSymbol* type)
{
    StructureValue* structureValue = new StructureValue(type);
    values.push_back(std::unique_ptr<Value>(structureValue));
    return structureValue;
}

void EvaluationContext::AddValue(Value* value)
{
    values.push_back(std::unique_ptr<Value>(value));
}

std::expected<bool, int> EvaluationContext::Write(Writer& writer, Context* context)
{
    std::expected<bool, int> rv = trueValue.Write(writer);
    if (!rv) return rv;
    rv = falseValue.Write(writer);
    if (!rv) return rv;
    rv = nullPtrValue.Write(writer);
    if (!rv) return rv;
    std::vector<Symbol*> exportValues;
    for (const auto& value : values)
    {
        if (value->IsExportSymbol(context))
        {
            exportValues.push_back(value.get());
        }
    }
    std::uint32_t count = exportValues.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    if (!rv) return rv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(count); ++i)
    {
        Symbol* value = exportValues[i];
        rv = writer.Write(value);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EvaluationContext::Read(Reader& reader)
{
    readingEvaluationContext = true;
    std::expected<bool, int> rv = trueValue.Read(reader);
    if (!rv) return rv;
    rv = falseValue.Read(reader);
    if (!rv) return rv;
    rv = nullPtrValue.Read(reader);
    if (!rv) return rv;
    MapValue(&nullPtrValue);
    MapValue(&trueValue);
    MapValue(&falseValue);
    std::expected<std::uint32_t, int> urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t count = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(count); ++i)
    {
        std::expected<Symbol*, int> s = reader.ReadSymbol();
        if (!s) return std::unexpected<int>(s.error());
        Symbol* symbol = *s;
        if (symbol->IsValueSymbol())
        {
            Value* value = static_cast<Value*>(symbol);
            values.push_back(std::unique_ptr<Value>(value));
            MapValue(value);
            if (symbol->IsIntegerValueSymbol())
            {
                IntegerValue* integerValue = static_cast<IntegerValue*>(symbol);
                integerValueMap[std::make_pair(std::make_pair(integerValue->GetValue(), integerValue->Rep()), integerValue->GetType())] = integerValue;
            }
            else if (symbol->IsFloatingValueSymbol())
            {
                FloatingValue* floatingValue = static_cast<FloatingValue*>(symbol);
                floatingValueMap[std::make_pair(std::make_pair(floatingValue->GetValue(), floatingValue->Rep()), floatingValue->GetType())] = floatingValue;
            }
            else if (symbol->IsStringValueSymbol())
            {
                StringValue* stringValue = static_cast<StringValue*>(symbol);
                stringValueMap[std::make_pair(stringValue->GetValue(), stringValue->GetType())] = stringValue;
            }
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("otava.symbols.value: value symbol expected"));
        }
    }
    readingEvaluationContext = false;
    return std::expected<bool, int>(true);
}

Value* EvaluationContext::GetValue(const util::uuid& valueId) const
{
    auto it = valueMap.find(valueId);
    if (it != valueMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void EvaluationContext::MapValue(Value* value)
{
    valueMap[value->Id()] = value;
}

std::expected<bool, int> EvaluationContext::Resolve(SymbolTable& symbolTable, Context* context)
{
    for (const auto& value : values)
    {
        std::expected<bool, int> rv = value->Resolve(symbolTable, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

} // namespace otava::symbols
