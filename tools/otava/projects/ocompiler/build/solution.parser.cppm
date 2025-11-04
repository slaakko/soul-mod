
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/build/solution.parser' using soul parser generator ospg version 5.0.0

export module otava.solution_parser;

import std;
import soul.lexer;
import soul.parser;
import otava.build_solution;

export namespace otava::solution_parser {

template<typename LexerT>
struct SolutionParser
{
    static std::expected<std::unique_ptr<otava::build::Solution>, int> Parse(LexerT& lexer);
    static std::expected<soul::parser::Match, int> SolutionFile(LexerT& lexer);
    static std::expected<soul::parser::Match, int> SolutionDeclaration(LexerT& lexer);
    static std::expected<soul::parser::Match, int> FilePath(LexerT& lexer, otava::build::Solution* sln);
    static std::expected<soul::parser::Match, int> ProjectFilePath(LexerT& lexer);
    static std::expected<soul::parser::Match, int> QualifiedId(LexerT& lexer);
};

} // namespace otava::solution_parser
