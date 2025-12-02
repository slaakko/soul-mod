// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.optimizer.arithmetics;

namespace otava::optimizer {

std::expected<bool, int> OptimizeNot(otava::intermediate::NotInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    if (inst->Operand()->IsBoolValue())
    {
        otava::intermediate::BoolValue* boolValue = static_cast<otava::intermediate::BoolValue*>(inst->Operand());
        otava::intermediate::Value* value = context->GetBoolValue(!boolValue->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    return std::expected<bool, int>(optimized);
}

std::expected<bool, int> OptimizeNeg(otava::intermediate::NegInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    switch (inst->Operand()->Kind())
    {
        case otava::intermediate::ValueKind::sbyteValue:
        {
            otava::intermediate::SByteValue* sbyteValue = static_cast<otava::intermediate::SByteValue*>(inst->Operand());
            otava::intermediate::Value* value = context->GetSByteValue(-sbyteValue->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
            break;
        }
        case otava::intermediate::ValueKind::shortValue:
        {
            otava::intermediate::ShortValue* shortValue = static_cast<otava::intermediate::ShortValue*>(inst->Operand());
            otava::intermediate::Value* value = context->GetShortValue(-shortValue->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
            break;
        }
        case otava::intermediate::ValueKind::intValue:
        {
            otava::intermediate::IntValue* intValue = static_cast<otava::intermediate::IntValue*>(inst->Operand());
            otava::intermediate::Value* value = context->GetIntValue(-intValue->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
            break;
        }
        case otava::intermediate::ValueKind::longValue:
        {
            otava::intermediate::LongValue* longValue = static_cast<otava::intermediate::LongValue*>(inst->Operand());
            otava::intermediate::Value* value = context->GetLongValue(-longValue->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
            break;
        }
        case otava::intermediate::ValueKind::floatValue:
        {
            otava::intermediate::FloatValue* floatValue = static_cast<otava::intermediate::FloatValue*>(inst->Operand());
            otava::intermediate::Value* value = context->GetFloatValue(-floatValue->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
            break;
        }
        case otava::intermediate::ValueKind::doubleValue:
        {
            otava::intermediate::DoubleValue* doubleValue = static_cast<otava::intermediate::DoubleValue*>(inst->Operand());
            otava::intermediate::Value* value = context->GetDoubleValue(-doubleValue->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
            break;
        }
    }
    return std::expected<bool, int>(optimized);
}

std::expected<bool, int> OptimizeSignExtend(otava::intermediate::SignExtendInstruction* inst, otava::intermediate::Context* context)
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
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
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
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
                    optimized = true;
                    break;
                }
                case otava::intermediate::ValueKind::shortValue:
                {
                    otava::intermediate::ShortValue* shortValue = static_cast<otava::intermediate::ShortValue*>(inst->Operand());
                    otava::intermediate::Value* value = context->GetIntValue(static_cast<std::int32_t>(shortValue->GetValue()));
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
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
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
                    optimized = true;
                    break;
                }
                case otava::intermediate::ValueKind::shortValue:
                {
                    otava::intermediate::ShortValue* shortValue = static_cast<otava::intermediate::ShortValue*>(inst->Operand());
                    otava::intermediate::Value* value = context->GetLongValue(static_cast<std::int64_t>(shortValue->GetValue()));
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
                    optimized = true;
                    break;
                }
                case otava::intermediate::ValueKind::intValue:
                {
                    otava::intermediate::IntValue* intValue = static_cast<otava::intermediate::IntValue*>(inst->Operand());
                    otava::intermediate::Value* value = context->GetLongValue(static_cast<std::int64_t>(intValue->GetValue()));
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
                    optimized = true;
                    break;
                }
            }
            break;
        }
    }
    return std::expected<bool, int>(optimized);
}

std::expected<bool, int> OptimizeZeroExtend(otava::intermediate::ZeroExtendInstruction* inst, otava::intermediate::Context* context)
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
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
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
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
                    optimized = true;
                    break;
                }
                case otava::intermediate::ValueKind::ushortValue:
                {
                    otava::intermediate::UShortValue* ushortValue = static_cast<otava::intermediate::UShortValue*>(inst->Operand());
                    otava::intermediate::Value* value = context->GetUIntValue(static_cast<std::uint32_t>(ushortValue->GetValue()));
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
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
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
                    optimized = true;
                    break;
                }
                case otava::intermediate::ValueKind::ushortValue:
                {
                    otava::intermediate::UShortValue* ushortValue = static_cast<otava::intermediate::UShortValue*>(inst->Operand());
                    otava::intermediate::Value* value = context->GetULongValue(static_cast<std::uint64_t>(ushortValue->GetValue()));
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
                    optimized = true;
                    break;
                }
                case otava::intermediate::ValueKind::uintValue:
                {
                    otava::intermediate::UIntValue* uintValue = static_cast<otava::intermediate::UIntValue*>(inst->Operand());
                    otava::intermediate::Value* value = context->GetULongValue(static_cast<std::uint64_t>(uintValue->GetValue()));
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
                    optimized = true;
                    break;
                }
            }
            break;
        }
    }
    return std::expected<bool, int>(optimized);
}

std::expected<bool, int> OptimizeAdd(otava::intermediate::AddInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (left->IsZero())
    {
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, right);
        if (!rv) return rv;
        optimized = true;
    }
    else if (right->IsZero())
    {
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, left);
        if (!rv) return rv;
        optimized = true;
    }
    else
    {
        if (left->IsSByteValue() && right->IsSByteValue())
        {
            otava::intermediate::SByteValue* leftV = static_cast<otava::intermediate::SByteValue*>(left);
            otava::intermediate::SByteValue* rightV = static_cast<otava::intermediate::SByteValue*>(right);
            otava::intermediate::Value* value = context->GetSByteValue(leftV->GetValue() + rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
        else if (left->IsByteValue() && right->IsByteValue())
        {
            otava::intermediate::ByteValue* leftV = static_cast<otava::intermediate::ByteValue*>(left);
            otava::intermediate::ByteValue* rightV = static_cast<otava::intermediate::ByteValue*>(right);
            otava::intermediate::Value* value = context->GetByteValue(leftV->GetValue() + rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
        else if (left->IsShortValue() && right->IsShortValue())
        {
            otava::intermediate::ShortValue* leftV = static_cast<otava::intermediate::ShortValue*>(left);
            otava::intermediate::ShortValue* rightV = static_cast<otava::intermediate::ShortValue*>(right);
            otava::intermediate::Value* value = context->GetShortValue(leftV->GetValue() + rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
        else if (left->IsUShortValue() && right->IsUShortValue())
        {
            otava::intermediate::UShortValue* leftV = static_cast<otava::intermediate::UShortValue*>(left);
            otava::intermediate::UShortValue* rightV = static_cast<otava::intermediate::UShortValue*>(right);
            otava::intermediate::Value* value = context->GetUShortValue(leftV->GetValue() + rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
        else if (left->IsIntValue() && right->IsIntValue())
        {
            otava::intermediate::IntValue* leftV = static_cast<otava::intermediate::IntValue*>(left);
            otava::intermediate::IntValue* rightV = static_cast<otava::intermediate::IntValue*>(right);
            otava::intermediate::Value* value = context->GetIntValue(leftV->GetValue() + rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
        else if (left->IsUIntValue() && right->IsUIntValue())
        {
            otava::intermediate::UIntValue* leftV = static_cast<otava::intermediate::UIntValue*>(left);
            otava::intermediate::UIntValue* rightV = static_cast<otava::intermediate::UIntValue*>(right);
            otava::intermediate::Value* value = context->GetUIntValue(leftV->GetValue() + rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
        else if (left->IsLongValue() && right->IsLongValue())
        {
            otava::intermediate::LongValue* leftV = static_cast<otava::intermediate::LongValue*>(left);
            otava::intermediate::LongValue* rightV = static_cast<otava::intermediate::LongValue*>(right);
            otava::intermediate::Value* value = context->GetLongValue(leftV->GetValue() + rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
        else if (left->IsULongValue() && right->IsULongValue())
        {
            otava::intermediate::ULongValue* leftV = static_cast<otava::intermediate::ULongValue*>(left);
            otava::intermediate::ULongValue* rightV = static_cast<otava::intermediate::ULongValue*>(right);
            otava::intermediate::Value* value = context->GetULongValue(leftV->GetValue() + rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
        else if (left->IsFloatValue() && right->IsFloatValue())
        {
            otava::intermediate::FloatValue* leftV = static_cast<otava::intermediate::FloatValue*>(left);
            otava::intermediate::FloatValue* rightV = static_cast<otava::intermediate::FloatValue*>(right);
            otava::intermediate::Value* value = context->GetFloatValue(leftV->GetValue() + rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
        else if (left->IsDoubleValue() && right->IsDoubleValue())
        {
            otava::intermediate::DoubleValue* leftV = static_cast<otava::intermediate::DoubleValue*>(left);
            otava::intermediate::DoubleValue* rightV = static_cast<otava::intermediate::DoubleValue*>(right);
            otava::intermediate::Value* value = context->GetDoubleValue(leftV->GetValue() + rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
    }
    return std::expected<bool, int>(optimized);
}

std::expected<bool, int> OptimizeSub(otava::intermediate::SubInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (right->IsZero())
    {
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, left);
        if (!rv) return rv;
        optimized = true;
    }
    else
    {
        if (left->IsSByteValue() && right->IsSByteValue())
        {
            otava::intermediate::SByteValue* leftV = static_cast<otava::intermediate::SByteValue*>(left);
            otava::intermediate::SByteValue* rightV = static_cast<otava::intermediate::SByteValue*>(right);
            otava::intermediate::Value* value = context->GetSByteValue(leftV->GetValue() - rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
        else if (left->IsByteValue() && right->IsByteValue())
        {
            otava::intermediate::ByteValue* leftV = static_cast<otava::intermediate::ByteValue*>(left);
            otava::intermediate::ByteValue* rightV = static_cast<otava::intermediate::ByteValue*>(right);
            otava::intermediate::Value* value = context->GetByteValue(leftV->GetValue() - rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
        else if (left->IsShortValue() && right->IsShortValue())
        {
            otava::intermediate::ShortValue* leftV = static_cast<otava::intermediate::ShortValue*>(left);
            otava::intermediate::ShortValue* rightV = static_cast<otava::intermediate::ShortValue*>(right);
            otava::intermediate::Value* value = context->GetShortValue(leftV->GetValue() - rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
        else if (left->IsUShortValue() && right->IsUShortValue())
        {
            otava::intermediate::UShortValue* leftV = static_cast<otava::intermediate::UShortValue*>(left);
            otava::intermediate::UShortValue* rightV = static_cast<otava::intermediate::UShortValue*>(right);
            otava::intermediate::Value* value = context->GetUShortValue(leftV->GetValue() - rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
        else if (left->IsIntValue() && right->IsIntValue())
        {
            otava::intermediate::IntValue* leftV = static_cast<otava::intermediate::IntValue*>(left);
            otava::intermediate::IntValue* rightV = static_cast<otava::intermediate::IntValue*>(right);
            otava::intermediate::Value* value = context->GetIntValue(leftV->GetValue() - rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
        else if (left->IsUIntValue() && right->IsUIntValue())
        {
            otava::intermediate::UIntValue* leftV = static_cast<otava::intermediate::UIntValue*>(left);
            otava::intermediate::UIntValue* rightV = static_cast<otava::intermediate::UIntValue*>(right);
            otava::intermediate::Value* value = context->GetUIntValue(leftV->GetValue() - rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
        else if (left->IsLongValue() && right->IsLongValue())
        {
            otava::intermediate::LongValue* leftV = static_cast<otava::intermediate::LongValue*>(left);
            otava::intermediate::LongValue* rightV = static_cast<otava::intermediate::LongValue*>(right);
            otava::intermediate::Value* value = context->GetLongValue(leftV->GetValue() - rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
        else if (left->IsULongValue() && right->IsULongValue())
        {
            otava::intermediate::ULongValue* leftV = static_cast<otava::intermediate::ULongValue*>(left);
            otava::intermediate::ULongValue* rightV = static_cast<otava::intermediate::ULongValue*>(right);
            otava::intermediate::Value* value = context->GetULongValue(leftV->GetValue() - rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
        else if (left->IsFloatValue() && right->IsFloatValue())
        {
            otava::intermediate::FloatValue* leftV = static_cast<otava::intermediate::FloatValue*>(left);
            otava::intermediate::FloatValue* rightV = static_cast<otava::intermediate::FloatValue*>(right);
            otava::intermediate::Value* value = context->GetFloatValue(leftV->GetValue() - rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
        else if (left->IsDoubleValue() && right->IsDoubleValue())
        {
            otava::intermediate::DoubleValue* leftV = static_cast<otava::intermediate::DoubleValue*>(left);
            otava::intermediate::DoubleValue* rightV = static_cast<otava::intermediate::DoubleValue*>(right);
            otava::intermediate::Value* value = context->GetDoubleValue(leftV->GetValue() - rightV->GetValue());
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
            if (!rv) return rv;
            optimized = true;
        }
    }
    return std::expected<bool, int>(optimized);
}

std::expected<bool, int> OptimizeMul(otava::intermediate::MulInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (left->IsZero())
    {
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, left);
        if (!rv) return rv;
        optimized = true;
    }
    else if (right->IsZero())
    {
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, right);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsOne())
    {
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, right);
        if (!rv) return rv;
        optimized = true;
    }
    else if (right->IsOne())
    {
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, left);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsTwo())
    {
        otava::intermediate::Instruction* addInst = context->CreateAdd(right, right);
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithInstruction(inst, addInst);
        if (!rv) return rv;
        optimized = true;
    }
    else if (right->IsTwo())
    {
        otava::intermediate::Instruction* addInst = context->CreateAdd(left, left);
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithInstruction(inst, addInst);
        if (!rv) return rv;
        optimized = true;
    }
    else
    {
        otava::intermediate::Value* leftLog2 = left->Log2(context);
        if (leftLog2)
        {
            otava::intermediate::Instruction* shlInst = context->CreateShl(right, leftLog2);
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithInstruction(inst, shlInst);
            if (!rv) return rv;
            optimized = true;
        }
        else
        {
            otava::intermediate::Value* rightLog2 = right->Log2(context);
            if (rightLog2)
            {
                otava::intermediate::Instruction* shlInst = context->CreateShl(left, rightLog2);
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithInstruction(inst, shlInst);
                if (!rv) return rv;
                optimized = true;
            }
            else
            {
                if (left->IsSByteValue() && right->IsSByteValue())
                {
                    otava::intermediate::SByteValue* leftV = static_cast<otava::intermediate::SByteValue*>(left);
                    otava::intermediate::SByteValue* rightV = static_cast<otava::intermediate::SByteValue*>(right);
                    otava::intermediate::Value* value = context->GetSByteValue(leftV->GetValue() * rightV->GetValue());
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
                    optimized = true;
                }
                else if (left->IsByteValue() && right->IsByteValue())
                {
                    otava::intermediate::ByteValue* leftV = static_cast<otava::intermediate::ByteValue*>(left);
                    otava::intermediate::ByteValue* rightV = static_cast<otava::intermediate::ByteValue*>(right);
                    otava::intermediate::Value* value = context->GetByteValue(leftV->GetValue() * rightV->GetValue());
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
                    optimized = true;
                }
                else if (left->IsShortValue() && right->IsShortValue())
                {
                    otava::intermediate::ShortValue* leftV = static_cast<otava::intermediate::ShortValue*>(left);
                    otava::intermediate::ShortValue* rightV = static_cast<otava::intermediate::ShortValue*>(right);
                    otava::intermediate::Value* value = context->GetShortValue(leftV->GetValue() * rightV->GetValue());
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
                    optimized = true;
                }
                else if (left->IsUShortValue() && right->IsUShortValue())
                {
                    otava::intermediate::UShortValue* leftV = static_cast<otava::intermediate::UShortValue*>(left);
                    otava::intermediate::UShortValue* rightV = static_cast<otava::intermediate::UShortValue*>(right);
                    otava::intermediate::Value* value = context->GetUShortValue(leftV->GetValue() * rightV->GetValue());
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
                    optimized = true;
                }
                else if (left->IsIntValue() && right->IsIntValue())
                {
                    otava::intermediate::IntValue* leftV = static_cast<otava::intermediate::IntValue*>(left);
                    otava::intermediate::IntValue* rightV = static_cast<otava::intermediate::IntValue*>(right);
                    otava::intermediate::Value* value = context->GetIntValue(leftV->GetValue() * rightV->GetValue());
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
                    optimized = true;
                }
                else if (left->IsUIntValue() && right->IsUIntValue())
                {
                    otava::intermediate::UIntValue* leftV = static_cast<otava::intermediate::UIntValue*>(left);
                    otava::intermediate::UIntValue* rightV = static_cast<otava::intermediate::UIntValue*>(right);
                    otava::intermediate::Value* value = context->GetUIntValue(leftV->GetValue() * rightV->GetValue());
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
                    optimized = true;
                }
                else if (left->IsLongValue() && right->IsLongValue())
                {
                    otava::intermediate::LongValue* leftV = static_cast<otava::intermediate::LongValue*>(left);
                    otava::intermediate::LongValue* rightV = static_cast<otava::intermediate::LongValue*>(right);
                    otava::intermediate::Value* value = context->GetLongValue(leftV->GetValue() * rightV->GetValue());
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
                    optimized = true;
                }
                else if (left->IsULongValue() && right->IsULongValue())
                {
                    otava::intermediate::ULongValue* leftV = static_cast<otava::intermediate::ULongValue*>(left);
                    otava::intermediate::ULongValue* rightV = static_cast<otava::intermediate::ULongValue*>(right);
                    otava::intermediate::Value* value = context->GetULongValue(leftV->GetValue() * rightV->GetValue());
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
                    optimized = true;
                }
                else if (left->IsFloatValue() && right->IsFloatValue())
                {
                    otava::intermediate::FloatValue* leftV = static_cast<otava::intermediate::FloatValue*>(left);
                    otava::intermediate::FloatValue* rightV = static_cast<otava::intermediate::FloatValue*>(right);
                    otava::intermediate::Value* value = context->GetFloatValue(leftV->GetValue() * rightV->GetValue());
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
                    optimized = true;
                }
                else if (left->IsDoubleValue() && right->IsDoubleValue())
                {
                    otava::intermediate::DoubleValue* leftV = static_cast<otava::intermediate::DoubleValue*>(left);
                    otava::intermediate::DoubleValue* rightV = static_cast<otava::intermediate::DoubleValue*>(right);
                    otava::intermediate::Value* value = context->GetDoubleValue(leftV->GetValue() * rightV->GetValue());
                    std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                    if (!rv) return rv;
                    optimized = true;
                }
            }
        }
    }
    return std::expected<bool, int>(optimized);
}

std::expected<bool, int> OptimizeDiv(otava::intermediate::DivInstruction* inst, otava::intermediate::Context* context)
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
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, left);
        if (!rv) return rv;
        optimized = true;
    }
    else
    {
        otava::intermediate::Value* rightLog2 = right->Log2(context);
        if (rightLog2)
        {
            otava::intermediate::Instruction* shrInst = context->CreateShr(left, rightLog2);
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithInstruction(inst, shrInst);
            if (!rv) return rv;
            optimized = true;
        }
        else
        {
            if (left->IsSByteValue() && right->IsSByteValue())
            {
                otava::intermediate::SByteValue* leftV = static_cast<otava::intermediate::SByteValue*>(left);
                otava::intermediate::SByteValue* rightV = static_cast<otava::intermediate::SByteValue*>(right);
                otava::intermediate::Value* value = context->GetSByteValue(leftV->GetValue() / rightV->GetValue());
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
                optimized = true;
            }
            else if (left->IsByteValue() && right->IsByteValue())
            {
                otava::intermediate::ByteValue* leftV = static_cast<otava::intermediate::ByteValue*>(left);
                otava::intermediate::ByteValue* rightV = static_cast<otava::intermediate::ByteValue*>(right);
                otava::intermediate::Value* value = context->GetByteValue(leftV->GetValue() / rightV->GetValue());
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
                optimized = true;
            }
            else if (left->IsShortValue() && right->IsShortValue())
            {
                otava::intermediate::ShortValue* leftV = static_cast<otava::intermediate::ShortValue*>(left);
                otava::intermediate::ShortValue* rightV = static_cast<otava::intermediate::ShortValue*>(right);
                otava::intermediate::Value* value = context->GetShortValue(leftV->GetValue() / rightV->GetValue());
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
                optimized = true;
            }
            else if (left->IsUShortValue() && right->IsUShortValue())
            {
                otava::intermediate::UShortValue* leftV = static_cast<otava::intermediate::UShortValue*>(left);
                otava::intermediate::UShortValue* rightV = static_cast<otava::intermediate::UShortValue*>(right);
                otava::intermediate::Value* value = context->GetUShortValue(leftV->GetValue() / rightV->GetValue());
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
                optimized = true;
            }
            else if (left->IsIntValue() && right->IsIntValue())
            {
                otava::intermediate::IntValue* leftV = static_cast<otava::intermediate::IntValue*>(left);
                otava::intermediate::IntValue* rightV = static_cast<otava::intermediate::IntValue*>(right);
                otava::intermediate::Value* value = context->GetIntValue(leftV->GetValue() / rightV->GetValue());
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
                optimized = true;
            }
            else if (left->IsUIntValue() && right->IsUIntValue())
            {
                otava::intermediate::UIntValue* leftV = static_cast<otava::intermediate::UIntValue*>(left);
                otava::intermediate::UIntValue* rightV = static_cast<otava::intermediate::UIntValue*>(right);
                otava::intermediate::Value* value = context->GetUIntValue(leftV->GetValue() / rightV->GetValue());
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
                optimized = true;
            }
            else if (left->IsLongValue() && right->IsLongValue())
            {
                otava::intermediate::LongValue* leftV = static_cast<otava::intermediate::LongValue*>(left);
                otava::intermediate::LongValue* rightV = static_cast<otava::intermediate::LongValue*>(right);
                otava::intermediate::Value* value = context->GetLongValue(leftV->GetValue() / rightV->GetValue());
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
                optimized = true;
            }
            else if (left->IsULongValue() && right->IsULongValue())
            {
                otava::intermediate::ULongValue* leftV = static_cast<otava::intermediate::ULongValue*>(left);
                otava::intermediate::ULongValue* rightV = static_cast<otava::intermediate::ULongValue*>(right);
                otava::intermediate::Value* value = context->GetULongValue(leftV->GetValue() / rightV->GetValue());
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
                optimized = true;
            }
            else if (left->IsFloatValue() && right->IsFloatValue())
            {
                otava::intermediate::FloatValue* leftV = static_cast<otava::intermediate::FloatValue*>(left);
                otava::intermediate::FloatValue* rightV = static_cast<otava::intermediate::FloatValue*>(right);
                otava::intermediate::Value* value = context->GetFloatValue(leftV->GetValue() / rightV->GetValue());
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
                optimized = true;
            }
            else if (left->IsDoubleValue() && right->IsDoubleValue())
            {
                otava::intermediate::DoubleValue* leftV = static_cast<otava::intermediate::DoubleValue*>(left);
                otava::intermediate::DoubleValue* rightV = static_cast<otava::intermediate::DoubleValue*>(right);
                otava::intermediate::Value* value = context->GetDoubleValue(leftV->GetValue() / rightV->GetValue());
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
                optimized = true;
            }
        }
    }
    return std::expected<bool, int>(optimized);
}

std::expected<bool, int> OptimizeMod(otava::intermediate::ModInstruction* inst, otava::intermediate::Context* context)
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
            std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithInstruction(inst, andInst);
            if (!rv) return rv;
        }
        else
        {
            if (left->IsSByteValue() && right->IsSByteValue())
            {
                otava::intermediate::SByteValue* leftV = static_cast<otava::intermediate::SByteValue*>(left);
                otava::intermediate::SByteValue* rightV = static_cast<otava::intermediate::SByteValue*>(right);
                otava::intermediate::Value* value = context->GetSByteValue(leftV->GetValue() % rightV->GetValue());
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
                optimized = true;
            }
            else if (left->IsByteValue() && right->IsByteValue())
            {
                otava::intermediate::ByteValue* leftV = static_cast<otava::intermediate::ByteValue*>(left);
                otava::intermediate::ByteValue* rightV = static_cast<otava::intermediate::ByteValue*>(right);
                otava::intermediate::Value* value = context->GetByteValue(leftV->GetValue() % rightV->GetValue());
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
                optimized = true;
            }
            else if (left->IsShortValue() && right->IsShortValue())
            {
                otava::intermediate::ShortValue* leftV = static_cast<otava::intermediate::ShortValue*>(left);
                otava::intermediate::ShortValue* rightV = static_cast<otava::intermediate::ShortValue*>(right);
                otava::intermediate::Value* value = context->GetShortValue(leftV->GetValue() % rightV->GetValue());
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
                optimized = true;
            }
            else if (left->IsUShortValue() && right->IsUShortValue())
            {
                otava::intermediate::UShortValue* leftV = static_cast<otava::intermediate::UShortValue*>(left);
                otava::intermediate::UShortValue* rightV = static_cast<otava::intermediate::UShortValue*>(right);
                otava::intermediate::Value* value = context->GetUShortValue(leftV->GetValue() % rightV->GetValue());
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
                optimized = true;
            }
            else if (left->IsIntValue() && right->IsIntValue())
            {
                otava::intermediate::IntValue* leftV = static_cast<otava::intermediate::IntValue*>(left);
                otava::intermediate::IntValue* rightV = static_cast<otava::intermediate::IntValue*>(right);
                otava::intermediate::Value* value = context->GetIntValue(leftV->GetValue() % rightV->GetValue());
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
                optimized = true;
            }
            else if (left->IsUIntValue() && right->IsUIntValue())
            {
                otava::intermediate::UIntValue* leftV = static_cast<otava::intermediate::UIntValue*>(left);
                otava::intermediate::UIntValue* rightV = static_cast<otava::intermediate::UIntValue*>(right);
                otava::intermediate::Value* value = context->GetUIntValue(leftV->GetValue() % rightV->GetValue());
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
                optimized = true;
            }
            else if (left->IsLongValue() && right->IsLongValue())
            {
                otava::intermediate::LongValue* leftV = static_cast<otava::intermediate::LongValue*>(left);
                otava::intermediate::LongValue* rightV = static_cast<otava::intermediate::LongValue*>(right);
                otava::intermediate::Value* value = context->GetLongValue(leftV->GetValue() % rightV->GetValue());
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
                optimized = true;
            }
            else if (left->IsULongValue() && right->IsULongValue())
            {
                otava::intermediate::ULongValue* leftV = static_cast<otava::intermediate::ULongValue*>(left);
                otava::intermediate::ULongValue* rightV = static_cast<otava::intermediate::ULongValue*>(right);
                otava::intermediate::Value* value = context->GetULongValue(leftV->GetValue() % rightV->GetValue());
                std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
                if (!rv) return rv;
                optimized = true;
            }
        }
    }
    return std::expected<bool, int>(optimized);
}

std::expected<bool, int> OptimizeAnd(otava::intermediate::AndInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (left->IsSByteValue() && right->IsSByteValue())
    {
        otava::intermediate::SByteValue* leftV = static_cast<otava::intermediate::SByteValue*>(left);
        otava::intermediate::SByteValue* rightV = static_cast<otava::intermediate::SByteValue*>(right);
        otava::intermediate::Value* value = context->GetSByteValue(leftV->GetValue() & rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsByteValue() && right->IsByteValue())
    {
        otava::intermediate::ByteValue* leftV = static_cast<otava::intermediate::ByteValue*>(left);
        otava::intermediate::ByteValue* rightV = static_cast<otava::intermediate::ByteValue*>(right);
        otava::intermediate::Value* value = context->GetByteValue(leftV->GetValue() & rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsShortValue() && right->IsShortValue())
    {
        otava::intermediate::ShortValue* leftV = static_cast<otava::intermediate::ShortValue*>(left);
        otava::intermediate::ShortValue* rightV = static_cast<otava::intermediate::ShortValue*>(right);
        otava::intermediate::Value* value = context->GetShortValue(leftV->GetValue() & rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsUShortValue() && right->IsUShortValue())
    {
        otava::intermediate::UShortValue* leftV = static_cast<otava::intermediate::UShortValue*>(left);
        otava::intermediate::UShortValue* rightV = static_cast<otava::intermediate::UShortValue*>(right);
        otava::intermediate::Value* value = context->GetUShortValue(leftV->GetValue() & rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsIntValue() && right->IsIntValue())
    {
        otava::intermediate::IntValue* leftV = static_cast<otava::intermediate::IntValue*>(left);
        otava::intermediate::IntValue* rightV = static_cast<otava::intermediate::IntValue*>(right);
        otava::intermediate::Value* value = context->GetIntValue(leftV->GetValue() & rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsUIntValue() && right->IsUIntValue())
    {
        otava::intermediate::UIntValue* leftV = static_cast<otava::intermediate::UIntValue*>(left);
        otava::intermediate::UIntValue* rightV = static_cast<otava::intermediate::UIntValue*>(right);
        otava::intermediate::Value* value = context->GetUIntValue(leftV->GetValue() & rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsLongValue() && right->IsLongValue())
    {
        otava::intermediate::LongValue* leftV = static_cast<otava::intermediate::LongValue*>(left);
        otava::intermediate::LongValue* rightV = static_cast<otava::intermediate::LongValue*>(right);
        otava::intermediate::Value* value = context->GetLongValue(leftV->GetValue() & rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsULongValue() && right->IsULongValue())
    {
        otava::intermediate::ULongValue* leftV = static_cast<otava::intermediate::ULongValue*>(left);
        otava::intermediate::ULongValue* rightV = static_cast<otava::intermediate::ULongValue*>(right);
        otava::intermediate::Value* value = context->GetULongValue(leftV->GetValue() & rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    return std::expected<bool, int>(optimized);
}

std::expected<bool, int> OptimizeOr(otava::intermediate::OrInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (left->IsSByteValue() && right->IsSByteValue())
    {
        otava::intermediate::SByteValue* leftV = static_cast<otava::intermediate::SByteValue*>(left);
        otava::intermediate::SByteValue* rightV = static_cast<otava::intermediate::SByteValue*>(right);
        otava::intermediate::Value* value = context->GetSByteValue(leftV->GetValue() | rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsByteValue() && right->IsByteValue())
    {
        otava::intermediate::ByteValue* leftV = static_cast<otava::intermediate::ByteValue*>(left);
        otava::intermediate::ByteValue* rightV = static_cast<otava::intermediate::ByteValue*>(right);
        otava::intermediate::Value* value = context->GetByteValue(leftV->GetValue() | rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsShortValue() && right->IsShortValue())
    {
        otava::intermediate::ShortValue* leftV = static_cast<otava::intermediate::ShortValue*>(left);
        otava::intermediate::ShortValue* rightV = static_cast<otava::intermediate::ShortValue*>(right);
        otava::intermediate::Value* value = context->GetShortValue(leftV->GetValue() | rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsUShortValue() && right->IsUShortValue())
    {
        otava::intermediate::UShortValue* leftV = static_cast<otava::intermediate::UShortValue*>(left);
        otava::intermediate::UShortValue* rightV = static_cast<otava::intermediate::UShortValue*>(right);
        otava::intermediate::Value* value = context->GetUShortValue(leftV->GetValue() | rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsIntValue() && right->IsIntValue())
    {
        otava::intermediate::IntValue* leftV = static_cast<otava::intermediate::IntValue*>(left);
        otava::intermediate::IntValue* rightV = static_cast<otava::intermediate::IntValue*>(right);
        otava::intermediate::Value* value = context->GetIntValue(leftV->GetValue() | rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsUIntValue() && right->IsUIntValue())
    {
        otava::intermediate::UIntValue* leftV = static_cast<otava::intermediate::UIntValue*>(left);
        otava::intermediate::UIntValue* rightV = static_cast<otava::intermediate::UIntValue*>(right);
        otava::intermediate::Value* value = context->GetUIntValue(leftV->GetValue() | rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsLongValue() && right->IsLongValue())
    {
        otava::intermediate::LongValue* leftV = static_cast<otava::intermediate::LongValue*>(left);
        otava::intermediate::LongValue* rightV = static_cast<otava::intermediate::LongValue*>(right);
        otava::intermediate::Value* value = context->GetLongValue(leftV->GetValue() | rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsULongValue() && right->IsULongValue())
    {
        otava::intermediate::ULongValue* leftV = static_cast<otava::intermediate::ULongValue*>(left);
        otava::intermediate::ULongValue* rightV = static_cast<otava::intermediate::ULongValue*>(right);
        otava::intermediate::Value* value = context->GetULongValue(leftV->GetValue() | rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    return std::expected<bool, int>(optimized);
}

std::expected<bool, int> OptimizeXor(otava::intermediate::XorInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (left->IsSByteValue() && right->IsSByteValue())
    {
        otava::intermediate::SByteValue* leftV = static_cast<otava::intermediate::SByteValue*>(left);
        otava::intermediate::SByteValue* rightV = static_cast<otava::intermediate::SByteValue*>(right);
        otava::intermediate::Value* value = context->GetSByteValue(leftV->GetValue() ^ rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsByteValue() && right->IsByteValue())
    {
        otava::intermediate::ByteValue* leftV = static_cast<otava::intermediate::ByteValue*>(left);
        otava::intermediate::ByteValue* rightV = static_cast<otava::intermediate::ByteValue*>(right);
        otava::intermediate::Value* value = context->GetByteValue(leftV->GetValue() ^ rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsShortValue() && right->IsShortValue())
    {
        otava::intermediate::ShortValue* leftV = static_cast<otava::intermediate::ShortValue*>(left);
        otava::intermediate::ShortValue* rightV = static_cast<otava::intermediate::ShortValue*>(right);
        otava::intermediate::Value* value = context->GetShortValue(leftV->GetValue() ^ rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsUShortValue() && right->IsUShortValue())
    {
        otava::intermediate::UShortValue* leftV = static_cast<otava::intermediate::UShortValue*>(left);
        otava::intermediate::UShortValue* rightV = static_cast<otava::intermediate::UShortValue*>(right);
        otava::intermediate::Value* value = context->GetUShortValue(leftV->GetValue() ^ rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsIntValue() && right->IsIntValue())
    {
        otava::intermediate::IntValue* leftV = static_cast<otava::intermediate::IntValue*>(left);
        otava::intermediate::IntValue* rightV = static_cast<otava::intermediate::IntValue*>(right);
        otava::intermediate::Value* value = context->GetIntValue(leftV->GetValue() ^ rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsUIntValue() && right->IsUIntValue())
    {
        otava::intermediate::UIntValue* leftV = static_cast<otava::intermediate::UIntValue*>(left);
        otava::intermediate::UIntValue* rightV = static_cast<otava::intermediate::UIntValue*>(right);
        otava::intermediate::Value* value = context->GetUIntValue(leftV->GetValue() ^ rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsLongValue() && right->IsLongValue())
    {
        otava::intermediate::LongValue* leftV = static_cast<otava::intermediate::LongValue*>(left);
        otava::intermediate::LongValue* rightV = static_cast<otava::intermediate::LongValue*>(right);
        otava::intermediate::Value* value = context->GetLongValue(leftV->GetValue() ^ rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsULongValue() && right->IsULongValue())
    {
        otava::intermediate::ULongValue* leftV = static_cast<otava::intermediate::ULongValue*>(left);
        otava::intermediate::ULongValue* rightV = static_cast<otava::intermediate::ULongValue*>(right);
        otava::intermediate::Value* value = context->GetULongValue(leftV->GetValue() ^ rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    return std::expected<bool, int>(optimized);
}

std::expected<bool, int> OptimizeShl(otava::intermediate::ShlInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (left->IsSByteValue() && right->IsSByteValue())
    {
        otava::intermediate::SByteValue* leftV = static_cast<otava::intermediate::SByteValue*>(left);
        otava::intermediate::SByteValue* rightV = static_cast<otava::intermediate::SByteValue*>(right);
        otava::intermediate::Value* value = context->GetSByteValue(leftV->GetValue() << rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsByteValue() && right->IsByteValue())
    {
        otava::intermediate::ByteValue* leftV = static_cast<otava::intermediate::ByteValue*>(left);
        otava::intermediate::ByteValue* rightV = static_cast<otava::intermediate::ByteValue*>(right);
        otava::intermediate::Value* value = context->GetByteValue(leftV->GetValue() << rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsShortValue() && right->IsShortValue())
    {
        otava::intermediate::ShortValue* leftV = static_cast<otava::intermediate::ShortValue*>(left);
        otava::intermediate::ShortValue* rightV = static_cast<otava::intermediate::ShortValue*>(right);
        otava::intermediate::Value* value = context->GetShortValue(leftV->GetValue() << rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsUShortValue() && right->IsUShortValue())
    {
        otava::intermediate::UShortValue* leftV = static_cast<otava::intermediate::UShortValue*>(left);
        otava::intermediate::UShortValue* rightV = static_cast<otava::intermediate::UShortValue*>(right);
        otava::intermediate::Value* value = context->GetUShortValue(leftV->GetValue() << rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsIntValue() && right->IsIntValue())
    {
        otava::intermediate::IntValue* leftV = static_cast<otava::intermediate::IntValue*>(left);
        otava::intermediate::IntValue* rightV = static_cast<otava::intermediate::IntValue*>(right);
        otava::intermediate::Value* value = context->GetIntValue(leftV->GetValue() << rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsUIntValue() && right->IsUIntValue())
    {
        otava::intermediate::UIntValue* leftV = static_cast<otava::intermediate::UIntValue*>(left);
        otava::intermediate::UIntValue* rightV = static_cast<otava::intermediate::UIntValue*>(right);
        otava::intermediate::Value* value = context->GetUIntValue(leftV->GetValue() << rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsLongValue() && right->IsLongValue())
    {
        otava::intermediate::LongValue* leftV = static_cast<otava::intermediate::LongValue*>(left);
        otava::intermediate::LongValue* rightV = static_cast<otava::intermediate::LongValue*>(right);
        otava::intermediate::Value* value = context->GetLongValue(leftV->GetValue() << rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsULongValue() && right->IsULongValue())
    {
        otava::intermediate::ULongValue* leftV = static_cast<otava::intermediate::ULongValue*>(left);
        otava::intermediate::ULongValue* rightV = static_cast<otava::intermediate::ULongValue*>(right);
        otava::intermediate::Value* value = context->GetULongValue(leftV->GetValue() << rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    return std::expected<bool, int>(optimized);
}

std::expected<bool, int> OptimizeShr(otava::intermediate::ShrInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (left->IsSByteValue() && right->IsSByteValue())
    {
        otava::intermediate::SByteValue* leftV = static_cast<otava::intermediate::SByteValue*>(left);
        otava::intermediate::SByteValue* rightV = static_cast<otava::intermediate::SByteValue*>(right);
        otava::intermediate::Value* value = context->GetSByteValue(leftV->GetValue() >> rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsByteValue() && right->IsByteValue())
    {
        otava::intermediate::ByteValue* leftV = static_cast<otava::intermediate::ByteValue*>(left);
        otava::intermediate::ByteValue* rightV = static_cast<otava::intermediate::ByteValue*>(right);
        otava::intermediate::Value* value = context->GetByteValue(leftV->GetValue() >> rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsShortValue() && right->IsShortValue())
    {
        otava::intermediate::ShortValue* leftV = static_cast<otava::intermediate::ShortValue*>(left);
        otava::intermediate::ShortValue* rightV = static_cast<otava::intermediate::ShortValue*>(right);
        otava::intermediate::Value* value = context->GetShortValue(leftV->GetValue() >> rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsUShortValue() && right->IsUShortValue())
    {
        otava::intermediate::UShortValue* leftV = static_cast<otava::intermediate::UShortValue*>(left);
        otava::intermediate::UShortValue* rightV = static_cast<otava::intermediate::UShortValue*>(right);
        otava::intermediate::Value* value = context->GetUShortValue(leftV->GetValue() >> rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsIntValue() && right->IsIntValue())
    {
        otava::intermediate::IntValue* leftV = static_cast<otava::intermediate::IntValue*>(left);
        otava::intermediate::IntValue* rightV = static_cast<otava::intermediate::IntValue*>(right);
        otava::intermediate::Value* value = context->GetIntValue(leftV->GetValue() >> rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsUIntValue() && right->IsUIntValue())
    {
        otava::intermediate::UIntValue* leftV = static_cast<otava::intermediate::UIntValue*>(left);
        otava::intermediate::UIntValue* rightV = static_cast<otava::intermediate::UIntValue*>(right);
        otava::intermediate::Value* value = context->GetUIntValue(leftV->GetValue() >> rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsLongValue() && right->IsLongValue())
    {
        otava::intermediate::LongValue* leftV = static_cast<otava::intermediate::LongValue*>(left);
        otava::intermediate::LongValue* rightV = static_cast<otava::intermediate::LongValue*>(right);
        otava::intermediate::Value* value = context->GetLongValue(leftV->GetValue() >> rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsULongValue() && right->IsULongValue())
    {
        otava::intermediate::ULongValue* leftV = static_cast<otava::intermediate::ULongValue*>(left);
        otava::intermediate::ULongValue* rightV = static_cast<otava::intermediate::ULongValue*>(right);
        otava::intermediate::Value* value = context->GetULongValue(leftV->GetValue() >> rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    return std::expected<bool, int>(optimized);
}

std::expected<bool, int> OptimizeEqual(otava::intermediate::EqualInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (left->IsBoolValue() && right->IsBoolValue())
    {
        otava::intermediate::BoolValue* leftV = static_cast<otava::intermediate::BoolValue*>(left);
        otava::intermediate::BoolValue* rightV = static_cast<otava::intermediate::BoolValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() == rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsSByteValue() && right->IsSByteValue())
    {
        otava::intermediate::SByteValue* leftV = static_cast<otava::intermediate::SByteValue*>(left);
        otava::intermediate::SByteValue* rightV = static_cast<otava::intermediate::SByteValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() == rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsByteValue() && right->IsByteValue())
    {
        otava::intermediate::ByteValue* leftV = static_cast<otava::intermediate::ByteValue*>(left);
        otava::intermediate::ByteValue* rightV = static_cast<otava::intermediate::ByteValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() == rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsShortValue() && right->IsShortValue())
    {
        otava::intermediate::ShortValue* leftV = static_cast<otava::intermediate::ShortValue*>(left);
        otava::intermediate::ShortValue* rightV = static_cast<otava::intermediate::ShortValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() == rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsUShortValue() && right->IsUShortValue())
    {
        otava::intermediate::UShortValue* leftV = static_cast<otava::intermediate::UShortValue*>(left);
        otava::intermediate::UShortValue* rightV = static_cast<otava::intermediate::UShortValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() == rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsIntValue() && right->IsIntValue())
    {
        otava::intermediate::IntValue* leftV = static_cast<otava::intermediate::IntValue*>(left);
        otava::intermediate::IntValue* rightV = static_cast<otava::intermediate::IntValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() == rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsUIntValue() && right->IsUIntValue())
    {
        otava::intermediate::UIntValue* leftV = static_cast<otava::intermediate::UIntValue*>(left);
        otava::intermediate::UIntValue* rightV = static_cast<otava::intermediate::UIntValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() == rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsLongValue() && right->IsLongValue())
    {
        otava::intermediate::LongValue* leftV = static_cast<otava::intermediate::LongValue*>(left);
        otava::intermediate::LongValue* rightV = static_cast<otava::intermediate::LongValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() == rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsULongValue() && right->IsULongValue())
    {
        otava::intermediate::ULongValue* leftV = static_cast<otava::intermediate::ULongValue*>(left);
        otava::intermediate::ULongValue* rightV = static_cast<otava::intermediate::ULongValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() == rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsFloatValue() && right->IsFloatValue())
    {
        otava::intermediate::FloatValue* leftV = static_cast<otava::intermediate::FloatValue*>(left);
        otava::intermediate::FloatValue* rightV = static_cast<otava::intermediate::FloatValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() == rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsDoubleValue() && right->IsDoubleValue())
    {
        otava::intermediate::DoubleValue* leftV = static_cast<otava::intermediate::DoubleValue*>(left);
        otava::intermediate::DoubleValue* rightV = static_cast<otava::intermediate::DoubleValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() == rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    return std::expected<bool, int>(optimized);
}

std::expected<bool, int> OptimizeLess(otava::intermediate::LessInstruction* inst, otava::intermediate::Context* context)
{
    bool optimized = false;
    otava::intermediate::Value* left = inst->Left();
    otava::intermediate::Value* right = inst->Right();
    if (left->IsSByteValue() && right->IsSByteValue())
    {
        otava::intermediate::SByteValue* leftV = static_cast<otava::intermediate::SByteValue*>(left);
        otava::intermediate::SByteValue* rightV = static_cast<otava::intermediate::SByteValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() < rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsByteValue() && right->IsByteValue())
    {
        otava::intermediate::ByteValue* leftV = static_cast<otava::intermediate::ByteValue*>(left);
        otava::intermediate::ByteValue* rightV = static_cast<otava::intermediate::ByteValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() < rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsShortValue() && right->IsShortValue())
    {
        otava::intermediate::ShortValue* leftV = static_cast<otava::intermediate::ShortValue*>(left);
        otava::intermediate::ShortValue* rightV = static_cast<otava::intermediate::ShortValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() < rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsUShortValue() && right->IsUShortValue())
    {
        otava::intermediate::UShortValue* leftV = static_cast<otava::intermediate::UShortValue*>(left);
        otava::intermediate::UShortValue* rightV = static_cast<otava::intermediate::UShortValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() < rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsIntValue() && right->IsIntValue())
    {
        otava::intermediate::IntValue* leftV = static_cast<otava::intermediate::IntValue*>(left);
        otava::intermediate::IntValue* rightV = static_cast<otava::intermediate::IntValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() < rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return  rv;
        optimized = true;
    }
    else if (left->IsUIntValue() && right->IsUIntValue())
    {
        otava::intermediate::UIntValue* leftV = static_cast<otava::intermediate::UIntValue*>(left);
        otava::intermediate::UIntValue* rightV = static_cast<otava::intermediate::UIntValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() < rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsLongValue() && right->IsLongValue())
    {
        otava::intermediate::LongValue* leftV = static_cast<otava::intermediate::LongValue*>(left);
        otava::intermediate::LongValue* rightV = static_cast<otava::intermediate::LongValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() < rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsULongValue() && right->IsULongValue())
    {
        otava::intermediate::ULongValue* leftV = static_cast<otava::intermediate::ULongValue*>(left);
        otava::intermediate::ULongValue* rightV = static_cast<otava::intermediate::ULongValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() < rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsFloatValue() && right->IsFloatValue())
    {
        otava::intermediate::FloatValue* leftV = static_cast<otava::intermediate::FloatValue*>(left);
        otava::intermediate::FloatValue* rightV = static_cast<otava::intermediate::FloatValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() < rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return rv;
        optimized = true;
    }
    else if (left->IsDoubleValue() && right->IsDoubleValue())
    {
        otava::intermediate::DoubleValue* leftV = static_cast<otava::intermediate::DoubleValue*>(left);
        otava::intermediate::DoubleValue* rightV = static_cast<otava::intermediate::DoubleValue*>(right);
        otava::intermediate::Value* value = context->GetBoolValue(leftV->GetValue() < rightV->GetValue());
        std::expected<bool, int> rv = otava::intermediate::ReplaceInstructionWithValue(inst, value);
        if (!rv) return  rv;
        optimized = true;
    }
    return std::expected<bool, int>(optimized);
}

std::expected<bool, int> OptimizeArithmetics(otava::intermediate::Function* fn, otava::intermediate::Context* context)
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
                        std::expected<bool, int> rv = OptimizeNot(notInst, context);
                        if (!rv) return rv; else if (*rv) optimized = true;
                        break;
                    }
                    case otava::intermediate::OpCode::neg:
                    {
                        otava::intermediate::NegInstruction* negInst = static_cast<otava::intermediate::NegInstruction*>(inst);
                        std::expected<bool, int> rv = OptimizeNeg(negInst, context);
                        if (!rv) return rv; else if (*rv) optimized = true;
                        break;
                    }
                    case otava::intermediate::OpCode::signextend:
                    {
                        otava::intermediate::SignExtendInstruction* signExtendInst = static_cast<otava::intermediate::SignExtendInstruction*>(inst);
                        std::expected<bool, int> rv = OptimizeSignExtend(signExtendInst, context);
                        if (!rv) return rv; else if (*rv) optimized = true;
                        break;
                    }
                    case otava::intermediate::OpCode::zeroextend:
                    {
                        otava::intermediate::ZeroExtendInstruction* zeroExtendInst = static_cast<otava::intermediate::ZeroExtendInstruction*>(inst);
                        std::expected<bool, int> rv = OptimizeZeroExtend(zeroExtendInst, context);
                        if (!rv) return rv; else if (*rv) optimized = true;
                        break;
                    }
                    case otava::intermediate::OpCode::add:
                    {
                        otava::intermediate::AddInstruction* addInst = static_cast<otava::intermediate::AddInstruction*>(inst);
                        std::expected<bool, int> rv = OptimizeAdd(addInst, context);
                        if (!rv) return rv; else if (*rv) optimized = true;
                        break;
                    }
                    case otava::intermediate::OpCode::sub:
                    {
                        otava::intermediate::SubInstruction* subInst = static_cast<otava::intermediate::SubInstruction*>(inst);
                        std::expected<bool, int> rv = OptimizeSub(subInst, context);
                        if (!rv) return rv; else if (*rv) optimized = true;
                        break;
                    }
                    case otava::intermediate::OpCode::mul:
                    {
                        otava::intermediate::MulInstruction* mulInst = static_cast<otava::intermediate::MulInstruction*>(inst);
                        std::expected<bool, int> rv = OptimizeMul(mulInst, context);
                        if (!rv) return rv; else if (*rv) optimized = true;
                        break;
                    }
                    case otava::intermediate::OpCode::div_:
                    {
                        otava::intermediate::DivInstruction* divInst = static_cast<otava::intermediate::DivInstruction*>(inst);
                        std::expected<bool, int> rv = OptimizeDiv(divInst, context);
                        if (!rv) return rv; else if (*rv) optimized = true;
                        break;
                    }
                    case otava::intermediate::OpCode::mod:
                    {
                        otava::intermediate::ModInstruction* modInst = static_cast<otava::intermediate::ModInstruction*>(inst);
                        std::expected<bool, int> rv = OptimizeMod(modInst, context);
                        if (!rv) return rv; else if (*rv) optimized = true;
                        break;
                    }
                    case otava::intermediate::OpCode::and_:
                    {
                        otava::intermediate::AndInstruction* andInst = static_cast<otava::intermediate::AndInstruction*>(inst);
                        std::expected<bool, int> rv = OptimizeAnd(andInst, context);
                        if (!rv) return rv; else if (*rv) optimized = true;
                        break;
                    }
                    case otava::intermediate::OpCode::or_:
                    {
                        otava::intermediate::OrInstruction* orInst = static_cast<otava::intermediate::OrInstruction*>(inst);
                        std::expected<bool, int> rv = OptimizeOr(orInst, context);
                        if (!rv) return rv; else if (*rv) optimized = true;
                        break;
                    }
                    case otava::intermediate::OpCode::xor_:
                    {
                        otava::intermediate::XorInstruction* xorInst = static_cast<otava::intermediate::XorInstruction*>(inst);
                        std::expected<bool, int> rv = OptimizeXor(xorInst, context);
                        if (!rv) return rv; else if (*rv) optimized = true;
                        break;
                    }
                    case otava::intermediate::OpCode::shl:
                    {
                        otava::intermediate::ShlInstruction* shlInst = static_cast<otava::intermediate::ShlInstruction*>(inst);
                        std::expected<bool, int> rv = OptimizeShl(shlInst, context);
                        if (!rv) return rv; else if (*rv) optimized = true;
                        break;
                    }
                    case otava::intermediate::OpCode::shr:
                    {
                        otava::intermediate::ShrInstruction* shrInst = static_cast<otava::intermediate::ShrInstruction*>(inst);
                        std::expected<bool, int> rv = OptimizeShr(shrInst, context);
                        if (!rv) return rv; else if (*rv) optimized = true;
                        break;
                    }
                    case otava::intermediate::OpCode::equal:
                    {
                        otava::intermediate::EqualInstruction* equalInst = static_cast<otava::intermediate::EqualInstruction*>(inst);
                        std::expected<bool, int> rv = OptimizeEqual(equalInst, context);
                        if (!rv) return rv; else if (*rv) optimized = true;
                        break;
                    }
                    case otava::intermediate::OpCode::less:
                    {
                        otava::intermediate::LessInstruction* lessInst = static_cast<otava::intermediate::LessInstruction*>(inst);
                        std::expected<bool, int> rv = OptimizeLess(lessInst, context);
                        if (!rv) return rv; else if (*rv) optimized = true;
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
    return std::expected<bool, int>(optimized);
}

} // otava::optimizer
