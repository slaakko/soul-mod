export module otava.optimizer.identity_calls;

import std;
import otava.intermediate;

export namespace otava::optimizer {

void OptimizeIdentityCalls(otava::intermediate::Function* fn, otava::intermediate::IntermediateContext* context);

} // otava::optimizer
