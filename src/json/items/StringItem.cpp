#include "StringItem.h"

namespace json
{
    std::string StringItem::toString() const
    {
        return this->getValue();
    }
    
    std::ostream& operator<<(std::ostream& out, const StringItem& jsonItem)
    {
        out << jsonItem.toString();
        return out;
    }
    
    std::ostream& operator<<(std::ostream& out, const StringItem* jsonItem)
    {
        out << jsonItem->toString();
        return out;
    }
}