// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util_expected.ansi;

import std;

export namespace util {

extern const std::string fgBlack;
extern const std::string fgDarkRed;
extern const std::string fgDarkGreen;
extern const std::string fgDarkYellow;
extern const std::string fgDarkBlue;
extern const std::string fgDarkMagenta;
extern const std::string fgDarkCyan;
extern const std::string fgGray;
extern const std::string fgRed;
extern const std::string fgGreen;
extern const std::string fgYellow;
extern const std::string fgBlue;
extern const std::string fgMagenta;
extern const std::string fgCyan;
extern const std::string fgWhite;

extern const std::string bgBlack;
extern const std::string bgDarkRed;
extern const std::string bgDarkGreen;
extern const std::string bgDarkYellow;
extern const std::string bgDarkBlue;
extern const std::string bgDarkMagenta;
extern const std::string bgDarkCyan;
extern const std::string bgGray;
extern const std::string bgRed;
extern const std::string bgGreen;
extern const std::string bgYellow;
extern const std::string bgBlue;
extern const std::string bgMagenta;
extern const std::string bgCyan;
extern const std::string bgWhite;

extern const std::string reset;

#ifdef _WIN32

std::expected<std::string, int> AnsiIntercept(int handle, const std::string& text);

#endif

void AnsiInit();
void AnsiDone();

} // namespace util
