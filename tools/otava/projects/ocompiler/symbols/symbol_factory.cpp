// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.symbol.factory;

import otava.symbols.symbol;
import otava.symbols.type.symbol;
import otava.symbols.class_group.symbol;
import otava.symbols.class_templates;
import otava.symbols.concept_group.symbol;
import otava.symbols.function.group.symbol;
import otava.symbols.variable.group.symbol;
import otava.symbols.alias.group.symbol;
import otava.symbols.enum_group.symbol;
import otava.symbols.concepts;
import otava.symbols.value;
import otava.symbols.symbol.table;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.fundamental.type.conversion;
import otava.symbols.function.type.symbol;
import otava.symbols.error;
import otava.symbols.alias.type.symbol;
import otava.symbols.alias.type.templates;
import otava.symbols.array.type.symbol;
import otava.symbols.block;
import otava.symbols.classes;
import otava.symbols.compound.type.symbol;
import otava.symbols.enums;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.namespaces;
import otava.symbols.templates;
import otava.symbols.variable.symbol;
import otava.symbols.fundamental.type.operation;
import otava.symbols.friends;

namespace otava::symbols {

std::expected<Symbol*, int> CreateSymbol(SymbolKind symbolKind, const std::u32string& name, SymbolTable* symbolTable)
{
    switch (symbolKind)
    {
        case SymbolKind::classGroupSymbol:
        {
            return std::expected<Symbol*, int>(new ClassGroupSymbol(name));
        }
        case SymbolKind::conceptGroupSymbol:
        {
            return std::expected<Symbol*, int>(new ConceptGroupSymbol(name));
        }
        case SymbolKind::functionGroupSymbol:
        {
            return std::expected<Symbol*, int>(new FunctionGroupSymbol(name));
        }
        case SymbolKind::variableGroupSymbol:
        {
            return std::expected<Symbol*, int>(new VariableGroupSymbol(name));
        }
        case SymbolKind::aliasGroupSymbol:
        {
            return std::expected<Symbol*, int>(new AliasGroupSymbol(name));
        }
        case SymbolKind::enumGroupSymbol:
        {
            return std::expected<Symbol*, int>(new EnumGroupSymbol(name));
        }
        case SymbolKind::boolValueSymbol:
        {
            return std::expected<Symbol*, int>(new BoolValue(name, nullptr));
        }
        case SymbolKind::integerValueSymbol:
        {
            return std::expected<Symbol*, int>(new IntegerValue(name, nullptr));
        }
        case SymbolKind::floatingValueSymbol:
        {
            return std::expected<Symbol*, int>(new FloatingValue(name, nullptr));
        }
        case SymbolKind::nullPtrValueSymbol:
        {
            return std::expected<Symbol*, int>(new NullPtrValue(nullptr));
        }
        case SymbolKind::stringValueSymbol:
        {
            return std::expected<Symbol*, int>(new StringValue(nullptr));
        }
        case SymbolKind::charValueSymbol:
        {
            return std::expected<Symbol*, int>(new CharValue(nullptr));
        }
        case SymbolKind::arrayValueSymbol:
        {
            return std::expected<Symbol*, int>(new ArrayValue(nullptr));
        }
        case SymbolKind::structureValueSymbol:
        {
            return std::expected<Symbol*, int>(new StructureValue(nullptr));
        }
        case SymbolKind::genericTypeSymbol:
        {
            return std::unexpected<int>(util::AllocateError("not implemented"));
        }
        case SymbolKind::nullPtrTypeSymbol:
        {
            return std::unexpected<int>(util::AllocateError("not implemented"));
        }
        case SymbolKind::aliasTypeSymbol:
        {
            return std::expected<Symbol*, int>(new AliasTypeSymbol(name));
        }
        case SymbolKind::arrayTypeSymbol:
        {
            return std::expected<Symbol*, int>(new ArrayTypeSymbol(name));
        }
        case SymbolKind::blockSymbol:
        {
            return std::expected<Symbol*, int>(new BlockSymbol());
        }
        case SymbolKind::classTypeSymbol:
        {
            return std::expected<Symbol*, int>(new ClassTypeSymbol(name));
        }
        case SymbolKind::forwardClassDeclarationSymbol:
        {
            return std::expected<Symbol*, int>(new ForwardClassDeclarationSymbol(name));
        }
        case SymbolKind::compoundTypeSymbol:
        {
            return std::expected<Symbol*, int>(new CompoundTypeSymbol(name));
        }
        case SymbolKind::explicitInstantiationSymbol:
        {
            return std::expected<Symbol*, int>(new ExplicitInstantiationSymbol());
        }
        case SymbolKind::conceptSymbol:
        {
            return std::expected<Symbol*, int>(new ConceptSymbol(name));
        }
        case SymbolKind::enumTypeSymbol:
        {
            return std::expected<Symbol*, int>(new EnumeratedTypeSymbol(name));
        }
        case SymbolKind::forwardEnumDeclarationSymbol:
        {
            return std::expected<Symbol*, int>(new ForwardEnumDeclarationSymbol(name));
        }
        case SymbolKind::enumConstantSymbol:
        {
            return std::expected<Symbol*, int>(new EnumConstantSymbol(name));
        }
        case SymbolKind::functionSymbol:
        {
            return std::expected<Symbol*, int>(new FunctionSymbol(name));
        }
        case SymbolKind::functionDefinitionSymbol:
        {
            return std::expected<Symbol*, int>(new FunctionDefinitionSymbol(name));
        }
        case SymbolKind::explicitlyInstantiatedFunctionDefinitionSymbol:
        {
            return std::expected<Symbol*, int>(new ExplicitlyInstantiatedFunctionDefinitionSymbol(name));
        }
        case SymbolKind::functionTypeSymbol:
        {
            return std::expected<Symbol*, int>(new FunctionTypeSymbol(name));
        }
        case SymbolKind::fundamentalTypeSymbol:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeSymbol(name));
        }
        case SymbolKind::namespaceSymbol:
        {
            return std::expected<Symbol*, int>(new NamespaceSymbol(name));
        }
        case SymbolKind::templateDeclarationSymbol:
        {
            return std::expected<Symbol*, int>(new TemplateDeclarationSymbol());
        }
        case SymbolKind::typenameConstraintSymbol:
        {
            return std::expected<Symbol*, int>(new TypenameConstraintSymbol());
        }
        case SymbolKind::templateParameterSymbol:
        {
            return std::expected<Symbol*, int>(new TemplateParameterSymbol(name));
        }
        case SymbolKind::varArgTypeSymbol:
        {
            return std::unexpected<int>(util::AllocateError("not implemented"));
        }
        case SymbolKind::variableSymbol:
        {
            return std::expected<Symbol*, int>(new VariableSymbol(name));
        }
        case SymbolKind::parameterSymbol:
        {
            return std::expected<Symbol*, int>(new ParameterSymbol(name));
        }
        case SymbolKind::classTemplateSpecializationSymbol:
        {
            ClassTemplateSpecializationSymbol* specialization = new ClassTemplateSpecializationSymbol(name);
            return std::expected<Symbol*, int>(specialization);
        }
        case SymbolKind::aliasTypeTemplateSpecializationSymbol:
        {
            AliasTypeTemplateSpecializationSymbol* specialization = new AliasTypeTemplateSpecializationSymbol(name);
            return std::expected<Symbol*, int>(specialization);
        }
        case SymbolKind::nestedTypeSymbol:
        {
            return std::expected<Symbol*, int>(new NestedTypeSymbol(name));
        }
        case SymbolKind::dependentTypeSymbol:
        {
            return std::expected<Symbol*, int>(new DependentTypeSymbol(name));
        }
        case SymbolKind::errorSymbol:
        {
            return std::expected<Symbol*, int>(new ErrorTypeSymbol());
        }
        case SymbolKind::symbolValueSymbol:
        {
            return std::expected<Symbol*, int>(new SymbolValue());
        }
        case SymbolKind::invokeValueSymbol:
        {
            return std::expected<Symbol*, int>(new InvokeValue());
        }
        case SymbolKind::constraintExprSymbol:
        {
            return std::expected<Symbol*, int>(new ConstraintExprSymbol());
        }
        case SymbolKind::fundamentalTypeNot:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeNotOperation());
        }
        case SymbolKind::fundamentalTypeUnaryPlus:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeUnaryPlusOperation());
        }
        case SymbolKind::fundamentalTypeUnaryMinus:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeUnaryMinusOperation());
        }
        case SymbolKind::fundamentalTypeComplement:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeComplementOperation());
        }
        case SymbolKind::fundamentalTypeAdd:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeAddOperation());
        }
        case SymbolKind::fundamentalTypeSub:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeSubOperation());
        }
        case SymbolKind::fundamentalTypeMul:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeMulOperation());
        }
        case SymbolKind::fundamentalTypeDiv:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeDivOperation());
        }
        case SymbolKind::fundamentalTypeMod:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeModOperation());
        }
        case SymbolKind::fundamentalTypeAnd:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeAndOperation());
        }
        case SymbolKind::fundamentalTypeOr:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeOrOperation());
        }
        case SymbolKind::fundamentalTypeXor:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeXorOperation());
        }
        case SymbolKind::fundamentalTypeShl:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeShlOperation());
        }
        case SymbolKind::fundamentalTypeShr:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeShrOperation());
        }
        case SymbolKind::fundamentalTypePlusAssign:
        {
            return std::expected<Symbol*, int>(new FundamentalTypePlusAssignOperation());
        }
        case SymbolKind::fundamentalTypeMinusAssign:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeMinusAssignOperation());
        }
        case SymbolKind::fundamentalTypeMulAssign:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeMulAssignOperation());
        }
        case SymbolKind::fundamentalTypeDivAssign:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeDivAssignOperation());
        }
        case SymbolKind::fundamentalTypeModAssign:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeModAssignOperation());
        }
        case SymbolKind::fundamentalTypeAndAssign:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeAndAssignOperation());
        }
        case SymbolKind::fundamentalTypeOrAssign:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeOrAssignOperation());
        }
        case SymbolKind::fundamentalTypeXorAssign:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeXorAssignOperation());
        }
        case SymbolKind::fundamentalTypeShlAssign:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeShlAssignOperation());
        }
        case SymbolKind::fundamentalTypeShrAssign:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeShrAssignOperation());
        }
        case SymbolKind::fundamentalTypeEqual:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeEqualOperation());
        }
        case SymbolKind::fundamentalTypeLess:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeLessOperation());
        }
        case SymbolKind::fundamentalTypeBoolean:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeBooleanConversion());
        }
        case SymbolKind::fundamentalTypeSignExtension:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeSignExtendConversion());
        }
        case SymbolKind::fundamentalTypeZeroExtension:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeZeroExtendConversion());
        }
        case SymbolKind::fundamentalTypeFloatingPointExtension:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeFloatingPointExtendConversion());
        }
        case SymbolKind::fundamentalTypeTruncate:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeTruncateConversion());
        }
        case SymbolKind::fundamentalTypeBitcast:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeBitcastConversion());
        }
        case SymbolKind::fundamentalTypeIntToFloat:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeIntToFloatConversion());
        }
        case SymbolKind::fundamentalTypeFloatToInt:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeFloatToIntConversion());
        }
        case SymbolKind::fundamentalTypeBoolToInt:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeBoolToIntConversion());
        }
        case SymbolKind::fundamentalTypeDefaultCtor:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeDefaultCtor());
        }
        case SymbolKind::fundamentalTypeCopyCtor:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeCopyCtor());
        }
        case SymbolKind::fundamentalTypeMoveCtor:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeMoveCtor());
        }
        case SymbolKind::fundamentalTypeCopyAssignment:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeCopyAssignment());
        }
        case SymbolKind::fundamentalTypeMoveAssignment:
        {
            return std::expected<Symbol*, int>(new FundamentalTypeMoveAssignment());
        }
        case SymbolKind::enumTypeDefaultCtor:
        {
            return std::expected<Symbol*, int>(new EnumTypeDefaultCtor(name));
        }
        case SymbolKind::enumTypeCopyCtor:
        {
            return std::expected<Symbol*, int>(new EnumTypeCopyCtor(name));
        }
        case SymbolKind::enumTypeMoveCtor:
        {
            return std::expected<Symbol*, int>(new EnumTypeMoveCtor(name));
        }
        case SymbolKind::enumTypeCopyAssignment:
        {
            return std::expected<Symbol*, int>(new EnumTypeCopyAssignment(name));
        }
        case SymbolKind::enumTypeMoveAssignment:
        {
            return std::expected<Symbol*, int>(new EnumTypeMoveAssignment(name));
        }
        case SymbolKind::enumTypeEqual:
        {
            return std::expected<Symbol*, int>(new EnumTypeEqual(name));
        }
        case SymbolKind::enumTypeLess:
        {
            return std::expected<Symbol*, int>(new EnumTypeLess(name));
        }
        case SymbolKind::arrayTypeDefaultCtor:
        {
            return std::expected<Symbol*, int>(new ArrayTypeDefaultCtor(name));
        }
        case SymbolKind::arrayTypeCopyCtor:
        {
            return std::expected<Symbol*, int>(new ArrayTypeCopyCtor(name));
        }
        case SymbolKind::arrayTypeMoveCtor:
        {
            return std::expected<Symbol*, int>(new ArrayTypeMoveCtor(name));
        }
        case SymbolKind::arrayTypeCopyAssignment:
        {
            return std::expected<Symbol*, int>(new ArrayTypeCopyAssignment(name));
        }
        case SymbolKind::arrayTypeMoveAssignment:
        {
            return std::expected<Symbol*, int>(new ArrayTypeMoveAssignment(name));
        }
        case SymbolKind::arrayTypeBegin:
        {
            return std::expected<Symbol*, int>(new ArrayTypeBegin(name));
        }
        case SymbolKind::arrayTypeEnd:
        {
            return std::expected<Symbol*, int>(new ArrayTypeEnd(name));
        }
        case SymbolKind::functionGroupTypeSymbol:
        {
            return std::expected<Symbol*, int>(new FunctionGroupTypeSymbol(name));
        }
        case SymbolKind::classGroupTypeSymbol:
        {
            return std::expected<Symbol*, int>(new ClassGroupTypeSymbol(name));
        }
        case SymbolKind::aliasGroupTypeSymbol:
        {
            return std::expected<Symbol*, int>(new AliasGroupTypeSymbol(name));
        }
        case SymbolKind::friendSymbol:
        {
            return std::expected<Symbol*, int>(new FriendSymbol(name));
        }
    }
    return std::unexpected<int>(util::AllocateError("not implemented"));
}

} // namespace otava::symbols
