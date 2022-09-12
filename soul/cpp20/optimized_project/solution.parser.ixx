
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/optimized_project/solution.parser' using soul parser generator spg version 4.1.0

export module soul.cpp20.sln.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.proj.ast;

using namespace soul::cpp20::proj::ast;

export namespace soul::cpp20::sln::parser {

template<typename Lexer>
struct SolutionParser
{
    static std::unique_ptr<soul::cpp20::proj::ast::Solution> Parse(Lexer& lexer);
    static soul::parser::Match SolutionFile(Lexer& lexer);
    static soul::parser::Match SolutionDeclaration(Lexer& lexer);
    static soul::parser::Match FilePath(Lexer& lexer, soul::cpp20::proj::ast::Solution* sln);
    static soul::parser::Match ProjectFilePath(Lexer& lexer);
    static soul::parser::Match QualifiedId(Lexer& lexer);
};

} // namespace soul::cpp20::sln::parser
