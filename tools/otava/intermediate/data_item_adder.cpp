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

DataItemAdder::DataItemAdder(Context* context_, otava::assembly::Data* data_) : Visitor(context_), context(context_), data(data_)
{
}

void DataItemAdder::Visit(BoolValue& value)
{
    int64_t v = value.GetValue() ? 1 : 0;
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(v, 1));
}

void DataItemAdder::Visit(SByteValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(value.GetValue(), 1));
}

void DataItemAdder::Visit(ByteValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(value.GetValue(), 1));
}

void DataItemAdder::Visit(ShortValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(value.GetValue(), 2));
}

void DataItemAdder::Visit(UShortValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(value.GetValue(), 2));
}

void DataItemAdder::Visit(IntValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(value.GetValue(), 4));
}

void DataItemAdder::Visit(UIntValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(value.GetValue(), 4));
}

void DataItemAdder::Visit(LongValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(value.GetValue(), 8));
}

void DataItemAdder::Visit(ULongValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(value.GetValue(), 8));
}

void DataItemAdder::Visit(FloatValue& value)
{
    // todo
}

void DataItemAdder::Visit(DoubleValue& value)
{
    // todo
}

void DataItemAdder::Visit(NullValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Literal(0, 8));
}

void DataItemAdder::Visit(AddressValue& value)
{
    data->AddItem(value.GetType()->DataInstruction(), new otava::assembly::Symbol(value.GetValue()->Name()));
}

void DataItemAdder::Visit(ArrayValue& value)
{
    data->UseCommonInst(true);
    for (const auto& element : value.Elements())
    {
        element->Accept(*this);
    }
}

void DataItemAdder::Visit(StructureValue& value)
{
    for (Value* fieldValue : value.FieldValues())
    {
        fieldValue->Accept(*this);
    }
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
