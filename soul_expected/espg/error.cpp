// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.spg.error;

import util_expected;

namespace soul_expected::spg::error {

int RuleNameNotUnique(const std::string& fileName, soul_expected::ast::spg::RuleParser* rule)
{
    return util::AllocateError("error: rule name '" + rule->Name() + "' not unique in file '" + fileName + "' line " + 
        std::to_string(rule->GetSourcePos().line));
}

} // namespace soul_expected::spg::error
