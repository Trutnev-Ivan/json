#include "JsonParseKeyException.h"

namespace json
{
    const char* JsonParseKeyException::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
    {
        return "Error of parsing key object";
    }
}
