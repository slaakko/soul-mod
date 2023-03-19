
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/build/solution.parser' using soul parser generator spg version 4.1.0

export module otava.solution_parser;

import std.core;
import soul.lexer;
import soul.parser;
import otava.build_solution;

using namespace otava::build_solution;

export namespace otava::solution_parser {

template<typename Lexer>
struct SolutionParser
{
    static std::unique_ptr<otava::build::Solution> Parse(Lexer& lexer);
    static soul::parser::Match SolutionFile(Lexer& lexer);
    static soul::parser::Match SolutionDeclaration(Lexer& lexer);
    static soul::parser::Match FilePath(Lexer& lexer, otava::build::Solution* sln);
    static soul::parser::Match ProjectFilePath(Lexer& lexer);
    static soul::parser::Match QualifiedId(Lexer& lexer);
};

} // namespace otava::solution_parser
