#include <json/Json.h>
#include "../Test.h"

class JsonItemTest: public Test
{
public:
    virtual void run() override
    {
        ASSERT_EQUALS(json::String("value").getValue(), "value");
        ASSERT_EQUALS(json::String("text").getValue(), "text");
        ASSERT_EQUALS(json::String("1234qwer").getValue(), "1234qwer");

        ASSERT_FLOATS_ARE_SAME(json::Float(2.3).getValue(), 2.3f);
        ASSERT_FLOATS_ARE_SAME(json::Float(2).getValue(), 2.f);
        ASSERT_FLOATS_ARE_SAME(json::Float(1.00023328).getValue(), 1.00023328f);
        ASSERT_FLOATS_ARE_SAME(json::Float(-2.3).getValue(), -2.3f);
        ASSERT_FLOATS_ARE_SAME(json::Float(-2).getValue(), -2.f);
        ASSERT_FLOATS_ARE_SAME(json::Float(-1.00023328).getValue(), -1.00023328f);

        ASSERT_TRUE(json::Bool(true).getValue());
        ASSERT_FALSE(json::Bool(false).getValue());

        ASSERT_EQUALS(json::Int(2).getValue(), 2);
        ASSERT_EQUALS(json::Int(10234).getValue(), 10234);
        ASSERT_EQUALS(json::Int(-2).getValue(), -2);
        ASSERT_EQUALS(json::Int(-10234).getValue(), -10234);

        json::Array array;
        ASSERT_EQUALS(array.getLength(), 0);
        ASSERT_NO_THROWS_EXCEPTION(array.push_back<json::String>(new json::String("test")););
        ASSERT_NO_THROWS_EXCEPTION(array.push_back<json::Int>(new json::Int(5)););
        ASSERT_NO_THROWS_EXCEPTION(array.push_back<json::Float>(new json::Float(-2.5)););
        ASSERT_NO_THROWS_EXCEPTION(array.push_back<json::Bool>(new json::Bool(false)););
        ASSERT_NO_THROWS_EXCEPTION(array.push_back<json::Object>(new json::Object););
        ASSERT_NO_THROWS_EXCEPTION(array.push_back<json::Array>(new json::Array););
        ASSERT_EQUALS(array.getLength(), 6);
        ASSERT_NO_THROWS_EXCEPTION(array.push_back<json::String>(new json::String("qwer")););
        ASSERT_NO_THROWS_EXCEPTION(array.push_back<json::String>(new json::String("sacasd")););
        ASSERT_THROWS_EXCEPTION(array.push_back<std::string>(new std::string("qwerty")), json::JsonItemTypeException);
        ASSERT_THROWS_EXCEPTION(array.push_back<int>(new int(5)), json::JsonItemTypeException);
        ASSERT_THROWS_EXCEPTION(array.push_back<float>(new float(5)), json::JsonItemTypeException);
        ASSERT_THROWS_EXCEPTION(array.push_back<double>(new double(5)), json::JsonItemTypeException);
        ASSERT_THROWS_EXCEPTION(array.push_back<bool>(new bool(5)), json::JsonItemTypeException);
        ASSERT_THROWS_EXCEPTION(array.push_back<char>(new char('c')), json::JsonItemTypeException);
        ASSERT_THROWS_EXCEPTION(array[30], std::out_of_range);
        ASSERT_THROWS_EXCEPTION(array.cast<json::Int>(0), json::JsonCastTypeException);
        ASSERT_EQUALS(array.cast<json::String>(0)->getValue(), "test");
        ASSERT_NO_THROWS_EXCEPTION(array.push_back<json::Int>(new json::Int(2)););
        json::IntItem* intItem = array.pop<json::Int>();
        ASSERT_EQUALS(intItem->getValue(), 2);
        delete intItem;
        ASSERT_THROWS_EXCEPTION(array.pop<json::Bool>(), json::JsonCastTypeException);
        int arrayLength = array.getLength();
        ASSERT_THROWS_EXCEPTION(array.insert<std::string>(1, new std::string("TEST")), json::JsonItemTypeException);
        ASSERT_NO_THROWS_EXCEPTION(array.insert<json::String>(1, new json::String("VALUE")));
        ASSERT_EQUALS(array.getLength(), arrayLength + 1);
        ASSERT_NO_THROWS_EXCEPTION(array.erase(0));
        ASSERT_EQUALS(array.getLength(), arrayLength);
        ASSERT_NO_THROWS_EXCEPTION(array.erase(array.begin(), array.end()));
        ASSERT_EQUALS(array.getLength(), 0);

        json::Object object;
        ASSERT_EQUALS(object.getLength(), 0);
        ASSERT_NO_THROWS_EXCEPTION(object.push<json::String>("string", new json::String("test")));
        ASSERT_NO_THROWS_EXCEPTION(object.push<json::Int>("int", new json::Int(1)));
        ASSERT_NO_THROWS_EXCEPTION(object.push<json::Float>("float", new json::Float(2.5)));
        ASSERT_NO_THROWS_EXCEPTION(object.push<json::Bool>("bool", new json::Bool(true)));
        ASSERT_NO_THROWS_EXCEPTION(object.push<json::Object>("object", new json::Object));
        ASSERT_NO_THROWS_EXCEPTION(object.push<json::Array>("array", new json::Array));
        ASSERT_EQUALS(object.getLength(), 6);
        ASSERT_THROWS_EXCEPTION(object.push<std::string>("val", new std::string("val")), json::JsonItemTypeException);
        ASSERT_THROWS_EXCEPTION(object.push<int>("val", new int(2)), json::JsonItemTypeException);
        ASSERT_THROWS_EXCEPTION(object.push<float>("val", new float(2.523f)), json::JsonItemTypeException);
        ASSERT_THROWS_EXCEPTION(object.push<double>("val", new double(-34.92)), json::JsonItemTypeException);
        ASSERT_THROWS_EXCEPTION(object.push<bool>("val", new bool(false)), json::JsonItemTypeException);
        ASSERT_THROWS_EXCEPTION(object.push<char>("val", new char('c')), json::JsonItemTypeException);
        ASSERT_TRUE(object.contains("string"));
        ASSERT_FALSE(object.contains("key"));
        ASSERT_NO_THROWS_EXCEPTION(object.cast<json::String>("string"));
        ASSERT_THROWS_EXCEPTION(object.cast<std::string>("string"), json::JsonCastTypeException);
        ASSERT_THROWS_EXCEPTION(object.cast<json::Int>("string"), json::JsonCastTypeException);
        ASSERT_THROWS_EXCEPTION(object.cast<json::Float>("string"), json::JsonCastTypeException);
        ASSERT_THROWS_EXCEPTION(object.cast<json::Bool>("string"), json::JsonCastTypeException);
        ASSERT_THROWS_EXCEPTION(object.cast<json::Array>("string"), json::JsonCastTypeException);
        ASSERT_THROWS_EXCEPTION(object.cast<json::Object>("string"), json::JsonCastTypeException);
        int objectLength = object.getLength();
        ASSERT_NO_THROWS_EXCEPTION(object.erase("string"));
        ASSERT_EQUALS(object.getLength(), objectLength - 1);
        ASSERT_NO_THROWS_EXCEPTION(object.erase(object.begin(), object.end()));
        ASSERT_EQUALS(object.getLength(), 0);
    }
};