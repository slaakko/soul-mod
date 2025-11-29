// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util.error;

import std;

export namespace util {

int AllocateError(const std::string& msg);
std::string GetErrorMessage(int error, bool includeStackTrace);
std::string GetErrorMessage(int error);
std::string GetStackTrace(int error);
void FreeStackTrace(int error);

} // util
