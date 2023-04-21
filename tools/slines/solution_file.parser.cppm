
// this file has been automatically generated from 'C:/work/soul-mod/tools/slines/solution_file.parser' using soul parser generator spg version 4.1.0

export module solution_file.parser;

import std.core;
import soul.lexer;
import soul.parser;
import solution_file.ast;
import project_file.ast;

using namespace solution_file::ast;
using namespace project_file::ast;

export namespace solution_file::parser {

template<typename LexerT>
struct solution_file_parser
{
    static std::unique_ptr<solution_file::ast::Solution> Parse(LexerT& lexer);
    static soul::parser::Match file(LexerT& lexer);
    static soul::parser::Match header(LexerT& lexer);
    static soul::parser::Match visual_studio_version(LexerT& lexer);
    static soul::parser::Match minimum_visual_studio_version(LexerT& lexer);
    static soul::parser::Match projects(LexerT& lexer, solution_file::ast::Solution* solution);
    static soul::parser::Match project_(LexerT& lexer, std::string root);
    static soul::parser::Match project_sections(LexerT& lexer);
    static soul::parser::Match project_section(LexerT& lexer);
    static soul::parser::Match solution_items_section(LexerT& lexer);
    static soul::parser::Match path_lines(LexerT& lexer);
    static soul::parser::Match path_line(LexerT& lexer);
    static soul::parser::Match project_dependencies_section(LexerT& lexer);
    static soul::parser::Match guid_lines(LexerT& lexer);
    static soul::parser::Match guid_line(LexerT& lexer);
    static soul::parser::Match global(LexerT& lexer);
    static soul::parser::Match global_sections(LexerT& lexer);
    static soul::parser::Match global_section(LexerT& lexer);
    static soul::parser::Match solution_configuration_platform_section(LexerT& lexer);
    static soul::parser::Match config_lines(LexerT& lexer);
    static soul::parser::Match config_line(LexerT& lexer);
    static soul::parser::Match config(LexerT& lexer);
    static soul::parser::Match project_configuration_platform_section(LexerT& lexer);
    static soul::parser::Match guid_config_lines(LexerT& lexer);
    static soul::parser::Match guid_config_line(LexerT& lexer);
    static soul::parser::Match guid_config(LexerT& lexer);
    static soul::parser::Match solution_properties_section(LexerT& lexer);
    static soul::parser::Match hide_solution_node_lines(LexerT& lexer);
    static soul::parser::Match hide_solution_node_line(LexerT& lexer);
    static soul::parser::Match nested_project_section(LexerT& lexer);
    static soul::parser::Match nested_projects(LexerT& lexer);
    static soul::parser::Match nested_project(LexerT& lexer);
    static soul::parser::Match extensibility_globals_section(LexerT& lexer);
    static soul::parser::Match solution_guids(LexerT& lexer);
    static soul::parser::Match solution_guid(LexerT& lexer);
};

} // namespace solution_file::parser
