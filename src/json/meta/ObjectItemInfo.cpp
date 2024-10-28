#include "ObjectItemInfo.h"

namespace json
{
    ObjectItemInfo::ObjectItemInfo(char keyQuotesType)
    {
        this->keyQuotesType = keyQuotesType;
    }
    
    char ObjectItemInfo::getKeyQuotesType()
    {
        return this->keyQuotesType;
    }
    
    void ObjectItemInfo::endKeyParse()
    {
        this->keyParsed = true;
    }
    
    bool ObjectItemInfo::isKeyParsed()
    {
        return this->keyParsed;
    }
    
    void ObjectItemInfo::setValue(MetaInfo* value)
    {
        this->value = value;
    }
    
    MetaInfo* ObjectItemInfo::getValue()
    {
        return this->value;
    }
    
    void ObjectItemInfo::appendToKey(char c)
    {
        if (this->key.length())
            prevKeyChar = this->key[this->key.length() - 1];
    
        this->key += c;
    }
    
    bool ObjectItemInfo::isEscaped()
    {
        return this->prevKeyChar == '\\';
    }
    
    std::string ObjectItemInfo::getKey()
    {
        return this->key;
    }
    
    PARSING_ELEMENT ObjectItemInfo::getType()
    {
        return PARSING_ELEMENT::OBJECT_ITEM;
    }
    
    std::string ObjectItemInfo::toString()
    {
        return "\"" + this->getKey() + "\": " + this->getValue()->toString();
    }
}