// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.optimizer.arithmetics;

namespace otava::optimizer {

bool OptimizeNot(otava::intermediate::NotInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    if (inst->Operand()->IsBoolValue())
    {
        otava::intermediate::BoolValue* boolValue = static_cast<otava::intermediate::BoolValue*>(inst->Operand());
        otava::intermediate::Value* value = context->GetBoolValue(!boolValue->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    return optimized;
}

bool OptimizeNeg(otava::intermediate::NegInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    switch (inst->Operand()->Kind())
    {
        case otava::intermediate::ValueKind::sbyteValue:
        {
            otava::intermediate::SByteValue* sbyteValue = static_cast<otava::intermediate::SByteValue*>(inst->Operand());
            otava::intermediate::Value* value = context->GetSByteValue(-sbyteValue->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
            break;
        }
        case otava::intermediate::ValueKind::shortValue:
        {
            otava::intermediate::ShortValue* shortValue = static_cast<otava::intermediate::ShortValue*>(inst->Operand());
            otava::intermediate::Value* value = context->GetShortValue(-shortValue->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
            break;
        }
        case otava::intermediate::ValueKind::intValue:
        {
            otava::intermediate::IntValue* intValue = static_cast<otava::intermediate::IntValue*>(inst->Operand());
            otava::intermediate::Value* value = context->GetIntValue(-intValue->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
            break;
        }
        case otava::intermediate::ValueKind::longValue:
        {
            otava::intermediate::LongValue* longValue = static_cast<otava::intermediate::LongValue*>(inst->Operand());
            otava::intermediate::Value* value = context->GetLongValue(-longValue->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
            break;
        }
        case otava::intermediate::ValueKind::floatValue:
        {
            otava::intermediate::FloatValue* floatValue = static_cast<otava::intermediate::FloatValue*>(inst->Operand());
            otava::intermediate::Value* value = context->GetFloatValue(-floatValue->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
            break;
        }
        case otava::intermediate::ValueKind::doubleValue:
        {
            otava::intermediate::DoubleValue* doubleValue = static_cast<otava::intermediate::DoubleValue*>(inst->Operand());
            otava::intermediate::Value* value = context->GetDoubleValue(-doubleValue->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
            break;
        }
    }
    return optimized;
}

bool OptimizeSignExtend(otava::intermediate::SignExtendInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    switch (inst->Result()->GetType()->Id())
    {
        case otava::intermediate::shortTypeId:
        {
            if (inst->Operand()->IsSByteValue())
            {
                otava::intermediate::SByteValue* sbyteValue = static_cast<otava::intermediate::SByteValue*>(inst->Operand());
                otava::intermediate::Value* value = context->GetShortValue(static_cast<std::int16_t>(sbyteValue->GetValue()));
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
            break;
        }
        case otava::intermediate::intTypeId:
        {
            switch (inst->Operand()->Kind())
            {
                case otava::intermediate::ValueKind::sbyteValue:
                {
                    otava::intermediate::SByteValue* sbyteValue = static_cast<otava::intermediate::SByteValue*>(inst->Operand());
                    otava::intermediate::Value* value = context->GetIntValue(static_cast<std::int32_t>(sbyteValue->GetValue()));
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                    break;
                }
                case otava::intermediate::ValueKind::shortValue:
                {
                    otava::intermediate::ShortValue* shortValue = static_cast<otava::intermediate::ShortValue*>(inst->Operand());
                    otava::intermediate::Value* value = context->GetIntValue(static_cast<std::int32_t>(shortValue->GetValue()));
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                    break;
                }
            }
            break;
        }
        case otava::intermediate::longTypeId:
        {
            switch (inst->Operand()->Kind())
            {
                case otava::intermediate::ValueKind::sbyteValue:
                {
                    otava::intermediate::SByteValue* sbyteValue = static_cast<otava::intermediate::SByteValue*>(inst->Operand());
                    otava::intermediate::Value* value = context->GetLongValue(static_cast<std::int64_t>(sbyteValue->GetValue()));
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                    break;
                }
                case otava::intermediate::ValueKind::shortValue:
                {
                    otava::intermediate::ShortValue* shortValue = static_cast<otava::intermediate::ShortValue*>(inst->Operand());
                    otava::intermediate::Value* value = context->GetLongValue(static_cast<std::int64_t>(shortValue->GetValue()));
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                    break;
                }
                case otava::intermediate::ValueKind::intValue:
                {
                    otava::intermediate::IntValue* intValue = static_cast<otava::intermediate::IntValue*>(inst->Operand());
                    otava::intermediate::Value* value = context->GetLongValue(static_cast<std::int64_t>(intValue->GetValue()));
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                    break;
                }
            }
            break;
        }
    }
    return optimized;
}

bool OptimizeZeroExtend(otava::intermediate::ZeroExtendInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    switch (inst->Result()->GetType()->Id())
    {
        case otava::intermediate::ushortTypeId:
        {
            if (inst->Operand()->IsByteValue())
            {
                otava::intermediate::ByteValue* byteValue = static_cast<otava::intermediate::ByteValue*>(inst->Operand());
                otava::intermediate::Value* value = context->GetUShortValue(static_cast<std::uint16_t>(byteValue->GetValue()));
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
            break;
        }
        case otava::intermediate::uintTypeId:
        {
            switch (inst->Operand()->Kind())
            {
                case otava::intermediate::ValueKind::byteValue:
                {
                    otava::intermediate::ByteValue* byteValue = static_cast<otava::intermediate::ByteValue*>(inst->Operand());
                    otava::intermediate::Value* value = context->GetUIntValue(static_cast<std::uint32_t>(byteValue->GetValue()));
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                    break;
                }
                case otava::intermediate::ValueKind::ushortValue:
                {
                    otava::intermediate::UShortValue* ushortValue = static_cast<otava::intermediate::UShortValue*>(inst->Operand());
                    otava::intermediate::Value* value = context->GetUIntValue(static_cast<std::uint32_t>(ushortValue->GetValue()));
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                    break;
                }
            }
            break;
        }
        case otava::intermediate::ulongTypeId:
        {
            switch (inst->Operand()->Kind())
            {
                case otava::intermediate::ValueKind::byteValue:
                {
                    otava::intermediate::ByteValue* byteValue = static_cast<otava::intermediate::ByteValue*>(inst->Operand());
                    otava::intermediate::Value* value = context->GetULongValue(static_cast<std::uint64_t>(byteValue->GetValue()));
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                    break;
                }
                case otava::intermediate::ValueKind::ushortValue:
                {
                    otava::intermediate::UShortValue* ushortValue = static_cast<otava::intermediate::UShortValue*>(inst->Operand());
                    otava::intermediate::Value* value = context->GetULongValue(static_cast<std::uint64_t>(ushortValue->GetValue()));
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                    break;
                }
                case otava::intermediate::ValueKind::uintValue:
                {
                    otava::intermediate::UIntValue* uintValue = static_cast<otava::intermediate::UIntValue*>(inst->Operand());
                    otava::intermediate::Value* value = context->GetULongValue(static_cast<std::uint64_t>(uintValue->GetValue()));
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                    break;
                }
            }
            break;
        }
    }
    return optimized;
}

bool OptimizeAdd(otava::intermediate::AddInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (left->IsZero())
    {
        otava::intermediate::ReplaceInstructionWithValue(inst, right);
        optimized = true;
    }
    else if (right->IsZero())
    {
        otava::intermediate::ReplaceInstructionWithValue(inst, left);
        optimized = true;
    }
    else
    {
        if (left->IsSByteValue() && right->IsSByteValue())
        {
            otava::intermediate::Value* value = context->GetSByteValue(
                static_cast<otava::intermediate::SByteValue*>(left)->GetValue() +
                static_cast<otava::intermediate::SByteValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
        else if (left->IsByteValue() && right->IsByteValue())
        {
            otava::intermediate::Value* value = context->GetByteValue(
                static_cast<otava::intermediate::ByteValue*>(left)->GetValue() +
                static_cast<otava::intermediate::ByteValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
        else if (left->IsShortValue() && right->IsShortValue())
        {
            otava::intermediate::Value* value = context->GetShortValue(
                static_cast<otava::intermediate::ShortValue*>(left)->GetValue() +
                static_cast<otava::intermediate::ShortValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
        else if (left->IsUShortValue() && right->IsUShortValue())
        {
            otava::intermediate::Value* value = context->GetUShortValue(
                static_cast<otava::intermediate::UShortValue*>(left)->GetValue() +
                static_cast<otava::intermediate::UShortValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
        else if (left->IsIntValue() && right->IsIntValue())
        {
            otava::intermediate::Value* value = context->GetIntValue(
                static_cast<otava::intermediate::IntValue*>(left)->GetValue() +
                static_cast<otava::intermediate::IntValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
        else if (left->IsUIntValue() && right->IsUIntValue())
        {
            otava::intermediate::Value* value = context->GetUIntValue(
                static_cast<otava::intermediate::UIntValue*>(left)->GetValue() +
                static_cast<otava::intermediate::UIntValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
        else if (left->IsLongValue() && right->IsLongValue())
        {
            otava::intermediate::Value* value = context->GetLongValue(
                static_cast<otava::intermediate::LongValue*>(left)->GetValue() +
                static_cast<otava::intermediate::LongValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
        else if (left->IsULongValue() && right->IsULongValue())
        {
            otava::intermediate::Value* value = context->GetULongValue(
                static_cast<otava::intermediate::ULongValue*>(left)->GetValue() +
                static_cast<otava::intermediate::ULongValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
        else if (left->IsFloatValue() && right->IsFloatValue())
        {
            otava::intermediate::Value* value = context->GetFloatValue(
                static_cast<otava::intermediate::FloatValue*>(left)->GetValue() +
                static_cast<otava::intermediate::FloatValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
        else if (left->IsDoubleValue() && right->IsDoubleValue())
        {
            otava::intermediate::Value* value = context->GetDoubleValue(
                static_cast<otava::intermediate::DoubleValue*>(left)->GetValue() +
                static_cast<otava::intermediate::DoubleValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
    }
    return optimized;
}

bool OptimizeSub(otava::intermediate::SubInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (right->IsZero())
    {
        otava::intermediate::ReplaceInstructionWithValue(inst, left);
        optimized = true;
    }
    else
    {
        if (left->IsSByteValue() && right->IsSByteValue())
        {
            otava::intermediate::Value* value = context->GetSByteValue(
                static_cast<otava::intermediate::SByteValue*>(left)->GetValue() -
                static_cast<otava::intermediate::SByteValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
        else if (left->IsByteValue() && right->IsByteValue())
        {
            otava::intermediate::Value* value = context->GetByteValue(
                static_cast<otava::intermediate::ByteValue*>(left)->GetValue() -
                static_cast<otava::intermediate::ByteValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
        else if (left->IsShortValue() && right->IsShortValue())
        {
            otava::intermediate::Value* value = context->GetShortValue(
                static_cast<otava::intermediate::ShortValue*>(left)->GetValue() -
                static_cast<otava::intermediate::ShortValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
        else if (left->IsUShortValue() && right->IsUShortValue())
        {
            otava::intermediate::Value* value = context->GetUShortValue(
                static_cast<otava::intermediate::UShortValue*>(left)->GetValue() -
                static_cast<otava::intermediate::UShortValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
        else if (left->IsIntValue() && right->IsIntValue())
        {
            otava::intermediate::Value* value = context->GetIntValue(
                static_cast<otava::intermediate::IntValue*>(left)->GetValue() -
                static_cast<otava::intermediate::IntValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
        else if (left->IsUIntValue() && right->IsUIntValue())
        {
            otava::intermediate::Value* value = context->GetUIntValue(
                static_cast<otava::intermediate::UIntValue*>(left)->GetValue() -
                static_cast<otava::intermediate::UIntValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
        else if (left->IsLongValue() && right->IsLongValue())
        {
            otava::intermediate::Value* value = context->GetLongValue(
                static_cast<otava::intermediate::LongValue*>(left)->GetValue() -
                static_cast<otava::intermediate::LongValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
        else if (left->IsULongValue() && right->IsULongValue())
        {
            otava::intermediate::Value* value = context->GetULongValue(
                static_cast<otava::intermediate::ULongValue*>(left)->GetValue() -
                static_cast<otava::intermediate::ULongValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
        else if (left->IsFloatValue() && right->IsFloatValue())
        {
            otava::intermediate::Value* value = context->GetFloatValue(
                static_cast<otava::intermediate::FloatValue*>(left)->GetValue() -
                static_cast<otava::intermediate::FloatValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
        else if (left->IsDoubleValue() && right->IsDoubleValue())
        {
            otava::intermediate::Value* value = context->GetDoubleValue(
                static_cast<otava::intermediate::DoubleValue*>(left)->GetValue() -
                static_cast<otava::intermediate::DoubleValue*>(right)->GetValue());
            otava::intermediate::ReplaceInstructionWithValue(inst, value);
            optimized = true;
        }
    }
    return optimized;
}

bool OptimizeMul(otava::intermediate::MulInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (left->IsZero())
    {
        otava::intermediate::ReplaceInstructionWithValue(inst, left);
        optimized = true;
    }
    else if (right->IsZero())
    {
        otava::intermediate::ReplaceInstructionWithValue(inst, right);
        optimized = true;
    }
    else if (left->IsOne())
    {
        otava::intermediate::ReplaceInstructionWithValue(inst, right);
        optimized = true;
    }
    else if (right->IsOne())
    {
        otava::intermediate::ReplaceInstructionWithValue(inst, left);
        optimized = true;
    }
    else if (left->IsTwo())
    {
        otava::intermediate::Instruction* addInst = context->CreateAdd(right, right);
        otava::intermediate::ReplaceInstructionWithInstruction(inst, addInst);
        optimized = true;
    }
    else if (right->IsTwo())
    {
        otava::intermediate::Instruction* addInst = context->CreateAdd(left, left);
        otava::intermediate::ReplaceInstructionWithInstruction(inst, addInst);
        optimized = true;
    }
    else
    {
        otava::intermediate::Value* leftLog2 = left->Log2(context);
        if (leftLog2)
        {
            otava::intermediate::Instruction* shlInst = context->CreateShl(right, leftLog2);
            otava::intermediate::ReplaceInstructionWithInstruction(inst, shlInst);
            optimized = true;
        }
        else
        {
            otava::intermediate::Value* rightLog2 = right->Log2(context);
            if (rightLog2)
            {
                otava::intermediate::Instruction* shlInst = context->CreateShl(left, rightLog2);
                otava::intermediate::ReplaceInstructionWithInstruction(inst, shlInst);
                optimized = true;
            }
            else
            {
                if (left->IsSByteValue() && right->IsSByteValue())
                {
                    otava::intermediate::Value* value = context->GetSByteValue(
                        static_cast<otava::intermediate::SByteValue*>(left)->GetValue() *
                        static_cast<otava::intermediate::SByteValue*>(right)->GetValue());
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                }
                else if (left->IsByteValue() && right->IsByteValue())
                {
                    otava::intermediate::Value* value = context->GetByteValue(
                        static_cast<otava::intermediate::ByteValue*>(left)->GetValue() *
                        static_cast<otava::intermediate::ByteValue*>(right)->GetValue());
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                }
                else if (left->IsShortValue() && right->IsShortValue())
                {
                    otava::intermediate::Value* value = context->GetShortValue(
                        static_cast<otava::intermediate::ShortValue*>(left)->GetValue() *
                        static_cast<otava::intermediate::ShortValue*>(right)->GetValue());
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                }
                else if (left->IsUShortValue() && right->IsUShortValue())
                {
                    otava::intermediate::Value* value = context->GetUShortValue(
                        static_cast<otava::intermediate::UShortValue*>(left)->GetValue() *
                        static_cast<otava::intermediate::UShortValue*>(right)->GetValue());
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                }
                else if (left->IsIntValue() && right->IsIntValue())
                {
                    otava::intermediate::Value* value = context->GetIntValue(
                        static_cast<otava::intermediate::IntValue*>(left)->GetValue() *
                        static_cast<otava::intermediate::IntValue*>(right)->GetValue());
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                }
                else if (left->IsUIntValue() && right->IsUIntValue())
                {
                    otava::intermediate::Value* value = context->GetUIntValue(
                        static_cast<otava::intermediate::UIntValue*>(left)->GetValue() *
                        static_cast<otava::intermediate::UIntValue*>(right)->GetValue());
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                }
                else if (left->IsLongValue() && right->IsLongValue())
                {
                    otava::intermediate::Value* value = context->GetLongValue(
                        static_cast<otava::intermediate::LongValue*>(left)->GetValue() *
                        static_cast<otava::intermediate::LongValue*>(right)->GetValue());
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                }
                else if (left->IsULongValue() && right->IsULongValue())
                {
                    otava::intermediate::Value* value = context->GetULongValue(
                        static_cast<otava::intermediate::ULongValue*>(left)->GetValue() *
                        static_cast<otava::intermediate::ULongValue*>(right)->GetValue());
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                }
                else if (left->IsFloatValue() && right->IsFloatValue())
                {
                    otava::intermediate::Value* value = context->GetFloatValue(
                        static_cast<otava::intermediate::FloatValue*>(left)->GetValue() *
                        static_cast<otava::intermediate::FloatValue*>(right)->GetValue());
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                }
                else if (left->IsDoubleValue() && right->IsDoubleValue())
                {
                    otava::intermediate::Value* value = context->GetDoubleValue(
                        static_cast<otava::intermediate::DoubleValue*>(left)->GetValue() *
                        static_cast<otava::intermediate::DoubleValue*>(right)->GetValue());
                    otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    optimized = true;
                }
            }
        }
    }
    return optimized;
}

bool OptimizeDiv(otava::intermediate::DivInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (right->IsZero())
    {
        otava::intermediate::Warning("division by zero", inst->Span(), context);
    }
    else if (right->IsOne())
    {
        otava::intermediate::ReplaceInstructionWithValue(inst, left);
        optimized = true;
    }
    else
    {
        otava::intermediate::Value* rightLog2 = right->Log2(context);
        if (rightLog2)
        {
            otava::intermediate::Instruction* shrInst = context->CreateShr(left, rightLog2);
            otava::intermediate::ReplaceInstructionWithInstruction(inst, shrInst);
            optimized = true;
        }
        else 
        {
            if (left->IsSByteValue() && right->IsSByteValue())
            {
                otava::intermediate::Value* value = context->GetSByteValue(
                    static_cast<otava::intermediate::SByteValue*>(left)->GetValue() /
                    static_cast<otava::intermediate::SByteValue*>(right)->GetValue());
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
            else if (left->IsByteValue() && right->IsByteValue())
            {
                otava::intermediate::Value* value = context->GetByteValue(
                    static_cast<otava::intermediate::ByteValue*>(left)->GetValue() /
                    static_cast<otava::intermediate::ByteValue*>(right)->GetValue());
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
            else if (left->IsShortValue() && right->IsShortValue())
            {
                otava::intermediate::Value* value = context->GetShortValue(
                    static_cast<otava::intermediate::ShortValue*>(left)->GetValue() /
                    static_cast<otava::intermediate::ShortValue*>(right)->GetValue());
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
            else if (left->IsUShortValue() && right->IsUShortValue())
            {
                otava::intermediate::Value* value = context->GetUShortValue(
                    static_cast<otava::intermediate::UShortValue*>(left)->GetValue() /
                    static_cast<otava::intermediate::UShortValue*>(right)->GetValue());
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
            else if (left->IsIntValue() && right->IsIntValue())
            {
                otava::intermediate::Value* value = context->GetIntValue(
                    static_cast<otava::intermediate::IntValue*>(left)->GetValue() /
                    static_cast<otava::intermediate::IntValue*>(right)->GetValue());
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
            else if (left->IsUIntValue() && right->IsUIntValue())
            {
                otava::intermediate::Value* value = context->GetUIntValue(
                    static_cast<otava::intermediate::UIntValue*>(left)->GetValue() /
                    static_cast<otava::intermediate::UIntValue*>(right)->GetValue());
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
            else if (left->IsLongValue() && right->IsLongValue())
            {
                otava::intermediate::Value* value = context->GetLongValue(
                    static_cast<otava::intermediate::LongValue*>(left)->GetValue() /
                    static_cast<otava::intermediate::LongValue*>(right)->GetValue());
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
            else if (left->IsULongValue() && right->IsULongValue())
            {
                otava::intermediate::Value* value = context->GetULongValue(
                    static_cast<otava::intermediate::ULongValue*>(left)->GetValue() /
                    static_cast<otava::intermediate::ULongValue*>(right)->GetValue());
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
            else if (left->IsFloatValue() && right->IsFloatValue())
            {
                otava::intermediate::Value* value = context->GetFloatValue(
                    static_cast<otava::intermediate::FloatValue*>(left)->GetValue() /
                    static_cast<otava::intermediate::FloatValue*>(right)->GetValue());
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
            else if (left->IsDoubleValue() && right->IsDoubleValue())
            {
                otava::intermediate::Value* value = context->GetDoubleValue(
                    static_cast<otava::intermediate::DoubleValue*>(left)->GetValue() /
                    static_cast<otava::intermediate::DoubleValue*>(right)->GetValue());
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
        }
    }
    return optimized;
}

bool OptimizeMod(otava::intermediate::ModInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (right->IsZero())
    {
        otava::intermediate::Warning("division by zero", inst->Span(), context);
    }
    else 
    {
        otava::intermediate::Value* rightModPowerOfTwo = right->ModPowerOfTwo(context);
        if (rightModPowerOfTwo)
        {
            otava::intermediate::Instruction* andInst = context->CreateAnd(left, rightModPowerOfTwo);
            otava::intermediate::ReplaceInstructionWithInstruction(inst, andInst);
        }
        else
        {
            if (left->IsSByteValue() && right->IsSByteValue())
            {
                otava::intermediate::Value* value = context->GetSByteValue(
                    static_cast<otava::intermediate::SByteValue*>(left)->GetValue() %
                    static_cast<otava::intermediate::SByteValue*>(right)->GetValue());
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
            else if (left->IsByteValue() && right->IsByteValue())
            {
                otava::intermediate::Value* value = context->GetByteValue(
                    static_cast<otava::intermediate::ByteValue*>(left)->GetValue() %
                    static_cast<otava::intermediate::ByteValue*>(right)->GetValue());
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
            else if (left->IsShortValue() && right->IsShortValue())
            {
                otava::intermediate::Value* value = context->GetShortValue(
                    static_cast<otava::intermediate::ShortValue*>(left)->GetValue() %
                    static_cast<otava::intermediate::ShortValue*>(right)->GetValue());
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
            else if (left->IsUShortValue() && right->IsUShortValue())
            {
                otava::intermediate::Value* value = context->GetUShortValue(
                    static_cast<otava::intermediate::UShortValue*>(left)->GetValue() %
                    static_cast<otava::intermediate::UShortValue*>(right)->GetValue());
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
            else if (left->IsIntValue() && right->IsIntValue())
            {
                otava::intermediate::Value* value = context->GetIntValue(
                    static_cast<otava::intermediate::IntValue*>(left)->GetValue() %
                    static_cast<otava::intermediate::IntValue*>(right)->GetValue());
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
            else if (left->IsUIntValue() && right->IsUIntValue())
            {
                otava::intermediate::Value* value = context->GetUIntValue(
                    static_cast<otava::intermediate::UIntValue*>(left)->GetValue() %
                    static_cast<otava::intermediate::UIntValue*>(right)->GetValue());
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
            else if (left->IsLongValue() && right->IsLongValue())
            {
                otava::intermediate::Value* value = context->GetLongValue(
                    static_cast<otava::intermediate::LongValue*>(left)->GetValue() %
                    static_cast<otava::intermediate::LongValue*>(right)->GetValue());
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
            else if (left->IsULongValue() && right->IsULongValue())
            {
                otava::intermediate::Value* value = context->GetULongValue(
                    static_cast<otava::intermediate::ULongValue*>(left)->GetValue() %
                    static_cast<otava::intermediate::ULongValue*>(right)->GetValue());
                otava::intermediate::ReplaceInstructionWithValue(inst, value);
                optimized = true;
            }
        }
    }
    return optimized;
}

bool OptimizeAnd(otava::intermediate::AndInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (left->IsSByteValue() && right->IsSByteValue())
    {
        otava::intermediate::Value* value = context->GetSByteValue(
            static_cast<otava::intermediate::SByteValue*>(left)->GetValue() &
            static_cast<otava::intermediate::SByteValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsByteValue() && right->IsByteValue())
    {
        otava::intermediate::Value* value = context->GetByteValue(
            static_cast<otava::intermediate::ByteValue*>(left)->GetValue() &
            static_cast<otava::intermediate::ByteValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsShortValue() && right->IsShortValue())
    {
        otava::intermediate::Value* value = context->GetShortValue(
            static_cast<otava::intermediate::ShortValue*>(left)->GetValue() &
            static_cast<otava::intermediate::ShortValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsUShortValue() && right->IsUShortValue())
    {
        otava::intermediate::Value* value = context->GetUShortValue(
            static_cast<otava::intermediate::UShortValue*>(left)->GetValue() &
            static_cast<otava::intermediate::UShortValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsIntValue() && right->IsIntValue())
    {
        otava::intermediate::Value* value = context->GetIntValue(
            static_cast<otava::intermediate::IntValue*>(left)->GetValue() &
            static_cast<otava::intermediate::IntValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsUIntValue() && right->IsUIntValue())
    {
        otava::intermediate::Value* value = context->GetUIntValue(
            static_cast<otava::intermediate::UIntValue*>(left)->GetValue() &
            static_cast<otava::intermediate::UIntValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsLongValue() && right->IsLongValue())
    {
        otava::intermediate::Value* value = context->GetLongValue(
            static_cast<otava::intermediate::LongValue*>(left)->GetValue() &
            static_cast<otava::intermediate::LongValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsULongValue() && right->IsULongValue())
    {
        otava::intermediate::Value* value = context->GetULongValue(
            static_cast<otava::intermediate::ULongValue*>(left)->GetValue() &
            static_cast<otava::intermediate::ULongValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    return optimized;
}

bool OptimizeOr(otava::intermediate::OrInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (left->IsSByteValue() && right->IsSByteValue())
    {
        otava::intermediate::Value* value = context->GetSByteValue(
            static_cast<otava::intermediate::SByteValue*>(left)->GetValue() |
            static_cast<otava::intermediate::SByteValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsByteValue() && right->IsByteValue())
    {
        otava::intermediate::Value* value = context->GetByteValue(
            static_cast<otava::intermediate::ByteValue*>(left)->GetValue() |
            static_cast<otava::intermediate::ByteValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsShortValue() && right->IsShortValue())
    {
        otava::intermediate::Value* value = context->GetShortValue(
            static_cast<otava::intermediate::ShortValue*>(left)->GetValue() |
            static_cast<otava::intermediate::ShortValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsUShortValue() && right->IsUShortValue())
    {
        otava::intermediate::Value* value = context->GetUShortValue(
            static_cast<otava::intermediate::UShortValue*>(left)->GetValue() |
            static_cast<otava::intermediate::UShortValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsIntValue() && right->IsIntValue())
    {
        otava::intermediate::Value* value = context->GetIntValue(
            static_cast<otava::intermediate::IntValue*>(left)->GetValue() |
            static_cast<otava::intermediate::IntValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsUIntValue() && right->IsUIntValue())
    {
        otava::intermediate::Value* value = context->GetUIntValue(
            static_cast<otava::intermediate::UIntValue*>(left)->GetValue() |
            static_cast<otava::intermediate::UIntValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsLongValue() && right->IsLongValue())
    {
        otava::intermediate::Value* value = context->GetLongValue(
            static_cast<otava::intermediate::LongValue*>(left)->GetValue() |
            static_cast<otava::intermediate::LongValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsULongValue() && right->IsULongValue())
    {
        otava::intermediate::Value* value = context->GetULongValue(
            static_cast<otava::intermediate::ULongValue*>(left)->GetValue() |
            static_cast<otava::intermediate::ULongValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    return optimized;
}

bool OptimizeXor(otava::intermediate::XorInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (left->IsSByteValue() && right->IsSByteValue())
    {
        otava::intermediate::Value* value = context->GetSByteValue(
            static_cast<otava::intermediate::SByteValue*>(left)->GetValue() ^
            static_cast<otava::intermediate::SByteValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsByteValue() && right->IsByteValue())
    {
        otava::intermediate::Value* value = context->GetByteValue(
            static_cast<otava::intermediate::ByteValue*>(left)->GetValue() ^
            static_cast<otava::intermediate::ByteValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsShortValue() && right->IsShortValue())
    {
        otava::intermediate::Value* value = context->GetShortValue(
            static_cast<otava::intermediate::ShortValue*>(left)->GetValue() ^
            static_cast<otava::intermediate::ShortValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsUShortValue() && right->IsUShortValue())
    {
        otava::intermediate::Value* value = context->GetUShortValue(
            static_cast<otava::intermediate::UShortValue*>(left)->GetValue() ^
            static_cast<otava::intermediate::UShortValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsIntValue() && right->IsIntValue())
    {
        otava::intermediate::Value* value = context->GetIntValue(
            static_cast<otava::intermediate::IntValue*>(left)->GetValue() ^
            static_cast<otava::intermediate::IntValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsUIntValue() && right->IsUIntValue())
    {
        otava::intermediate::Value* value = context->GetUIntValue(
            static_cast<otava::intermediate::UIntValue*>(left)->GetValue() ^
            static_cast<otava::intermediate::UIntValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsLongValue() && right->IsLongValue())
    {
        otava::intermediate::Value* value = context->GetLongValue(
            static_cast<otava::intermediate::LongValue*>(left)->GetValue() ^
            static_cast<otava::intermediate::LongValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsULongValue() && right->IsULongValue())
    {
        otava::intermediate::Value* value = context->GetULongValue(
            static_cast<otava::intermediate::ULongValue*>(left)->GetValue() ^
            static_cast<otava::intermediate::ULongValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    return optimized;
}

bool OptimizeShl(otava::intermediate::ShlInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (left->IsSByteValue() && right->IsSByteValue())
    {
        otava::intermediate::Value* value = context->GetSByteValue(
            static_cast<otava::intermediate::SByteValue*>(left)->GetValue() <<
            static_cast<otava::intermediate::SByteValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsByteValue() && right->IsByteValue())
    {
        otava::intermediate::Value* value = context->GetByteValue(
            static_cast<otava::intermediate::ByteValue*>(left)->GetValue() <<
            static_cast<otava::intermediate::ByteValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsShortValue() && right->IsShortValue())
    {
        otava::intermediate::Value* value = context->GetShortValue(
            static_cast<otava::intermediate::ShortValue*>(left)->GetValue() <<
            static_cast<otava::intermediate::ShortValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsUShortValue() && right->IsUShortValue())
    {
        otava::intermediate::Value* value = context->GetUShortValue(
            static_cast<otava::intermediate::UShortValue*>(left)->GetValue() <<
            static_cast<otava::intermediate::UShortValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsIntValue() && right->IsIntValue())
    {
        otava::intermediate::Value* value = context->GetIntValue(
            static_cast<otava::intermediate::IntValue*>(left)->GetValue() <<
            static_cast<otava::intermediate::IntValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsUIntValue() && right->IsUIntValue())
    {
        otava::intermediate::Value* value = context->GetUIntValue(
            static_cast<otava::intermediate::UIntValue*>(left)->GetValue() <<
            static_cast<otava::intermediate::UIntValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsLongValue() && right->IsLongValue())
    {
        otava::intermediate::Value* value = context->GetLongValue(
            static_cast<otava::intermediate::LongValue*>(left)->GetValue() <<
            static_cast<otava::intermediate::LongValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsULongValue() && right->IsULongValue())
    {
        otava::intermediate::Value* value = context->GetULongValue(
            static_cast<otava::intermediate::ULongValue*>(left)->GetValue() <<
            static_cast<otava::intermediate::ULongValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    return optimized;
}

bool OptimizeShr(otava::intermediate::ShrInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (left->IsSByteValue() && right->IsSByteValue())
    {
        otava::intermediate::Value* value = context->GetSByteValue(
            static_cast<otava::intermediate::SByteValue*>(left)->GetValue() >>
            static_cast<otava::intermediate::SByteValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsByteValue() && right->IsByteValue())
    {
        otava::intermediate::Value* value = context->GetByteValue(
            static_cast<otava::intermediate::ByteValue*>(left)->GetValue() >>
            static_cast<otava::intermediate::ByteValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsShortValue() && right->IsShortValue())
    {
        otava::intermediate::Value* value = context->GetShortValue(
            static_cast<otava::intermediate::ShortValue*>(left)->GetValue() >>
            static_cast<otava::intermediate::ShortValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsUShortValue() && right->IsUShortValue())
    {
        otava::intermediate::Value* value = context->GetUShortValue(
            static_cast<otava::intermediate::UShortValue*>(left)->GetValue() >>
            static_cast<otava::intermediate::UShortValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsIntValue() && right->IsIntValue())
    {
        otava::intermediate::Value* value = context->GetIntValue(
            static_cast<otava::intermediate::IntValue*>(left)->GetValue() >>
            static_cast<otava::intermediate::IntValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsUIntValue() && right->IsUIntValue())
    {
        otava::intermediate::Value* value = context->GetUIntValue(
            static_cast<otava::intermediate::UIntValue*>(left)->GetValue() >>
            static_cast<otava::intermediate::UIntValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsLongValue() && right->IsLongValue())
    {
        otava::intermediate::Value* value = context->GetLongValue(
            static_cast<otava::intermediate::LongValue*>(left)->GetValue() >>
            static_cast<otava::intermediate::LongValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsULongValue() && right->IsULongValue())
    {
        otava::intermediate::Value* value = context->GetULongValue(
            static_cast<otava::intermediate::ULongValue*>(left)->GetValue() >>
            static_cast<otava::intermediate::ULongValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    return optimized;
}

bool OptimizeEqual(otava::intermediate::EqualInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (left->IsBoolValue() && right->IsBoolValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::BoolValue*>(left)->GetValue() ==
            static_cast<otava::intermediate::BoolValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsSByteValue() && right->IsSByteValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::SByteValue*>(left)->GetValue() ==
            static_cast<otava::intermediate::SByteValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsByteValue() && right->IsByteValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::ByteValue*>(left)->GetValue() ==
            static_cast<otava::intermediate::ByteValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsShortValue() && right->IsShortValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::ShortValue*>(left)->GetValue() ==
            static_cast<otava::intermediate::ShortValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsUShortValue() && right->IsUShortValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::UShortValue*>(left)->GetValue() ==
            static_cast<otava::intermediate::UShortValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsIntValue() && right->IsIntValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::IntValue*>(left)->GetValue() ==
            static_cast<otava::intermediate::IntValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsUIntValue() && right->IsUIntValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::UIntValue*>(left)->GetValue() ==
            static_cast<otava::intermediate::UIntValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsLongValue() && right->IsLongValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::LongValue*>(left)->GetValue() ==
            static_cast<otava::intermediate::LongValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsULongValue() && right->IsULongValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::ULongValue*>(left)->GetValue() ==
            static_cast<otava::intermediate::ULongValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsFloatValue() && right->IsFloatValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::FloatValue*>(left)->GetValue() ==
            static_cast<otava::intermediate::FloatValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsDoubleValue() && right->IsDoubleValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::DoubleValue*>(left)->GetValue() ==
            static_cast<otava::intermediate::DoubleValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    return optimized;
}

bool OptimizeLess(otava::intermediate::LessInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (left->IsBoolValue() && right->IsBoolValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::BoolValue*>(left)->GetValue() <
            static_cast<otava::intermediate::BoolValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsSByteValue() && right->IsSByteValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::SByteValue*>(left)->GetValue() <
            static_cast<otava::intermediate::SByteValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsByteValue() && right->IsByteValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::ByteValue*>(left)->GetValue() <
            static_cast<otava::intermediate::ByteValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsShortValue() && right->IsShortValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::ShortValue*>(left)->GetValue() <
            static_cast<otava::intermediate::ShortValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsUShortValue() && right->IsUShortValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::UShortValue*>(left)->GetValue() <
            static_cast<otava::intermediate::UShortValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsIntValue() && right->IsIntValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::IntValue*>(left)->GetValue() <
            static_cast<otava::intermediate::IntValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsUIntValue() && right->IsUIntValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::UIntValue*>(left)->GetValue() <
            static_cast<otava::intermediate::UIntValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsLongValue() && right->IsLongValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::LongValue*>(left)->GetValue() <
            static_cast<otava::intermediate::LongValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsULongValue() && right->IsULongValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::ULongValue*>(left)->GetValue() <
            static_cast<otava::intermediate::ULongValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsFloatValue() && right->IsFloatValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::FloatValue*>(left)->GetValue() <
            static_cast<otava::intermediate::FloatValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    else if (left->IsDoubleValue() && right->IsDoubleValue())
    {
        otava::intermediate::Value* value = context->GetBoolValue(
            static_cast<otava::intermediate::DoubleValue*>(left)->GetValue() <
            static_cast<otava::intermediate::DoubleValue*>(right)->GetValue());
        otava::intermediate::ReplaceInstructionWithValue(inst, value);
        optimized = true;
    }
    return optimized;
}

bool OptimizeArithmetics(otava::intermediate::Function* fn, otava::intermediate::Context* context)
{
    bool optimized = true;
    int count = 0;
    int maxArithmeticOptimizationCount = context->MaxArithmeticOptimizationCount();
    while (optimized && count < maxArithmeticOptimizationCount)
    {
        optimized = false;
        otava::intermediate::BasicBlock* bb = fn->FirstBasicBlock();
        while (bb)
        {
            otava::intermediate::Instruction* inst = bb->FirstInstruction();
            while (inst)
            {
                otava::intermediate::Instruction* next = inst->Next();
                switch (inst->GetOpCode())
                {
                    case otava::intermediate::OpCode::not_:
                    {
                        otava::intermediate::NotInstruction* notInst = static_cast<otava::intermediate::NotInstruction*>(inst);
                        if (OptimizeNot(notInst, context))
                        {
                            optimized = true;
                        }
                        break;
                    }
                    case otava::intermediate::OpCode::neg:
                    {
                        otava::intermediate::NegInstruction* negInst = static_cast<otava::intermediate::NegInstruction*>(inst);
                        if (OptimizeNeg(negInst, context))
                        {
                            optimized = true;
                        }
                        break;
                    }
                    case otava::intermediate::OpCode::signextend:
                    {
                        otava::intermediate::SignExtendInstruction* signExtendInst = static_cast<otava::intermediate::SignExtendInstruction*>(inst);
                        if (OptimizeSignExtend(signExtendInst, context))
                        {
                            optimized = true;
                        }
                        break;
                    }
                    case otava::intermediate::OpCode::zeroextend:
                    {
                        otava::intermediate::ZeroExtendInstruction* zeroExtendInst = static_cast<otava::intermediate::ZeroExtendInstruction*>(inst);
                        if (OptimizeZeroExtend(zeroExtendInst, context))
                        {
                            optimized = true;
                        }
                        break;
                    }
                    case otava::intermediate::OpCode::add:
                    {
                        otava::intermediate::AddInstruction* addInst = static_cast<otava::intermediate::AddInstruction*>(inst);
                        if (OptimizeAdd(addInst, context))
                        {
                            optimized = true;
                        }
                        break;
                    }
                    case otava::intermediate::OpCode::sub:
                    {
                        otava::intermediate::SubInstruction* subInst = static_cast<otava::intermediate::SubInstruction*>(inst);
                        if (OptimizeSub(subInst, context))
                        {
                            optimized = true;
                        }
                        break;
                    }
                    case otava::intermediate::OpCode::mul:
                    {
                        otava::intermediate::MulInstruction* mulInst = static_cast<otava::intermediate::MulInstruction*>(inst);
                        if (OptimizeMul(mulInst, context))
                        {
                            optimized = true;
                        }
                        break;
                    }
                    case otava::intermediate::OpCode::div_:
                    {
                        otava::intermediate::DivInstruction* divInst = static_cast<otava::intermediate::DivInstruction*>(inst);
                        if (OptimizeDiv(divInst, context))
                        {
                            optimized = true;
                        }
                        break;
                    }
                    case otava::intermediate::OpCode::mod:
                    {
                        otava::intermediate::ModInstruction* modInst = static_cast<otava::intermediate::ModInstruction*>(inst);
                        if (OptimizeMod(modInst, context))
                        {
                            optimized = true;
                        }
                        break;
                    }
                    case otava::intermediate::OpCode::and_:
                    {
                        otava::intermediate::AndInstruction* andInst = static_cast<otava::intermediate::AndInstruction*>(inst);
                        if (OptimizeAnd(andInst, context))
                        {
                            optimized = true;
                        }
                        break;
                    }
                    case otava::intermediate::OpCode::or_:
                    {
                        otava::intermediate::OrInstruction* orInst = static_cast<otava::intermediate::OrInstruction*>(inst);
                        if (OptimizeOr(orInst, context))
                        {
                            optimized = true;
                        }
                        break;
                    }
                    case otava::intermediate::OpCode::xor_:
                    {
                        otava::intermediate::XorInstruction* xorInst = static_cast<otava::intermediate::XorInstruction*>(inst);
                        if (OptimizeXor(xorInst, context))
                        {
                            optimized = true;
                        }
                        break;
                    }
                    case otava::intermediate::OpCode::shl:
                    {
                        otava::intermediate::ShlInstruction* shlInst = static_cast<otava::intermediate::ShlInstruction*>(inst);
                        if (OptimizeShl(shlInst, context))
                        {
                            optimized = true;
                        }
                        break;
                    }
                    case otava::intermediate::OpCode::shr:
                    {
                        otava::intermediate::ShrInstruction* shrInst = static_cast<otava::intermediate::ShrInstruction*>(inst);
                        if (OptimizeShr(shrInst, context))
                        {
                            optimized = true;
                        }
                        break;
                    }
                    case otava::intermediate::OpCode::equal:
                    {
                        otava::intermediate::EqualInstruction* equalInst = static_cast<otava::intermediate::EqualInstruction*>(inst);
                        if (OptimizeEqual(equalInst, context))
                        {
                            optimized = true;
                        }
                        break;
                    }
                    case otava::intermediate::OpCode::less:
                    {
                        otava::intermediate::LessInstruction* lessInst = static_cast<otava::intermediate::LessInstruction*>(inst);
                        if (OptimizeLess(lessInst, context))
                        {
                            optimized = true;
                        }
                        break;
                    }
                }
                inst = next;
            }
            bb = bb->Next();
        }
        if (optimized)
        {
            ++count;
            fn->SetNumbers();
        }
    }
    return optimized;
}

} // otava::optimizer
