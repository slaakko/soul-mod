
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/build/project.parser' using soul parser generator ospg version 5.0.0

export module otava.project_parser;

import std;
import soul.lexer;
import soul.parser;
import otava.build_project;

export namespace otava::project_parser {

template<typename LexerT>
struct ProjectParser
{
    static std::expected<std::unique_ptr<otava::build::Project>, int> Parse(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ProjectFile(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ProjectDeclaration(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Define(LexerT& lexer, otava::build::Project* projectFile);
    static std::expected<soul::parser::Match, int> TargetDeclaration(LexerT& lexer, otava::build::Project* projectFile);
    static std::expected<soul::parser::Match, int> Target(LexerT& lexer);
    static std::expected<soul::parser::Match, int> FilePath(LexerT& lexer, otava::build::Project* projectFile);
    static std::expected<soul::parser::Match, int> InterfaceFilePath(LexerT& lexer);
    static std::expected<soul::parser::Match, int> SourceFilePath(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ResourceFilePath(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ReferenceFilePath(LexerT& lexer);
    static std::expected<soul::parser::Match, int> QualifiedId(LexerT& lexer);
};

} // namespace otava::project_parser
