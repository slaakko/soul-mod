// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.nonterminal.info;

namespace soul::spg {

NonterminalInfo::NonterminalInfo(const std::string& name_, bool ptrType_) : name(name_), ptrType(ptrType_), count(0)
{
}

} // namespace soul::spg
