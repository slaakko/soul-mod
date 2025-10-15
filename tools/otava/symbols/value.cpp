// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.value;

import util.unicode;
import otava.symbols.exception;
import otava.symbols.fundamental.type.symbol;
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
import otava.ast.error;

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

void Value::Write(Writer& writer)
{
    Symbol::Write(writer);
    if (type)
    {
        writer.GetBinaryStreamWriter().Write(type->Id());
    }
    else
    {
        writer.GetBinaryStreamWriter().Write(util::nil_uuid());
    }
}

void Value::Read(Reader& reader)
{
    Symbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(typeId);
}

void Value::Resolve(SymbolTable& symbolTable, Context* context)
{
    Symbol::Resolve(symbolTable, context);
    if (typeId != util::nil_uuid())
    {
        type = symbolTable.GetType(typeId);
        if (!type)
        {
            std::cout << "Value::Resolve(): warning: type of '" + util::ToUtf8(FullName()) + "' not resolved" << "\n";
        }
    }
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

otava::intermediate::Value* Value::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("cannot evaluate statically", sourcePos, context);
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

Value* BoolValue::Convert(ValueKind kind, EvaluationContext& context)
{
    switch (kind)
    {
        case ValueKind::boolValue: return this;
        case ValueKind::integerValue: 
        {
            return context.GetIntegerValue(static_cast<std::int64_t>(value), util::ToUtf32(std::to_string(value)),
                context.GetSymbolTable().GetFundamentalTypeSymbol(FundamentalTypeKind::intType));
        }
        case ValueKind::floatingValue: 
        {
            return context.GetFloatingValue(static_cast<double>(value), util::ToUtf32(std::to_string(value)),
                context.GetSymbolTable().GetFundamentalTypeSymbol(FundamentalTypeKind::doubleType));
        }
    }
    return this;
}

void BoolValue::Write(Writer& writer)
{
    Value::Write(writer);
    writer.GetBinaryStreamWriter().Write(value);
}

void BoolValue::Read(Reader& reader)
{
    Value::Read(reader);
    value = reader.GetBinaryStreamReader().ReadBool();
}

void BoolValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

otava::intermediate::Value* BoolValue::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return emitter.EmitBool(value);
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

Value* IntegerValue::Convert(ValueKind kind, EvaluationContext& context)
{
    switch (kind)
    {
        case ValueKind::boolValue: return ToBoolValue(context);
        case ValueKind::integerValue: return this;
        case ValueKind::floatingValue: 
        {
            return context.GetFloatingValue(static_cast<double>(value), util::ToUtf32(std::to_string(value)), 
                context.GetSymbolTable().GetFundamentalTypeSymbol(FundamentalTypeKind::doubleType));
        }
    }
    return this;
}

void IntegerValue::Write(Writer& writer)
{
    Value::Write(writer);
    writer.GetBinaryStreamWriter().Write(value);
}

void IntegerValue::Read(Reader& reader)
{
    Value::Read(reader);
    value = reader.GetBinaryStreamReader().ReadLong();
}

void IntegerValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

otava::intermediate::Value* IntegerValue::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    otava::intermediate::Type* irType = GetType()->IrType(emitter, sourcePos, context);
    return emitter.EmitIntegerValue(irType, value);
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

Value* FloatingValue::Convert(ValueKind kind, EvaluationContext& context) 
{
    switch (kind)
    {
        case ValueKind::boolValue: return ToBoolValue(context);
        case ValueKind::integerValue: 
        {
            return context.GetIntegerValue(static_cast<std::int64_t>(value), util::ToUtf32(std::to_string(value)), 
                context.GetSymbolTable().GetFundamentalTypeSymbol(FundamentalTypeKind::intType));
        }
        case ValueKind::floatingValue: return this;
    }
    return this;
}

void FloatingValue::Write(Writer& writer)
{
    Value::Write(writer);
    writer.GetBinaryStreamWriter().Write(value);
}

void FloatingValue::Read(Reader& reader)
{
    Value::Read(reader);
    value = reader.GetBinaryStreamReader().ReadDouble();
}

void FloatingValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

otava::intermediate::Value* FloatingValue::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    otava::intermediate::Type* irType = GetType()->IrType(emitter, sourcePos, context);
    return emitter.EmitFloatingValue(irType, value);
}

NullPtrValue::NullPtrValue(TypeSymbol* type_) : Value(SymbolKind::nullPtrValueSymbol, U"nullptr", type_)
{
}

BoolValue* NullPtrValue::ToBoolValue(EvaluationContext& context)
{
    return context.GetBoolValue(false);
}

Value* NullPtrValue::Convert(ValueKind kind, EvaluationContext& context)
{
    switch (kind)
    {
        case ValueKind::boolValue: return ToBoolValue(context);
    }
    return this;
}

void NullPtrValue::Write(Writer& writer)
{
    Value::Write(writer);
}

void NullPtrValue::Read(Reader& reader)
{
    Value::Read(reader);
}

void NullPtrValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

otava::intermediate::Value* NullPtrValue::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return GetType()->IrType(emitter, sourcePos, context)->DefaultValue();
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

Value* StringValue::Convert(ValueKind kind, EvaluationContext& context)
{
    return this;
}

void StringValue::Write(Writer& writer)
{
    Value::Write(writer);
    writer.GetBinaryStreamWriter().Write(value);
}

void StringValue::Read(Reader& reader)
{
    Value::Read(reader);
    value = reader.GetBinaryStreamReader().ReadUtf8String();
}

void StringValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

otava::intermediate::Value* StringValue::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    TypeSymbol* type = GetType()->DirectType(context)->FinalType(sourcePos, context);
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
        ThrowException("unknown base type for string type '" + util::ToUtf8(type->FullName()) + "'");
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

Value* CharValue::Convert(ValueKind kind, EvaluationContext& context)
{
    return this;
}

void CharValue::Write(Writer& writer)
{
    Value::Write(writer);
    writer.GetBinaryStreamWriter().Write(value);
}

void CharValue::Read(Reader& reader)
{
    Value::Read(reader);
    value = reader.GetBinaryStreamReader().ReadUChar();
}

void CharValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

otava::intermediate::Value* CharValue::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    otava::intermediate::Type* irType = GetType()->IrType(emitter, sourcePos, context);
    return emitter.EmitIntegerValue(irType, value);
}

SymbolValue::SymbolValue() : Value(SymbolKind::symbolValueSymbol, std::u32string(), nullptr), symbol(nullptr)
{
}

SymbolValue::SymbolValue(Symbol* symbol_) : Value(SymbolKind::symbolValueSymbol, std::u32string(), nullptr), symbol(symbol_)
{
}

Value* SymbolValue::Convert(ValueKind kind, EvaluationContext& context)
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
                            return context.GetIntegerValue(integerValue->GetValue(), enumConstantSymbol->Name(), value->GetType());
                        }
                        case ValueKind::boolValue:
                        {
                            BoolValue* boolValue = static_cast<BoolValue*>(value);
                            return context.GetIntegerValue(static_cast<std::int64_t>(boolValue->GetValue()), enumConstantSymbol->Name(), value->GetType());
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

void SymbolValue::Write(Writer& writer)
{
    Value::Write(writer);
    writer.GetBinaryStreamWriter().Write(symbol->Id());
}

void SymbolValue::Read(Reader& reader)
{
    Value::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(symbolId);
}

void SymbolValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void SymbolValue::Resolve(SymbolTable& symbolTable, Context* context)
{
    Value::Resolve(symbolTable, context);
    symbol = symbolTable.GetSymbolMap()->GetSymbol(symbolTable.GetModule(), SymbolKind::null, symbolId);
}

std::u32string SymbolValue::ToString() const
{
    return symbol->Name();
}

otava::intermediate::Value* SymbolValue::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (symbol->IsVariableSymbol())
    {
        VariableSymbol* variableSymbol = static_cast<VariableSymbol*>(symbol);
        Value* value = variableSymbol->GetValue();
        if (value)
        {
            return value->IrValue(emitter, sourcePos, context);
        }
    }
    ThrowException("cannot evaluate statically", sourcePos, context);
    return nullptr;
}

InvokeValue::InvokeValue() : Value(SymbolKind::invokeValueSymbol, std::u32string(), nullptr), subject(nullptr)
{
}

InvokeValue::InvokeValue(Value* subject_) : Value(SymbolKind::invokeValueSymbol, std::u32string(), nullptr), subject(subject_)
{
}

Value* InvokeValue::Convert(ValueKind kind, EvaluationContext& context)
{
    return this;
}

BoolValue* InvokeValue::ToBoolValue(EvaluationContext& context)
{
    return context.GetBoolValue(false);
}

bool InvokeValue::IsExportSymbol(Context* context) const
{
    return false;
}

void InvokeValue::Write(Writer& writer)
{
    Value::Write(writer);
    writer.GetBinaryStreamWriter().Write(subject->Id());
}

void InvokeValue::Read(Reader& reader)
{
    Value::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(subjectId);
}

void InvokeValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void InvokeValue::Resolve(SymbolTable& symbolTable, Context* context)
{
    Value::Resolve(symbolTable, context);
    EvaluationContext* evaluationContext = symbolTable.GetModule()->GetEvaluationContext();
    subject = evaluationContext->GetValue(subjectId);
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

void ArrayValue::Write(Writer& writer)
{
    Value::Write(writer);
    std::uint32_t count = elementValues.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    for (const auto& elementValue : elementValues)
    {
        writer.Write(elementValue);
    }
}

void ArrayValue::Read(Reader& reader)
{
    Value::Read(reader);
    std::uint32_t count = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (std::uint32_t i = 0; i < count; ++i)
    {
        Symbol* symbol = reader.ReadSymbol();
        SymbolTable* symbolTable = reader.GetSymbolTable();
        EvaluationContext* evaluationContext = symbolTable->GetModule()->GetEvaluationContext();
        evaluationContext->AddValue(static_cast<Value*>(symbol));
        elementValues.push_back(static_cast<Value*>(symbol));
    }
}

BoolValue* ArrayValue::ToBoolValue(EvaluationContext& context)
{
    return context.GetBoolValue(false);
}

Value* ArrayValue::Convert(ValueKind kind, EvaluationContext& context)
{
    return this;
}

void ArrayValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

otava::intermediate::Value* ArrayValue::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    otava::intermediate::ArrayType* arrayType = static_cast<otava::intermediate::ArrayType*>(GetType()->IrType(emitter, sourcePos, context));
    std::vector<otava::intermediate::Value*> elements;
    for (const auto& elementValue : elementValues)
    {
        elements.push_back(elementValue->IrValue(emitter, sourcePos, context));
    }
    return emitter.EmitArrayValue(elements, arrayType);
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

void StructureValue::Write(Writer& writer)
{
    Value::Write(writer);
    std::uint32_t count = fieldValues.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    for (const auto& fieldValue : fieldValues)
    {
        writer.Write(fieldValue);
    }
}

void StructureValue::Read(Reader& reader)
{
    Value::Read(reader);
    std::uint32_t count = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (std::uint32_t i = 0; i < count; ++i)
    {
        Symbol* symbol = reader.ReadSymbol();
        SymbolTable* symbolTable = reader.GetSymbolTable();
        EvaluationContext* evaluationContext = symbolTable->GetModule()->GetEvaluationContext();
        evaluationContext->AddValue(static_cast<Value*>(symbol));
        fieldValues.push_back(static_cast<Value*>(symbol));
    }
}

void StructureValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

BoolValue* StructureValue::ToBoolValue(EvaluationContext& context)
{
    return context.GetBoolValue(false);
}

Value* StructureValue::Convert(ValueKind kind, EvaluationContext& context)
{
    return this;
}

otava::intermediate::Value* StructureValue::IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    otava::intermediate::StructureType* structureType = static_cast<otava::intermediate::StructureType*>(GetType()->IrType(emitter, sourcePos, context));
    std::vector<otava::intermediate::Value*> fields;
    for (const auto& fieldValue : fieldValues)
    {
        fields.push_back(fieldValue->IrValue(emitter, sourcePos, context));
    }
    return emitter.EmitStructureValue(fields, structureType);
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

void EvaluationContext::Write(Writer& writer, Context* context)
{
    trueValue.Write(writer);
    falseValue.Write(writer);
    nullPtrValue.Write(writer);
    std::vector<Symbol*> exportValues;
    for (const auto& value : values)
    {
        if (value->IsExportSymbol(context))
        {
            exportValues.push_back(value.get());
        }
    }
    std::uint32_t count = exportValues.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    for (std::uint32_t i = 0; i < count; ++i)
    {
        Symbol* value = exportValues[i];
        writer.Write(value);
    }
}

void EvaluationContext::Read(Reader& reader)
{
    readingEvaluationContext = true;
    trueValue.Read(reader);
    falseValue.Read(reader);
    nullPtrValue.Read(reader);
    MapValue(&nullPtrValue);
    MapValue(&trueValue);
    MapValue(&falseValue);
    std::uint32_t count = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (std::uint32_t i = 0; i < count; ++i)
    {
        Symbol* symbol = reader.ReadSymbol();
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
            otava::ast::SetExceptionThrown();
            throw std::runtime_error("otava.symbols.value: value symbol expected");
        }
    }
    readingEvaluationContext = false;
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

void EvaluationContext::Resolve(SymbolTable& symbolTable, Context* context)
{
    for (const auto& value : values)
    {
        value->Resolve(symbolTable, context);
    }
}

} // namespace otava::symbols
