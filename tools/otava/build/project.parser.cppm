
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/build/project.parser' using soul parser generator spg version 5.0.0

export module otava.project_parser;

import std;
import soul.lexer;
import soul.parser;
import otava.build_project;

using namespace otava::build_project;

export namespace otava::project_parser {

template<typename LexerT>
struct ProjectParser
{
    static std::unique_ptr<otava::build::Project> Parse(LexerT& lexer);
    static soul::parser::Match ProjectFile(LexerT& lexer);
    static soul::parser::Match ProjectDeclaration(LexerT& lexer);
    static soul::parser::Match Define(LexerT& lexer, otava::build::Project* projectFile);
    static soul::parser::Match TargetDeclaration(LexerT& lexer, otava::build::Project* projectFile);
    static soul::parser::Match Target(LexerT& lexer);
    static soul::parser::Match FilePath(LexerT& lexer, otava::build::Project* projectFile);
    static soul::parser::Match InterfaceFilePath(LexerT& lexer);
    static soul::parser::Match SourceFilePath(LexerT& lexer);
    static soul::parser::Match ResourceFilePath(LexerT& lexer);
    static soul::parser::Match ReferenceFilePath(LexerT& lexer);
    static soul::parser::Match QualifiedId(LexerT& lexer);
};

} // namespace otava::project_parser
