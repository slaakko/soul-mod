// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.optimizer.jump_table_switch;

import std;
import otava.intermediate;

export namespace otava::optimizer {

void EmitJumpTableSwitch(otava::intermediate::SwitchInstruction& inst, otava::intermediate::CodeGenerator& codeGenerator);

} // otava::optimizer
