// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.build.project_file;

import soul.xml.dom;
import util.code.formatter;
import util.uuid;

namespace otava::build {

void MakeProjectFile(const std::string& projectFilePath, const std::string& projectName, const std::vector<std::string> asmFiles, const std::vector<std::string>& cppFiles, 
    const std::string& libraryDirs, ProjectTarget target, bool verbose)
{
    util::uuid projectUuid = util::random_uuid();

    soul::xml::Document projectDoc;
    soul::xml::Element* rootElement = soul::xml::MakeElement("Project");
    rootElement->SetAttribute("DefaultTargets", "Build");
    rootElement->SetAttribute("xmlns", "http://schemas.microsoft.com/developer/msbuild/2003");
    projectDoc.AppendChild(rootElement);
    soul::xml::Element* configurationItemGroup = soul::xml::MakeElement("ItemGroup");
    configurationItemGroup->SetAttribute("Label", "ProjectConfigurations");

    soul::xml::Element* projectDebugConfig = soul::xml::MakeElement("ProjectConfiguration");
    projectDebugConfig->SetAttribute("Include", "Debug|x64");
    soul::xml::Element* debugConfig = soul::xml::MakeElement("Configuration");
    soul::xml::Text* debugText = soul::xml::MakeText("Debug");
    debugConfig->AppendChild(debugText);
    projectDebugConfig->AppendChild(debugConfig);
    soul::xml::Element* debugPlatform = soul::xml::MakeElement("Platform");
    soul::xml::Text* debugPlatformText = soul::xml::MakeText("x64");
    debugPlatform->AppendChild(debugPlatformText);
    projectDebugConfig->AppendChild(debugPlatform);
    configurationItemGroup->AppendChild(projectDebugConfig);

    soul::xml::Element* projectReleaseConfig = soul::xml::MakeElement("ProjectConfiguration");
    projectReleaseConfig->SetAttribute("Include", "Release|x64");
    soul::xml::Element* releaseConfig = soul::xml::MakeElement("Configuration");
    soul::xml::Text* releaseText = soul::xml::MakeText("Release");
    releaseConfig->AppendChild(releaseText);
    projectReleaseConfig->AppendChild(releaseConfig);
    soul::xml::Element* releasePlatform = soul::xml::MakeElement("Platform");
    soul::xml::Text* releasePlatformText = soul::xml::MakeText("x64");
    releasePlatform->AppendChild(releasePlatformText);
    projectReleaseConfig->AppendChild(releasePlatform);
    configurationItemGroup->AppendChild(projectReleaseConfig);

    rootElement->AppendChild(configurationItemGroup);

    soul::xml::Element* globalsPropertyGroup = soul::xml::MakeElement("PropertyGroup");
    globalsPropertyGroup->SetAttribute("Label", "Globals");
    soul::xml::Element* vcProjectVersion = soul::xml::MakeElement("VCProjectVersion");
    soul::xml::Text* vcProjectVersionText = soul::xml::MakeText("16.0");
    vcProjectVersion->AppendChild(vcProjectVersionText);
    globalsPropertyGroup->AppendChild(vcProjectVersion);
    soul::xml::Element* keyword = soul::xml::MakeElement("Keyword");
    soul::xml::Text* keywordText = soul::xml::MakeText("Win32Proj");
    keyword->AppendChild(keywordText);
    globalsPropertyGroup->AppendChild(keyword);
    soul::xml::Element* projectGuid = soul::xml::MakeElement("ProjectGuid");
    soul::xml::Text* projectGuildText = soul::xml::MakeText(util::ToString(projectUuid));
    projectGuid->AppendChild(projectGuildText);
    globalsPropertyGroup->AppendChild(projectGuid);
    soul::xml::Element* rootNamespace = soul::xml::MakeElement("RootNamespace");
    soul::xml::Text* rootNamespaceText = soul::xml::MakeText(projectName);
    rootNamespace->AppendChild(rootNamespaceText);
    globalsPropertyGroup->AppendChild(rootNamespace);
    soul::xml::Element* targetPlatformVersion = soul::xml::MakeElement("WindowsTargetPlatformVersion");
    soul::xml::Text* targetPlatformVersionText = soul::xml::MakeText("10.0");
    targetPlatformVersion->AppendChild(targetPlatformVersionText);
    globalsPropertyGroup->AppendChild(targetPlatformVersion);

    rootElement->AppendChild(globalsPropertyGroup);

    soul::xml::Element* importProject = soul::xml::MakeElement("Import");
    importProject->SetAttribute("Project", "$(VCTargetsPath)\\Microsoft.Cpp.Default.props");
    rootElement->AppendChild(importProject);

    soul::xml::Element* debugPropertyGroup = soul::xml::MakeElement("PropertyGroup");
    debugPropertyGroup->SetAttribute("Condition", "'$(Configuration)|$(Platform)'=='Debug|x64'");
    debugPropertyGroup->SetAttribute("Label", "Configuration");
    soul::xml::Element* debugConfigurationType = soul::xml::MakeElement("ConfigurationType");
    if (target == ProjectTarget::program)
    {
        soul::xml::Text* debugConfigurationTypeText = soul::xml::MakeText("Application");
        debugConfigurationType->AppendChild(debugConfigurationTypeText);
        debugPropertyGroup->AppendChild(debugConfigurationType);
    }
    else if (target == ProjectTarget::library)
    {
        soul::xml::Text* debugConfigurationTypeText = soul::xml::MakeText("StaticLibrary");
        debugConfigurationType->AppendChild(debugConfigurationTypeText);
        debugPropertyGroup->AppendChild(debugConfigurationType);
    }
    soul::xml::Element* debugUseDebugLibraries = soul::xml::MakeElement("UseDebugLibraries");
    soul::xml::Text* debugUseDebugLibrariesText = soul::xml::MakeText("true");
    debugUseDebugLibraries->AppendChild(debugUseDebugLibrariesText);
    debugPropertyGroup->AppendChild(debugUseDebugLibraries);
    soul::xml::Element* debugPlatformToolset = soul::xml::MakeElement("PlatformToolset");
    soul::xml::Text* debugPlatformToolsetText = soul::xml::MakeText("v143");
    debugPlatformToolset->AppendChild(debugPlatformToolsetText);
    debugPropertyGroup->AppendChild(debugPlatformToolset);
    soul::xml::Element* debugCharacterSet = soul::xml::MakeElement("CharacterSet");
    soul::xml::Text* debugCharacterSetText = soul::xml::MakeText("Unicode");
    debugCharacterSet->AppendChild(debugCharacterSetText);
    debugPropertyGroup->AppendChild(debugCharacterSet);
    rootElement->AppendChild(debugPropertyGroup);

    soul::xml::Element* releasePropertyGroup = soul::xml::MakeElement("PropertyGroup");
    releasePropertyGroup->SetAttribute("Condition", "'$(Configuration)|$(Platform)'=='Release|x64'");
    releasePropertyGroup->SetAttribute("Label", "Configuration");
    soul::xml::Element* releaseConfigurationType = soul::xml::MakeElement("ConfigurationType");
    if (target == ProjectTarget::program)
    {
        soul::xml::Text* releaseConfigurationTypeText = soul::xml::MakeText("Application");
        releaseConfigurationType->AppendChild(releaseConfigurationTypeText);
        releasePropertyGroup->AppendChild(releaseConfigurationType);
    }
    else if (target == ProjectTarget::library)
    {
        soul::xml::Text* releaseConfigurationTypeText = soul::xml::MakeText("StaticLibrary");
        releaseConfigurationType->AppendChild(releaseConfigurationTypeText);
        releasePropertyGroup->AppendChild(releaseConfigurationType);
    }
    soul::xml::Element* releaseUseDebugLibraries = soul::xml::MakeElement("UseDebugLibraries");
    soul::xml::Text* releaseUseDebugLibrariesText = soul::xml::MakeText("false");
    releaseUseDebugLibraries->AppendChild(releaseUseDebugLibrariesText);
    releasePropertyGroup->AppendChild(releaseUseDebugLibraries);
    soul::xml::Element* releasePlatformToolset = soul::xml::MakeElement("PlatformToolset");
    soul::xml::Text* releasePlatformToolsetText = soul::xml::MakeText("v143");
    releasePlatformToolset->AppendChild(releasePlatformToolsetText);
    releasePropertyGroup->AppendChild(releasePlatformToolset);
    soul::xml::Element* releaseCharacterSet = soul::xml::MakeElement("CharacterSet");
    soul::xml::Text* releaseCharacterSetText = soul::xml::MakeText("Unicode");
    releaseCharacterSet->AppendChild(releaseCharacterSetText);
    releasePropertyGroup->AppendChild(releaseCharacterSet);
    soul::xml::Element* wholeProgramOptimization = soul::xml::MakeElement("WholeProgramOptimization");
    soul::xml::Text* wholeProgramOptimizationText = soul::xml::MakeText("true");
    wholeProgramOptimization->AppendChild(wholeProgramOptimizationText);
    releasePropertyGroup->AppendChild(wholeProgramOptimization);
    rootElement->AppendChild(releasePropertyGroup);

    soul::xml::Element* importCppProject = soul::xml::MakeElement("Import");
    importCppProject->SetAttribute("Project", "$(VCTargetsPath)\\Microsoft.Cpp.props");
    rootElement->AppendChild(importCppProject);

    soul::xml::Element* masmGroup = soul::xml::MakeElement("ImportGroup");
    masmGroup->SetAttribute("Label", "ExtensionSettings");
    soul::xml::Element* masmProps = soul::xml::MakeElement("Import");
    masmProps->SetAttribute("Project", "$(VCTargetsPath)\\BuildCustomizations\\masm.props");
    masmGroup->AppendChild(masmProps);
    rootElement->AppendChild(masmGroup);

    soul::xml::Element* importSharedGroup = soul::xml::MakeElement("ImportGroup");
    importSharedGroup->SetAttribute("Label", "Shared");
    rootElement->AppendChild(importSharedGroup);

    soul::xml::Element* debugImportPropertySheets = soul::xml::MakeElement("ImportGroup");
    debugImportPropertySheets->SetAttribute("Label", "PropertySheets");
    debugImportPropertySheets->SetAttribute("Condition", "'$(Configuration)|$(Platform)'=='Debug|x64'");
    soul::xml::Element* debugPropertySheet = soul::xml::MakeElement("Import");
    debugPropertySheet->SetAttribute("Project", "$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props");
    debugPropertySheet->SetAttribute("Condition", "exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')");
    debugPropertySheet->SetAttribute("Label", "LocalAppDataPlatform");
    debugImportPropertySheets->AppendChild(debugPropertySheet);
    rootElement->AppendChild(debugImportPropertySheets);

    soul::xml::Element* releaseImportPropertySheets = soul::xml::MakeElement("ImportGroup");
    releaseImportPropertySheets->SetAttribute("Label", "PropertySheets");
    releaseImportPropertySheets->SetAttribute("Condition", "'$(Configuration)|$(Platform)'=='Release|x64'");
    soul::xml::Element* releasePropertySheet = soul::xml::MakeElement("Import");
    releasePropertySheet->SetAttribute("Project", "$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props");
    releasePropertySheet->SetAttribute("Condition", "exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')");
    releasePropertySheet->SetAttribute("Label", "LocalAppDataPlatform");
    releaseImportPropertySheets->AppendChild(releasePropertySheet);
    rootElement->AppendChild(releaseImportPropertySheets);

    soul::xml::Element* userMacros = soul::xml::MakeElement("PropertyGroup");
    userMacros->SetAttribute("Label", "UserMacros");
    rootElement->AppendChild(userMacros);

    soul::xml::Element* debugOutDirPropertyGroup = soul::xml::MakeElement("PropertyGroup");
    debugOutDirPropertyGroup->SetAttribute("Condition", "'$(Configuration)|$(Platform)' == 'Debug|x64'");
    soul::xml::Element* debugOutDir = soul::xml::MakeElement("OutDir");
    soul::xml::Text* debugOutDirText = soul::xml::MakeText("./");
    debugOutDir->AppendChild(debugOutDirText);
    debugOutDirPropertyGroup->AppendChild(debugOutDir);
    rootElement->AppendChild(debugOutDirPropertyGroup);

    soul::xml::Element* releaseOutDirPropertyGroup = soul::xml::MakeElement("PropertyGroup");
    releaseOutDirPropertyGroup->SetAttribute("Condition", "'$(Configuration)|$(Platform)'=='Release|x64'");
    soul::xml::Element* releaseOutDir = soul::xml::MakeElement("OutDir");
    soul::xml::Text* releaseOutDirText = soul::xml::MakeText("./");
    releaseOutDir->AppendChild(releaseOutDirText);
    releaseOutDirPropertyGroup->AppendChild(releaseOutDir);
    rootElement->AppendChild(releaseOutDirPropertyGroup);

    soul::xml::Element* debugItemDefinitionGroup = soul::xml::MakeElement("ItemDefinitionGroup");
    debugItemDefinitionGroup->SetAttribute("Condition", "'$(Configuration)|$(Platform)'=='Debug|x64'");
    soul::xml::Element* debugClCompile = soul::xml::MakeElement("ClCompile");
    soul::xml::Element* debugWarningLevel = soul::xml::MakeElement("WarningLevel");
    soul::xml::Text* debugWarningLevelText = soul::xml::MakeText("Level3");
    debugWarningLevel->AppendChild(debugWarningLevelText);
    debugClCompile->AppendChild(debugWarningLevel);
    soul::xml::Element* debugSdlCheck = soul::xml::MakeElement("SDLCheck");
    soul::xml::Text* debugSdlCheckText = soul::xml::MakeText("true");
    debugSdlCheck->AppendChild(debugSdlCheckText);
    debugClCompile->AppendChild(debugSdlCheck);
    soul::xml::Element* debugPreprocessor = soul::xml::MakeElement("PreprocessorDefinitions");
    soul::xml::Text* debugPreprocessorText = soul::xml::MakeText("_DEBUG;_CONSOLE;%(PreprocessorDefinitions)");
    debugPreprocessor->AppendChild(debugPreprocessorText);
    debugClCompile->AppendChild(debugPreprocessor);
    soul::xml::Element* debugConformanceMode = soul::xml::MakeElement("ConformanceMode");
    soul::xml::Text* debugConformanceModeText = soul::xml::MakeText("true");
    debugConformanceMode->AppendChild(debugConformanceModeText);
    debugClCompile->AppendChild(debugConformanceMode);
    debugItemDefinitionGroup->AppendChild(debugClCompile);
    soul::xml::Element* debugLink = soul::xml::MakeElement("Link");
    soul::xml::Element* debugSubSystem = soul::xml::MakeElement("SubSystem");
    if (target == ProjectTarget::program)
    {
        soul::xml::Text* debugSubSystemText = soul::xml::MakeText("Console");
        debugSubSystem->AppendChild(debugSubSystemText);
    }
    debugLink->AppendChild(debugSubSystem);
    soul::xml::Element* debugGenDebugInfo = soul::xml::MakeElement("GenerateDebugInformation");
    soul::xml::Text* debugGenDebugInfoText = soul::xml::MakeText("true");
    debugGenDebugInfo->AppendChild(debugGenDebugInfoText);
    debugLink->AppendChild(debugGenDebugInfo);
    if (target == ProjectTarget::program)
    {
        soul::xml::Element* debugLibraryDirs = soul::xml::MakeElement("AdditionalLibraryDirectories");
        soul::xml::Text* debugLibraryDirsText = soul::xml::MakeText(libraryDirs);
        debugLibraryDirs->AppendChild(debugLibraryDirsText);
        debugLink->AppendChild(debugLibraryDirs);
        soul::xml::Element* debugDependencies = soul::xml::MakeElement("AdditionalDependencies");
        soul::xml::Text* debugDependenciesText = soul::xml::MakeText("std.lib;ortd.lib");
        debugDependencies->AppendChild(debugDependenciesText);
        debugLink->AppendChild(debugDependencies);
    }
    debugItemDefinitionGroup->AppendChild(debugLink);

    rootElement->AppendChild(debugItemDefinitionGroup);

    soul::xml::Element* releaseItemDefinitionGroup = soul::xml::MakeElement("ItemDefinitionGroup");
    releaseItemDefinitionGroup->SetAttribute("Condition", "'$(Configuration)|$(Platform)'=='Release|x64'");
    soul::xml::Element* releaseClCompile = soul::xml::MakeElement("ClCompile");
    soul::xml::Element* releaseWarningLevel = soul::xml::MakeElement("WarningLevel");
    soul::xml::Text* releaseWarningLevelText = soul::xml::MakeText("Level3");
    releaseWarningLevel->AppendChild(releaseWarningLevelText);
    releaseClCompile->AppendChild(releaseWarningLevel);
    soul::xml::Element* releaseFunctionLevelLinking = soul::xml::MakeElement("FunctionLevelLinking");
    soul::xml::Text* releaseFunctionLevelLinkingText = soul::xml::MakeText("true");
    releaseFunctionLevelLinking->AppendChild(releaseFunctionLevelLinkingText);
    releaseClCompile->AppendChild(releaseFunctionLevelLinking);
    soul::xml::Element* releaseIntrinsics = soul::xml::MakeElement("IntrinsicFunctions");
    soul::xml::Text* releaseIntrinsicsText = soul::xml::MakeText("true");
    releaseIntrinsics->AppendChild(releaseIntrinsicsText);
    releaseClCompile->AppendChild(releaseIntrinsics);
    soul::xml::Element* releaseSdlCheck = soul::xml::MakeElement("SDLCheck");
    soul::xml::Text* releaseSdlCheckText = soul::xml::MakeText("true");
    releaseSdlCheck->AppendChild(releaseSdlCheckText);
    releaseClCompile->AppendChild(releaseSdlCheck);
    soul::xml::Element* releasePreprocessor = soul::xml::MakeElement("PreprocessorDefinitions");
    soul::xml::Text* releasePreprocessorText = soul::xml::MakeText("NDEBUG;_CONSOLE;%(PreprocessorDefinitions)");
    releasePreprocessor->AppendChild(releasePreprocessorText);
    releaseClCompile->AppendChild(releasePreprocessor);
    soul::xml::Element* releaseConformanceMode = soul::xml::MakeElement("ConformanceMode");
    soul::xml::Text* releaseConformanceModeText = soul::xml::MakeText("true");
    releaseConformanceMode->AppendChild(releaseConformanceModeText);
    releaseClCompile->AppendChild(releaseConformanceMode);
    releaseItemDefinitionGroup->AppendChild(releaseClCompile);
    soul::xml::Element* releaseLink = soul::xml::MakeElement("Link");
    soul::xml::Element* releaseSubSystem = soul::xml::MakeElement("SubSystem");
    if (target == ProjectTarget::program)
    {
        soul::xml::Text* releaseSubSystemText = soul::xml::MakeText("Console");
        releaseSubSystem->AppendChild(releaseSubSystemText);
    }
    releaseLink->AppendChild(releaseSubSystem);
    soul::xml::Element* releaseComdatFolding = soul::xml::MakeElement("EnableCOMDATFolding");
    soul::xml::Text* releaseComdatFoldingText = soul::xml::MakeText("true");
    releaseComdatFolding->AppendChild(releaseComdatFoldingText);
    releaseLink->AppendChild(releaseComdatFolding);
    soul::xml::Element* releaseOptimizeRefs = soul::xml::MakeElement("OptimizeReferences");
    soul::xml::Text* releaseOptimizeRefsText = soul::xml::MakeText("true");
    releaseOptimizeRefs->AppendChild(releaseOptimizeRefsText);
    releaseLink->AppendChild(releaseOptimizeRefs);
    soul::xml::Element* releaseGenDebugInfo = soul::xml::MakeElement("GenerateDebugInformation");
    soul::xml::Text* releaseGenDebugInfoText = soul::xml::MakeText("true");
    releaseGenDebugInfo->AppendChild(releaseGenDebugInfoText);
    releaseLink->AppendChild(releaseGenDebugInfo);
    if (target == ProjectTarget::program)
    {
        soul::xml::Element* releaseLibraryDirs = soul::xml::MakeElement("AdditionalLibraryDirectories");
        soul::xml::Text* releaseLibraryDirsText = soul::xml::MakeText(libraryDirs);
        releaseLibraryDirs->AppendChild(releaseLibraryDirsText);
        releaseLink->AppendChild(releaseLibraryDirs);
        soul::xml::Element* releaseDependencies = soul::xml::MakeElement("AdditionalDependencies");
        soul::xml::Text* releaseDepenciesText = soul::xml::MakeText("std.lib;ort.lib");
        releaseDependencies->AppendChild(releaseDepenciesText);
        releaseLink->AppendChild(releaseDependencies);
    }
    releaseItemDefinitionGroup->AppendChild(releaseLink);

    rootElement->AppendChild(releaseItemDefinitionGroup);

    soul::xml::Element* masmItemGroup = soul::xml::MakeElement("ItemGroup");
    for (const auto& asmFile : asmFiles)
    {
        soul::xml::Element* masm = soul::xml::MakeElement("MASM");
        masm->SetAttribute("Include", asmFile);
        masmItemGroup->AppendChild(masm);
    }
    rootElement->AppendChild(masmItemGroup);
    
    soul::xml::Element* clItemGroup = soul::xml::MakeElement("ItemGroup");
    for (const auto& cppFile : cppFiles)
    {
        soul::xml::Element* clCompile = soul::xml::MakeElement("ClCompile");
        clCompile->SetAttribute("Include", cppFile);
        clItemGroup->AppendChild(clCompile);
    }
    rootElement->AppendChild(clItemGroup);

    soul::xml::Element* cppTargets = soul::xml::MakeElement("Import");
    cppTargets->SetAttribute("Project", "$(VCTargetsPath)\\Microsoft.Cpp.targets");
    rootElement->AppendChild(cppTargets);

    soul::xml::Element* extensionTargets = soul::xml::MakeElement("ImportGroup");
    extensionTargets->SetAttribute("Label", "ExtensionTargets");
    soul::xml::Element* importMasm = soul::xml::MakeElement("Import");
    importMasm->SetAttribute("Project", "$(VCTargetsPath)\\BuildCustomizations\\masm.targets");
    extensionTargets->AppendChild(importMasm);
    rootElement->AppendChild(extensionTargets);

    std::ofstream projectFile(projectFilePath);
    util::CodeFormatter formatter(projectFile);
    formatter.SetIndentSize(1);
    projectDoc.Write(formatter);

    if (verbose)
    {
        std::cout << "==> " << projectFilePath << std::endl;
    }
}

} // namespace otava::build
