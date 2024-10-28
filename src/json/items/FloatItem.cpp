#include "FloatItem.h"

namespace json
{
    std::string FloatItem::toString() const
    {
        return std::to_string(this->getValue());
    }
    
    std::ostream& operator<<(std::ostream& out, const FloatItem& floatItem)
    {
        out << floatItem.toString();
        return out;
    }
    
    std::ostream& operator<<(std::ostream& out, const FloatItem* floatItem)
    {
        out << floatItem->toString();
        return out;
    }
}