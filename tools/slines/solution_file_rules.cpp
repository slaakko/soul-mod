module solution_file.rules;

namespace solution_file::rules {

std::mutex ruleMtx;

std::map<int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<int64_t, std::string> ruleNameMap = {
        { 8253265351345700865, "solution_file_parser.file" },
        { 8253265351345700866, "solution_file_parser.header" },
        { 8253265351345700867, "solution_file_parser.visual_studio_version" },
        { 8253265351345700868, "solution_file_parser.minimum_visual_studio_version" },
        { 8253265351345700869, "solution_file_parser.projects" },
        { 8253265351345700870, "solution_file_parser.project_" },
        { 8253265351345700871, "solution_file_parser.project_sections" },
        { 8253265351345700872, "solution_file_parser.project_section" },
        { 8253265351345700873, "solution_file_parser.solution_items_section" },
        { 8253265351345700874, "solution_file_parser.path_lines" },
        { 8253265351345700875, "solution_file_parser.path_line" },
        { 8253265351345700876, "solution_file_parser.project_dependencies_section" },
        { 8253265351345700877, "solution_file_parser.guid_lines" },
        { 8253265351345700878, "solution_file_parser.guid_line" },
        { 8253265351345700879, "solution_file_parser.global" },
        { 8253265351345700880, "solution_file_parser.global_sections" },
        { 8253265351345700881, "solution_file_parser.global_section" },
        { 8253265351345700882, "solution_file_parser.solution_configuration_platform_section" },
        { 8253265351345700883, "solution_file_parser.config_lines" },
        { 8253265351345700884, "solution_file_parser.config_line" },
        { 8253265351345700885, "solution_file_parser.config" },
        { 8253265351345700886, "solution_file_parser.project_configuration_platform_section" },
        { 8253265351345700887, "solution_file_parser.guid_config_lines" },
        { 8253265351345700888, "solution_file_parser.guid_config_line" },
        { 8253265351345700889, "solution_file_parser.guid_config" },
        { 8253265351345700890, "solution_file_parser.solution_properties_section" },
        { 8253265351345700891, "solution_file_parser.hide_solution_node_lines" },
        { 8253265351345700892, "solution_file_parser.hide_solution_node_line" },
        { 8253265351345700893, "solution_file_parser.nested_project_section" },
        { 8253265351345700894, "solution_file_parser.nested_projects" },
        { 8253265351345700895, "solution_file_parser.nested_project" },
        { 8253265351345700896, "solution_file_parser.extensibility_globals_section" },
        { 8253265351345700897, "solution_file_parser.solution_guids" },
        { 8253265351345700898, "solution_file_parser.solution_guid" }
    };
    return &ruleNameMap;
}

} // solution_file::rules
