<?xml version="1.0" encoding="utf-8"?>
<Project DefaultTargets="Build" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
    <ItemGroup Label="ProjectConfigurations">
        <ProjectConfiguration Include="Debug|Win32">
            <Configuration>Debug</Configuration>
            <Platform>Win32</Platform>
        </ProjectConfiguration>
        <ProjectConfiguration Include="Release|Win32">
            <Configuration>Release</Configuration>
            <Platform>Win32</Platform>
        </ProjectConfiguration>
        <ProjectConfiguration Include="Debug|x64">
            <Configuration>Debug</Configuration>
            <Platform>x64</Platform>
        </ProjectConfiguration>
        <ProjectConfiguration Include="Release|x64">
            <Configuration>Release</Configuration>
            <Platform>x64</Platform>
        </ProjectConfiguration>
    </ItemGroup>
    <PropertyGroup Label="Globals">
        <VCProjectVersion>16.0</VCProjectVersion>
        <Keyword>Win32Proj</Keyword>
        <ProjectGuid>{9dbb759c-7e26-4339-a413-7dd1454ee5ae}</ProjectGuid>
        <RootNamespace>util</RootNamespace>
        <WindowsTargetPlatformVersion>10.0</WindowsTargetPlatformVersion>
    </PropertyGroup>
    <Import Project="$(VCTargetsPath)\Microsoft.Cpp.Default.props"/>
    <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'" Label="Configuration">
        <ConfigurationType>StaticLibrary</ConfigurationType>
        <UseDebugLibraries>true</UseDebugLibraries>
        <PlatformToolset>v143</PlatformToolset>
        <CharacterSet>Unicode</CharacterSet>
    </PropertyGroup>
    <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'" Label="Configuration">
        <ConfigurationType>StaticLibrary</ConfigurationType>
        <UseDebugLibraries>false</UseDebugLibraries>
        <PlatformToolset>v143</PlatformToolset>
        <WholeProgramOptimization>true</WholeProgramOptimization>
        <CharacterSet>Unicode</CharacterSet>
    </PropertyGroup>
    <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'" Label="Configuration">
        <ConfigurationType>StaticLibrary</ConfigurationType>
        <UseDebugLibraries>true</UseDebugLibraries>
        <PlatformToolset>v143</PlatformToolset>
        <CharacterSet>Unicode</CharacterSet>
    </PropertyGroup>
    <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'" Label="Configuration">
        <ConfigurationType>StaticLibrary</ConfigurationType>
        <UseDebugLibraries>false</UseDebugLibraries>
        <PlatformToolset>v143</PlatformToolset>
        <WholeProgramOptimization>true</WholeProgramOptimization>
        <CharacterSet>Unicode</CharacterSet>
    </PropertyGroup>
    <Import Project="$(VCTargetsPath)\Microsoft.Cpp.props"/>
    <ImportGroup Label="ExtensionSettings"/>
    <ImportGroup Label="Shared"/>
    <ImportGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'" Label="PropertySheets">
        <Import Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props"/>
        <Import Project="..\config\build.props"/>
    </ImportGroup>
    <ImportGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'" Label="PropertySheets">
        <Import Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props"/>
        <Import Project="..\config\build.props"/>
    </ImportGroup>
    <ImportGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'" Label="PropertySheets">
        <Import Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props"/>
        <Import Project="..\config\build.props"/>
    </ImportGroup>
    <ImportGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'" Label="PropertySheets">
        <Import Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props"/>
        <Import Project="..\config\build.props"/>
    </ImportGroup>
    <PropertyGroup Label="UserMacros"/>
    <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
        <LinkIncremental>true</LinkIncremental>
    </PropertyGroup>
    <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
        <LinkIncremental>false</LinkIncremental>
    </PropertyGroup>
    <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
        <LinkIncremental>true</LinkIncremental>
        <TargetName>utild</TargetName>
    </PropertyGroup>
    <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
        <LinkIncremental>false</LinkIncremental>
        <TargetName>util</TargetName>
    </PropertyGroup>
    <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
        <ClCompile>
            <WarningLevel>Level3</WarningLevel>
            <SDLCheck>true</SDLCheck>
            <PreprocessorDefinitions>WIN32;_DEBUG;_LIB;%(PreprocessorDefinitions)</PreprocessorDefinitions>
            <ConformanceMode>true</ConformanceMode>
        </ClCompile>
        <Link>
            <SubSystem/>
            <GenerateDebugInformation>true</GenerateDebugInformation>
        </Link>
    </ItemDefinitionGroup>
    <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
        <ClCompile>
            <WarningLevel>Level3</WarningLevel>
            <FunctionLevelLinking>true</FunctionLevelLinking>
            <IntrinsicFunctions>true</IntrinsicFunctions>
            <SDLCheck>true</SDLCheck>
            <PreprocessorDefinitions>WIN32;NDEBUG;_LIB;%(PreprocessorDefinitions)</PreprocessorDefinitions>
            <ConformanceMode>true</ConformanceMode>
        </ClCompile>
        <Link>
            <SubSystem/>
            <EnableCOMDATFolding>true</EnableCOMDATFolding>
            <OptimizeReferences>true</OptimizeReferences>
            <GenerateDebugInformation>true</GenerateDebugInformation>
        </Link>
    </ItemDefinitionGroup>
    <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
        <ClCompile>
            <WarningLevel>Level3</WarningLevel>
            <SDLCheck>true</SDLCheck>
            <PreprocessorDefinitions>_DEBUG;_LIB;%(PreprocessorDefinitions)</PreprocessorDefinitions>
            <ConformanceMode>true</ConformanceMode>
            <LanguageStandard>stdcpplatest</LanguageStandard>
            <EnableModules>true</EnableModules>
            <MultiProcessorCompilation>true</MultiProcessorCompilation>
            <DebugInformationFormat>ProgramDatabase</DebugInformationFormat>
            <AdditionalIncludeDirectories>.;..;$(BOOST_INCLUDE_DIR)</AdditionalIncludeDirectories>
            <DisableSpecificWarnings>5050;4267;4244</DisableSpecificWarnings>
        </ClCompile>
        <Link>
            <SubSystem/>
            <GenerateDebugInformation>true</GenerateDebugInformation>
        </Link>
    </ItemDefinitionGroup>
    <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
        <ClCompile>
            <WarningLevel>Level3</WarningLevel>
            <FunctionLevelLinking>true</FunctionLevelLinking>
            <IntrinsicFunctions>true</IntrinsicFunctions>
            <SDLCheck>true</SDLCheck>
            <PreprocessorDefinitions>NDEBUG;_LIB;%(PreprocessorDefinitions)</PreprocessorDefinitions>
            <ConformanceMode>true</ConformanceMode>
            <LanguageStandard>stdcpplatest</LanguageStandard>
            <EnableModules>true</EnableModules>
            <MultiProcessorCompilation>true</MultiProcessorCompilation>
            <AdditionalIncludeDirectories>.;..;$(BOOST_INCLUDE_DIR)</AdditionalIncludeDirectories>
            <DisableSpecificWarnings>5050;4267;4244</DisableSpecificWarnings>
        </ClCompile>
        <Link>
            <SubSystem/>
            <EnableCOMDATFolding>true</EnableCOMDATFolding>
            <OptimizeReferences>true</OptimizeReferences>
            <GenerateDebugInformation>true</GenerateDebugInformation>
        </Link>
    </ItemDefinitionGroup>
    <ItemGroup>
        <ClCompile Include="align.cppm"/>
        <ClCompile Include="ansi.cpp"/>
        <ClCompile Include="ansi.cppm"/>
        <ClCompile Include="binary_resource_ptr.cpp"/>
        <ClCompile Include="binary_resource_ptr.cppm"/>
        <ClCompile Include="binary_stream_reader.cpp"/>
        <ClCompile Include="binary_stream_reader.cppm"/>
        <ClCompile Include="binary_stream_writer.cpp"/>
        <ClCompile Include="binary_stream_writer.cppm"/>
        <ClCompile Include="buffered_stream.cpp"/>
        <ClCompile Include="buffered_stream.cppm"/>
        <ClCompile Include="code_formatter.cpp"/>
        <ClCompile Include="code_formatter.cppm"/>
        <ClCompile Include="component.cpp"/>
        <ClCompile Include="component.cppm"/>
        <ClCompile Include="compression.cppm"/>
        <ClCompile Include="container.cpp"/>
        <ClCompile Include="container.cppm"/>
        <ClCompile Include="deflate_stream.cpp"/>
        <ClCompile Include="deflate_stream.cppm"/>
        <ClCompile Include="error.cpp"/>
        <ClCompile Include="error.cppm"/>
        <ClCompile Include="fiber.cpp"/>
        <ClCompile Include="fiber.cppm"/>
        <ClCompile Include="file_stream.cpp"/>
        <ClCompile Include="file_stream.cppm"/>
        <ClCompile Include="file_util.cpp"/>
        <ClCompile Include="file_util.cppm"/>
        <ClCompile Include="init_done.cpp"/>
        <ClCompile Include="init_done.cppm"/>
        <ClCompile Include="intrusive_list.cppm"/>
        <ClCompile Include="json.cpp"/>
        <ClCompile Include="json.cppm"/>
        <ClCompile Include="log.cpp"/>
        <ClCompile Include="log.cppm"/>
        <ClCompile Include="log_file_writer.cpp"/>
        <ClCompile Include="log_file_writer.cppm"/>
        <ClCompile Include="memory_reader.cpp"/>
        <ClCompile Include="memory_reader.cppm"/>
        <ClCompile Include="memory_stream.cpp"/>
        <ClCompile Include="memory_stream.cppm"/>
        <ClCompile Include="memory_writer.cpp"/>
        <ClCompile Include="memory_writer.cppm"/>
        <ClCompile Include="path.cpp"/>
        <ClCompile Include="path.cppm"/>
        <ClCompile Include="rand.cpp"/>
        <ClCompile Include="rand.cppm"/>
        <ClCompile Include="sha1.cpp"/>
        <ClCompile Include="sha1.cppm"/>
        <ClCompile Include="socket.cpp"/>
        <ClCompile Include="socket.cppm"/>
        <ClCompile Include="stream.cpp"/>
        <ClCompile Include="stream.cppm"/>
        <ClCompile Include="synchronized_queue.cppm"/>
        <ClCompile Include="system.cpp"/>
        <ClCompile Include="system.cppm"/>
        <ClCompile Include="text_util.cpp"/>
        <ClCompile Include="text_util.cppm"/>
        <ClCompile Include="time.cpp"/>
        <ClCompile Include="time.cppm"/>
        <ClCompile Include="unicode.conversion.cpp"/>
        <ClCompile Include="unicode.cpp"/>
        <ClCompile Include="unicode.engine.cpp"/>
        <ClCompile Include="unicode.cppm"/>
        <ClCompile Include="util.cppm"/>
        <ClCompile Include="uuid.cpp"/>
        <ClCompile Include="uuid.cppm"/>
        <ClCompile Include="ZLibInterface.c"/>
    </ItemGroup>
    <ItemGroup>
        <ClInclude Include="ZLibInterface.h"/>
    </ItemGroup>
    <ItemGroup>
        <None Include="util.project"/>
    </ItemGroup>
    <Import Project="$(VCTargetsPath)\Microsoft.Cpp.targets"/>
    <ImportGroup Label="ExtensionTargets"/>
</Project>