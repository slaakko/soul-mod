
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/build/project.parser' using soul parser generator spg version 4.1.0

export module otava.project_parser;

import std.core;
import soul.lexer;
import soul.parser;
import otava.build_project;

using namespace otava::build_project;

export namespace otava::project_parser {

template<typename Lexer>
struct ProjectParser
{
    static std::unique_ptr<otava::build::Project> Parse(Lexer& lexer);
    static soul::parser::Match ProjectFile(Lexer& lexer);
    static soul::parser::Match ProjectDeclaration(Lexer& lexer);
    static soul::parser::Match Define(Lexer& lexer, otava::build::Project* projectFile);
    static soul::parser::Match TargetDeclaration(Lexer& lexer, otava::build::Project* projectFile);
    static soul::parser::Match Target(Lexer& lexer);
    static soul::parser::Match FilePath(Lexer& lexer, otava::build::Project* projectFile);
    static soul::parser::Match InterfaceFilePath(Lexer& lexer);
    static soul::parser::Match SourceFilePath(Lexer& lexer);
    static soul::parser::Match ReferenceFilePath(Lexer& lexer);
    static soul::parser::Match QualifiedId(Lexer& lexer);
};

} // namespace otava::project_parser
