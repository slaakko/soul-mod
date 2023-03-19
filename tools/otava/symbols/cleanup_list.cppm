// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.cleanup_list;

import std.core;
import soul.ast.source.pos;

export namespace otava::symbols {

class BoundFunctionCallNode;
class Context;
class Emitter;

class CleanupList
{
public:
    CleanupList(Emitter& emitter);
    bool IsDirty() const { return dirty; }
    void Reset() { dirty = false; }
    void Add(BoundFunctionCallNode* destructorCall);
    void Remove(int count);
    void Clear();
    void GenerateCleanup(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context);
    void GeneratePopContext(Emitter& emitter, bool reset);
private:
    bool dirty;
    std::vector<std::unique_ptr<BoundFunctionCallNode>> list;
};

} // namespace otava::symbols
