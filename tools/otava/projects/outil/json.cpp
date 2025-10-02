// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util.json;

import util.error;
import util.unicode;
import util.text.util;

namespace util {

std::string JsonValueTypeStr(JsonValueType type)
{
    std::string str;
    if ((type & JsonValueType::object) != JsonValueType::none)
    {
        if (!str.empty())
        {
            str.append(" | ");
        }
        str.append("object");
    }
    if ((type & JsonValueType::array) != JsonValueType::none)
    {
        if (!str.empty())
        {
            str.append(" | ");
        }
        str.append("array");
    }
    if ((type & JsonValueType::string) != JsonValueType::none)
    {
        if (!str.empty())
        {
            str.append(" | ");
        }
        str.append("string");
    }
    if ((type & JsonValueType::number) != JsonValueType::none)
    {
        if (!str.empty())
        {
            str.append(" | ");
        }
        str.append("number");
    }
    if ((type & JsonValueType::boolean) != JsonValueType::none)
    {
        if (!str.empty())
        {
            str.append(" | ");
        }
        str.append("boolean");
    }
    return str;
}

JsonValue::JsonValue(JsonValueType type_) : type(type_)
{
}

JsonValue::~JsonValue()
{
}

std::expected<bool, int> JsonValue::Write(CodeFormatter& formatter)
{
    std::expected<std::string, int> rv = ToString();
    if (!rv) return std::unexpected<int>(rv.error());
    std::string str = *rv;
    formatter.Write(str);
    return std::expected<bool, int>(true);
}

JsonString::JsonString() : JsonValue(JsonValueType::string), value()
{
}

JsonString::JsonString(const std::u32string& value_) : JsonValue(JsonValueType::string), value(value_)
{
}

JsonValue* JsonString::Clone() const
{
    return new JsonString(value);
}

void JsonString::SetValue(const std::u32string& value_)
{
    value = value_;
}

void JsonString::Append(char32_t c)
{
    value.append(1, c);
}

std::expected<std::u16string, int> JsonString::JsonCharStr(char32_t c) const
{
    std::u16string result;
    std::u32string s(1, c);
    std::expected<std::u16string, int> rv = ToUtf16(s);
    if (!rv) return rv;
    std::u16string t = *rv;
    for (char16_t x : t)
    {
        switch (x)
        {
        case '"': 
        { 
            result.append(1, '\\');
            result.append(1, '"');
            break; 
        }
        case '\\': 
        { 
            result.append(2, '\\');
            break; 
        }
        case '\b': 
        { 
            result.append(1, '\\');
            result.append(1, 'b');
            break; 
        }
        case '\f': 
        { 
            result.append(1, '\\');
            result.append(1, 'f');
            break;
        }
        case '\n': 
        { 
            result.append(1, '\\');
            result.append(1, 'n');
            break;
        }
        case '\r': 
        { 
            result.append(1, '\\');
            result.append(1, 'r');
            break;
        }
        case '\t': 
        { 
            result.append(1, '\\');
            result.append(1, 't');
            break;
        }
        default:
        {
            if (x >= 32 && x <= 126)
            {
                result.append(1, x);
            }
            else
            {
                std::expected<std::u16string, int> rv = ToUtf16(ToHexString(static_cast<std::uint16_t>(x)));
                if (!rv) return rv;
                std::u16string u16str = std::move(*rv);
                result.append(1, '\\').append(1, 'u').append(u16str);
            }
            break;
        }
        }
    }
    return std::expected<std::u16string, int>(result);
}

std::expected<std::string, int> JsonString::ToString() const
{
    std::u16string s;
    for (char32_t c : value)
    {
        std::expected<std::u16string, int> rv = JsonCharStr(c);
        if (!rv) return std::unexpected<int>(rv.error());
        std::u16string str = std::move(*rv);
        s.append(std::move(str));
    }
    std::expected<std::string, int> rv = ToUtf8(s);
    if (!rv) return rv;
    return "\"" + *rv + "\"";
}

JsonNumber::JsonNumber() : JsonValue(JsonValueType::number), value(0.0)
{
}

JsonNumber::JsonNumber(double value_) : JsonValue(JsonValueType::number), value(value_)
{
}

JsonValue* JsonNumber::Clone() const
{
    return new JsonNumber(value);
}

std::expected<std::string, int> JsonNumber::ToString() const
{
    if (value == static_cast<std::int64_t>(value))
    {
        return ToUtf8(std::to_string(static_cast<std::int64_t>(value)));
    }
    else
    {
        return ToUtf8(std::to_string(value));
    }
}

JsonBool::JsonBool() : JsonValue(JsonValueType::boolean), value(false)
{
}

JsonBool::JsonBool(bool value_) : JsonValue(JsonValueType::boolean), value(value_)
{
}

JsonValue* JsonBool::Clone() const
{
    return new JsonBool(value);
}

std::expected<std::string, int> JsonBool::ToString() const
{
    return value ? std::expected<std::string, int>("true") : std::expected < std::string, int>("false");
}

JsonObject::JsonObject() : JsonValue(JsonValueType::object), fieldValues(), fieldMap()
{
}

void JsonObject::AddField(const std::u32string& fieldName, std::unique_ptr<JsonValue>&& fieldValue)
{
    fieldMap[fieldName] = fieldValue.get();
    fieldValues.push_back(std::move(fieldValue));
}

JsonValue* JsonObject::GetField(const std::u32string& fieldName) const
{
    auto it = fieldMap.find(fieldName);
    if (it != fieldMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

bool JsonObject::HasField(const std::u32string& fieldName) const
{
    return GetField(fieldName) != nullptr;
}

std::expected<JsonString*, int> JsonObject::GetStringField(const std::u32string& fieldName) const
{
    JsonValue* value = GetField(fieldName);
    if (value)
    {
        if (value->IsString())
        {
            JsonString* str = static_cast<JsonString*>(value);
            return std::expected<JsonString*, int>(str);
        }
        else
        {
            std::expected<std::string, int> rv = ToUtf8(fieldName);
            if (!rv) return std::unexpected<int>(rv.error());
            std::string fieldNameStr = *rv;
            return std::unexpected<int>(AllocateError("error getting field " + fieldNameStr + ": string field expected"));
        }
    }
    else
    {
        JsonString* null = nullptr;
        return std::expected<JsonString*, int>(null);
    }
}

std::expected<JsonNumber*, int> JsonObject::GetNumberField(const std::u32string& fieldName) const
{
    JsonValue* value = GetField(fieldName);
    if (value)
    {
        if (value->IsNumber())
        {
            JsonNumber* number = static_cast<JsonNumber*>(value);
            return std::expected<JsonNumber*, int>(number);
        }
        else
        {
            std::expected<std::string, int> rv = ToUtf8(fieldName);
            if (!rv) return std::unexpected<int>(rv.error());
            std::string fieldNameStr = *rv;
            return std::unexpected<int>(AllocateError("error getting field " + fieldNameStr + ": number field expected"));
        }
    }
    else
    {
        JsonNumber* null = nullptr;
        return std::expected<JsonNumber*, int>(null);
    }
}

std::expected<JsonBool*, int> JsonObject::GetBooleanField(const std::u32string& fieldName) const
{
    JsonValue* value = GetField(fieldName);
    if (value)
    {
        if (value->IsBoolean())
        {
            JsonBool* boolean = static_cast<JsonBool*>(value);
            return std::expected<JsonBool*, int>(boolean);
        }
        else
        {
            std::expected<std::string, int> rv = ToUtf8(fieldName);
            if (!rv) return std::unexpected<int>(rv.error());
            std::string fieldNameStr = *rv;
            return std::unexpected<int>(AllocateError("error getting field " + fieldNameStr + ": Boolean field expected"));
        }
    }
    else
    {
        JsonBool* null = nullptr;
        return std::expected<JsonBool*, int>(null);
    }
}

std::expected<JsonObject*, int> JsonObject::GetObjectField(const std::u32string& fieldName) const
{
    JsonValue* value = GetField(fieldName);
    if (value)
    {
        if (value->IsObject())
        {
            JsonObject* object = static_cast<JsonObject*>(value);
            return std::expected<JsonObject*, int>(object);
        }
        else
        {
            std::expected<std::string, int> rv = ToUtf8(fieldName);
            if (!rv) return std::unexpected<int>(rv.error());
            std::string fieldNameStr = *rv;
            return std::unexpected<int>(AllocateError("error getting field " + fieldNameStr + ": object field expected"));
        }
    }
    else
    {
        JsonObject* null = nullptr;
        return std::expected<JsonObject*, int>(null);
    }
}

std::expected<JsonArray*, int> JsonObject::GetArrayField(const std::u32string& fieldName) const
{
    JsonValue* value = GetField(fieldName);
    if (value)
    {
        if (value->IsArray())
        {
            JsonArray* array = static_cast<JsonArray*>(value);
            return std::expected<JsonArray*, int>(array);
        }
        else
        {
            std::expected<std::string, int> rv = ToUtf8(fieldName);
            if (!rv) return std::unexpected<int>(rv.error());
            std::string fieldNameStr = *rv;
            return std::unexpected<int>(AllocateError("error getting field " + fieldNameStr + ": array field expected"));
        }
    }
    else
    {
        JsonArray* null = nullptr;
        return std::expected<JsonArray*, int>(null);
    }
}

JsonValue* JsonObject::Clone() const
{
    JsonObject* clone = new JsonObject();
    for (const auto& p : fieldMap)
    {
        clone->AddField(p.first, std::unique_ptr<JsonValue>(p.second->Clone()));
    }
    return clone;
}

std::expected<std::string, int> JsonObject::ToString() const
{
    std::string str = "{";
    bool first = true;
    for (const auto& p : fieldMap)
    {
        JsonString s(p.first);
        JsonValue* v = p.second;
        if (first)
        {
            first = false;
        }
        else
        {
            str.append(", ");
        }
        std::expected<std::string, int> rv = s.ToString();
        if (!rv) return rv;
        std::expected<std::string, int> vrv = v->ToString();
        if (!vrv) return vrv;
        str.append(*rv).append(":").append(*vrv);
    }
    str.append("}");
    return std::expected<std::string, int>(str);
}

std::expected<bool, int> JsonObject::Write(CodeFormatter& formatter)
{
    formatter.WriteLine("{");
    formatter.IncIndent();
    JsonValueType lastItemType = JsonValueType::object;
    bool first = true;
    for (const auto& p : fieldMap)
    {
        JsonString s(p.first);
        JsonValue* v = p.second;
        if (first)
        {
            first = false;
        }
        else
        {
            formatter.WriteLine(",");
        }
        auto rv = s.Write(formatter);
        if (!rv) return rv;
        formatter.Write(": ");
        if (v->IsObject())
        {
            formatter.WriteLine();
            formatter.IncIndent();
        }
        if (s.Value() == U"content")
        {
            formatter.BeginContent();
        }
        rv = v->Write(formatter);
        if (!rv) return rv;
        if (s.Value() == U"content")
        {
            formatter.EndContent();
        }
        if (v->IsObject())
        {
            formatter.DecIndent();
        }
        lastItemType = v->Type();
    }
    formatter.DecIndent();
    if (lastItemType != JsonValueType::array && lastItemType != JsonValueType::object)
    {
        formatter.WriteLine();
    }
    formatter.WriteLine("}");
    return std::expected<bool, int>(true);
}

JsonArray::JsonArray() : JsonValue(JsonValueType::array)
{
}

void JsonArray::AddItem(std::unique_ptr<JsonValue>&& item)
{
    items.push_back(std::move(item));
}

JsonValue* JsonArray::Clone() const
{
    JsonArray* clone = new JsonArray();
    for (const std::unique_ptr<JsonValue>& item : items)
    {
        clone->AddItem(std::unique_ptr<JsonValue>(item->Clone()));
    }
    return clone;
}

std::expected<JsonValue*, int> JsonArray::GetItem(int index) const
{
    if (index >= 0 && index < items.size())
    {
        return std::expected<JsonValue*, int>(items[index].get());
    }
    else
    {
        return std::unexpected<int>(AllocateError("invalid JSON array index"));
    }
}

std::expected<JsonValue*, int> JsonArray::operator[](int index) const
{
    return GetItem(index);
}

std::expected<std::string, int> JsonArray::ToString() const
{
    std::string str = "[";
    bool first = true;
    for (const std::unique_ptr<JsonValue>& item : items)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            str.append(", ");
        }
        std::expected<std::string, int> rv = item->ToString();
        if (!rv) return rv;
        str.append(*rv);
    }
    str.append("]");
    return std::expected<std::string, int>(str);
}

std::expected<bool, int> JsonArray::Write(CodeFormatter& formatter)
{
    formatter.WriteLine("[");
    formatter.IncIndent();
    JsonValueType lastItemType = JsonValueType::array;
    bool first = true;
    for (const std::unique_ptr<JsonValue>& item : items)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            formatter.WriteLine(",");
        }
        std::expected<bool, int> rv = item->Write(formatter);
        if (!rv) return rv;
        lastItemType = item->Type();
    }
    formatter.DecIndent();
    if (lastItemType != JsonValueType::array && lastItemType != JsonValueType::object)
    {
        formatter.WriteLine();
    }
    formatter.WriteLine("]");
    return std::expected<bool, int>(true);
}

JsonNull::JsonNull() : JsonValue(JsonValueType::null)
{
}

JsonValue* JsonNull::Clone() const
{
    return new JsonNull();
}

std::expected<std::string, int> JsonNull::ToString() const
{
    return std::expected<std::string, int>("null");
}

} // namespace util
