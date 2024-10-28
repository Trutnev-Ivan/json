#include "JsonEmptyNextElementException.h"

namespace json
{
    const char* JsonEmptyNextElementException::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
    {
        return "No next element";
    }
}