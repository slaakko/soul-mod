// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.xml.xpath.function;

import util_expected;
import soul_expected.xml.dom_expected;

namespace soul_expected::xml::xpath {

class StringValueComputerVisitor : public soul_expected::xml::Visitor
{
public:
    void Visit(soul_expected::xml::Text& text) override;
    std::string GetStringValue() { return std::move(stringValue); }
private:
    std::string stringValue;
};

void StringValueComputerVisitor::Visit(soul_expected::xml::Text& text)
{
    stringValue.append(text.Data());
}

std::string GetStringValue(soul_expected::xml::ParentNode* node)
{
    StringValueComputerVisitor visitor;
    node->Accept(visitor);
    return visitor.GetStringValue();
}

std::string StringValue(soul_expected::xml::AttributeNode* attributeNode)
{
    return attributeNode->Value();
}

std::string StringValue(soul_expected::xml::Document* documentNode)
{
    return GetStringValue(documentNode);
}

std::string StringValue(soul_expected::xml::Element* elementNode)
{
    return GetStringValue(elementNode);
}

std::string StringValue(soul_expected::xml::ProcessingInstruction* processingInstructionNode)
{
    return std::string(processingInstructionNode->Data());
}

std::string StringValue(soul_expected::xml::Text* textNode)
{
    return std::string(textNode->Data());
}

std::string StringValue(soul_expected::xml::CDataSection* cdataSectionNode)
{
    return std::string(cdataSectionNode->Data());
}

std::string StringValue(soul_expected::xml::Comment* commentNode)
{
    return std::string(commentNode->Data());
}

std::string StringValue(soul_expected::xml::Node* node)
{
    switch (node->Kind())
    {
    case soul_expected::xml::NodeKind::attributeNode:
    {
        soul_expected::xml::AttributeNode* attributeNode = static_cast<soul_expected::xml::AttributeNode*>(node);
        return StringValue(attributeNode);
    }
    case soul_expected::xml::NodeKind::documentNode:
    {
        soul_expected::xml::Document* documentNode = static_cast<soul_expected::xml::Document*>(node);
        return StringValue(documentNode);
    }
    case soul_expected::xml::NodeKind::elementNode:
    {
        soul_expected::xml::Element* elementNode = static_cast<soul_expected::xml::Element*>(node);
        return StringValue(elementNode);
    }
    case soul_expected::xml::NodeKind::processingInstructionNode:
    {
        soul_expected::xml::ProcessingInstruction* processingInstructionNode = static_cast<soul_expected::xml::ProcessingInstruction*>(node);
        return StringValue(processingInstructionNode);
    }
    case soul_expected::xml::NodeKind::textNode:
    {
        soul_expected::xml::Text* textNode = static_cast<soul_expected::xml::Text*>(node);
        return StringValue(textNode);
    }
    case soul_expected::xml::NodeKind::cdataSectionNode:
    {
        soul_expected::xml::CDataSection* cdataSectionNode = static_cast<soul_expected::xml::CDataSection*>(node);
        return StringValue(cdataSectionNode);
    }
    case soul_expected::xml::NodeKind::commentNode:
    {
        soul_expected::xml::Comment* commentNode = static_cast<soul_expected::xml::Comment*>(node);
        return StringValue(commentNode);
    }
    }
    return std::string();
}

std::expected<std::unique_ptr<Object>, int> EvaluateToString(NodeSet* nodeSet)
{
    if (nodeSet->Count() == 0)
    {
        return std::expected<std::unique_ptr<Object>, int>(std::unique_ptr<Object>(new String()));
    }
    else
    {
        auto n = nodeSet->GetNode(0);
        if (!n) return std::unexpected<int>(n.error());
        return std::expected<std::unique_ptr<Object>, int>(std::unique_ptr<Object>(new String(StringValue(*n))));
    }
}

std::expected<std::unique_ptr<Object>, int> EvaluateToString(Boolean* boolean)
{
    if (boolean->Value())
    {
        return std::expected<std::unique_ptr<Object>, int>(std::unique_ptr<Object>(new String("true")));
    }
    else
    {
        return std::expected<std::unique_ptr<Object>, int>(std::unique_ptr<Object>(new String("false")));
    }
}

std::expected<std::unique_ptr<Object>, int> EvaluateToString(Number* number)
{
    return std::expected<std::unique_ptr<Object>, int>(std::unique_ptr<Object>(new String(std::to_string(number->Value()))));
}

std::expected<std::unique_ptr<Object>, int> EvaluateToString(String* string)
{
    return std::expected<std::unique_ptr<Object>, int>(std::unique_ptr<Object>(new String(string->Value())));
}

std::expected<std::unique_ptr<Object>, int> EvaluateToBoolean(NodeSet* nodeSet)
{
    return std::expected<std::unique_ptr<Object>, int>(std::unique_ptr<Object>(new Boolean(nodeSet->Count() != 0)));
}

std::expected<std::unique_ptr<Object>, int> EvaluateToBoolean(Boolean* boolean)
{
    return std::expected<std::unique_ptr<Object>, int>(std::unique_ptr<Object>(new Boolean(boolean->Value())));
}

std::expected<std::unique_ptr<Object>, int> EvaluateToBoolean(Number* number)
{
    return std::expected<std::unique_ptr<Object>, int>(std::unique_ptr<Object>(new Boolean(number->Value() != 0)));
}

std::expected<std::unique_ptr<Object>, int> EvaluateToBoolean(String* string)
{
    return std::expected<std::unique_ptr<Object>, int>(std::unique_ptr<Object>(new Boolean(!string->Value().empty())));
}

std::expected<std::unique_ptr<Object>, int> EvaluateToNumber(String* string);

std::expected<std::unique_ptr<Object>, int> EvaluateToNumber(NodeSet* nodeSet)
{
    std::expected<std::unique_ptr<Object>, int> rv = EvaluateToString(nodeSet);
    if (!rv) return std::unexpected<int>(rv.error());
    std::unique_ptr<Object> stringResult = std::move(*rv);
    if (stringResult->IsString())
    {
        String* string = static_cast<String*>(stringResult.get());
        return EvaluateToNumber(string);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("string expected"));
    }
}

std::expected<std::unique_ptr<Object>, int> EvaluateToNumber(Boolean* boolean)
{
    if (boolean->Value())
    {
        return std::expected<std::unique_ptr<Object>, int>(std::unique_ptr<Object>(new Number(1)));
    }
    else
    {
        return std::expected<std::unique_ptr<Object>, int>(std::unique_ptr<Object>(new Number(0)));
    }
}

std::expected<std::unique_ptr<Object>, int> EvaluateToNumber(Number* number)
{
    return std::expected<std::unique_ptr<Object>, int>(std::unique_ptr<Object>(new Number(number->Value())));
}

std::expected<std::unique_ptr<Object>, int> EvaluateToNumber(String* string)
{
    return std::expected<std::unique_ptr<Object>, int>(std::unique_ptr<Object>(new Number(std::stod(util::Trim(string->Value())))));
}

constexpr const char* functionNames[static_cast<int>(FunctionKind::max)] =
{
    "boolean", "number", "string", "last", "position", "count"
};

std::expected<NodeSet*, int> NodeSetCast(Object* object, Function* function)
{
    if (object->IsNodeSet())
    {
        return std::expected<NodeSet*, int>(static_cast<NodeSet*>(object));
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("error: '" + function->Name() + "()' function requires a node-set, " + ObjectKindStr(object->Kind()) + " provided"));
    }
}

std::string FunctionName(FunctionKind kind)
{
    return functionNames[static_cast<int>(kind)];
}

Function::Function(FunctionKind kind_) : kind(kind_), name(FunctionName(kind_)), minArity(1), maxArity(1)
{
}

Function::Function(FunctionKind kind_, int minArity_, int maxArity_) : kind(kind_), name(FunctionName(kind_)), minArity(minArity_), maxArity(maxArity_)
{
}

Function::~Function()
{
}

std::string Function::ArityStr() const
{
    if (minArity == maxArity)
    {
        return std::to_string(minArity);
    }
    else if (minArity == 0)
    {
        return "at most " + std::to_string(maxArity);
    }
    else
    {
        return "at least " + std::to_string(minArity) + " and at most " + std::to_string(maxArity);
    }
}

std::expected<std::unique_ptr<Object>, int>  Function::Evaluate(Context& context, const std::vector<Object*>& arguments)
{
    int n = static_cast<int>(arguments.size());
    if (n < minArity || n > maxArity)
    {
        return std::unexpected<int>(util::AllocateError("wrong number of arguments for '" + name + "() function: " + ArityStr() + " arguments expected, " + 
            std::to_string(n) + " arguments provided"));
    }
    return DoEvaluate(context, arguments);
}

class BooleanFunction : public Function
{
public:
    BooleanFunction();
protected:
    std::expected<std::unique_ptr<Object>, int> DoEvaluate(Context& context, const std::vector<Object*>& arguments) override;
};

BooleanFunction::BooleanFunction() : Function(FunctionKind::boolean)
{
}

std::expected<std::unique_ptr<Object>, int> BooleanFunction::DoEvaluate(Context& context, const std::vector<Object*>& arguments)
{
    Object* arg = arguments[0];
    switch (arg->Kind())
    {
    case ObjectKind::nodeSet:
    {
        NodeSet* nodeSet = static_cast<NodeSet*>(arg);
        return EvaluateToBoolean(nodeSet);
    }
    case ObjectKind::boolean:
    {
        Boolean* boolean = static_cast<Boolean*>(arg);
        return EvaluateToBoolean(boolean);
    }
    case ObjectKind::number:
    {
        Number* number = static_cast<Number*>(arg);
        return EvaluateToBoolean(number);
    }
    case ObjectKind::string:
    {
        String* string = static_cast<String*>(arg);
        return EvaluateToBoolean(string);
    }
    }
    return std::expected<std::unique_ptr<Object>, int>(std::unique_ptr<Object>(new Boolean()));
}

class NumberFunction : public Function
{
public:
    NumberFunction();
protected:
    std::expected<std::unique_ptr<Object>, int> DoEvaluate(Context& context, const std::vector<Object*>& arguments) override;
};

NumberFunction::NumberFunction() : Function(FunctionKind::number, 0, 1)
{
}

std::expected<std::unique_ptr<Object>, int> NumberFunction::DoEvaluate(Context& context, const std::vector<Object*>& arguments)
{
    Object* arg = nullptr;
    NodeSet nodeSet;
    if (arguments.empty())
    {
        nodeSet.Add(context.Node());
        arg = &nodeSet;
    }
    else
    {
        arg = arguments[0];
    }
    switch (arg->Kind())
    {
    case ObjectKind::nodeSet:
    {
        NodeSet* nodeSet = static_cast<NodeSet*>(arg);
        return EvaluateToNumber(nodeSet);
    }
    case ObjectKind::boolean:
    {
        Boolean* boolean = static_cast<Boolean*>(arg);
        return EvaluateToNumber(boolean);
    }
    case ObjectKind::number:
    {
        Number* number = static_cast<Number*>(arg);
        return EvaluateToNumber(number);
    }
    case ObjectKind::string:
    {
        String* string = static_cast<String*>(arg);
        return EvaluateToNumber(string);
    }
    }
    return std::unexpected<int>(util::AllocateError("error: invalid argument to '" + Name() + "()' function"));
}

class StringFunction : public Function
{
public:
    StringFunction();
protected:
    std::expected<std::unique_ptr<Object>, int> DoEvaluate(Context& context, const std::vector<Object*>& arguments) override;
};

StringFunction::StringFunction() : Function(FunctionKind::string, 0, 1)
{
}

std::expected<std::unique_ptr<Object>, int> StringFunction::DoEvaluate(Context& context, const std::vector<Object*>& arguments)
{
    Object* arg = nullptr;
    NodeSet nodeSet;
    if (arguments.empty())
    {
        nodeSet.Add(context.Node());
        arg = &nodeSet;
    }
    else
    {
        arg = arguments[0];
    }
    switch (arg->Kind())
    {
    case ObjectKind::nodeSet:
    {
        NodeSet* nodeSet = static_cast<NodeSet*>(arg);
        return EvaluateToString(nodeSet);
    }
    case ObjectKind::boolean:
    {
        Boolean* boolean = static_cast<Boolean*>(arg);
        return EvaluateToString(boolean);
    }
    case ObjectKind::number:
    {
        Number* number = static_cast<Number*>(arg);
        return EvaluateToString(number);
    }
    case ObjectKind::string:
    {
        String* string = static_cast<String*>(arg);
        return EvaluateToString(string);
    }
    }
    return std::unexpected<int>(util::AllocateError("error: invalid argument to '" + Name() + "()' function"));
}

class LastFunction : public Function
{
public:
    LastFunction();
protected:
    std::expected<std::unique_ptr<Object>, int> DoEvaluate(Context& context, const std::vector<Object*>& arguments) override;
};

LastFunction::LastFunction() : Function(FunctionKind::last, 0, 0)
{
}

std::expected<std::unique_ptr<Object>, int> LastFunction::DoEvaluate(Context& context, const std::vector<Object*>& arguments)
{
    return std::unique_ptr<Object>(new Number(context.Size()));
}

class PositionFunction : public Function
{
public:
    PositionFunction();
protected:
    std::expected<std::unique_ptr<Object>, int> DoEvaluate(Context& context, const std::vector<Object*>& arguments) override;
};

PositionFunction::PositionFunction() : Function(FunctionKind::position, 0, 0)
{
}

std::expected<std::unique_ptr<Object>, int> PositionFunction::DoEvaluate(Context& context, const std::vector<Object*>& arguments)
{
    return std::unique_ptr<Object>(new Number(context.Pos()));
}

class CountFunction : public Function
{
public:
    CountFunction();
protected:
    std::expected<std::unique_ptr<Object>, int> DoEvaluate(Context& context, const std::vector<Object*>& arguments) override;
};

CountFunction::CountFunction() : Function(FunctionKind::count)
{
}

std::expected<std::unique_ptr<Object>, int> CountFunction::DoEvaluate(Context& context, const std::vector<Object*>& arguments)
{
    auto rv = NodeSetCast(arguments[0], this);
    if (!rv) return std::unexpected<int>(rv.error());
    NodeSet* nodeSet = *rv;
    return std::unique_ptr<Object>(new Number(nodeSet->Count()));
}

class FunctionLibrary
{
public:
    static FunctionLibrary& Instance();
    std::expected<Function*, int> GetFunction(FunctionKind kind) const;
    std::expected<Function*, int> GetFunction(const std::string& name) const;
    void Install(Function* function);
private:
    FunctionLibrary();
    std::vector<std::unique_ptr<Function>> functions;
    std::map<std::string, Function*> functionMap;
};

FunctionLibrary& FunctionLibrary::Instance()
{
    static FunctionLibrary instance;
    return instance;
}

FunctionLibrary::FunctionLibrary()
{
    functions.resize(static_cast<int>(FunctionKind::max));
    Install(new BooleanFunction());
    Install(new NumberFunction());
    Install(new StringFunction());
    Install(new LastFunction());
    Install(new PositionFunction());
    Install(new CountFunction());
}

void FunctionLibrary::Install(Function* function)
{
    functions[static_cast<int>(function->Kind())].reset(function);
    functionMap[function->Name()] = function;
}

std::expected<Function*, int> FunctionLibrary::GetFunction(FunctionKind kind) const
{
    Function* function = functions[static_cast<int>(kind)].get();
    if (!function)
    {
        return std::unexpected<int>(util::AllocateError("error: soul_expected::xml::xpath::FunctionLibrary::GetFunction: function '" + FunctionName(kind) + "()' not installed"));
    }
    return std::expected<Function*, int>(function);
}

std::expected<Function*, int> FunctionLibrary::GetFunction(const std::string& name) const
{
    auto it = functionMap.find(name);
    if (it != functionMap.cend())
    {
        return std::expected<Function*, int>(it->second);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("error: soul_expected::xml::xpath::FunctionLibrary::GetFunction: function '" + name + "()' not found"));
    }
}

std::expected<Function*, int> GetFunction(FunctionKind kind)
{
    return FunctionLibrary::Instance().GetFunction(kind);
}

std::expected<Function*, int> GetFunction(const std::string& name)
{
    return FunctionLibrary::Instance().GetFunction(name);
}

} // namespace soul_expected::xml::xpath
