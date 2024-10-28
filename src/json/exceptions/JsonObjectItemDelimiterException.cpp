#include "JsonObjectItemDelimiterException.h"

namespace json
{
    const char* JsonObjectItemDelimiterException::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
    {
        return "No object item delimiter (char ':' after key)";
    }
}