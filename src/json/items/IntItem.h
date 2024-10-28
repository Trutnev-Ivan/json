#pragma once
#include "JsonItem.h"

namespace json
{
    class IntItem: public JsonItem<int>
    {
    public:
        IntItem(int value):
            JsonItem(value)
            {}
        virtual std::string toString() const override;
        friend std::ostream& operator<<(std::ostream& out, const IntItem& intItem);
        friend std::ostream& operator<<(std::ostream& out, const IntItem* intItem);
    };
}