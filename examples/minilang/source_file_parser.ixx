
// this file has been automatically generated from 'C:/work/soul-mod/examples/minilang/source_file_parser.parser' using soul parser generator spg version 4.0.0

export module minilang.parser.source.file;

import std.core;
import soul.lexer;
import soul.parser;
import minilang.tree;

using namespace minilang::tree;

export namespace minilang::parser::source::file {

template<typename Lexer>
struct SourceFileParser
{
    static std::unique_ptr<minilang::tree::SourceFileNode> Parse(Lexer& lexer);
    static soul::parser::Match SourceFile(Lexer& lexer);
};

} // namespace minilang::parser::source::file
