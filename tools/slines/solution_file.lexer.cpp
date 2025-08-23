// this file has been automatically generated from 'C:/work/soul-mod/tools/slines/solution_file.lexer' using soul lexer generator slg version 4.1.0

module solution_file.lexer;

using namespace solution_file::token;

namespace solution_file::lexer {

soul::ast::common::TokenCollection* GetTokens()
{
    static soul::ast::common::TokenCollection tokens("solution_file.lexer.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul::ast::common::Token(MICROSOFT, "MICROSOFT", "'Microsoft'"));
        tokens.AddToken(new soul::ast::common::Token(VISUAL, "VISUAL", "'Visual'"));
        tokens.AddToken(new soul::ast::common::Token(STUDIO, "STUDIO", "'Studio'"));
        tokens.AddToken(new soul::ast::common::Token(SOLUTION, "SOLUTION", "'Solution'"));
        tokens.AddToken(new soul::ast::common::Token(FILE_, "FILE_", "'File'"));
        tokens.AddToken(new soul::ast::common::Token(PIPE, "PIPE", "'|'"));
        tokens.AddToken(new soul::ast::common::Token(DOT, "DOT", "'.'"));
        tokens.AddToken(new soul::ast::common::Token(COMMA, "COMMA", "','"));
        tokens.AddToken(new soul::ast::common::Token(ASSIGN, "ASSIGN", "'='"));
        tokens.AddToken(new soul::ast::common::Token(GUID, "GUID", "GUID"));
        tokens.AddToken(new soul::ast::common::Token(PATH, "PATH", "path"));
        tokens.AddToken(new soul::ast::common::Token(STRING, "STRING", "string"));
        tokens.AddToken(new soul::ast::common::Token(NUMBER, "NUMBER", "number"));
        tokens.AddToken(new soul::ast::common::Token(TRUE, "TRUE", "'True'"));
        tokens.AddToken(new soul::ast::common::Token(FALSE, "FALSE", "'False'"));
        tokens.AddToken(new soul::ast::common::Token(LPAREN, "LPAREN", "'('"));
        tokens.AddToken(new soul::ast::common::Token(RPAREN, "RPAREN", "')'"));
        tokens.AddToken(new soul::ast::common::Token(ID, "ID", "identifier"));
        tokens.AddToken(new soul::ast::common::Token(CONFIG, "CONFIG", "config"));
        tokens.AddToken(new soul::ast::common::Token(GUID_CONFIG, "GUID_CONFIG", "GUID config"));
        tokens.AddToken(new soul::ast::common::Token(FORMAT, "FORMAT", "'Format'"));
        tokens.AddToken(new soul::ast::common::Token(VERSION, "VERSION", "'Version'"));
        tokens.AddToken(new soul::ast::common::Token(VISUAL_STUDIO_VERSION, "VISUAL_STUDIO_VERSION", "'VisualStudioVersion'"));
        tokens.AddToken(new soul::ast::common::Token(MINIMUM_VERSION, "MINIMUM_VERSION", "'MinimumVisualStudioVersion'"));
        tokens.AddToken(new soul::ast::common::Token(PROJECT, "PROJECT", "'Project'"));
        tokens.AddToken(new soul::ast::common::Token(END_PROJECT, "END_PROJECT", "'EndProject'"));
        tokens.AddToken(new soul::ast::common::Token(PROJECT_SECTION, "PROJECT_SECTION", "'ProjectSection'"));
        tokens.AddToken(new soul::ast::common::Token(END_PROJECT_SECTION, "END_PROJECT_SECTION", "'EndProjectSection'"));
        tokens.AddToken(new soul::ast::common::Token(SOLUTION_ITEMS, "SOLUTION_ITEMS", "'SolutionItems'"));
        tokens.AddToken(new soul::ast::common::Token(PREPROJECT, "PREPROJECT", "'preProject'"));
        tokens.AddToken(new soul::ast::common::Token(POSTPROJECT, "POSTPROJECT", "'postProject'"));
        tokens.AddToken(new soul::ast::common::Token(PROJECT_DEPENDENCIES, "PROJECT_DEPENDENCIES", "'ProjectDependencies'"));
        tokens.AddToken(new soul::ast::common::Token(GLOBAL, "GLOBAL", "'Global'"));
        tokens.AddToken(new soul::ast::common::Token(END_GLOBAL, "END_GLOBAL", "'EndGlobal'"));
        tokens.AddToken(new soul::ast::common::Token(GLOBAL_SECTION, "GLOBAL_SECTION", "'GlobalSection'"));
        tokens.AddToken(new soul::ast::common::Token(END_GLOBAL_SECTION, "END_GLOBAL_SECTION", "'EndGlobalSection'"));
        tokens.AddToken(new soul::ast::common::Token(SOLUTION_CONFIGURATION_PLATFORMS, "SOLUTION_CONFIGURATION_PLATFORMS", "'SolutionConfigurationPlatforms'"));
        tokens.AddToken(new soul::ast::common::Token(PROJECT_CONFIGURATION_PLATFORMS, "PROJECT_CONFIGURATION_PLATFORMS", "'ProjectConfigurationPlatforms'"));
        tokens.AddToken(new soul::ast::common::Token(SOLUTION_PROPERTIES, "SOLUTION_PROPERTIES", "'SolutionProperties'"));
        tokens.AddToken(new soul::ast::common::Token(HIDE_SOLUTION_NODE, "HIDE_SOLUTION_NODE", "'HideSolutionNode'"));
        tokens.AddToken(new soul::ast::common::Token(PRESOLUTION, "PRESOLUTION", "'preSolution'"));
        tokens.AddToken(new soul::ast::common::Token(POSTSOLUTION, "POSTSOLUTION", "'postSolution'"));
        tokens.AddToken(new soul::ast::common::Token(SOLUTION_GUID, "SOLUTION_GUID", "'SolutionGuid'"));
        tokens.AddToken(new soul::ast::common::Token(EXTENSIBILITY_GLOBALS, "EXTENSIBILITY_GLOBALS", "'ExtensibilityGlobals'"));
        tokens.AddToken(new soul::ast::common::Token(NESTED_PROJECTS, "NESTED_PROJECTS", "'NestedProjects'"));
    }
    return &tokens;
}

solution_file_lexer_Variables::solution_file_lexer_Variables() :
    inSolutionItems(), inSolutionConfigurationPlatforms(), inProjectConfigurationPlatforms()
{
}

std::mutex mtx;

std::mutex& MakeLexerMtx() { return mtx; }

template<>
soul::lexer::KeywordMap<char>* GetKeywords<char>()
{
    static const soul::lexer::Keyword<char> keywords[] = {
         { "Microsoft", MICROSOFT },
         { "Visual", VISUAL },
         { "Studio", STUDIO },
         { "Solution", SOLUTION },
         { "File", FILE_ },
         { "Format", FORMAT },
         { "Version", VERSION },
         { "VisualStudioVersion", VISUAL_STUDIO_VERSION },
         { "MinimumVisualStudioVersion", MINIMUM_VERSION },
         { "Project", PROJECT },
         { "EndProject", END_PROJECT },
         { "ProjectSection", PROJECT_SECTION },
         { "EndProjectSection", END_PROJECT_SECTION },
         { "SolutionItems", SOLUTION_ITEMS },
         { "preProject", PREPROJECT },
         { "postProject", POSTPROJECT },
         { "ProjectDependencies", PROJECT_DEPENDENCIES },
         { "Global", GLOBAL },
         { "EndGlobal", END_GLOBAL },
         { "GlobalSection", GLOBAL_SECTION },
         { "EndGlobalSection", END_GLOBAL_SECTION },
         { "SolutionConfigurationPlatforms", SOLUTION_CONFIGURATION_PLATFORMS },
         { "ProjectConfigurationPlatforms", PROJECT_CONFIGURATION_PLATFORMS },
         { "SolutionProperties", SOLUTION_PROPERTIES },
         { "HideSolutionNode", HIDE_SOLUTION_NODE },
         { "preSolution", PRESOLUTION },
         { "postSolution", POSTSOLUTION },
         { "SolutionGuid", SOLUTION_GUID },
         { "ExtensibilityGlobals", EXTENSIBILITY_GLOBALS },
         { "NestedProjects", NESTED_PROJECTS },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()
{
    static const soul::lexer::Keyword<char8_t> keywords[] = {
         { u8"Microsoft", MICROSOFT },
         { u8"Visual", VISUAL },
         { u8"Studio", STUDIO },
         { u8"Solution", SOLUTION },
         { u8"File", FILE_ },
         { u8"Format", FORMAT },
         { u8"Version", VERSION },
         { u8"VisualStudioVersion", VISUAL_STUDIO_VERSION },
         { u8"MinimumVisualStudioVersion", MINIMUM_VERSION },
         { u8"Project", PROJECT },
         { u8"EndProject", END_PROJECT },
         { u8"ProjectSection", PROJECT_SECTION },
         { u8"EndProjectSection", END_PROJECT_SECTION },
         { u8"SolutionItems", SOLUTION_ITEMS },
         { u8"preProject", PREPROJECT },
         { u8"postProject", POSTPROJECT },
         { u8"ProjectDependencies", PROJECT_DEPENDENCIES },
         { u8"Global", GLOBAL },
         { u8"EndGlobal", END_GLOBAL },
         { u8"GlobalSection", GLOBAL_SECTION },
         { u8"EndGlobalSection", END_GLOBAL_SECTION },
         { u8"SolutionConfigurationPlatforms", SOLUTION_CONFIGURATION_PLATFORMS },
         { u8"ProjectConfigurationPlatforms", PROJECT_CONFIGURATION_PLATFORMS },
         { u8"SolutionProperties", SOLUTION_PROPERTIES },
         { u8"HideSolutionNode", HIDE_SOLUTION_NODE },
         { u8"preSolution", PRESOLUTION },
         { u8"postSolution", POSTSOLUTION },
         { u8"SolutionGuid", SOLUTION_GUID },
         { u8"ExtensibilityGlobals", EXTENSIBILITY_GLOBALS },
         { u8"NestedProjects", NESTED_PROJECTS },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()
{
    static const soul::lexer::Keyword<char16_t> keywords[] = {
         { u"Microsoft", MICROSOFT },
         { u"Visual", VISUAL },
         { u"Studio", STUDIO },
         { u"Solution", SOLUTION },
         { u"File", FILE_ },
         { u"Format", FORMAT },
         { u"Version", VERSION },
         { u"VisualStudioVersion", VISUAL_STUDIO_VERSION },
         { u"MinimumVisualStudioVersion", MINIMUM_VERSION },
         { u"Project", PROJECT },
         { u"EndProject", END_PROJECT },
         { u"ProjectSection", PROJECT_SECTION },
         { u"EndProjectSection", END_PROJECT_SECTION },
         { u"SolutionItems", SOLUTION_ITEMS },
         { u"preProject", PREPROJECT },
         { u"postProject", POSTPROJECT },
         { u"ProjectDependencies", PROJECT_DEPENDENCIES },
         { u"Global", GLOBAL },
         { u"EndGlobal", END_GLOBAL },
         { u"GlobalSection", GLOBAL_SECTION },
         { u"EndGlobalSection", END_GLOBAL_SECTION },
         { u"SolutionConfigurationPlatforms", SOLUTION_CONFIGURATION_PLATFORMS },
         { u"ProjectConfigurationPlatforms", PROJECT_CONFIGURATION_PLATFORMS },
         { u"SolutionProperties", SOLUTION_PROPERTIES },
         { u"HideSolutionNode", HIDE_SOLUTION_NODE },
         { u"preSolution", PRESOLUTION },
         { u"postSolution", POSTSOLUTION },
         { u"SolutionGuid", SOLUTION_GUID },
         { u"ExtensibilityGlobals", EXTENSIBILITY_GLOBALS },
         { u"NestedProjects", NESTED_PROJECTS },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()
{
    static const soul::lexer::Keyword<char32_t> keywords[] = {
         { U"Microsoft", MICROSOFT },
         { U"Visual", VISUAL },
         { U"Studio", STUDIO },
         { U"Solution", SOLUTION },
         { U"File", FILE_ },
         { U"Format", FORMAT },
         { U"Version", VERSION },
         { U"VisualStudioVersion", VISUAL_STUDIO_VERSION },
         { U"MinimumVisualStudioVersion", MINIMUM_VERSION },
         { U"Project", PROJECT },
         { U"EndProject", END_PROJECT },
         { U"ProjectSection", PROJECT_SECTION },
         { U"EndProjectSection", END_PROJECT_SECTION },
         { U"SolutionItems", SOLUTION_ITEMS },
         { U"preProject", PREPROJECT },
         { U"postProject", POSTPROJECT },
         { U"ProjectDependencies", PROJECT_DEPENDENCIES },
         { U"Global", GLOBAL },
         { U"EndGlobal", END_GLOBAL },
         { U"GlobalSection", GLOBAL_SECTION },
         { U"EndGlobalSection", END_GLOBAL_SECTION },
         { U"SolutionConfigurationPlatforms", SOLUTION_CONFIGURATION_PLATFORMS },
         { U"ProjectConfigurationPlatforms", PROJECT_CONFIGURATION_PLATFORMS },
         { U"SolutionProperties", SOLUTION_PROPERTIES },
         { U"HideSolutionNode", HIDE_SOLUTION_NODE },
         { U"preSolution", PRESOLUTION },
         { U"postSolution", POSTSOLUTION },
         { U"SolutionGuid", SOLUTION_GUID },
         { U"ExtensibilityGlobals", EXTENSIBILITY_GLOBALS },
         { U"NestedProjects", NESTED_PROJECTS },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace solution_file::lexer
