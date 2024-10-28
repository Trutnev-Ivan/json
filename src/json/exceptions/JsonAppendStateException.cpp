#include "JsonAppendStateException.h"

namespace json
{
    const char* JsonAppendStateException::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
    {
        return "Invalid append state. Only array item or object item can append.";
    }
}