
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/command/command.parser' using soul parser generator spg version 4.1.0

export module otava.command.parser;

import std.core;
import soul.lexer;
import soul.parser;
import otava.command.ast;

using namespace otava::command::ast;

export namespace otava::command::parser {

template<typename Lexer>
struct CommandParser
{
    static std::unique_ptr<otava::command::ast::Command> Parse(Lexer& lexer);
    static soul::parser::Match Command(Lexer& lexer);
    static soul::parser::Match BuildCommand(Lexer& lexer);
    static soul::parser::Match DumpCommand(Lexer& lexer);
    static soul::parser::Match AssembleCommand(Lexer& lexer);
    static soul::parser::Match IntermediateCompileCommand(Lexer& lexer);
    static soul::parser::Match FilePath(Lexer& lexer);
};

} // namespace otava::command::parser
