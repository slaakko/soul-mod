// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

import std.core;
import soul.slg.classmap;
import util;

using namespace util;
using namespace soul::slg;

int main(int argc, const char** argv)
{
    std::string root = GetFullPath("C:\\work\\soul-mod\\soul\\slg");
    std::string classMapName = "soul.slg.lex.classmap";
    MakeClassMap(root, classMapName, 0x110000);
    MakeResourceFile(root, classMapName);
}