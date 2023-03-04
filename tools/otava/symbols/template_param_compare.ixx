export module otava.symbols.template_param_compare;

import std.core;

export namespace otava::symbols {

class TemplateParameterSymbol;

struct TemplateParamLess
{
    bool operator()(TemplateParameterSymbol* left, TemplateParameterSymbol* right) const;
};

} // namespace otava::symbols
