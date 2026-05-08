#include <gtest/gtest.h>
#include "json/json.h"

// ── JsonValue 기본 타입 ──────────────────────────────────────

TEST(JsonValueTest, NullDefault) {
    JsonValue v;
    EXPECT_TRUE(v.isNull());
}

TEST(JsonValueTest, BoolValue) {
    JsonValue v(true);
    EXPECT_TRUE(v.isBool());
    EXPECT_TRUE(v.asBool());
}

TEST(JsonValueTest, NumberValue) {
    JsonValue v(3.14);
    EXPECT_TRUE(v.isNumber());
    EXPECT_DOUBLE_EQ(v.asDouble(), 3.14);
}

TEST(JsonValueTest, StringValue) {
    JsonValue v(std::string("hello"));
    EXPECT_TRUE(v.isString());
    EXPECT_EQ(v.asString(), "hello");
}

// ── JsonValue Array / Object ─────────────────────────────────

TEST(JsonValueTest, ArrayAccess) {
    JsonValue arr = JsonValue::makeArray();
    arr.push(JsonValue(1.0));
    arr.push(JsonValue(std::string("two")));

    EXPECT_TRUE(arr.isArray());
    EXPECT_EQ(arr.size(), 2u);
    EXPECT_DOUBLE_EQ(arr[0].asDouble(), 1.0);
    EXPECT_EQ(arr[1].asString(), "two");
}

TEST(JsonValueTest, ObjectAccess) {
    JsonValue obj = JsonValue::makeObject();
    obj["id"]   = JsonValue(42.0);
    obj["name"] = JsonValue(std::string("test"));

    EXPECT_TRUE(obj.isObject());
    EXPECT_DOUBLE_EQ(obj["id"].asDouble(), 42.0);
    EXPECT_EQ(obj["name"].asString(), "test");
}

// ── Json::parse ──────────────────────────────────────────────

TEST(JsonParseTest, ParseString) {
    JsonValue v = Json::parse(R"("hello")");
    EXPECT_EQ(v.asString(), "hello");
}

TEST(JsonParseTest, ParseNumber) {
    JsonValue v = Json::parse("123.45");
    EXPECT_DOUBLE_EQ(v.asDouble(), 123.45);
}

TEST(JsonParseTest, ParseBool) {
    EXPECT_TRUE(Json::parse("true").asBool());
    EXPECT_FALSE(Json::parse("false").asBool());
}

TEST(JsonParseTest, ParseNull) {
    EXPECT_TRUE(Json::parse("null").isNull());
}

TEST(JsonParseTest, ParseObject) {
    JsonValue v = Json::parse(R"({"id":1,"name":"Alice"})");
    EXPECT_DOUBLE_EQ(v["id"].asDouble(), 1.0);
    EXPECT_EQ(v["name"].asString(), "Alice");
}

TEST(JsonParseTest, ParseArray) {
    JsonValue v = Json::parse(R"([1,2,3])");
    EXPECT_EQ(v.size(), 3u);
    EXPECT_DOUBLE_EQ(v[0].asDouble(), 1.0);
}

TEST(JsonParseTest, ParseNestedObject) {
    JsonValue v = Json::parse(R"({"user":{"id":7,"active":true}})");
    EXPECT_DOUBLE_EQ(v["user"]["id"].asDouble(), 7.0);
    EXPECT_TRUE(v["user"]["active"].asBool());
}

// ── Json::stringify 직렬화 후 재파싱 ─────────────────────────

TEST(JsonSerializeTest, RoundTrip) {
    JsonValue original = Json::parse(R"({"id":1,"name":"test","values":[1,2,3]})");
    std::string text   = Json::stringify(original);
    JsonValue restored = Json::parse(text);

    EXPECT_DOUBLE_EQ(restored["id"].asDouble(), 1.0);
    EXPECT_EQ(restored["name"].asString(), "test");
    EXPECT_EQ(restored["values"].size(), 3u);
}

// ── JsonParseError 예외 ───────────────────────────────────────

TEST(JsonParseTest, InvalidJsonThrows) {
    EXPECT_THROW(Json::parse("{invalid}"), JsonParseError);
}

TEST(JsonParseTest, EmptyStringThrows) {
    EXPECT_THROW(Json::parse(""), JsonParseError);
}
