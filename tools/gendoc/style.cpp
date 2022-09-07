// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module gendoc.style;

import util;
import std.filesystem;

namespace gendoc {

void MakeStyleFile(const std::string& rootDir)
{
    std::string styleDir = util::GetFullPath(util::Path::Combine(rootDir, "style"));
    std::filesystem::create_directories(styleDir);
    std::string styleFilePath = util::Path::Combine(styleDir, "style.css");
    std::ofstream styleFile(styleFilePath);
    util::CodeFormatter formatter(styleFile);
    formatter.WriteLine("body");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("max-width: 1200px;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();
    formatter.WriteLine("h1, h2, h3, h4, h5, h6");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("color: #005ab4;");
    formatter.WriteLine("font-family: sans-serif;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();
    formatter.WriteLine("table.doc");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("background-color: FloralWhite;");
    formatter.WriteLine("color: black;");
    formatter.WriteLine("margin: 20px;");
    formatter.WriteLine("padding: 20px;");
    formatter.WriteLine("border: 1px solid #dddddd;");
    formatter.WriteLine("border-collapse: collapse;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();
    formatter.WriteLine("th, td");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("border: 1px solid #dddddd;");
    formatter.WriteLine("padding: 8px;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();
    formatter.WriteLine("td.right");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("text-align: right;");
    formatter.WriteLine("border: 1px solid #dddddd;");
    formatter.WriteLine("padding: 8px;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();
    formatter.WriteLine("th");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("background-color: #ffecc6");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();
    formatter.WriteLine(".specifier");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("color: blue;");
    formatter.WriteLine("font-weight: bold;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();
    formatter.WriteLine(".diagram");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("text-align: center;");
    formatter.DecIndent();
    formatter.WriteLine("}");
}

} // namespace gendoc
