#include "JsonParseException.h"

namespace json
{
    JsonParseException::JsonParseException(char c)
    {
        this->invalidChar = c;
    }

    const char* JsonParseException::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
    {
        return "Invalid char: " + this->invalidChar;
    }
}