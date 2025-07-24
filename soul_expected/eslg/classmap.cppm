// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.slg.classmap;

import std;

export namespace soul_expected::slg {

std::expected<bool, int> MakeCompressedClassMap(const std::string& root, const std::string& classMapName, bool verbose);
std::expected<bool, int> MakeResourceFile(const std::string& root, const std::string& classMapName, bool verbose);

} // namespce soul_expected::slg
