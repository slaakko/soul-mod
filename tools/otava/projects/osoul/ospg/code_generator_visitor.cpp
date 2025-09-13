// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.code.generator.visitor;

import soul.spg.parsing.util;
import soul.spg.code.modifier;
import soul.spg.array.generator;
import soul.lexer.error;

namespace soul::spg {

CodeGeneratorVisitor::CodeGeneratorVisitor(soul::ast::spg::SpgFile* spgFile_, bool verbose_, bool noDebugSupport_, const std::string& version_,
    soul::lexer::FileMap& fileMap_) :
    spgFile(spgFile_), verbose(verbose_), noDebugSupport(noDebugSupport_), version(version_), formatter(nullptr),
    stage(CodeGenerationStage::generateInterface), currentParser(nullptr), parentMatchNumber(0), setParentMatchNumber(-1), sn(0), fileMap(fileMap_)
{
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::ChoiceParser& parser)
{
    if (!Valid()) return;
    if (stage == CodeGenerationStage::generateImplementation)
    {
        int prevSetParentMatchNumber0 = setParentMatchNumber;
        std::expected<bool, int> rv = formatter->WriteLine("soul::parser::Match match(false);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        setParentMatchNumber = parentMatchNumber;
        rv = formatter->WriteLine("soul::parser::Match* parentMatch" + std::to_string(parentMatchNumber++) + " = &match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("std::int64_t save = lexer.GetPos();");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        parser.Left()->Accept(*this);
        if (!Valid()) return;
        rv = formatter->WriteLine("*parentMatch" + std::to_string(setParentMatchNumber) + " = match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("if (!match.hit)");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        int prevSetParentMatchNumber1 = setParentMatchNumber;
        rv = formatter->WriteLine("soul::parser::Match match(false);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        setParentMatchNumber = parentMatchNumber;
        rv = formatter->WriteLine("soul::parser::Match* parentMatch" + std::to_string(parentMatchNumber++) + " = &match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("lexer.SetPos(save);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        parser.Right()->Accept(*this);
        if (!Valid()) return;
        rv = formatter->WriteLine("*parentMatch" + std::to_string(setParentMatchNumber) + " = match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        setParentMatchNumber = prevSetParentMatchNumber1;
        rv = formatter->WriteLine("*parentMatch" + std::to_string(setParentMatchNumber) + " = match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        setParentMatchNumber = prevSetParentMatchNumber0;
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::SwitchParser& parser)
{
    if (!Valid()) return;
    int prevSetParentMatchNumber0 = setParentMatchNumber;
    std::expected<bool, int> rv = formatter->WriteLine("soul::parser::Match match(false);");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    setParentMatchNumber = parentMatchNumber;
    rv = formatter->WriteLine("soul::parser::Match* parentMatch" + std::to_string(parentMatchNumber++) + " = &match;");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("switch (*lexer)");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("{");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->IncIndent();
    for (const auto& caseParser : parser.CaseParsers())
    {
        caseParser->Accept(*this);
        if (!Valid()) return;
    }
    formatter->DecIndent();
    rv = formatter->WriteLine("}");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    setParentMatchNumber = prevSetParentMatchNumber0;
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::CaseParser& parser)
{
    if (!Valid()) return;
    for (const auto* token : parser.First().Tokens())
    {
        if (!token->IsEpsilon() && !token->IsAny())
        {
            std::expected<bool, int> rv = formatter->WriteLine("case " + token->FullCppId() + ":");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
        }
    }
    std::expected<bool, int> rv = formatter->WriteLine("{");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->IncIndent();
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    rv = formatter->WriteLine("if (match.hit)");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("{");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->IncIndent();
    rv = formatter->WriteLine("*parentMatch" + std::to_string(setParentMatchNumber) + " = match;");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->DecIndent();
    rv = formatter->WriteLine("}");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("break;");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->DecIndent();
    rv = formatter->WriteLine("}");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::SequenceParser& parser)
{
    if (!Valid()) return;
    if (stage == CodeGenerationStage::generateImplementation)
    {
        std::expected<bool, int> rv = formatter->WriteLine("soul::parser::Match match(false);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        int prevSetParentMatchNumber0 = setParentMatchNumber;
        setParentMatchNumber = parentMatchNumber;
        rv = formatter->WriteLine("soul::parser::Match* parentMatch" + std::to_string(parentMatchNumber++) + " = &match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        parser.Left()->Accept(*this);
        if (!Valid()) return;
        rv = formatter->WriteLine("*parentMatch" + std::to_string(setParentMatchNumber) + " = match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("if (match.hit)");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("soul::parser::Match match(false);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        int prevSetParentMatchNumber1 = setParentMatchNumber;
        setParentMatchNumber = parentMatchNumber;
        rv = formatter->WriteLine("soul::parser::Match* parentMatch" + std::to_string(parentMatchNumber++) + " = &match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        parser.Right()->Accept(*this);
        if (!Valid()) return;
        rv = formatter->WriteLine("*parentMatch" + std::to_string(setParentMatchNumber) + " = match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        setParentMatchNumber = prevSetParentMatchNumber1;
        rv = formatter->WriteLine("*parentMatch" + std::to_string(setParentMatchNumber) + " = match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        setParentMatchNumber = prevSetParentMatchNumber0;
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::DifferenceParser& parser)
{
    if (!Valid()) return;
    if (stage == CodeGenerationStage::generateImplementation)
    {
        std::expected<bool, int> rv = formatter->WriteLine("soul::parser::Match match(false);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        int prevSetParentMatchNumber0 = setParentMatchNumber;
        setParentMatchNumber = parentMatchNumber;
        rv = formatter->WriteLine("soul::parser::Match* parentMatch" + std::to_string(parentMatchNumber++) + " = &match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("std::int64_t save = lexer.GetPos();");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        parser.Left()->Accept(*this);
        if (!Valid()) return;
        rv = formatter->WriteLine("*parentMatch" + std::to_string(setParentMatchNumber) + " = match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("if (match.hit)");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("soul::parser::Match match(false);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        int prevSetParentMatchNumber1 = setParentMatchNumber;
        setParentMatchNumber = parentMatchNumber;
        rv = formatter->WriteLine("soul::parser::Match* parentMatch" + std::to_string(parentMatchNumber++) + " = &match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("std::int64_t tmp = lexer.GetPos();");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("lexer.SetPos(save);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("save = tmp;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        parser.Right()->Accept(*this);
        if (!Valid()) return;
        rv = formatter->WriteLine("*parentMatch" + std::to_string(setParentMatchNumber) + " = match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        setParentMatchNumber = prevSetParentMatchNumber1;
        rv = formatter->WriteLine("if (!match.hit)");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("lexer.SetPos(save);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("*parentMatch" + std::to_string(setParentMatchNumber) + " = soul::parser::Match(!match.hit, match.value);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        setParentMatchNumber = prevSetParentMatchNumber0;
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::ListParser& parser)
{
    if (!Valid()) return;
    if (stage == CodeGenerationStage::generateImplementation)
    {
        parser.Child()->Accept(*this);
        if (!Valid()) return;
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::LookaheadParser& parser)
{
    if (!Valid()) return;
    if (stage == CodeGenerationStage::generateImplementation)
    {
        std::expected<bool, int> rv = formatter->WriteLine("soul::parser::Match match(true);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("std::int64_t save = lexer.GetPos();");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        int prevSetParentMatchNumber = setParentMatchNumber;
        setParentMatchNumber = parentMatchNumber;
        rv = formatter->WriteLine("soul::parser::Match* parentMatch" + std::to_string(parentMatchNumber++) + " = &match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        parser.Child()->Accept(*this);
        if (!Valid()) return;
        rv = formatter->WriteLine("if (match.hit)");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("*parentMatch" + std::to_string(setParentMatchNumber) + " = match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("lexer.SetPos(save);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("else");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("*parentMatch" + std::to_string(setParentMatchNumber) + " = soul::parser::Match(false);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("lexer.SetPos(save);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        setParentMatchNumber = prevSetParentMatchNumber;
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::KleeneParser& parser)
{
    if (!Valid()) return;
    if (stage == CodeGenerationStage::generateImplementation)
    {
        std::expected<bool, int> rv = formatter->WriteLine("soul::parser::Match match(true);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        int prevSetParentMatchNumber = setParentMatchNumber;
        setParentMatchNumber = parentMatchNumber;
        rv = formatter->WriteLine("soul::parser::Match* parentMatch" + std::to_string(parentMatchNumber++) + " = &match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("while (true)");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("std::int64_t save = lexer.GetPos();");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        parser.Child()->Accept(*this);
        if (!Valid()) return;
        rv = formatter->WriteLine("if (match.hit)");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("*parentMatch" + std::to_string(setParentMatchNumber) + " = match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("else");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("lexer.SetPos(save);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("break;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        setParentMatchNumber = prevSetParentMatchNumber;
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::PositiveParser& parser)
{
    if (!Valid()) return;
    if (stage == CodeGenerationStage::generateImplementation)
    {
        std::expected<bool, int> rv = formatter->WriteLine("soul::parser::Match match(false);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        int prevSetParentMatchNumber0 = setParentMatchNumber;
        setParentMatchNumber = parentMatchNumber;
        rv = formatter->WriteLine("soul::parser::Match* parentMatch" + std::to_string(parentMatchNumber++) + " = &match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        parser.Child()->Accept(*this);
        if (!Valid()) return;
        rv = formatter->WriteLine("*parentMatch" + std::to_string(setParentMatchNumber) + " = match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("if (match.hit)");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("soul::parser::Match match(true);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        int prevSetParentMatchNumber1 = setParentMatchNumber;
        setParentMatchNumber = parentMatchNumber;
        rv = formatter->WriteLine("soul::parser::Match* parentMatch" + std::to_string(parentMatchNumber++) + " = &match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("while (true)");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("std::int64_t save = lexer.GetPos();");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        parser.Child()->Accept(*this);
        if (!Valid()) return;
        rv = formatter->WriteLine("if (match.hit)");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("*parentMatch" + std::to_string(setParentMatchNumber) + " = match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("else");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("lexer.SetPos(save);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("break;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        setParentMatchNumber = prevSetParentMatchNumber1;
        setParentMatchNumber = prevSetParentMatchNumber0;
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::OptionalParser& parser)
{
    if (!Valid()) return;
    if (stage == CodeGenerationStage::generateImplementation)
    {
        std::expected<bool, int> rv = formatter->WriteLine("soul::parser::Match match(true);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("std::int64_t save = lexer.GetPos();");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        int prevSetParentMatchNumber = setParentMatchNumber;
        setParentMatchNumber = parentMatchNumber;
        rv = formatter->WriteLine("soul::parser::Match* parentMatch" + std::to_string(parentMatchNumber++) + " = &match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        parser.Child()->Accept(*this);
        if (!Valid()) return;
        rv = formatter->WriteLine("if (match.hit)");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("*parentMatch" + std::to_string(setParentMatchNumber) + " = match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("else");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("lexer.SetPos(save);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        setParentMatchNumber = prevSetParentMatchNumber;
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::ExpectationParser& parser)
{
    if (!Valid()) return;
    if (stage == CodeGenerationStage::generateImplementation)
    {
        std::expected<bool, int> rv = formatter->WriteLine("soul::parser::Match match(true);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        int prevSetParentMatchNumber0 = setParentMatchNumber;
        setParentMatchNumber = parentMatchNumber;
        rv = formatter->WriteLine("soul::parser::Match* parentMatch" + std::to_string(parentMatchNumber++) + " = &match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("std::int64_t pos = lexer.GetPos();");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        parser.Child()->Accept(*this);
        if (!Valid()) return;
        rv = formatter->WriteLine("if (match.hit)");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("*parentMatch" + std::to_string(setParentMatchNumber) + " = match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("else");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        if (parser.Child()->IsNonterminalParser())
        {
            soul::ast::spg::NonterminalParser* nonterminalParser = static_cast<soul::ast::spg::NonterminalParser*>(parser.Child());
            soul::ast::spg::RuleParser* rule = nonterminalParser->Rule();
            std::string ruleInfo = rule->Info();
            if (ruleInfo.empty())
            {
                ruleInfo = rule->Name();
            }
            rv = formatter->WriteLine("return lexer.ExpectationFailure(pos, \"" + ruleInfo + "\");");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
        }
        else if (parser.Child()->IsTokenParser())
        {
            soul::ast::spg::TokenParser* tokenParser = static_cast<soul::ast::spg::TokenParser*>(parser.Child());
            rv = formatter->WriteLine("return lexer.ExpectationFailure(pos, lexer.GetTokenInfo(" + tokenParser->GetToken()->FullCppId() + "));");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
        }
        else
        {
            std::string parserName = parser.Child()->Name();
            rv = formatter->WriteLine("return lexer.ExpectationFailure(pos, \"" + parserName + "\");");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        setParentMatchNumber = prevSetParentMatchNumber0;
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::ActionParser& parser)
{
    if (!Valid()) return;
    int prevSetParentMatchNumber = setParentMatchNumber;
    std::expected<bool, int> rv = formatter->WriteLine("soul::parser::Match match(false);");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    setParentMatchNumber = parentMatchNumber;
    rv = formatter->WriteLine("soul::parser::Match* parentMatch" + std::to_string(parentMatchNumber++) + " = &match;");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("{");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->IncIndent();
    rv = formatter->WriteLine("std::int64_t pos = lexer.GetPos();");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    soul::ast::cpp::CodeEvaluationVisitor codeEvaluationVisitor;
    parser.SuccessCode()->Accept(codeEvaluationVisitor);
    if (!codeEvaluationVisitor)
    {
        SetError(codeEvaluationVisitor.Error());
        return;
    }
    if (codeEvaluationVisitor.HasReturn())
    {
        currentRule->SetHasReturn();
    }
    bool hasPass = codeEvaluationVisitor.HasPass();
    bool hasVars = codeEvaluationVisitor.HasVars();
    if (hasPass)
    {
        rv = formatter->WriteLine("bool pass = true;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    if (hasVars)
    {
        rv = formatter->WriteLine("auto vars = static_cast<typename LexerT::VariableClassType*>(lexer.GetVariables());");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    rv = formatter->WriteLine("if (match.hit)");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    bool nonterminalValue = parser.Child()->IsNonterminalParser();
    bool ptrType = false;
    if (currentRule->ReturnType() != nullptr)
    {
        ptrType = currentRule->ReturnType()->IsPtrType();
    }
    std::string nonterminalName;
    soul::ast::cpp::TypeIdNode* returnType = nullptr;
    if (!ptrType)
    {
        returnType = currentRule->ReturnType();
    }
    if (nonterminalValue)
    {
        soul::ast::spg::NonterminalParser* nt = static_cast<soul::ast::spg::NonterminalParser*>(parser.Child());
        nonterminalName = nt->InstanceName();
    }
    soul::spg::parsing::util::CountNonterminals(parser.SuccessCode(), nonterminalInfos);
    soul::ast::common::TokenMap* tokenMap = parser.GetTokenMap();
    rv = ModifyCode(parser.SuccessCode(), ptrType, nonterminalName, nonterminalInfos, returnType, noDebugSupport, currentRule->Name(), tokenMap, fileMap);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = parser.SuccessCode()->Write(*formatter);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    if (parser.FailureCode())
    {
        rv = formatter->WriteLine("else");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = parser.FailureCode()->Write(*formatter);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    if (hasPass)
    {
        rv = formatter->WriteLine("if (match.hit && !pass)");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("match = soul::parser::Match(false);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    rv = formatter->WriteLine("*parentMatch" + std::to_string(setParentMatchNumber) + " = match;");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    setParentMatchNumber = prevSetParentMatchNumber;
    formatter->DecIndent();
    rv = formatter->WriteLine("}");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::NonterminalParser& parser)
{
    if (!Valid()) return;
    if (stage == CodeGenerationStage::generateImplementation)
    {
        soul::ast::spg::RuleParser* rule = parser.Rule();
        soul::ast::spg::GrammarParser* grammar = rule->Grammar();
        soul::ast::spg::ParserFile* parserFile = grammar->GetParserFile();
        std::string ruleName = parserFile->GetExportModule()->NamespaceName() + "::" + grammar->Name() + "<LexerT>::" + rule->Name();
        std::expected<bool, int> rv = formatter->Write("std::expected<soul::parser::Match, int> m = " + ruleName + "(lexer");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        if (parser.Arguments())
        {
            for (const auto& arg : parser.Arguments()->Exprs())
            {
                rv = formatter->Write(", ");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                rv = arg->Write(*formatter);
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
            }
        }
        rv = formatter->WriteLine(");");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("if (!m) return std::unexpected<int>(m.error());");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("soul::parser::Match match = *m;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        soul::ast::spg::RuleParser* calledRule = parser.Rule();
        if (calledRule->ReturnType() != nullptr)
        {
            rv = formatter->Write(parser.InstanceName() + ".reset(");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            if (calledRule->ReturnType()->IsPtrType())
            {
                rv = formatter->Write("static_cast<");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                rv = calledRule->ReturnType()->Write(*formatter);
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                rv = formatter->WriteLine(">(match.value));");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
            }
            else
            {
                rv = formatter->Write("static_cast<soul::parser::Value<");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                rv = calledRule->ReturnType()->Write(*formatter);
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                rv = formatter->WriteLine(">*>(match.value));");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
            }
        }
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::EmptyParser& parser)
{
    if (!Valid()) return;
    if (stage == CodeGenerationStage::generateImplementation)
    {
        std::expected<bool, int> rv = formatter->WriteLine("soul::parser::Match match(true);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::AnyParser& parser)
{
    if (!Valid()) return;
    if (stage == CodeGenerationStage::generateImplementation)
    {
        std::expected<bool, int> rv = formatter->WriteLine("soul::parser::Match match(false);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("if (*lexer != soul::lexer::END_TOKEN)");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("auto a = ++lexer;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("if (!a) return std::unexpected<int>(a.error());");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("match.hit = true;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::TokenParser& parser)
{
    if (!Valid()) return;
    if (stage == CodeGenerationStage::generateImplementation)
    {
        std::expected<bool, int> rv = formatter->WriteLine("soul::parser::Match match(false);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("if (*lexer == " + parser.GetToken()->FullCppId() + ")");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("auto a = ++lexer;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("if (!a) return std::unexpected<int>(a.error());");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("match.hit = true;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::CharParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = formatter->WriteLine("soul::parser::Match match(false);");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("if (*lexer == " + std::to_string(static_cast<std::int32_t>(parser.Chr())) + ")");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("{");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->IncIndent();
    rv = formatter->WriteLine("auto a = ++lexer;");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("if (!a) return std::unexpected<int>(a.error());");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("match.hit = true;");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->DecIndent();
    rv = formatter->WriteLine("}");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::StringParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = formatter->WriteLine("soul::parser::Match match(true);");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("for (std::int32_t i : " + parser.ArrayName() + ")");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("{");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->IncIndent();
    rv = formatter->WriteLine("if (*lexer == i)");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("{");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->IncIndent();
    rv = formatter->WriteLine("auto a = ++lexer;");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("if (!a) return std::unexpected<int>(a.error());");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->DecIndent();
    rv = formatter->WriteLine("}");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("else");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("{");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->IncIndent();
    rv = formatter->WriteLine("match.hit = false;");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("break;");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->DecIndent();
    rv = formatter->WriteLine("}");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->DecIndent();
    rv = formatter->WriteLine("}");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::CharSetParser& parser)
{
    if (!Valid()) return;
    if (parser.GetCharSet()->Inverse())
    {
        std::expected<bool, int> rv = formatter->WriteLine("soul::parser::Match match(lexer.Pos() != lexer.End());");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("for (const soul::ast::spg::Range& range : " + parser.ArrayName() + ")");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("if (*lexer >= range.first && *lexer <= range.last)");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("match.hit = false;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("break;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("if (match.hit)");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("auto a = ++lexer;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("if (!a) return std::unexpected<int>(a.error());");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    else
    {
        std::expected<bool, int> rv = formatter->WriteLine("soul::parser::Match match(false);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("for (const soul::ast::spg::Range& range : " + parser.ArrayName() + ")");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("if (*lexer >= range.first && *lexer <= range.last)");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("match.hit = true;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("auto a = ++lexer;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("if (!a) return std::unexpected<int>(a.error());");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("break;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::GroupParser& parser)
{
    if (!Valid()) return;
    if (stage == CodeGenerationStage::generateImplementation)
    {
        std::expected<bool, int> rv = formatter->WriteLine("soul::parser::Match match(false);");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        int prevSetParentMatchNumber = setParentMatchNumber;
        setParentMatchNumber = parentMatchNumber;
        rv = formatter->WriteLine("soul::parser::Match* parentMatch" + std::to_string(parentMatchNumber++) + " = &match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        parser.Child()->Accept(*this);
        if (!Valid()) return;
        rv = formatter->WriteLine("*parentMatch" + std::to_string(setParentMatchNumber) + " = match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        setParentMatchNumber = prevSetParentMatchNumber;
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::RuleParser& parser)
{
    if (!Valid()) return;
    parentMatchNumber = 0;
    setParentMatchNumber = -1;
    currentRule = &parser;
    if (stage == CodeGenerationStage::generateInterface)
    {
        std::expected<bool, int> rv = formatter->Write("static std::expected<soul::parser::Match, int> " + parser.Name() + "(LexerT& lexer");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        for (const auto& param : parser.Params())
        {
            rv = formatter->Write(", ");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = param->Type()->Write(*formatter);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = formatter->Write(" ");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = formatter->Write(param->Name());
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
        }
        rv = formatter->WriteLine(");");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    else if (stage == CodeGenerationStage::generateImplementation)
    {
        bool first = false;
        if (!currentParser->Rules().empty())
        {
            if (currentParser->Rules().front().get() == &parser)
            {
                first = true;
            }
        }
        if (!first)
        {
            formatter->WriteLine();
        }
        std::expected<bool, int> rv = formatter->WriteLine("template<typename LexerT>");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->Write("std::expected<soul::parser::Match, int> " + parser.Grammar()->Name() + "<LexerT>::" + parser.Name() + "(LexerT& lexer");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        for (const auto& param : parser.Params())
        {
            rv = formatter->Write(", ");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = param->Type()->Write(*formatter);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = formatter->Write(" ");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = formatter->Write(param->Name());
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
        }
        rv = formatter->WriteLine(")");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        if (!noDebugSupport)
        {
            rv = formatter->WriteLine("#ifdef SOUL_PARSER_DEBUG_SUPPORT");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = formatter->WriteLine("std::int64_t parser_debug_match_pos = 0;");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = formatter->WriteLine("bool parser_debug_write_to_log = lexer.Log() != nullptr;");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = formatter->WriteLine("if (parser_debug_write_to_log)");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = formatter->WriteLine("{");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            formatter->IncIndent();
            rv = formatter->WriteLine("parser_debug_match_pos = lexer.GetPos();");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = formatter->WriteLine("soul::lexer::WriteBeginRuleToLog(lexer, \"" + parser.Name() + "\");");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            formatter->DecIndent();
            rv = formatter->WriteLine("}");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = formatter->WriteLine("#endif");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
        }
        rv = formatter->WriteLine("soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, " + std::to_string(parser.Id()) + ");");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        for (const auto& variable : parser.Vars())
        {
            rv = variable->Type()->Write(*formatter);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = formatter->Write(" ");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = formatter->Write(variable->Name());
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = formatter->Write(" = ");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            if (variable->Type()->IsPtrType())
            {
                rv = formatter->WriteLine("nullptr;");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
            }
            else
            {
                rv = variable->Type()->Write(*formatter);
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                rv = formatter->WriteLine("();");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
            }
        }
        nonterminalInfos.clear();
        for (auto nonterminal : parser.Nonterminals())
        {
            bool found = false;
            for (const auto& info : nonterminalInfos)
            {
                if (info.nonterminalParser->InstanceName() == nonterminal->InstanceName())
                {
                    found = true;
                    break;
                }
            }
            if (found) continue;
            soul::ast::spg::RuleParser* calledRule = nonterminal->Rule();
            if (!calledRule)
            {
                SetError(util::AllocateError("rule not set"));
                return;
            }
            if (calledRule->ReturnType() != nullptr)
            {
                if (calledRule->ReturnType()->IsPtrType())
                {
                    rv = formatter->Write("std::unique_ptr<");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    rv = calledRule->ReturnType()->WriteNonPtrType(*formatter);
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    rv = formatter->Write(">");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    nonterminalInfos.push_back(NonterminalInfo(nonterminal, true));
                }
                else
                {
                    rv = formatter->Write("std::unique_ptr<soul::parser::Value<");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    rv = calledRule->ReturnType()->Write(*formatter);
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    rv = formatter->Write(">>");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    nonterminalInfos.push_back(NonterminalInfo(nonterminal, false));
                }
                rv = formatter->WriteLine(" " + nonterminal->InstanceName() + ";");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
            }
        }
        parser.Definition()->Accept(*this);
        if (!Valid()) return;
        if (!noDebugSupport)
        {
            rv = formatter->WriteLine("#ifdef SOUL_PARSER_DEBUG_SUPPORT");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = formatter->WriteLine("if (parser_debug_write_to_log)");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = formatter->WriteLine("{");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            formatter->IncIndent();
            rv = formatter->WriteLine("if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, \"" + parser.Name() + "\");");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = formatter->WriteLine("else soul::lexer::WriteFailureToLog(lexer, \"" + parser.Name() + "\");");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            formatter->DecIndent();
            rv = formatter->WriteLine("}");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = formatter->WriteLine("#endif");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
        }
        rv = formatter->WriteLine("if (!match.hit)");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        rv = formatter->WriteLine("match.value = nullptr;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("return match;");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("}");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        for (const auto& info : nonterminalInfos)
        {
            if (info.ptrType && info.count > 1)
            {
                if (!soul::spg::parsing::util::IsListParserNonterminal(info))
                {
                    std::expected<std::string, int> rv = soul::lexer::MakeMessage("warning",
                        "unique pointer value of nonterminal '" + info.nonterminalParser->InstanceName() + "' used " + std::to_string(info.count) +
                        " times in semantic actions of rule '" +
                        parser.Name() + "' of parser '" + parser.Grammar()->Name() + "'", parser.GetSourcePos(), fileMap);
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    std::string message = std::move(*rv);
                    for (const auto& sourcePos : info.sourcePositions)
                    {
                        std::expected<std::string, int> rv = soul::lexer::MakeMessage("info", "see reference", sourcePos, fileMap);
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        message.append("\n").append(*rv);
                    }
                    std::cout << message << "\n";
                }
            }
        }
        if (parser.ReturnType() != nullptr && !parser.HasReturn())
        {
            std::cout << "warning: rule '" << parser.Name() <<
                "' of parser '" << parser.Grammar()->Name() << "' returns value, but no semantic action has a return statement." << "\n";
        }
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::GrammarParser& parser)
{
    if (!Valid()) return;
    currentParser = &parser;
    if (stage == CodeGenerationStage::generateInterface)
    {
        std::expected<bool, int> rv = formatter->WriteLine("template<typename LexerT>");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("struct " + parser.Name());
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = formatter->WriteLine("{");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        formatter->IncIndent();
        if (parser.Main())
        {
            if (!parser.Rules().empty())
            {
                const std::unique_ptr<soul::ast::spg::RuleParser>& startRule = parser.Rules().front();
                if (startRule->ReturnType() != nullptr)
                {
                    rv = formatter->Write("static ");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    if (startRule->ReturnType()->IsPtrType())
                    {
                        rv = formatter->Write("std::expected<std::unique_ptr<");
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        rv = startRule->ReturnType()->WriteNonPtrType(*formatter);
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        rv = formatter->Write(">, int>");
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                    }
                    else
                    {
                        rv = formatter->Write("std::expected<");
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        rv = startRule->ReturnType()->Write(*formatter);
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        rv = formatter->Write(", int>");
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                    }
                    rv = formatter->Write(" Parse(LexerT& lexer");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                }
                else
                {
                    rv = formatter->Write("static void Parse(LexerT& lexer");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                }
                for (const auto& param : startRule->Params())
                {
                    rv = formatter->Write(", ");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    rv = param->Type()->Write(*formatter);
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    rv = formatter->Write(" ");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    rv = formatter->Write(param->Name());
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                }
                rv = formatter->WriteLine(");");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
            }
        }
        for (const auto& rule : parser.Rules())
        {
            rule->Accept(*this);
            if (!Valid()) return;
        }
        formatter->DecIndent();
        rv = formatter->WriteLine("};");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    else if (stage == CodeGenerationStage::generateImplementation)
    {
        if (parser.Main())
        {
            if (!parser.Rules().empty())
            {
                std::expected<bool, int> rv = formatter->WriteLine("template<typename LexerT>");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                const std::unique_ptr<soul::ast::spg::RuleParser>& startRule = parser.Rules().front();
                if (startRule->ReturnType() != nullptr)
                {
                    if (startRule->ReturnType()->IsPtrType())
                    {
                        rv = formatter->Write("std::expected<std::unique_ptr<");
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        rv = startRule->ReturnType()->WriteNonPtrType(*formatter);
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        rv = formatter->Write(">, int>");
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                    }
                    else
                    {
                        rv = formatter->Write("std::expected<");
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        rv = startRule->ReturnType()->Write(*formatter);
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        rv = formatter->Write(", int>");
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                    }
                    rv = formatter->Write(" " + parser.Name() + "<LexerT>::Parse(LexerT& lexer");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                }
                else
                {
                    rv = formatter->Write("void " + parser.Name() + "<LexerT>::Parse(LexerT& lexer");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                }
                for (const auto& param : startRule->Params())
                {
                    rv = formatter->Write(", ");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    rv = param->Type()->Write(*formatter);
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    rv = formatter->Write(" ");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    rv = formatter->Write(param->Name());
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                }
                rv = formatter->WriteLine(")");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                rv = formatter->WriteLine("{");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                formatter->IncIndent();
                soul::ast::spg::RuleParser* rule = startRule.get();
                if (rule->ReturnType() != nullptr)
                {
                    rv = formatter->Write("std::unique_ptr<");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    if (rule->ReturnType()->IsPtrType())
                    {
                        rv = rule->ReturnType()->WriteNonPtrType(*formatter);
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        rv = formatter->Write(">");
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                    }
                    else
                    {
                        rv = formatter->Write("soul::parser::Value<");
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        rv = rule->ReturnType()->Write(*formatter);
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        rv = formatter->Write(">>");
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                    }
                    rv = formatter->WriteLine(" value;");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                }
                if (!noDebugSupport)
                {
                    rv = formatter->WriteLine("#ifdef SOUL_PARSER_DEBUG_SUPPORT");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    rv = formatter->WriteLine("if (lexer.Log())");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    rv = formatter->WriteLine("{");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    formatter->IncIndent();
                    rv = formatter->WriteLine("lexer.Log()->WriteBeginRule(\"parse\");");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    rv = formatter->WriteLine("lexer.Log()->IncIndent();");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    formatter->DecIndent();
                    rv = formatter->WriteLine("}");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    rv = formatter->WriteLine("#endif");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                }
                rv = formatter->WriteLine("auto a = ++lexer;");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                rv = formatter->WriteLine("if (!a) return std::unexpected<int>(a.error());");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                std::string ruleName = rule->Grammar()->Name() + "<LexerT>::" + rule->Name();
                rv = formatter->Write("std::expected<soul::parser::Match, int> m = " + ruleName + "(lexer");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                for (const auto& param : startRule->Params())
                {
                    rv = formatter->Write(", ");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    rv = formatter->Write(param->Name());
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                }
                rv = formatter->WriteLine(");");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                rv = formatter->WriteLine("if (!m) return std::unexpected<int>(m.error());");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                rv = formatter->WriteLine("soul::parser::Match match = *m;");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                soul::ast::spg::RuleParser* calledRule = rule;
                if (!calledRule)
                {
                    SetError(util::AllocateError("rule not set"));
                    return;
                }
                if (calledRule->ReturnType() != nullptr)
                {
                    rv = formatter->Write("value.reset(");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    if (calledRule->ReturnType()->IsPtrType())
                    {
                        rv = formatter->Write("static_cast<");
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        rv = calledRule->ReturnType()->Write(*formatter);
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        rv = formatter->WriteLine(">(match.value));");
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                    }
                    else
                    {
                        rv = formatter->Write("static_cast<soul::parser::Value<");
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        rv = calledRule->ReturnType()->Write(*formatter);
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        rv = formatter->WriteLine(">*>(match.value));");
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                    }
                }
                if (!noDebugSupport)
                {
                    rv = formatter->WriteLine("#ifdef SOUL_PARSER_DEBUG_SUPPORT");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    rv = formatter->WriteLine("if (lexer.Log())");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    rv = formatter->WriteLine("{");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    formatter->IncIndent();
                    rv = formatter->WriteLine("lexer.Log()->DecIndent();");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    rv = formatter->WriteLine("lexer.Log()->WriteEndRule(\"parse\");");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    formatter->DecIndent();
                    rv = formatter->WriteLine("}");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    rv = formatter->WriteLine("#endif");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                }
                rv = formatter->WriteLine("if (match.hit)");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                rv = formatter->WriteLine("{");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                formatter->IncIndent();
                rv = formatter->WriteLine("if (*lexer == soul::lexer::END_TOKEN)");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                rv = formatter->WriteLine("{");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                formatter->IncIndent();
                if (startRule->ReturnType())
                {
                    if (startRule->ReturnType()->IsPtrType())
                    {
                        rv = formatter->WriteLine("return value;");
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                    }
                    else
                    {
                        rv = formatter->WriteLine("return value->value;");
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                    }
                }
                else
                {
                    rv = formatter->WriteLine("return;");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                }
                formatter->DecIndent();
                rv = formatter->WriteLine("}");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                rv = formatter->WriteLine("else");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                rv = formatter->WriteLine("{");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                formatter->IncIndent();
                rv = formatter->WriteLine("return lexer.FarthestError();");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                formatter->DecIndent();
                rv = formatter->WriteLine("}");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                formatter->DecIndent();
                rv = formatter->WriteLine("}");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                rv = formatter->WriteLine("else");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                rv = formatter->WriteLine("{");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                formatter->IncIndent();
                std::string ruleInfo = rule->Info();
                if (ruleInfo.empty())
                {
                    ruleInfo = rule->Name();
                }
                rv = formatter->WriteLine("return lexer.FarthestError();");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                formatter->DecIndent();
                rv = formatter->WriteLine("}");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                if (startRule->ReturnType())
                {
                    if (startRule->ReturnType()->IsPtrType())
                    {
                        rv = formatter->WriteLine("return value;");
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                    }
                    else
                    {
                        rv = formatter->WriteLine("return value->value;");
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                    }
                }
                else
                {
                    rv = formatter->WriteLine("return;");
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                }
                formatter->DecIndent();
                rv = formatter->WriteLine("}");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                formatter->WriteLine();
            }
        }
        for (const auto& rule : parser.Rules())
        {
            rule->Accept(*this);
            if (!Valid()) return;
        }
    }
}

void CodeGeneratorVisitor::Visit(soul::ast::spg::ParserFile& parserFile)
{
    if (!Valid()) return;
    if (parserFile.IsExternal())
    {
        if (verbose)
        {
            std::cout << "> " << parserFile.FilePath() << "\n";
            std::cout << "skipping external parser file '" << parserFile.FilePath() << "'" << "\n";
        }
        return;
    }
    if (verbose)
    {
        std::cout << "> " << parserFile.FilePath() << "\n";
        std::cout << "generating code..." << "\n";
    }
    sn = 0;
    stage = CodeGenerationStage::generateInterface;
    std::string interfaceFileName = parserFile.FilePath() + ".cppm";
    std::ofstream interfaceFile(interfaceFileName);
    util::CodeFormatter interfaceFormatter(interfaceFile);
    formatter = &interfaceFormatter;

    formatter->WriteLine();
    std::expected<bool, int> rv = formatter->WriteLine("// this file has been automatically generated from '" + parserFile.FilePath() +
        "' using soul parser generator ospg version " + version);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->WriteLine();
    soul::ast::common::ExportModule* mod = parserFile.GetExportModule();
    rv = formatter->WriteLine("export module " + mod->ModuleName() + ";");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->WriteLine();
    rv = formatter->WriteLine("import std;");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("import soul.lexer;");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("import soul.parser;");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    bool hasInterfaceImports = false;
    for (const auto& imprt : parserFile.Imports())
    {
        if (imprt->Prefix() == soul::ast::common::ImportPrefix::interfacePrefix)
        {
            hasInterfaceImports = true;
            rv = formatter->WriteLine("import " + imprt->ModuleName() + ";");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
        }
    }
    formatter->WriteLine();
    rv = formatter->WriteLine("export namespace " + soul::ast::common::ToNamespaceName(mod->ModuleName()) + " {");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->WriteLine();
    bool first = true;
    for (const auto& parser : parserFile.Parsers())
    {
        if (first)
        {
            first = false;
        }
        else
        {
            formatter->WriteLine();
        }
        parser->Accept(*this);
        if (!Valid()) return;
    }
    formatter->WriteLine();
    rv = formatter->WriteLine("} // namespace " + soul::ast::common::ToNamespaceName(mod->ModuleName()));
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    if (verbose)
    {
        std::cout << "==> " << interfaceFileName << "\n";
    }

    stage = CodeGenerationStage::generateImplementation;
    std::string implementationFileName = parserFile.FilePath() + ".cpp";
    std::ofstream implementationFile(implementationFileName);
    if (!implementationFile)
    {
        SetError(util::AllocateError("cannot create '" + implementationFileName + "'"));
        return;
    }
    util::CodeFormatter implementationFormatter(implementationFile);
    formatter = &implementationFormatter;

    formatter->WriteLine();
    rv = formatter->WriteLine("// this file has been automatically generated from '" + parserFile.FilePath() + "' using soul parser generator ospg version " + version);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->WriteLine();
    rv = formatter->WriteLine("module " + mod->ModuleName() + ";");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->WriteLine();
    rv = formatter->WriteLine("import util;");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("import soul.ast.spg;");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = formatter->WriteLine("import soul.ast.common;");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    for (const auto& imprt : parserFile.Imports())
    {
        if (imprt->Prefix() == soul::ast::common::ImportPrefix::implementationPrefix)
        {
            rv = formatter->WriteLine("import " + imprt->ModuleName() + ";");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
        }
    }
    formatter->WriteLine();
    rv = formatter->WriteLine("namespace " + soul::ast::common::ToNamespaceName(mod->ModuleName()) + " {");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter->WriteLine();
    rv = GenerateArrays(parserFile, *formatter, sn);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    for (const auto& parser : parserFile.Parsers())
    {
        parser->Accept(*this);
        if (!Valid()) return;
    }
    formatter->WriteLine();
    bool hasLexers = false;
    for (const auto& parser : parserFile.Parsers())
    {
        for (const auto& lexer : parser->Lexers())
        {
            if (lexer->TypeSpecifiers().size() > 0)
            {
                soul::ast::cpp::TypeSpecifierNode* firstTypeSpecifier = lexer->TypeSpecifiers()[0].get();
                std::string charTypeName = "char";
                if (firstTypeSpecifier->Kind() == soul::ast::cpp::NodeKind::typeNameNode)
                {
                    soul::ast::cpp::TypeNameNode* lexerType = static_cast<soul::ast::cpp::TypeNameNode*>(firstTypeSpecifier);
                    if (lexerType->IsTemplate() && lexerType->TemplateArgs().size() > 0)
                    {
                        soul::ast::cpp::Node* firstTemplateArg = lexerType->TemplateArgs()[0].get();
                        charTypeName = firstTemplateArg->ToString();
                    }
                }
                hasLexers = true;
                rv = formatter->WriteLine("template struct " + parser->Name() + "<soul::lexer::Lexer<" + lexer->ToString() + ", " + charTypeName + ">>;");
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
            }
        }
    }
    if (hasLexers)
    {
        formatter->WriteLine();
    }
    rv = formatter->WriteLine("} // namespace " + soul::ast::common::ToNamespaceName(mod->ModuleName()));
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    if (verbose)
    {
        std::cout << "==> " << implementationFileName << "\n";
    }
}

} // soul::spg
