#include "ObjectInfo.h"

namespace json
{
    PARSING_ELEMENT ObjectInfo::getType()
    {
        return PARSING_ELEMENT::OBJECT;
    }

    void ObjectInfo::appendItem(ObjectItemInfo* item)
    {
        this->items.push_back(item);
    }

    std::vector<ObjectItemInfo*> ObjectInfo::getItems()
    {
        return this->items;
    }

    std::string ObjectInfo::toString()
    {
        std::string str = "{\n";

        for (ObjectItemInfo* item: this->items)
        {
            str += item->toString() + ",\n";
        }

        str += "}";
        return str;
    }

    int ObjectInfo::size()
    {
        return this->items.size();
    }

    ObjectItemInfo* ObjectInfo::operator[](int index)
    {
        return this->items[index];
    }
}