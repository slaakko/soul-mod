// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.assembly.context;

import otava.assembly.literal;
import otava.assembly.symbol;
import otava.assembly.function;
import otava.assembly.macro;
import otava.assembly.data;
import otava.assembly.instruction;
import otava.assembly.file;
import util;

namespace otava::assembly {

std::expected<bool, int> CheckSize(std::int64_t size, const std::string& message)
{
    if (size != 1 && size != 2 && size != 4 && size != 8 && size != highByteRegSize && size != 16)
    {
        return std::unexpected<int>(util::AllocateError(message));
    }
    return std::expected<bool, int>(true);
}

Context::Context() : file(nullptr), registerPool(new RegisterPool(registers)), currentFunction(nullptr), floatingLiteralCounter(0), jumpTabLabelCounter(0)
{
}

void Context::ResetRegisterPool()
{
    registerPool.reset(new RegisterPool(registers));
}

std::expected<Register*, int> Context::GetLocalReg(std::int64_t size)
{
    std::expected<bool, int> rv = CheckSize(size, "otava.assembly.GetLocalReg: invalid size: " + std::to_string(size));
    if (!rv) return std::unexpected<int>(rv.error());
    std::expected<RegisterGroup*, int> rrv = registerPool->GetLocalRegisterGroup();
    if (!rrv) return std::unexpected<int>(rrv.error());
    RegisterGroup* regGroup = *rrv;
    return regGroup->GetReg(static_cast<int>(size));
}

std::expected<Register*, int> Context::GetGlobalReg(std::int64_t size, RegisterGroupKind regGroupKind)
{
    return GetGlobalReg(size, regGroupKind, true);
}

std::expected<Register*, int> Context::GetGlobalReg(std::int64_t size, RegisterGroupKind regGroupKind, bool used)
{
    std::expected<bool, int> rv = CheckSize(size, "otava.assembly.GetGlobalReg: invalid size: " + std::to_string(size));
    if (!rv) return std::unexpected<int>(rv.error());
    RegisterGroup* regGroup = registerPool->GetRegisterGroup(regGroupKind, used);
    if (regGroup->IsLocal())
    {
        return std::unexpected<int>(util::AllocateError("global reg group kind expected"));
    }
    return std::expected<Register*, int>(regGroup->GetReg(static_cast<int>(size)));
}

IntegerLiteral* Context::MakeIntegerLiteral(std::int64_t value, int size)
{
    IntegerLiteral* literal = new IntegerLiteral(value, size);
    values.push_back(std::unique_ptr<Value>(literal));
    return literal;
}

std::expected<Value*, int> Context::MakeFloatLiteralSymbol(float value)
{
    FloatLiteral* literal = new FloatLiteral(value);
    values.push_back(std::unique_ptr<Value>(literal));
    Symbol* symbol = MakeSymbol("floating_" + std::to_string(floatingLiteralCounter++) + "_" + file->Id());
    std::expected<Value*, int> rv = MakeSizePrefix(4, MakeContent(symbol));
    if (!rv) return rv;
    Value* expr = *rv;
    Data* data = new Data();
    Instruction* inst = new Instruction(OpCode::REAL4);
    inst->SetNoColon();
    inst->SetLabel(symbol->Name());
    inst->AddOperand(literal);
    data->AddInstruction(std::unique_ptr<Instruction>(inst));
    file->GetDataSection().AddData(data);
    return std::expected<Value*, int>(expr);
}

std::expected<Value*, int> Context::MakeDoubleLiteralSymbol(double value)
{
    DoubleLiteral* literal = new DoubleLiteral(value);
    values.push_back(std::unique_ptr<Value>(literal));
    Symbol* symbol = MakeSymbol("floating_" + std::to_string(floatingLiteralCounter++) + "_" + file->Id());
    std::expected<Value*, int> rv = MakeSizePrefix(8, MakeContent(symbol));
    if (!rv) return rv;
    Value* expr = *rv;
    Data* data = new Data();
    Instruction* inst = new Instruction(OpCode::REAL8);
    inst->SetNoColon();
    inst->SetLabel(symbol->Name());
    inst->AddOperand(literal);
    data->AddInstruction(std::unique_ptr<Instruction>(inst));
    file->GetDataSection().AddData(data);
    return std::expected<Value*, int>(expr);
}

Symbol* Context::MakeSymbol(const std::string& symbolName)
{
    Symbol* symbol = new Symbol(symbolName);
    values.push_back(std::unique_ptr<Value>(symbol));
    return symbol;
}

Macro* Context::MakeMacro(const std::string& name)
{
    Macro* macro = new Macro(name);
    values.push_back(std::unique_ptr<Value>(macro));
    if (currentFunction)
    {
        currentFunction->AddMacro(macro);
    }
    return macro;
}

Value* Context::MakeContent(Value* value)
{
    Value* content = new Content(value);
    values.push_back(std::unique_ptr<Value>(content));
    return content;
}

std::expected<Value*, int> Context::MakeSizePrefix(std::int64_t size, Value* value)
{
    std::expected<bool, int> rv = CheckSize(size, "otava.assembly.MakeSizePrefix: invalid size");
    if (!rv) return std::unexpected<int>(rv.error());
    Value* sizePrefix = new SizePrefix(static_cast<int>(size), value);
    values.push_back(std::unique_ptr<Value>(sizePrefix));
    return std::expected<Value*, int>(sizePrefix);
}

Value* Context::MakeBinaryExpr(Value* left, Value* right, Operator op)
{
    Value* value = new BinaryExpr(left, right, op);
    values.push_back(std::unique_ptr<Value>(value));
    return value;
}

} // otava::assembly
