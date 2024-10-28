#pragma once

#include <string>
#include "../exceptions/JsonCastTypeException.h"
#include "../exceptions/JsonItemTypeException.h"

namespace json
{
    class StringItem;
    class BoolItem;
    class ObjectItem;
    class ArrayItem;
    class FloatItem;
    class IntItem;

    template<class T>
    class JsonItem
    {
    protected:
        T value;
    public:

        JsonItem(T value)
        {
            this->setValue(value);
        }

        virtual T getValue() const
        {
            return this->value;
        }

        virtual void setValue(T value)
        {
            this->value = value;
        }

        virtual std::string toString() const {return "";};

        template<class instanceType>
        static bool isInstanceOfJsonItem()
        {
            return std::is_base_of_v<StringItem, instanceType>
            || std::is_base_of_v<BoolItem, instanceType>
            || std::is_base_of_v<ArrayItem, instanceType>
            || std::is_base_of_v<FloatItem, instanceType>
            || std::is_base_of_v<IntItem, instanceType>
            || std::is_base_of_v<ObjectItem, instanceType>;
        }
    };
}