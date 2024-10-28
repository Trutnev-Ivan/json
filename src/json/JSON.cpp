#include "JSON.h"

namespace json
{
    JSON::JSON()
    {

    }

    JSON::JSON(std::string value)
    {
        if (std::filesystem::is_regular_file(value))
            this->parseFile(value);
        else
            this->parseString(value);
    }

    JSON::~JSON()
    {
        if (this->arrayItem != nullptr)
            delete this->arrayItem;
        if (this->objectItem != nullptr)
            delete this->objectItem;

        this->arrayItem = nullptr;
        this->objectItem = nullptr;
    }

    void JSON::parseFile(std::string path)
    {
        if (!std::filesystem::exists(path))
            throw std::ifstream::failure("File " + path + " not exists");

        if (std::filesystem::path(path).extension() != ".json")
            throw std::ifstream::failure("File extension must be .json");

        std::ifstream* file = new std::ifstream(path);
        JsonParser* parser = new JsonParser(file);

        if (parser->isArray())
            this->arrayItem = parser->getArray();
        else if (parser->isObject())
            this->objectItem = parser->getObject();
        else
        {
            delete file;
            delete parser;
            throw JsonTopElementException();
        }

        file->close();
        delete file;
        delete parser;
    }

    void JSON::parseString(std::string value)
    {
        JsonParser* parser = new JsonParser(value);

        if (parser->isArray())
            this->arrayItem = parser->getArray();
        else if (parser->isObject())
            this->objectItem = parser->getObject();
        else
        {
            delete parser;
            throw JsonTopElementException();
        }

        delete parser;
    }

    bool JSON::isArray() const
    {
        return this->arrayItem != nullptr;
    }

    bool JSON::isObject() const
    {
        return this->objectItem != nullptr;
    }

    CommonItem JSON::get(int index) const
    {
        if (this->isObject())
            throw JsonTypeException();

        return this->arrayItem->get(index);
    }

    CommonItem JSON::get(std::string key) const
    {
        if (this->isArray())
            throw JsonTypeException();

        return this->objectItem->get(key);
    }

    int JSON::size() const
    {
        if (this->isArray())
            return this->arrayItem->getLength();
        else
            return this->objectItem->getLength();
    }

    std::list<CommonItem>::const_iterator JSON::arrayBegin()
    {
        if (this->isObject())
            throw JsonTypeException();

        return this->arrayItem->begin();
    }

    std::list<CommonItem>::const_iterator JSON::arrayEnd()
    {
        if (this->isObject())
            throw JsonTypeException();

        return this->arrayItem->end();
    }

    std::map<std::string, CommonItem>::const_iterator JSON::objectBegin()
    {
        if (this->isArray())
            throw JsonTypeException();

        return this->objectItem->begin();
    }

    std::map<std::string, CommonItem>::const_iterator JSON::objectEnd()
    {
        if (this->isArray())
            throw JsonTypeException();

        return this->objectItem->end();
    }

    void JSON::erase(int index)
    {
        if (this->isObject())
            throw JsonTypeException();

        this->arrayItem->erase(index);
    }

    void JSON::erase(int start, int end)
    {
        if (this->isObject())
            throw JsonTypeException();

        this->arrayItem->erase(start, end);
    }

    void JSON::erase(std::string key)
    {
        if (this->isArray())
            throw JsonTypeException();

        this->objectItem->erase(key);
    }

    void JSON::erase(std::list<CommonItem>::const_iterator iterator)
    {
        if (this->isObject())
            throw JsonTypeException();

        this->arrayItem->erase(iterator);
    }

    void JSON::erase(
        std::list<CommonItem>::const_iterator start,
        std::list<CommonItem>::const_iterator end
    )
    {
        if (this->isObject())
            throw JsonTypeException();

        this->arrayItem->erase(start, end);
    }
    void JSON::erase(std::map<std::string, CommonItem>::const_iterator iterator)
    {
        if (this->isArray())
            throw JsonTypeException();

        this->objectItem->erase(iterator);
    }

    void JSON::erase(
        std::map<std::string, CommonItem>::const_iterator start,
        std::map<std::string, CommonItem>::const_iterator end
    )
    {
        if (this->isArray())
            throw JsonTypeException();

        this->objectItem->erase(start, end);
    }

    bool JSON::contains(std::string key) const
    {
        if (this->isArray())
            throw JsonTypeException();

        return this->objectItem->contains(key);
    }

    CommonItem JSON::pop()
    {
        if (this->isObject())
            throw JsonTypeException();

        return this->arrayItem->pop();
    }

    std::string JSON::toString() const
    {
        if (this->isArray())
            return this->arrayItem->toString();

        return this->objectItem->toString();
    }

    std::ostream& operator<<(std::ostream& out, const JSON& json)
    {
        out << json.toString();
        return out;
    }

    std::ostream& operator<<(std::ostream& out, const JSON* json)
    {
        out << json->toString();
        return out;
    }

    CommonItem JSON::operator[](int index) const
    {
        return this->get(index);
    }

    CommonItem JSON::operator[](std::string key) const
    {
        return this->get(key);
    }

    std::ifstream& operator>>(std::ifstream& in, JSON& json)
    {
        JsonParser* parser = new JsonParser(&in);

        if (parser->isArray())
            json.arrayItem = parser->getArray();
        else if (parser->isObject())
            json.objectItem = parser->getObject();
        else
            throw JsonTopElementException();

        return in;
    }

    std::ifstream& operator>>(std::ifstream& in, JSON* json)
    {
    JsonParser* parser = new JsonParser(&in);

        if (parser->isArray())
            json->arrayItem = parser->getArray();
        else if (parser->isObject())
            json->objectItem = parser->getObject();
        else
            throw JsonTopElementException();

        return in;
    }
}
