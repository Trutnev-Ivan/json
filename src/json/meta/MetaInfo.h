#pragma once
#include <string>
#include "../exceptions/JsonParseException.h"

namespace json
{
    enum PARSING_ELEMENT {
        STRING,
        NUMBER,
        BOOL,
        ARRAY,
        ARRAY_ITEM,
        OBJECT,
        OBJECT_ITEM
    };

    class MetaInfo
    {
    public:
        virtual PARSING_ELEMENT getType() = 0;
        virtual std::string toString() = 0;
    };
}