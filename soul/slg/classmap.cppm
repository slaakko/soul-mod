// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.slg.classmap;

import std.core;

export namespace soul::slg {

void MakeCompressedClassMap(const std::string& root, const std::string& classMapName, bool verbose);
void MakeResourceFile(const std::string& root, const std::string& classMapName, bool verbose);

} // namespce soul::slg
