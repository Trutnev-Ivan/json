#pragma once
#include "JsonItem.h"

namespace json
{
    class StringItem: public JsonItem<std::string>
    {
    public:
        StringItem(std::string value):
            JsonItem<std::string>(value)
        {}
        virtual std::string toString() const override;
        friend std::ostream& operator<<(std::ostream& out, const StringItem& jsonItem);
        friend std::ostream& operator<<(std::ostream& out, const StringItem* jsonItem);
    };
}