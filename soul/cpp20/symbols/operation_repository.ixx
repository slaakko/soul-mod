// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.operation.repository;

import std.core;

export namespace soul::cpp20::symbols {

class BoundExpressionNode;
class BoundFunctionCallNode;

class OperationGroup
{
public:
    OperationGroup(const std::u32string& name_);
    virtual ~OperationGroup();
    const std::u32string& Name() const { return name; }
    virtual std::unique_ptr<BoundFunctionCallNode> GetOperation(std::vector<std::unique_ptr<BoundExpressionNode>>& args) = 0;
private:
    std::u32string name;
};

class OperationRepository
{
public:
    OperationRepository();
    std::unique_ptr<BoundFunctionCallNode> GetOperation(const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args);
private:
    void AddGroup(OperationGroup* group);
    std::map<std::u32string, OperationGroup*> groupMap;
    std::vector<std::unique_ptr<OperationGroup>> groups;
};

} // namespace soul::cpp20::symbols
