// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.operation.repository;

import otava.symbols.type.symbol;
import otava.symbols.bound.tree;
import otava.symbols.bound.tree.visitor;
import otava.symbols.function.symbol;

namespace otava::symbols {

struct ConversionKey
{
    ConversionKey(TypeSymbol* sourceType_, TypeSymbol* targetType_);
    TypeSymbol* sourceType;
    TypeSymbol* targetType;
};

ConversionKey::ConversionKey(TypeSymbol* sourceType_, TypeSymbol* targetType_) : sourceType(sourceType_), targetType(targetType_)
{
}

struct ConversionKeyLess
{
    bool operator()(const ConversionKey& left, const ConversionKey& right) const
    {
        if (left.sourceType < right.sourceType) return true;
        if (left.sourceType > right.sourceType) return false;
        return left.targetType < right.targetType;
    }
};

class ConversionFunctionSymbol : public FunctionSymbol
{
public:
    ConversionFunctionSymbol(const ConversionKey& key_);
    const ConversionKey& Key() const { return key; }
private:
    ConversionKey key;
};

ConversionFunctionSymbol::ConversionFunctionSymbol(const ConversionKey& key_) : FunctionSymbol(U"@conversion"), key(key_)
{
    SetReturnType(key.targetType);
}

class ConversionOperationGroup : public OperationGroup
{
public:
    ConversionOperationGroup();
    std::unique_ptr<BoundFunctionCallNode> GetOperation(std::vector<std::unique_ptr<BoundExpressionNode>>& args) override;
private:
    std::vector<std::unique_ptr<ConversionFunctionSymbol>> conversionFunctions;
    std::map<ConversionKey, ConversionFunctionSymbol*, ConversionKeyLess> conversionFunctionMap;
};

ConversionOperationGroup::ConversionOperationGroup() : OperationGroup(U"@conversion")
{
}

class TypeExtractor : public BoundTreeVisitor
{
public:
    TypeExtractor();
    void Visit(BoundTypeNode& node) override;
    TypeSymbol* GetType() const { return type; }
private:
    TypeSymbol* type;
};

TypeExtractor::TypeExtractor() : type(nullptr)
{
}

void TypeExtractor::Visit(BoundTypeNode& node)
{
    type = node.GetType();
}

TypeSymbol* ExtractType(BoundExpressionNode* node)
{
    TypeExtractor extractor;
    node->Accept(extractor);
    return extractor.GetType();
}

std::unique_ptr<BoundFunctionCallNode> ConversionOperationGroup::GetOperation(std::vector<std::unique_ptr<BoundExpressionNode>>& args)
{
    /*
        if (args.size() == 1)
    {
        TypeSymbol* targetType = ExtractType(subject.get());
        if (targetType)
        {
            TypeSymbol* sourceType = args.front()->GetType();
            if (sourceType)
            {
                ConversionKey key(sourceType, targetType);
                ConversionFunctionSymbol* conversionFunctionSymbol = nullptr;
                auto it = conversionFunctionMap.find(key);
                if (it != conversionFunctionMap.cend())
                {
                    conversionFunctionSymbol = it->second;
                }
                else
                {
                    conversionFunctionSymbol = new ConversionFunctionSymbol(key);
                    conversionFunctions.push_back(std::unique_ptr<ConversionFunctionSymbol>(conversionFunctionSymbol));
                    conversionFunctionMap[key] = conversionFunctionSymbol;
                }
                std::unique_ptr<BoundFunctionCallNode> functionCall(new BoundFunctionCallNode(conversionFunctionSymbol));
                for (auto& arg : args)
                {
                    functionCall->AddArgument(arg.release());
                }
                return functionCall;
            }
        }
    }
*/
    return std::unique_ptr<BoundFunctionCallNode>();
}

OperationGroup::OperationGroup(const std::u32string& name_) : name(name_)
{
}

OperationGroup::~OperationGroup()
{
}

OperationRepository::OperationRepository()
{
    AddGroup(new ConversionOperationGroup());
}

void OperationRepository::AddGroup(OperationGroup* group)
{
    groupMap[group->Name()] = group;
    groups.push_back(std::unique_ptr<OperationGroup>(group));
}

std::unique_ptr<BoundFunctionCallNode> OperationRepository::GetOperation(const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args)
{
    auto it = groupMap.find(groupName);
    if (it != groupMap.cend())
    {
        OperationGroup* group = it->second;
        return group->GetOperation(args);
    }
    else
    {
        return std::unique_ptr<BoundFunctionCallNode>();
    }
}

} // namespace otava::symbols
