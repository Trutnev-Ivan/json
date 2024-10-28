#pragma once
#include "JsonException.h"

namespace json
{
    class JsonParseException: public JsonException
    {
    protected:
        char invalidChar;
    public:
        JsonParseException(char c);
        virtual const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
    };
}