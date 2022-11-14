// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.data_item_adder;

import otava.assembly.literal;
import otava.assembly.symbol;
import otava.intermediate.data;

namespace otava::intermediate {

DataItemAdder::DataItemAdder(Context* context_, otava::assembly::Data* data_) : Visitor(context_), context(context_), data(data_)
{
}

void DataItemAdder::Visit(BoolValue& value)
{
    int64_t v = value.GetValue() ? 1 : 0;
    data->AddItem(new otava::assembly::Literal(v, 1));
}

void DataItemAdder::Visit(SByteValue& value)
{
    data->AddItem(new otava::assembly::Literal(value.GetValue(), 1));
}

void DataItemAdder::Visit(ByteValue& value)
{
    data->AddItem(new otava::assembly::Literal(value.GetValue(), 1));
}

void DataItemAdder::Visit(ShortValue& value)
{
    data->AddItem(new otava::assembly::Literal(value.GetValue(), 2));
}

void DataItemAdder::Visit(UShortValue& value)
{
    data->AddItem(new otava::assembly::Literal(value.GetValue(), 2));
}

void DataItemAdder::Visit(IntValue& value)
{
    data->AddItem(new otava::assembly::Literal(value.GetValue(), 4));
}

void DataItemAdder::Visit(UIntValue& value)
{
    data->AddItem(new otava::assembly::Literal(value.GetValue(), 4));
}

void DataItemAdder::Visit(LongValue& value)
{
    data->AddItem(new otava::assembly::Literal(value.GetValue(), 8));
}

void DataItemAdder::Visit(ULongValue& value)
{
    data->AddItem(new otava::assembly::Literal(value.GetValue(), 8));
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
    data->AddItem(new otava::assembly::Literal(0, 8));
}

void DataItemAdder::Visit(AddressValue& value)
{
    data->AddItem(new otava::assembly::Symbol(value.GetValue()->Name()));
}

void DataItemAdder::Visit(ArrayValue& value)
{
    // todo
}

void DataItemAdder::Visit(StructureValue& value)
{
    // todo
}

void DataItemAdder::Visit(StringValue& value)
{
    for (char c : value.GetValue())
    {
        data->AddItem(new otava::assembly::Literal(static_cast<uint8_t>(c), 1));
    }
    data->AddItem(new otava::assembly::Literal(0, 1));
}

void DataItemAdder::Visit(StringArrayValue& value)
{
    // todo
}

void DataItemAdder::Visit(ConversionValue& value)
{
    // todo
}

void DataItemAdder::Visit(ClsIdValue& value)
{
    // todo
}

void DataItemAdder::Visit(SymbolValue& value)
{
    data->AddItem(new otava::assembly::Symbol(value.Symbol()));
}

} // otava::intermediate
