// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.build.project_file;

import otava.build_project;
import otava.symbols;
import soul.xml.dom;
import util.code.formatter;
import util.error;
import util.uuid;
import util.path;

namespace otava::build {

std::expected<bool, int> MakeResourceFile(const std::string& resourceFilePath, const std::string& classIndexFilePath)
{
    std::ofstream resourceFile(resourceFilePath);
    if (!resourceFile) return std::unexpected<int>(util::AllocateError("could not create file '" + resourceFilePath + "'"));
    util::CodeFormatter formatter(resourceFile);
    formatter.WriteLine("CLASS_INDEX RCDATA \"" + classIndexFilePath + "\"");
    return std::expected<bool, int>(true);
}

std::expected<bool, int> MakeProjectFile(Project* project, const std::string& projectFilePath, const std::vector<std::string>& asmFiles, 
    const std::vector<std::string>& cppFiles, const std::vector<std::string>& resourceFiles, const std::string& libraryDirs, 
    const std::vector<Project*>& referencedProjects, const std::string& config, int optLevel, const std::string& classIndexFilePath, 
    ProjectTarget target, bool verbose)
{
    std::string references;
    if (!referencedProjects.empty())
    {
        for (Project* referencedProject : referencedProjects)
        {
            if (config == "release")
            {
                std::string releaseReference = util::Path::Combine(util::Path::Combine(util::Path::Combine(referencedProject->Root(), config),
                    std::to_string(otava::symbols::GetOptLevel(optLevel, true))), referencedProject->Name() + ".lib");
                references.append(";").append(releaseReference);
            }
            else
            {
                std::string debugReference = util::Path::Combine(util::Path::Combine(referencedProject->Root(), config), referencedProject->Name() + ".lib");
                references.append(";").append(debugReference);
            }
        }
    }
    if (target == ProjectTarget::program && !classIndexFilePath.empty())
    {
        std::expected<bool, int> rv = MakeResourceFile(util::Path::Combine(util::Path::GetDirectoryName(projectFilePath), "class_index.rc"), classIndexFilePath);
        if (!rv) return rv;
    }
    util::uuid projectUuid = util::random_uuid();

    soul::xml::Document projectDoc;
    soul::xml::Element* rootElement = soul::xml::MakeElement("Project");
    rootElement->SetAttribute("DefaultTargets", "Build");
    rootElement->SetAttribute("xmlns", "http://schemas.microsoft.com/developer/msbuild/2003");
    auto rv = projectDoc.AppendChild(rootElement);
    if (!rv) return rv;
    soul::xml::Element* configurationItemGroup = soul::xml::MakeElement("ItemGroup");
    configurationItemGroup->SetAttribute("Label", "ProjectConfigurations");

    soul::xml::Element* projectDebugConfig = soul::xml::MakeElement("ProjectConfiguration");
    projectDebugConfig->SetAttribute("Include", "Debug|x64");
    soul::xml::Element* debugConfig = soul::xml::MakeElement("Configuration");
    soul::xml::Text* debugText = soul::xml::MakeText("Debug");
    rv = debugConfig->AppendChild(debugText);
    if (!rv) return rv;
    rv = projectDebugConfig->AppendChild(debugConfig);
    if (!rv) return rv;
    soul::xml::Element* debugPlatform = soul::xml::MakeElement("Platform");
    soul::xml::Text* debugPlatformText = soul::xml::MakeText("x64");
    rv = debugPlatform->AppendChild(debugPlatformText);
    if (!rv) return rv;
    rv = projectDebugConfig->AppendChild(debugPlatform);
    if (!rv) return rv;
    rv = configurationItemGroup->AppendChild(projectDebugConfig);
    if (!rv) return rv;

    soul::xml::Element* projectReleaseConfig = soul::xml::MakeElement("ProjectConfiguration");
    projectReleaseConfig->SetAttribute("Include", "Release|x64");
    soul::xml::Element* releaseConfig = soul::xml::MakeElement("Configuration");
    soul::xml::Text* releaseText = soul::xml::MakeText("Release");
    rv = releaseConfig->AppendChild(releaseText);
    if (!rv) return rv;
    rv = projectReleaseConfig->AppendChild(releaseConfig);
    if (!rv) return rv;
    soul::xml::Element* releasePlatform = soul::xml::MakeElement("Platform");
    soul::xml::Text* releasePlatformText = soul::xml::MakeText("x64");
    rv = releasePlatform->AppendChild(releasePlatformText);
    if (!rv) return rv;
    rv = projectReleaseConfig->AppendChild(releasePlatform);
    if (!rv) return rv;
    rv = configurationItemGroup->AppendChild(projectReleaseConfig);
    if (!rv) return rv;

    rv = rootElement->AppendChild(configurationItemGroup);
    if (!rv) return rv;

    soul::xml::Element* globalsPropertyGroup = soul::xml::MakeElement("PropertyGroup");
    globalsPropertyGroup->SetAttribute("Label", "Globals");
    soul::xml::Element* vcProjectVersion = soul::xml::MakeElement("VCProjectVersion");
    soul::xml::Text* vcProjectVersionText = soul::xml::MakeText("16.0");
    rv = vcProjectVersion->AppendChild(vcProjectVersionText);
    if (!rv) return rv;
    rv = globalsPropertyGroup->AppendChild(vcProjectVersion);
    if (!rv) return rv;
    soul::xml::Element* keyword = soul::xml::MakeElement("Keyword");
    soul::xml::Text* keywordText = soul::xml::MakeText("Win32Proj");
    rv = keyword->AppendChild(keywordText);
    if (!rv) return rv;
    rv =  globalsPropertyGroup->AppendChild(keyword);
    if (!rv) return rv;
    soul::xml::Element* projectGuid = soul::xml::MakeElement("ProjectGuid");
    soul::xml::Text* projectGuildText = soul::xml::MakeText(util::ToString(projectUuid));
    rv = projectGuid->AppendChild(projectGuildText);
    if (!rv) return rv;
    rv = globalsPropertyGroup->AppendChild(projectGuid);
    if (!rv) return rv;
    soul::xml::Element* rootNamespace = soul::xml::MakeElement("RootNamespace");
    soul::xml::Text* rootNamespaceText = soul::xml::MakeText(project->Name());
    rv = rootNamespace->AppendChild(rootNamespaceText);
    if (!rv) return rv;
    rv = globalsPropertyGroup->AppendChild(rootNamespace);
    if (!rv) return rv;
    soul::xml::Element* targetPlatformVersion = soul::xml::MakeElement("WindowsTargetPlatformVersion");
    soul::xml::Text* targetPlatformVersionText = soul::xml::MakeText("10.0");
    rv = targetPlatformVersion->AppendChild(targetPlatformVersionText);
    if (!rv) return rv;
    rv = globalsPropertyGroup->AppendChild(targetPlatformVersion);
    if (!rv) return rv;

    rv = rootElement->AppendChild(globalsPropertyGroup);
    if (!rv) return rv;

    soul::xml::Element* importProject = soul::xml::MakeElement("Import");
    importProject->SetAttribute("Project", "$(VCTargetsPath)\\Microsoft.Cpp.Default.props");
    rv = rootElement->AppendChild(importProject);
    if (!rv) return rv;

    soul::xml::Element* debugPropertyGroup = soul::xml::MakeElement("PropertyGroup");
    debugPropertyGroup->SetAttribute("Condition", "'$(Configuration)|$(Platform)'=='Debug|x64'");
    debugPropertyGroup->SetAttribute("Label", "Configuration");
    soul::xml::Element* debugConfigurationType = soul::xml::MakeElement("ConfigurationType");
    if (target == ProjectTarget::program)
    {
        soul::xml::Text* debugConfigurationTypeText = soul::xml::MakeText("Application");
        rv = debugConfigurationType->AppendChild(debugConfigurationTypeText);
        if (!rv) return rv;
        rv = debugPropertyGroup->AppendChild(debugConfigurationType);
        if (!rv) return rv;
    }
    else if (target == ProjectTarget::library)
    {
        soul::xml::Text* debugConfigurationTypeText = soul::xml::MakeText("StaticLibrary");
        rv = debugConfigurationType->AppendChild(debugConfigurationTypeText);
        if (!rv) return rv;
        rv = debugPropertyGroup->AppendChild(debugConfigurationType);
        if (!rv) return rv;
    }
    soul::xml::Element* debugUseDebugLibraries = soul::xml::MakeElement("UseDebugLibraries");
    soul::xml::Text* debugUseDebugLibrariesText = soul::xml::MakeText("true");
    rv = debugUseDebugLibraries->AppendChild(debugUseDebugLibrariesText);
    if (!rv) return rv;
    rv = debugPropertyGroup->AppendChild(debugUseDebugLibraries);
    if (!rv) return rv;
    soul::xml::Element* debugPlatformToolset = soul::xml::MakeElement("PlatformToolset");
    soul::xml::Text* debugPlatformToolsetText = soul::xml::MakeText("v143");
    rv = debugPlatformToolset->AppendChild(debugPlatformToolsetText);
    if (!rv) return rv;
    rv = debugPropertyGroup->AppendChild(debugPlatformToolset);
    if (!rv) return rv;
    soul::xml::Element* debugCharacterSet = soul::xml::MakeElement("CharacterSet");
    soul::xml::Text* debugCharacterSetText = soul::xml::MakeText("Unicode");
    rv = debugCharacterSet->AppendChild(debugCharacterSetText);
    if (!rv) return rv;
    rv = debugPropertyGroup->AppendChild(debugCharacterSet);
    if (!rv) return rv;
    rv = rootElement->AppendChild(debugPropertyGroup);
    if (!rv) return rv;

    soul::xml::Element* releasePropertyGroup = soul::xml::MakeElement("PropertyGroup");
    releasePropertyGroup->SetAttribute("Condition", "'$(Configuration)|$(Platform)'=='Release|x64'");
    releasePropertyGroup->SetAttribute("Label", "Configuration");
    soul::xml::Element* releaseConfigurationType = soul::xml::MakeElement("ConfigurationType");
    if (target == ProjectTarget::program)
    {
        soul::xml::Text* releaseConfigurationTypeText = soul::xml::MakeText("Application");
        rv = releaseConfigurationType->AppendChild(releaseConfigurationTypeText);
        if (!rv) return rv;
        rv = releasePropertyGroup->AppendChild(releaseConfigurationType);
        if (!rv) return rv;
    }
    else if (target == ProjectTarget::library)
    {
        soul::xml::Text* releaseConfigurationTypeText = soul::xml::MakeText("StaticLibrary");
        rv = releaseConfigurationType->AppendChild(releaseConfigurationTypeText);
        if (!rv) return rv;
        rv = releasePropertyGroup->AppendChild(releaseConfigurationType);
        if (!rv) return rv;
    }
    soul::xml::Element* releaseUseDebugLibraries = soul::xml::MakeElement("UseDebugLibraries");
    soul::xml::Text* releaseUseDebugLibrariesText = soul::xml::MakeText("false");
    rv = releaseUseDebugLibraries->AppendChild(releaseUseDebugLibrariesText);
    if (!rv) return rv;
    rv = releasePropertyGroup->AppendChild(releaseUseDebugLibraries);
    if (!rv) return rv;
    soul::xml::Element* releasePlatformToolset = soul::xml::MakeElement("PlatformToolset");
    soul::xml::Text* releasePlatformToolsetText = soul::xml::MakeText("v143");
    rv = releasePlatformToolset->AppendChild(releasePlatformToolsetText);
    if (!rv) return rv;
    rv = releasePropertyGroup->AppendChild(releasePlatformToolset);
    if (!rv) return rv;
    soul::xml::Element* releaseCharacterSet = soul::xml::MakeElement("CharacterSet");
    soul::xml::Text* releaseCharacterSetText = soul::xml::MakeText("Unicode");
    rv = releaseCharacterSet->AppendChild(releaseCharacterSetText);
    if (!rv) return rv;
    rv = releasePropertyGroup->AppendChild(releaseCharacterSet);
    if (!rv) return rv;
    soul::xml::Element* wholeProgramOptimization = soul::xml::MakeElement("WholeProgramOptimization");
    soul::xml::Text* wholeProgramOptimizationText = soul::xml::MakeText("true");
    rv = wholeProgramOptimization->AppendChild(wholeProgramOptimizationText);
    if (!rv) return rv;
    rv = releasePropertyGroup->AppendChild(wholeProgramOptimization);
    if (!rv) return rv;
    rv = rootElement->AppendChild(releasePropertyGroup);
    if (!rv) return rv;

    soul::xml::Element* importCppProject = soul::xml::MakeElement("Import");
    importCppProject->SetAttribute("Project", "$(VCTargetsPath)\\Microsoft.Cpp.props");
    rv = rootElement->AppendChild(importCppProject);
    if (!rv) return rv;

    soul::xml::Element* masmGroup = soul::xml::MakeElement("ImportGroup");
    masmGroup->SetAttribute("Label", "ExtensionSettings");
    soul::xml::Element* masmProps = soul::xml::MakeElement("Import");
    masmProps->SetAttribute("Project", "$(VCTargetsPath)\\BuildCustomizations\\masm.props");
    rv = masmGroup->AppendChild(masmProps);
    if (!rv) return rv;
    rv = rootElement->AppendChild(masmGroup);
    if (!rv) return rv;

    soul::xml::Element* importSharedGroup = soul::xml::MakeElement("ImportGroup");
    importSharedGroup->SetAttribute("Label", "Shared");
    rv = rootElement->AppendChild(importSharedGroup);
    if (!rv) return rv;

    soul::xml::Element* debugImportPropertySheets = soul::xml::MakeElement("ImportGroup");
    debugImportPropertySheets->SetAttribute("Label", "PropertySheets");
    debugImportPropertySheets->SetAttribute("Condition", "'$(Configuration)|$(Platform)'=='Debug|x64'");
    soul::xml::Element* debugPropertySheet = soul::xml::MakeElement("Import");
    debugPropertySheet->SetAttribute("Project", "$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props");
    debugPropertySheet->SetAttribute("Condition", "exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')");
    debugPropertySheet->SetAttribute("Label", "LocalAppDataPlatform");
    rv = debugImportPropertySheets->AppendChild(debugPropertySheet);
    if (!rv) return rv;
    rv = rootElement->AppendChild(debugImportPropertySheets);
    if (!rv) return rv;

    soul::xml::Element* releaseImportPropertySheets = soul::xml::MakeElement("ImportGroup");
    releaseImportPropertySheets->SetAttribute("Label", "PropertySheets");
    releaseImportPropertySheets->SetAttribute("Condition", "'$(Configuration)|$(Platform)'=='Release|x64'");
    soul::xml::Element* releasePropertySheet = soul::xml::MakeElement("Import");
    releasePropertySheet->SetAttribute("Project", "$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props");
    releasePropertySheet->SetAttribute("Condition", "exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')");
    releasePropertySheet->SetAttribute("Label", "LocalAppDataPlatform");
    rv = releaseImportPropertySheets->AppendChild(releasePropertySheet);
    if (!rv) return rv;
    rv = rootElement->AppendChild(releaseImportPropertySheets);
    if (!rv) return rv;

    soul::xml::Element* userMacros = soul::xml::MakeElement("PropertyGroup");
    userMacros->SetAttribute("Label", "UserMacros");
    rv = rootElement->AppendChild(userMacros);
    if (!rv) return rv;

    soul::xml::Element* debugOutDirPropertyGroup = soul::xml::MakeElement("PropertyGroup");
    debugOutDirPropertyGroup->SetAttribute("Condition", "'$(Configuration)|$(Platform)' == 'Debug|x64'");
    soul::xml::Element* debugOutDir = soul::xml::MakeElement("OutDir");
    soul::xml::Text* debugOutDirText = soul::xml::MakeText("./");
    rv = debugOutDir->AppendChild(debugOutDirText);
    if (!rv) return rv;
    rv = debugOutDirPropertyGroup->AppendChild(debugOutDir);
    if (!rv) return rv;
    rv = rootElement->AppendChild(debugOutDirPropertyGroup);
    if (!rv) return rv;

    soul::xml::Element* releaseOutDirPropertyGroup = soul::xml::MakeElement("PropertyGroup");
    releaseOutDirPropertyGroup->SetAttribute("Condition", "'$(Configuration)|$(Platform)'=='Release|x64'");
    soul::xml::Element* releaseOutDir = soul::xml::MakeElement("OutDir");
    soul::xml::Text* releaseOutDirText = soul::xml::MakeText("./");
    rv = releaseOutDir->AppendChild(releaseOutDirText);
    if (!rv) return rv;
    rv = releaseOutDirPropertyGroup->AppendChild(releaseOutDir);
    if (!rv) return rv;
    rv = rootElement->AppendChild(releaseOutDirPropertyGroup);
    if (!rv) return rv;

    soul::xml::Element* debugItemDefinitionGroup = soul::xml::MakeElement("ItemDefinitionGroup");
    debugItemDefinitionGroup->SetAttribute("Condition", "'$(Configuration)|$(Platform)'=='Debug|x64'");
    soul::xml::Element* debugClCompile = soul::xml::MakeElement("ClCompile");
    soul::xml::Element* debugWarningLevel = soul::xml::MakeElement("WarningLevel");
    soul::xml::Text* debugWarningLevelText = soul::xml::MakeText("Level3");
    rv = debugWarningLevel->AppendChild(debugWarningLevelText);
    if (!rv) return rv;
    rv = debugClCompile->AppendChild(debugWarningLevel);
    if (!rv) return rv;
    soul::xml::Element* debugSdlCheck = soul::xml::MakeElement("SDLCheck");
    soul::xml::Text* debugSdlCheckText = soul::xml::MakeText("true");
    rv = debugSdlCheck->AppendChild(debugSdlCheckText);
    if (!rv) return rv;
    rv = debugClCompile->AppendChild(debugSdlCheck);
    if (!rv) return rv;
    soul::xml::Element* debugPreprocessor = soul::xml::MakeElement("PreprocessorDefinitions");
    soul::xml::Text* debugPreprocessorText = soul::xml::MakeText("_DEBUG;_CONSOLE;%(PreprocessorDefinitions)");
    rv = debugPreprocessor->AppendChild(debugPreprocessorText);
    if (!rv) return rv;
    rv = debugClCompile->AppendChild(debugPreprocessor);
    if (!rv) return rv;
    soul::xml::Element* debugConformanceMode = soul::xml::MakeElement("ConformanceMode");
    soul::xml::Text* debugConformanceModeText = soul::xml::MakeText("true");
    rv = debugConformanceMode->AppendChild(debugConformanceModeText);
    if (!rv) return rv;
    rv = debugClCompile->AppendChild(debugConformanceMode);
    if (!rv) return rv;
    rv = debugItemDefinitionGroup->AppendChild(debugClCompile);
    if (!rv) return rv;
    soul::xml::Element* debugLink = soul::xml::MakeElement("Link");
    soul::xml::Element* debugSubSystem = soul::xml::MakeElement("SubSystem");
    if (target == ProjectTarget::program)
    {
        soul::xml::Text* debugSubSystemText = soul::xml::MakeText("Console");
        rv = debugSubSystem->AppendChild(debugSubSystemText);
        if (!rv) return rv;
    }
    rv = debugLink->AppendChild(debugSubSystem);
    if (!rv) return rv;
    soul::xml::Element* debugGenDebugInfo = soul::xml::MakeElement("GenerateDebugInformation");
    soul::xml::Text* debugGenDebugInfoText = soul::xml::MakeText("true");
    rv = debugGenDebugInfo->AppendChild(debugGenDebugInfoText);
    if (!rv) return rv;
    rv = debugLink->AppendChild(debugGenDebugInfo);
    if (!rv) return rv;
    if (target == ProjectTarget::program)
    {
        soul::xml::Element* debugLibraryDirs = soul::xml::MakeElement("AdditionalLibraryDirectories");
        soul::xml::Text* debugLibraryDirsText = soul::xml::MakeText(libraryDirs);
        rv = debugLibraryDirs->AppendChild(debugLibraryDirsText);
        if (!rv) return rv;
        rv = debugLink->AppendChild(debugLibraryDirs);
        if (!rv) return rv;
        soul::xml::Element* debugDependencies = soul::xml::MakeElement("AdditionalDependencies");
        soul::xml::Text* debugDependenciesText = soul::xml::MakeText("std.lib;ortd.lib;utild.lib" + references);
        rv = debugDependencies->AppendChild(debugDependenciesText);
        if (!rv) return rv;
        rv = debugLink->AppendChild(debugDependencies);
        if (!rv) return rv;
    }
    rv = debugItemDefinitionGroup->AppendChild(debugLink);
    if (!rv) return rv;

    rv = rootElement->AppendChild(debugItemDefinitionGroup);
    if (!rv) return rv;

    soul::xml::Element* releaseItemDefinitionGroup = soul::xml::MakeElement("ItemDefinitionGroup");
    releaseItemDefinitionGroup->SetAttribute("Condition", "'$(Configuration)|$(Platform)'=='Release|x64'");
    soul::xml::Element* releaseClCompile = soul::xml::MakeElement("ClCompile");
    soul::xml::Element* releaseWarningLevel = soul::xml::MakeElement("WarningLevel");
    soul::xml::Text* releaseWarningLevelText = soul::xml::MakeText("Level3");
    rv = releaseWarningLevel->AppendChild(releaseWarningLevelText);
    if (!rv) return rv;
    rv = releaseClCompile->AppendChild(releaseWarningLevel);
    if (!rv) return rv;
    soul::xml::Element* releaseFunctionLevelLinking = soul::xml::MakeElement("FunctionLevelLinking");
    soul::xml::Text* releaseFunctionLevelLinkingText = soul::xml::MakeText("true");
    rv = releaseFunctionLevelLinking->AppendChild(releaseFunctionLevelLinkingText);
    if (!rv) return rv;
    rv = releaseClCompile->AppendChild(releaseFunctionLevelLinking);
    if (!rv) return rv;
    soul::xml::Element* releaseIntrinsics = soul::xml::MakeElement("IntrinsicFunctions");
    soul::xml::Text* releaseIntrinsicsText = soul::xml::MakeText("true");
    rv = releaseIntrinsics->AppendChild(releaseIntrinsicsText);
    if (!rv) return rv;
    rv = releaseClCompile->AppendChild(releaseIntrinsics);
    if (!rv) return rv;
    soul::xml::Element* releaseSdlCheck = soul::xml::MakeElement("SDLCheck");
    soul::xml::Text* releaseSdlCheckText = soul::xml::MakeText("true");
    rv = releaseSdlCheck->AppendChild(releaseSdlCheckText);
    if (!rv) return rv;
    rv = releaseClCompile->AppendChild(releaseSdlCheck);
    if (!rv) return rv;
    soul::xml::Element* releasePreprocessor = soul::xml::MakeElement("PreprocessorDefinitions");
    soul::xml::Text* releasePreprocessorText = soul::xml::MakeText("NDEBUG;_CONSOLE;%(PreprocessorDefinitions)");
    rv = releasePreprocessor->AppendChild(releasePreprocessorText);
    if (!rv) return rv;
    rv = releaseClCompile->AppendChild(releasePreprocessor);
    if (!rv) return rv;
    soul::xml::Element* releaseConformanceMode = soul::xml::MakeElement("ConformanceMode");
    soul::xml::Text* releaseConformanceModeText = soul::xml::MakeText("true");
    rv = releaseConformanceMode->AppendChild(releaseConformanceModeText);
    if (!rv) return rv;
    rv = releaseClCompile->AppendChild(releaseConformanceMode);
    if (!rv) return rv;
    rv = releaseItemDefinitionGroup->AppendChild(releaseClCompile);
    if (!rv) return rv;
    soul::xml::Element* releaseLink = soul::xml::MakeElement("Link");
    soul::xml::Element* releaseSubSystem = soul::xml::MakeElement("SubSystem");
    if (target == ProjectTarget::program)
    {
        soul::xml::Text* releaseSubSystemText = soul::xml::MakeText("Console");
        rv = releaseSubSystem->AppendChild(releaseSubSystemText);
        if (!rv) return rv;
    }
    rv = releaseLink->AppendChild(releaseSubSystem);
    if (!rv) return rv;
    soul::xml::Element* releaseComdatFolding = soul::xml::MakeElement("EnableCOMDATFolding");
    soul::xml::Text* releaseComdatFoldingText = soul::xml::MakeText("true");
    rv = releaseComdatFolding->AppendChild(releaseComdatFoldingText);
    if (!rv) return rv;
    rv = releaseLink->AppendChild(releaseComdatFolding);
    if (!rv) return rv;
    soul::xml::Element* releaseOptimizeRefs = soul::xml::MakeElement("OptimizeReferences");
    soul::xml::Text* releaseOptimizeRefsText = soul::xml::MakeText("true");
    rv = releaseOptimizeRefs->AppendChild(releaseOptimizeRefsText);
    if (!rv) return rv;
    rv = releaseLink->AppendChild(releaseOptimizeRefs);
    if (!rv) return rv;
    soul::xml::Element* releaseGenDebugInfo = soul::xml::MakeElement("GenerateDebugInformation");
    soul::xml::Text* releaseGenDebugInfoText = soul::xml::MakeText("true");
    rv = releaseGenDebugInfo->AppendChild(releaseGenDebugInfoText);
    if (!rv) return rv;
    rv = releaseLink->AppendChild(releaseGenDebugInfo);
    if (!rv) return rv;
    if (target == ProjectTarget::program)
    {
        soul::xml::Element* releaseLibraryDirs = soul::xml::MakeElement("AdditionalLibraryDirectories");
        soul::xml::Text* releaseLibraryDirsText = soul::xml::MakeText(libraryDirs);
        rv = releaseLibraryDirs->AppendChild(releaseLibraryDirsText);
        if (!rv) return rv;
        rv = releaseLink->AppendChild(releaseLibraryDirs);
        if (!rv) return rv;
        soul::xml::Element* releaseDependencies = soul::xml::MakeElement("AdditionalDependencies");
        soul::xml::Text* releaseDepenciesText = soul::xml::MakeText("std.lib;ort.lib;util.lib" + references);
        rv = releaseDependencies->AppendChild(releaseDepenciesText);
        if (!rv) return rv;
        rv = releaseLink->AppendChild(releaseDependencies);
        if (!rv) return rv;
    }
    rv = releaseItemDefinitionGroup->AppendChild(releaseLink);
    if (!rv) return rv;

    rv = rootElement->AppendChild(releaseItemDefinitionGroup);
    if (!rv) return rv;

    soul::xml::Element* masmItemGroup = soul::xml::MakeElement("ItemGroup");
    for (const auto& asmFile : asmFiles)
    {
        soul::xml::Element* masm = soul::xml::MakeElement("MASM");
        masm->SetAttribute("Include", asmFile);
        rv = masmItemGroup->AppendChild(masm);
        if (!rv) return rv;
    }
    rv = rootElement->AppendChild(masmItemGroup);
    if (!rv) return rv;

    soul::xml::Element* clItemGroup = soul::xml::MakeElement("ItemGroup");
    for (const auto& cppFile : cppFiles)
    {
        soul::xml::Element* clCompile = soul::xml::MakeElement("ClCompile");
        clCompile->SetAttribute("Include", cppFile);
        rv = clItemGroup->AppendChild(clCompile);
        if (!rv) return rv;
    }
    rv = rootElement->AppendChild(clItemGroup);
    if (!rv) return rv;

    if (target == ProjectTarget::program)
    {
        soul::xml::Element* rcItemGroup = soul::xml::MakeElement("ItemGroup");
        soul::xml::Element* rcCompile = soul::xml::MakeElement("ResourceCompile");
        if (!classIndexFilePath.empty())
        {
            rcCompile->SetAttribute("Include", "class_index.rc");
            rv = rcItemGroup->AppendChild(rcCompile);
            if (!rv) return rv;
        }
        for (const auto& resourceFile : resourceFiles)
        {
            soul::xml::Element* rcCompile = soul::xml::MakeElement("ResourceCompile");
            rcCompile->SetAttribute("Include", resourceFile);
            rv = rcItemGroup->AppendChild(rcCompile);
            if (!rv) return rv;
        }
        rv = rootElement->AppendChild(rcItemGroup);
        if (!rv) return rv;
    }

    soul::xml::Element* cppTargets = soul::xml::MakeElement("Import");
    cppTargets->SetAttribute("Project", "$(VCTargetsPath)\\Microsoft.Cpp.targets");
    rv = rootElement->AppendChild(cppTargets);
    if (!rv) return rv;

    soul::xml::Element* extensionTargets = soul::xml::MakeElement("ImportGroup");
    extensionTargets->SetAttribute("Label", "ExtensionTargets");
    soul::xml::Element* importMasm = soul::xml::MakeElement("Import");
    importMasm->SetAttribute("Project", "$(VCTargetsPath)\\BuildCustomizations\\masm.targets");
    rv = extensionTargets->AppendChild(importMasm);
    if (!rv) return rv;
    rv = rootElement->AppendChild(extensionTargets);
    if (!rv) return rv;

    std::ofstream projectFile(projectFilePath);
    if (!projectFile) return std::unexpected<int>(util::AllocateError("could not create project file '" + projectFilePath + "'"));
    util::CodeFormatter formatter(projectFile);
    formatter.SetIndentSize(1);
    rv = projectDoc.Write(formatter);
    if (!rv) return rv;

    if (verbose)
    {
        std::cout << "==> " << projectFilePath << std::endl;
    }
    return std::expected<bool, int>(true);
}

} // namespace otava::build
