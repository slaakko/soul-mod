// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.error;

import util;

namespace soul::spg {

int RuleNameNotUnique(const std::string& fileName, soul::ast::spg::RuleParser* rule)
{
    return util::AllocateError("error: rule name '" + rule->Name() + "' not unique in file '" + fileName + "' line " +
        std::to_string(rule->GetSourcePos().line));
}

} // namespace soul::spg
