
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/optimized_project/project.parser' using soul parser generator spg version 4.1.0

export module soul.cpp20.proj.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.proj.ast;

using namespace soul::cpp20::proj::ast;

export namespace soul::cpp20::proj::parser {

template<typename Lexer>
struct ProjectParser
{
    static std::unique_ptr<soul::cpp20::proj::ast::Project> Parse(Lexer& lexer);
    static soul::parser::Match ProjectFile(Lexer& lexer);
    static soul::parser::Match ProjectDeclaration(Lexer& lexer);
    static soul::parser::Match Define(Lexer& lexer, soul::cpp20::proj::ast::Project* proj);
    static soul::parser::Match FilePath(Lexer& lexer, soul::cpp20::proj::ast::Project* proj);
    static soul::parser::Match InterfaceFilePath(Lexer& lexer);
    static soul::parser::Match SourceFilePath(Lexer& lexer);
    static soul::parser::Match ReferenceFilePath(Lexer& lexer);
    static soul::parser::Match QualifiedId(Lexer& lexer);
};

} // namespace soul::cpp20::proj::parser
