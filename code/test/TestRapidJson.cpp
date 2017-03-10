#include <gtest/gtest.h>
#include <rapidjson/document.h>

using namespace rapidjson;

TEST(TestRapidJson, should_parse_json_correctly)
{
    const char* json = R"({
                            "hello": "world",
                            "t": true ,
                            "f": false,
                            "n": null,
                            "i": 123,
                            "pi": 3.1416,
                            "a": [1, 2, 3, 4]
                         })";
    Document document;
    document.Parse(json);

    ASSERT_TRUE(document.IsObject());

    ASSERT_TRUE(document.HasMember("hello"));
    ASSERT_TRUE(document["hello"].IsString());
    ASSERT_EQ(std::string("world"), document["hello"].GetString());

    ASSERT_TRUE(document["t"].IsBool());
    ASSERT_TRUE(document["t"].GetBool());

    ASSERT_FALSE(document["f"].GetBool());

    ASSERT_TRUE(document["n"].IsNull());

    ASSERT_TRUE(document["i"].IsNumber());
    ASSERT_TRUE(document["i"].IsInt());          
    ASSERT_EQ(123, document["i"].GetInt());

    ASSERT_TRUE(document["pi"].IsNumber());
    ASSERT_TRUE(document["pi"].IsDouble());
    ASSERT_NEAR(3.1416, document["pi"].GetDouble(), 0.0001);    

    const Value& a = document["a"];
    ASSERT_TRUE(a.IsArray());
    for (SizeType i = 0; i < a.Size(); i++)
            ASSERT_EQ(i + 1, a[i].GetInt());    
}