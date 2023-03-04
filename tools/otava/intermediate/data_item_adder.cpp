// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.data_item_adder;

import otava.assembly.literal;
import otava.assembly.symbol;
import otava.intermediate.data;
import otava.intermediate.type;

namespace otava::intermediate {

DataItemAdder::DataItemAdder(Context* context_, otava::assembly::Data* data_) : Visitor(context_), context(context_), data(data_), offset(0)
{
}

void DataItemAdder::Visit(BoolValue& value)
{
    int64_t v = value.GetValue() ? 1 : 0;
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(v, 1));
    offset += value.GetType()->Size();
}

void DataItemAdder::Visit(SByteValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(value.GetValue(), 1));
    offset += value.GetType()->Size();
}

void DataItemAdder::Visit(ByteValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(value.GetValue(), 1));
    offset += value.GetType()->Size();
}

void DataItemAdder::Visit(ShortValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(value.GetValue(), 2));
    offset += value.GetType()->Size();
}

void DataItemAdder::Visit(UShortValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(value.GetValue(), 2));
    offset += value.GetType()->Size();
}

void DataItemAdder::Visit(IntValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(value.GetValue(), 4));
    offset += value.GetType()->Size();
}

void DataItemAdder::Visit(UIntValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(value.GetValue(), 4));
    offset += value.GetType()->Size();
}

void DataItemAdder::Visit(LongValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(value.GetValue(), 8));
    offset += value.GetType()->Size();
}

void DataItemAdder::Visit(ULongValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(value.GetValue(), 8));
    offset += value.GetType()->Size();
}

void DataItemAdder::Visit(FloatValue& value)
{
    // todo
    offset += value.GetType()->Size();
}

void DataItemAdder::Visit(DoubleValue& value)
{
    // todo
    offset += value.GetType()->Size();
}

void DataItemAdder::Visit(NullValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(0, 8));
    offset += value.GetType()->Size();
}

void DataItemAdder::Visit(AddressValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Symbol(value.GetValue()->Name()));
    offset += value.GetType()->Size();
}

void DataItemAdder::Visit(ArrayValue& value)
{
    for (const auto& element : value.Elements())
    {
        element->Accept(*this);
        offset += element->GetType()->Size();
    }
}

void DataItemAdder::Visit(StructureValue& value)
{
    StructureType* type = static_cast<StructureType*>(value.GetType());
    int64_t soffset = 0;
    int64_t prevOffset = offset;
    offset = 0;
    int n = type->FieldCount();
    for (int i = 0; i < n; ++i)
    {
        int64_t fieldOffset = type->GetFieldOffset(i);
        soffset += fieldOffset;
        if (soffset > offset)
        {
            int64_t m = soffset - offset;
            for (int64_t i = 0; i < m; ++i)
            {
                data->AddItem(otava::assembly::DataInst::DB, new otava::assembly::Literal(0, 1));
                ++offset;
            }
        }
        Value* fieldValue = value.FieldValues()[i];
        fieldValue->Accept(*this);
    }
    int64_t size = type->Size();
    if (size > offset)
    {
        int64_t m = size - offset;
        for (int64_t i = 0; i < m; ++i)
        {
            data->AddItem(otava::assembly::DataInst::DB, new otava::assembly::Literal(0, 1));
            ++offset;
        }
    }
    offset = prevOffset + size;
}

void DataItemAdder::Visit(StringValue& value)
{
    data->UseCommonInst(true);
    for (char c : value.GetValue())
    {
        data->AddItem(otava::assembly::DataInst::DB, new otava::assembly::Literal(static_cast<uint8_t>(c), 1));
    }
    data->AddItem(otava::assembly::DataInst::DB, new otava::assembly::Literal(0, 1));
}

void DataItemAdder::Visit(StringArrayValue& value)
{
    // todo
}

void DataItemAdder::Visit(ConversionValue& value)
{
    value.From()->Accept(*this);
}

void DataItemAdder::Visit(ClsIdValue& value)
{
    // todo
}

void DataItemAdder::Visit(SymbolValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Symbol(value.Symbol()));
}

} // otava::intermediate
