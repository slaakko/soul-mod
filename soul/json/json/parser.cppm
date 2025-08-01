// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.json.parser;

import util.json;
import std;

export namespace soul::json {

std::unique_ptr<util::JsonValue> ParseJsonValue(const std::u32string& jsonText, const std::string& fileName);

std::unique_ptr<util::JsonValue> ParseJsonValue(const std::string& jsonText, const std::string& fileName);

std::unique_ptr<util::JsonValue> ParseJsonValue(const std::string& jsonText);

std::unique_ptr<util::JsonObject> ParseJsonObject(const std::string& jsonText, const std::string& fileName);

std::unique_ptr<util::JsonObject> ParseJsonObject(const std::string& jsonText);

} // namespace soul::json
