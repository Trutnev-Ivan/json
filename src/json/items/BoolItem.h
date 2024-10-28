#pragma once
#include "JsonItem.h"

namespace json
{
    class BoolItem: public JsonItem<bool>
    {
    public:
        BoolItem(bool value):
            JsonItem<bool>(value)
            {}
        virtual std::string toString() const override;
        friend std::ostream& operator<<(std::ostream& out, const BoolItem& boolItem);
        friend std::ostream& operator<<(std::ostream& out, const BoolItem* boolItem);
    };
}