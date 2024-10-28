#include "JsonTopElementException.h"

namespace json
{
    const char* JsonTopElementException::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
    {
        return "Top element in json must be object or array";
    }
}