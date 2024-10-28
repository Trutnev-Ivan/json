#pragma once

#include <string>
#include <filesystem>
#include <fstream>

#include "parser/JsonParser.h"
#include "exceptions/JsonTypeException.h"

namespace json
{
    using Array = ArrayItem;
    using Object = ObjectItem;
    using Bool = BoolItem;
    using String = StringItem;
    using Int = IntItem;
    using Float = FloatItem;

    class JSON
    {
    protected:
        ArrayItem* arrayItem = nullptr;
        ObjectItem* objectItem = nullptr;
        void parseFile(std::string path);
        void parseString(std::string value);
    public:
        JSON();
        JSON(std::string value);
        ~JSON();
        bool isArray() const;
        bool isObject() const;
        CommonItem get(int index) const;
        CommonItem get(std::string key) const;
        int size() const;
        std::list<CommonItem>::const_iterator arrayBegin();
        std::list<CommonItem>::const_iterator arrayEnd();
        std::map<std::string, CommonItem>::const_iterator objectBegin();
        std::map<std::string, CommonItem>::const_iterator objectEnd();
        void erase(int index);
        void erase(int start, int end);
        void erase(std::string key);
        void erase(std::list<CommonItem>::const_iterator iterator);
        void erase(
            std::list<CommonItem>::const_iterator start,
            std::list<CommonItem>::const_iterator end
        );
        void erase(std::map<std::string, CommonItem>::const_iterator iterator);
        void erase(
            std::map<std::string, CommonItem>::const_iterator start,
            std::map<std::string, CommonItem>::const_iterator end
        );
        bool contains(std::string key) const;
        CommonItem pop();
        std::string toString() const;
        friend std::ostream& operator<<(std::ostream& out, const JSON& json);
        friend std::ostream& operator<<(std::ostream& out, const JSON* json);
        friend std::ifstream& operator>>(std::ifstream& in, JSON& json);
        friend std::ifstream& operator>>(std::ifstream& in, JSON* json);
        CommonItem operator[](int index) const;
        CommonItem operator[](std::string key) const;

        template<class T>
        T* cast(int index) const
        {
            if (this->isObject())
                throw JsonTypeException();

            return this->arrayItem->cast<T>(index);
        }

        template<class T>
        T* cast(std::string key) const
        {
            if (this->isArray())
                throw JsonTypeException();

            return this->objectItem->cast<T>(key);
        }

        template<class T>
        JSON* push(T* item)
        {
            if (this->isObject())
                throw JsonTypeException();

            this->arrayItem->push_back<T>(item);
            return this;
        }

        template<class T>
        JSON* push(std::string key, T* item)
        {
            if (this->isArray())
                throw JsonTypeException();

            this->objectItem->push(key, item);
            return this;
        }

        template<class T>
        JSON* insert(int index, T* item)
        {
            if (this->isObject())
                throw JsonTypeException();

            this->arrayItem->insert<T>(index, item);
            return this;
        }

        template<class T>
        T* pop()
        {
            if (this->isObject())
                throw JsonTypeException();

            return this->arrayItem->pop<T>();
        }
    };
}