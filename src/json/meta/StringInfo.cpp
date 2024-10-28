#include "StringInfo.h"

namespace json
{
    StringInfo::StringInfo(char quoteType)
    {
        this->quoteType = quoteType;
    }
    
    char StringInfo::getQuoteType()
    {
        return this->quoteType;
    }
    
    bool StringInfo::isEscaped()
    {
        return this->prevChar == '\\';
    }
    
    std::string StringInfo::getValue()
    {
        return this->value;
    }
    
    void StringInfo::appendChar(char c)
    {
        if (this->value.length())
            this->prevChar = this->value[this->value.length() - 1];
    
        this->value += c;
    }
    
    PARSING_ELEMENT StringInfo::getType()
    {
        return PARSING_ELEMENT::STRING;
    }
    
    std::string StringInfo::toString()
    {
        return "\"" + this->getValue() + "\"";
    }
}