// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.symbol.factory;

import otava.symbols.symbol;
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
import otava.symbols.function.type.symbol;
import otava.symbols.exception;
import otava.symbols.alias.type.symbol;
import otava.symbols.alias.type.templates;
import otava.symbols.block;
import otava.symbols.classes;
import otava.symbols.compound.type.symbol;
import otava.symbols.enums;
import otava.symbols.function.symbol;
import otava.symbols.namespaces;
import otava.symbols.templates;
import otava.symbols.variable.symbol;
import otava.symbols.fundamental.type.operation;
import otava.symbols.fundamental.type.conversion;
import otava.ast.error;

namespace otava::symbols {

Symbol* CreateSymbol(SymbolKind symbolKind, const std::u32string& name, SymbolTable* symbolTable)
{
    switch (symbolKind)
    {
        case SymbolKind::classGroupSymbol:
        {
            return new ClassGroupSymbol(name);
        }
        case SymbolKind::conceptGroupSymbol:
        {
            return new ConceptGroupSymbol(name);
        }
        case SymbolKind::functionGroupSymbol:
        {
            return new FunctionGroupSymbol(name);
        }
        case SymbolKind::variableGroupSymbol:
        {
            return new VariableGroupSymbol(name);
        }
        case SymbolKind::aliasGroupSymbol:
        {
            return new AliasGroupSymbol(name);
        }
        case SymbolKind::enumGroupSymbol:
        {
            return new EnumGroupSymbol(name);
        }
        case SymbolKind::boolValueSymbol:
        {
            return new BoolValue(name, nullptr);
        }
        case SymbolKind::integerValueSymbol:
        {
            return new IntegerValue(name, nullptr);
        }
        case SymbolKind::floatingValueSymbol:
        {
            return new FloatingValue(name, nullptr);
        }
        case SymbolKind::nullPtrValueSymbol:
        {
            return new NullPtrValue(nullptr);
        }
        case SymbolKind::stringValueSymbol:
        {
            return new StringValue(symbolTable->MakeConstCharPtrType());
        }
        case SymbolKind::charValueSymbol:
        {
            return new CharValue(symbolTable->GetFundamentalTypeSymbol(FundamentalTypeKind::char32Type));
        }
        case SymbolKind::genericTypeSymbol:
        {
            otava::ast::SetExceptionThrown();
            throw std::runtime_error("not implemented");
        }
        case SymbolKind::nullPtrTypeSymbol:
        {
            otava::ast::SetExceptionThrown();
            throw std::runtime_error("not implemented");
        }
        case SymbolKind::aliasTypeSymbol:
        {
            return new AliasTypeSymbol(name);
        }
        case SymbolKind::arrayTypeSymbol:
        {
            otava::ast::SetExceptionThrown();
            throw std::runtime_error("not implemented");
        }
        case SymbolKind::blockSymbol:
        {
            return new BlockSymbol();
        }
        case SymbolKind::classTypeSymbol:
        {
            return new ClassTypeSymbol(name);
        }
        case SymbolKind::forwardClassDeclarationSymbol:
        {
            return new ForwardClassDeclarationSymbol(name);
        }
        case SymbolKind::compoundTypeSymbol:
        {
            CompoundTypeSymbol* compoundType = new CompoundTypeSymbol(name);
            compoundType->SetSymbolTable(symbolTable);
            return compoundType;
        }
        case SymbolKind::conceptSymbol:
        {
            return new ConceptSymbol(name);
        }
        case SymbolKind::enumTypeSymbol:
        {
            return new EnumeratedTypeSymbol(name);
        }
        case SymbolKind::forwardEnumDeclarationSymbol:
        {
            return new ForwardEnumDeclarationSymbol(name);
        }
        case SymbolKind::enumConstantSymbol:
        {
            return new EnumConstantSymbol(name);
        }
        case SymbolKind::functionSymbol:
        {
            return new FunctionSymbol(name);
        }
        case SymbolKind::functionDefinitionSymbol:
        {
            return new FunctionDefinitionSymbol(name);
        }
        case SymbolKind::functionTypeSymbol:
        {
            return new FunctionTypeSymbol(name);
        }
        case SymbolKind::fundamentalTypeSymbol:
        {
            return new FundamentalTypeSymbol(name);
        }
        case SymbolKind::namespaceSymbol:
        {
            return new NamespaceSymbol(name);
        }
        case SymbolKind::templateDeclarationSymbol:
        {
            return new TemplateDeclarationSymbol();
        }
        case SymbolKind::typenameConstraintSymbol:
        {
            return new TypenameConstraintSymbol();
        }
        case SymbolKind::templateParameterSymbol:
        {
            return new TemplateParameterSymbol(name);
        }
        case SymbolKind::varArgTypeSymbol:
        {
            otava::ast::SetExceptionThrown();
            throw std::runtime_error("not implemented");
        }
        case SymbolKind::variableSymbol:
        {
            return new VariableSymbol(name);
        }
        case SymbolKind::parameterSymbol:
        {
            return new ParameterSymbol(name);
        }
        case SymbolKind::classTemplateSpecializationSymbol:
        {
            ClassTemplateSpecializationSymbol* specialization = new ClassTemplateSpecializationSymbol(name);
            specialization->SetSymbolTable(symbolTable);
            return specialization;
        }
        case SymbolKind::aliasTypeTemplateSpecializationSymbol: 
        {
            AliasTypeTemplateSpecializationSymbol* specialization = new AliasTypeTemplateSpecializationSymbol(name);
            return specialization;
        }
        case SymbolKind::nestedTypeSymbol:
        {
            return new NestedTypeSymbol(name);
        }
        case SymbolKind::errorSymbol:
        {
            return new ErrorTypeSymbol();
        }
        case SymbolKind::symbolValueSymbol:
        {
            return new SymbolValue();
        }
        case SymbolKind::invokeValueSymbol:
        {
            return new InvokeValue();
        }
        case SymbolKind::constraintExprSymbol:
        {
            return new ConstraintExprSymbol();
        }
        case SymbolKind::fundamentalTypeNot:
        {
            return new FundamentalTypeNotOperation();
        }
        case SymbolKind::fundamentalTypeUnaryPlus:
        {
            return new FundamentalTypeUnaryPlusOperation();
        }
        case SymbolKind::fundamentalTypeUnaryMinus:
        {
            return new FundamentalTypeUnaryMinusOperation();
        }
        case SymbolKind::fundamentalTypeComplement:
        {
            return new FundamentalTypeComplementOperation();
        }
        case SymbolKind::fundamentalTypeAdd:
        {
            return new FundamentalTypeAddOperation();
        }
        case SymbolKind::fundamentalTypeSub:
        {
            return new FundamentalTypeSubOperation();
        }
        case SymbolKind::fundamentalTypeMul:
        {
            return new FundamentalTypeMulOperation();
        }
        case SymbolKind::fundamentalTypeDiv:
        {
            return new FundamentalTypeDivOperation();
        }
        case SymbolKind::fundamentalTypeMod:
        {
            return new FundamentalTypeModOperation();
        }
        case SymbolKind::fundamentalTypeAnd:
        {
            return new FundamentalTypeAndOperation();
        }
        case SymbolKind::fundamentalTypeOr:
        {
            return new FundamentalTypeOrOperation();
        }
        case SymbolKind::fundamentalTypeXor:
        {
            return new FundamentalTypeXorOperation();
        }
        case SymbolKind::fundamentalTypeShl:
        {
            return new FundamentalTypeShlOperation();
        }
        case SymbolKind::fundamentalTypeShr:
        {
            return new FundamentalTypeShrOperation();
        }
        case SymbolKind::fundamentalTypeEqual:
        {
            return new FundamentalTypeEqualOperation();
        }
        case SymbolKind::fundamentalTypeLess:
        {
            return new FundamentalTypeLessOperation();
        }
        case SymbolKind::fundamentalTypeBoolean:
        {
            return new FundamentalTypeBooleanConversion();
        }
        case SymbolKind::fundamentalTypeSignExtension:
        {
            return new FundamentalTypeSignExtendConversion();
        }
        case SymbolKind::fundamentalTypeZeroExtension:
        {
            return new FundamentalTypeZeroExtendConversion();
        }
        case SymbolKind::fundamentalTypeTruncate:
        {
            return new FundamentalTypeTruncateConversion();
        }
        case SymbolKind::fundamentalTypeBitcast:
        {
            return new FundamentalTypeBitcastConversion();
        }
        case SymbolKind::fundamentalTypeIntToFloat:
        {
            return new FundamentalTypeIntToFloatConversion();
        }
        case SymbolKind::fundamentalTypeFloatToInt:
        {
            return new FundamentalTypeFloatToIntConversion();
        }
        case SymbolKind::fundamentalTypeDefaultCtor:
        {
            return new FundamentalTypeDefaultCtor();
        }
        case SymbolKind::fundamentalTypeCopyCtor:
        {
            return new FundamentalTypeCopyCtor();
        }
        case SymbolKind::fundamentalTypeMoveCtor:
        {
            return new FundamentalTypeMoveCtor();
        }
        case SymbolKind::fundamentalTypeCopyAssignment:
        {
            return new FundamentalTypeCopyAssignment();
        }
        case SymbolKind::fundamentalTypeMoveAssignment:
        {
            return new FundamentalTypeMoveAssignment();
        }
    }
    otava::ast::SetExceptionThrown();
    throw std::runtime_error("not implemented");
}

} // namespace otava::symbols
