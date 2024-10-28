#include "JsonTypeException.h"

namespace json
{
    const char* JsonTypeException::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
    {
        return "Invalid json type element";
    }
}