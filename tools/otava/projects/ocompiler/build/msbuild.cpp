// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.build.msbuild;

import otava.build.config;
import util.path;
import util.code.formatter;
import util.file.stream;
import util.error;

namespace otava::build {

std::expected<bool, int> MSBuild(const std::string& projectFilePath, const std::string& config)
{
    std::expected<std::string, int> v = GetVCVars64Path();
    if (!v) return std::unexpected<int>(v.error());
    std::string vcvars64Path = std::move(*v);
    if (vcvars64Path.empty())
    {
        return std::unexpected<int>(util::AllocateError("vcvars64.bat not configured"));
    }
    std::string Config = "Debug";
    if (config == "release")
    {
        Config = "Release";
    }
    std::string projectDir = util::Path::GetDirectoryName(projectFilePath);
    std::expected<std::string, int> fp = util::GetFullPath(util::Path::Combine(projectDir, "build.bat"));
    if (!fp) return std::unexpected<int>(fp.error());
    std::string buildBatPath = std::move(*fp);
    {
        std::ofstream buildBatFile(buildBatPath);
        if (!buildBatFile) return std::unexpected<int>(util::AllocateError("could not create file '" + buildBatPath + "'"));
        util::CodeFormatter formatter(buildBatFile);
        formatter.WriteLine("@echo off");
        formatter.WriteLine("call \"" + vcvars64Path + "\"");
        formatter.WriteLine("msbuild -verbosity:minimal -t:Rebuild -p:Configuration=\"" + Config + "\" " + "\"" + projectFilePath + "\"" + " > \"" + projectDir +
            "/build.out.log\" 2> \"" + projectDir + "/build.error.log\"");
        formatter.WriteLine("exit %ERRORLEVEL%");
    }
    std::string commandLine = "cmd /C \"" + buildBatPath + "\"";
    int exitCode = ort_run_process(commandLine.c_str());
    std::string buildOutLogPath = projectDir + "/build.out.log";
    std::filesystem::path pd = buildOutLogPath;
    if (std::filesystem::exists(pd))
    {
        std::expected<std::string, int> r = util::ReadFile(buildOutLogPath);
        if (!r) return std::unexpected<int>(r.error());
        std::string buildOutLog = std::move(*r);
        std::cout << buildOutLog << std::endl;
    }
    std::string buildErrorLogPath = projectDir + "/build.error.log";
    std::filesystem::path pe = buildErrorLogPath;
    if (std::filesystem::exists(pe))
    {
        std::expected<std::string, int> r = util::ReadFile(buildErrorLogPath);
        if (!r) return std::unexpected<int>(r.error());
        std::string buildErrorLog = std::move(*r);
        if (!buildErrorLog.empty())
        {
            std::cout << buildErrorLog << std::endl;
        }
    }
    if (exitCode != 0)
    {
        if (exitCode == 999)
        {
            return std::unexpected<int>(util::AllocateError("could not create process '" + commandLine + "'"));
        }
        return std::unexpected<int>(util::AllocateError("msbuild failed with exit code " + std::to_string(exitCode)));
    }
    return std::expected<bool, int>(true);
}

} // namespace otava::build
