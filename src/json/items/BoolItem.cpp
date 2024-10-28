#include "BoolItem.h"

namespace json
{
    std::string BoolItem::toString() const
    {
        if (this->getValue())
            return "true";
    
        return "false";
    }
    
    std::ostream& operator<<(std::ostream& out, const BoolItem& boolItem)
    {
        out << boolItem.toString();
        return out;
    }
    
    std::ostream& operator<<(std::ostream& out, const BoolItem* boolItem)
    {
        out << boolItem->toString();
        return out;
    }
}