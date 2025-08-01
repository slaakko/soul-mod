// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.xpath.function;

import std;
import soul_expected.xml.node;
import soul_expected.xml.xpath.object;
import soul_expected.xml.xpath.context;

export namespace soul_expected::xml::xpath {

std::string StringValue(soul_expected::xml::Node* node);

enum class FunctionKind : int
{
    boolean, number, string, last, position, count, max
};

std::string FunctionName(FunctionKind kind);

class Function
{
public:
    Function(FunctionKind kind_);
    Function(FunctionKind kind_, int minArity_, int maxArity_);
    virtual ~Function();
    inline FunctionKind Kind() const { return kind; }
    inline const std::string& Name() const { return name; }
    inline int MinArity() const { return minArity; }
    inline int MaxArity() const { return maxArity; }
    std::expected<std::unique_ptr<Object>, int> Evaluate(Context& context, const std::vector<Object*>& arguments);
    std::string ArityStr() const;
protected:
    virtual std::expected<std::unique_ptr<Object>, int> DoEvaluate(Context& context, const std::vector<Object*>& arguments) = 0;
private:
    FunctionKind kind;
    std::string name;
    int minArity;
    int maxArity;
};

std::expected<Function*, int> GetFunction(FunctionKind kind);
std::expected<Function*, int> GetFunction(const std::string& name);

} // namespace soul_expected::xml::xpath
