
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

template<typename Lexer>
struct solution_file_parser
{
    static std::unique_ptr<solution_file::ast::Solution> Parse(Lexer& lexer);
    static soul::parser::Match file(Lexer& lexer);
    static soul::parser::Match header(Lexer& lexer);
    static soul::parser::Match visual_studio_version(Lexer& lexer);
    static soul::parser::Match minimum_visual_studio_version(Lexer& lexer);
    static soul::parser::Match projects(Lexer& lexer, solution_file::ast::Solution* solution);
    static soul::parser::Match project_(Lexer& lexer, std::string root);
    static soul::parser::Match project_sections(Lexer& lexer);
    static soul::parser::Match project_section(Lexer& lexer);
    static soul::parser::Match solution_items_section(Lexer& lexer);
    static soul::parser::Match path_lines(Lexer& lexer);
    static soul::parser::Match path_line(Lexer& lexer);
    static soul::parser::Match project_dependencies_section(Lexer& lexer);
    static soul::parser::Match guid_lines(Lexer& lexer);
    static soul::parser::Match guid_line(Lexer& lexer);
    static soul::parser::Match global(Lexer& lexer);
    static soul::parser::Match global_sections(Lexer& lexer);
    static soul::parser::Match global_section(Lexer& lexer);
    static soul::parser::Match solution_configuration_platform_section(Lexer& lexer);
    static soul::parser::Match config_lines(Lexer& lexer);
    static soul::parser::Match config_line(Lexer& lexer);
    static soul::parser::Match config(Lexer& lexer);
    static soul::parser::Match project_configuration_platform_section(Lexer& lexer);
    static soul::parser::Match guid_config_lines(Lexer& lexer);
    static soul::parser::Match guid_config_line(Lexer& lexer);
    static soul::parser::Match guid_config(Lexer& lexer);
    static soul::parser::Match solution_properties_section(Lexer& lexer);
    static soul::parser::Match hide_solution_node_lines(Lexer& lexer);
    static soul::parser::Match hide_solution_node_line(Lexer& lexer);
    static soul::parser::Match nested_project_section(Lexer& lexer);
    static soul::parser::Match nested_projects(Lexer& lexer);
    static soul::parser::Match nested_project(Lexer& lexer);
    static soul::parser::Match extensibility_globals_section(Lexer& lexer);
    static soul::parser::Match solution_guids(Lexer& lexer);
    static soul::parser::Match solution_guid(Lexer& lexer);
};

} // namespace solution_file::parser
