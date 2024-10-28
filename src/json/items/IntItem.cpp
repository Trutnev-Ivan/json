#include "IntItem.h"

namespace json
{
    std::string IntItem::toString() const
    {
        return std::to_string(this->getValue());
    }
    
    std::ostream& operator<<(std::ostream& out, const IntItem& intItem)
    {
        out << intItem.toString();
        return out;
    }
    
    std::ostream& operator<<(std::ostream& out, const IntItem* intItem)
    {
        out << intItem->toString();
        return out;
    }
}