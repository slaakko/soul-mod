// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

import std.core;
import util;
import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.compound.type.symbol;
import soul.cpp20.symbols.namespaces;
import soul.cpp20.symbols.modules;
import soul.cpp20.project.build;

int main()
{
    try
    {
        util::Init();
/*
        soul::cpp20::symbols::Module std("std");
        soul::cpp20::symbols::Writer writer(soul::cpp20::symbols::StdModuleFilePath(std.Name()));
        std.Write(writer);
*/
        soul::cpp20::project::build::Build(R"(C:\work\soul-mod\soul\cpp20\std\std.project)", soul::cpp20::project::build::BuildFlags::none);
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    util::Done();
    return 0;
}