// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.data_item_adder;

import std.core;
import otava.intermediate.visitor;
import otava.assembly.data;

export namespace otava::intermediate {

class Context;

class DataItemAdder : public Visitor
{
public:
    DataItemAdder(Context* context_, otava::assembly::Data* data_);
    void Visit(BoolValue& value) override;
    void Visit(SByteValue& value) override;
    void Visit(ByteValue& value) override;
    void Visit(ShortValue& value) override;
    void Visit(UShortValue& value) override;
    void Visit(IntValue& value) override;
    void Visit(UIntValue& value) override;
    void Visit(LongValue& value) override;
    void Visit(ULongValue& value) override;
    void Visit(FloatValue& value) override;
    void Visit(DoubleValue& value) override;
    void Visit(NullValue& value) override;
    void Visit(AddressValue& value) override;
    void Visit(ArrayValue& value) override;
    void Visit(StructureValue& value) override;
    void Visit(StringValue& value) override;
    void Visit(StringArrayValue& value) override;
    void Visit(ConversionValue& value) override;
    void Visit(ClsIdValue& value) override;
    void Visit(SymbolValue& value) override;
private:
    Context* context;
    otava::assembly::Data* data;
};

} // otava::intermediate
