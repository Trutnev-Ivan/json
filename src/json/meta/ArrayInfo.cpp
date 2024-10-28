#include "ArrayInfo.h"

namespace json
{
    PARSING_ELEMENT ArrayInfo::getType() 
    {
        return PARSING_ELEMENT::ARRAY;
    }

    void ArrayInfo::append(ArrayItemInfo* item)
    {
        this->items.push_back(item);
    }

    std::string ArrayInfo::toString()
    {
        std::string str = "[";

        for (ArrayItemInfo* item: this->items)
        {
            str += item->toString() + ", ";
        }

        str += "]";

        return str;
    }

    int ArrayInfo::size()
    {
        return this->items.size();
    }

    ArrayItemInfo* ArrayInfo::operator[](int index)
    {
        return this->items[index];
    }
}
