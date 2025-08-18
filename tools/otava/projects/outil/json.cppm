// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util.json;

import std;
import util.code.formatter;

export namespace util {

namespace json {}

enum class JsonValueType : int
{
    none = 0,
    object = 1 << 0,
    array = 1 << 1,
    string = 1 << 2,
    number = 1 << 3,
    boolean = 1 << 4,
    null = 1 << 5,
    any = object | array | string | number | boolean | null
};

constexpr JsonValueType operator|(JsonValueType left, JsonValueType right)
{
    return JsonValueType(int(left) | int(right));
}

constexpr JsonValueType operator&(JsonValueType left, JsonValueType right)
{
    return JsonValueType(int(left) & int(right));
}

constexpr JsonValueType operator~(JsonValueType type)
{
    return JsonValueType(~int(type));
}

std::string JsonValueTypeStr(JsonValueType type);

class JsonValue
{
public:
    JsonValue(JsonValueType type_);
    JsonValue(const JsonValue&) = delete;
    JsonValue& operator=(const JsonValue&) = delete;
    virtual ~JsonValue();
    virtual JsonValue* Clone() const = 0;
    inline JsonValueType Type() const { return type; }
    inline bool IsObject() const { return type == JsonValueType::object; }
    inline bool IsArray() const { return type == JsonValueType::array; }
    inline bool IsStructuredValue() const { return IsObject() || IsArray(); }
    inline bool IsString() const { return type == JsonValueType::string; }
    inline bool IsNumber() const { return type == JsonValueType::number; }
    inline bool IsBoolean() const { return type == JsonValueType::boolean; }
    inline bool IsNull() const { return type == JsonValueType::null; }
    virtual std::expected<std::string, int> ToString() const = 0;
    virtual std::expected<bool, int> Write(CodeFormatter& formatter);
private:
    JsonValueType type;
};

class JsonString : public JsonValue
{
public:
    JsonString();
    JsonString(const std::u32string& value_);
    void Append(char32_t c);
    JsonValue* Clone() const override;
    inline const std::u32string& Value() const { return value; }
    void SetValue(const std::u32string& value_);
    std::expected<std::u16string, int> JsonCharStr(char32_t c) const;
    std::expected<std::string, int> ToString() const override;
private:
    std::u32string value;
};

class JsonNumber : public JsonValue
{
public:
    JsonNumber();
    JsonNumber(double value_);
    JsonValue* Clone() const override;
    inline double Value() const { return value; }
    std::expected<std::string, int> ToString() const override;
private:
    double value;
};

class JsonBool : public JsonValue
{
public:
    JsonBool();
    JsonBool(bool value_);
    JsonValue* Clone() const override;
    inline bool Value() const { return value; }
    std::expected<std::string, int> ToString() const override;
private:
    bool value;
};

class JsonArray;

class JsonObject : public JsonValue
{
public:
    JsonObject();
    void AddField(const std::u32string& fieldName, std::unique_ptr<JsonValue>&& fieldValue);
    inline int FieldCount() const { return static_cast<int>(fieldValues.size()); }
    JsonValue* GetField(const std::u32string& fieldName) const;
    bool HasField(const std::u32string& fieldName) const;
    std::expected<JsonString*, int> GetStringField(const std::u32string& fieldName) const;
    std::expected<JsonNumber*, int> GetNumberField(const std::u32string& fieldName) const;
    std::expected<JsonBool*, int> GetBooleanField(const std::u32string& fieldName) const;
    std::expected<JsonObject*, int> GetObjectField(const std::u32string& fieldName) const;
    std::expected<JsonArray*, int> GetArrayField(const std::u32string& fieldName) const;
    JsonValue* Clone() const override;
    std::expected<std::string, int> ToString() const override;
    std::expected<bool, int> Write(CodeFormatter& formatter) override;
private:
    std::vector<std::unique_ptr<JsonValue>> fieldValues;
    std::map<std::u32string, JsonValue*> fieldMap;
};

class JsonArray : public JsonValue
{
public:
    JsonArray();
    void AddItem(std::unique_ptr<JsonValue>&& item);
    inline int Count() const { return static_cast<int>(items.size()); }
    std::expected<JsonValue*, bool> GetItem(int index) const;
    std::expected<JsonValue*, bool> operator[](int index) const;
    JsonValue* Clone() const override;
    std::expected<std::string, int> ToString() const override;
    std::expected<bool, int> Write(CodeFormatter& formatter) override;
private:
    std::vector<std::unique_ptr<JsonValue>> items;
};

class JsonNull : public JsonValue
{
public:
    JsonNull();
    JsonValue* Clone() const override;
    std::expected<std::string, int> ToString() const override;
};

} // namespace util
