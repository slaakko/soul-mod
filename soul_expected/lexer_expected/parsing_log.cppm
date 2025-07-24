// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.lexer.parsing.log;

import std;

export namespace soul_expected::lexer {

class ParsingLog
{
public:
    ParsingLog();
    ParsingLog(int maxLineLength_);
    virtual ~ParsingLog();
    virtual void IncIndent() = 0;
    virtual void DecIndent() = 0;
    virtual std::expected<bool, int> WriteBeginRule(const std::string& ruleName) = 0;
    virtual std::expected<bool, int> WriteEndRule(const std::string& ruleName) = 0;
    virtual std::expected<bool, int> WriteTry(const std::string& s) = 0;
    virtual std::expected<bool, int> WriteSuccess(const std::string& match) = 0;
    virtual std::expected<bool, int> WriteFail() = 0;
    virtual int MaxLineLength() const;
private:
    int maxLineLength;
};

} // namespace soul_expected::lexer
