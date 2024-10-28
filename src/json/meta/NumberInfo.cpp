#include "NumberInfo.h"

namespace json
{
    PARSING_ELEMENT NumberInfo::getType()
    {
        return PARSING_ELEMENT::NUMBER;
    }
    
    void NumberInfo::appendChar(char c)
    {
        if (!std::isdigit(c) && c != '.' && c != '-' || c == '-' && this->value.size() != 0)
            throw JsonParseException(c);
    
        this->value += c;
    }
    
    std::string NumberInfo::getValue()
    {
        return this->value;
    }
    
    std::string NumberInfo::toString()
    {
        return this->getValue();
    }
    
    bool NumberInfo::isFloat()
    {
        return this->value.find('.') != std::string::npos;
    }
}