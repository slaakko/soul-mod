
// this file has been automatically generated from 'C:/work/soul-mod/examples/minilang/source_file.parser' using soul parser generator spg version 4.1.0

export module minilang.parser.source.file;

import std.core;
import soul.lexer;
import soul.parser;
import minilang.ast;

using namespace minilang::ast;

export namespace minilang::parser::source::file {

template<typename Lexer>
struct SourceFileParser
{
    static std::unique_ptr<minilang::ast::SourceFileNode> Parse(Lexer& lexer);
    static soul::parser::Match SourceFile(Lexer& lexer);
};

} // namespace minilang::parser::source::file
