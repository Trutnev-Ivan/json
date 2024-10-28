#include "JsonCastTypeException.h"

namespace json
{
    const char* JsonCastTypeException::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
    {
        return "Json cast type exception";
    }
}