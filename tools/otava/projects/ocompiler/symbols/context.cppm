// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.context;

import std;

export namespace otava::symbols {

enum class ContextFlags : std::int64_t
{
    none = static_cast<std::int64_t>(0),
    hasDefiningTypeSpecifier = static_cast<std::int64_t>(1) << 0,
    friendSpecifier = static_cast<std::int64_t>(1) << 1,
    parsingParameters = static_cast<std::int64_t>(1) << 2,
    parsingConceptDefinition = static_cast<std::int64_t>(1) << 3,
    parsingTemplateId = static_cast<std::int64_t>(1) << 4,
    assumeType = static_cast<std::int64_t>(1) << 5,
    parseSavedMemberFunctionBody = static_cast<std::int64_t>(1) << 6,
    parsingTemplateDeclaration = static_cast<std::int64_t>(1) << 7,
    parseMemberFunction = static_cast<std::int64_t>(1) << 8,
    retMemberDeclSpecifiers = static_cast<std::int64_t>(1) << 9,
    addClassScope = static_cast<std::int64_t>(1) << 10,
    saveDeclarations = static_cast<std::int64_t>(1) << 11,
    linkageDeclaration = static_cast<std::int64_t>(1) << 12,
    instantiateFunctionTemplate = static_cast<std::int64_t>(1) << 13,
    instantiateAliasTypeTemplate = static_cast<std::int64_t>(1) << 14,
    instantiateMemFnOfClassTemplate = static_cast<std::int64_t>(1) << 15,
    instantiateInlineFunction = static_cast<std::int64_t>(1) << 16,
    dontBind = static_cast<std::int64_t>(1) << 17,
    parseSavedCtorInitializer = static_cast<std::int64_t>(1) << 18,
    skipFunctionDefinitions = static_cast<std::int64_t>(1) << 19,
    returnRef = static_cast<std::int64_t>(1) << 20,
    virtualSeen = static_cast<std::int64_t>(1) << 21,
    ignoreClassTemplateSpecializations = static_cast<std::int64_t>(1) << 22,
    generateMainWrapper = static_cast<std::int64_t>(1) << 23,
    noDynamicInit = static_cast<std::int64_t>(1) << 24,
    requireForwardResolved = static_cast<std::int64_t>(1) << 25,
    noPtrOps = static_cast<std::int64_t>(1) << 26,
    reinterpretCast = static_cast<std::int64_t>(1) << 27,
    derefAfterConv = static_cast<std::int64_t>(1) << 28,
    generatingVTab = static_cast<std::int64_t>(1) << 29,
    resolveNestedTypes = static_cast<std::int64_t>(1) << 30,
    release = static_cast<std::int64_t>(1) << 31,
    suppress_warning = static_cast<std::int64_t>(1) << 32,
    resolveDependentTypes = static_cast<std::int64_t>(1) << 33,
    processingAliasDeclation = static_cast<std::int64_t>(1) << 34,
    leaveBoundFunction = static_cast<std::int64_t>(1) << 35,
    skipFirstPtrToBooleanConversion = static_cast<std::int64_t>(1) << 36
};

constexpr ContextFlags operator|(ContextFlags left, ContextFlags right)
{
    return ContextFlags(std::int64_t(left) | std::int64_t(right));
}

constexpr ContextFlags operator&(ContextFlags left, ContextFlags right)
{
    return ContextFlags(std::int64_t(left) & std::int64_t(right));
}

constexpr ContextFlags operator~(ContextFlags flags)
{
    return ContextFlags(~std::int64_t(flags));
}

class Context
{
public:
    Context();
    inline void PushFlags() { flagStack.push(flags); }
    inline PopFlags() { flags = flagStack.top(); flagStack.pop(); }
    inline void PushSetFlag(ContextFlags flag) { PushFlags(); SetFlag(flag); }
    inline void PushResetFlag(ContextFlags flag) { PushFlags(); ResetFlag(flag); }
    inline void SetFlag(ContextFlags flag) { flags = flags | flag; }
    inline bool GetFlag(ContextFlags flag) const { return (flags & flag) != ContextFlags::none; }
    inline void ResetFlag(ContextFlags flag) { flags = flags & ~flag; }
private:
    ContextFlags flags;
    std::stack<ContextFlags> flagStack;
};

} // namespace otava::symbols
