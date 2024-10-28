#include "ArrayItemInfo.h"

namespace json
{
    PARSING_ELEMENT ArrayItemInfo::getType()
    {
        return PARSING_ELEMENT::ARRAY_ITEM;
    }
    
    void ArrayItemInfo::setValue(MetaInfo* value)
    {
        this->value = value;
    }
    
    MetaInfo* ArrayItemInfo::getValue()
    {
        return this->value;
    }
    
    std::string ArrayItemInfo::toString()
    {
        return this->value->toString();
    }
}