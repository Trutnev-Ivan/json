#include "JsonParser.h"

namespace json
{
    JsonParser::JsonParser(std::ifstream* file)
    {
        this->parsingElement = new std::stack<MetaInfo*>;
        JsonParserState* state = new StartState(this->parsingElement);
    
        while (!file->eof())
        {
            char c = file->get();
            state = state->next(c);
        }
    
        if (typeid(*state).hash_code() != typeid(EndState).hash_code())
            throw JsonTopElementException();

        this->topElement = state->getTopElement();
        delete state;
    }
    
    JsonParser::JsonParser(std::string json)
    {
        this->parsingElement = new std::stack<MetaInfo*>;
        JsonParserState* state = new StartState(this->parsingElement);
    
        for (char c: json)
        {
            state = state->next(c);
        }

        if (typeid(*state).hash_code() != typeid(EndState).hash_code())
        {
            delete state;
            throw JsonTopElementException();
        }
    
        this->topElement = state->getTopElement();
        delete state;
    }
    
    JsonParser::~JsonParser()
    {
        if (this->parsingElement != nullptr)
        {
            while (!this->parsingElement->empty())
            {
                switch (this->parsingElement->top()->getType())
                {
                    case PARSING_ELEMENT::ARRAY:
                        this->deleteObject(this->parsingElement->top());
                        break;
                    case PARSING_ELEMENT::OBJECT:
                        this->deleteArray(this->parsingElement->top());
                        break;
                    default:
                        delete this->parsingElement->top();
                }
            }

            delete this->parsingElement;
        }
        
        if (this->topElement != nullptr)
        {
            switch (this->topElement->getType())
            {
                case PARSING_ELEMENT::ARRAY:
                    this->deleteArray(this->topElement);
                    break;
                case PARSING_ELEMENT::OBJECT:
                    this->deleteObject(topElement);
                    break;
                default:
                    delete topElement;
            }
        }

    }
    
    void JsonParser::deleteObject(MetaInfo* object)
    {
        ObjectInfo* objectInfo = static_cast<ObjectInfo*>(object);
    
        for (int i = 0; i < objectInfo->size(); ++i)
        {
            ObjectItemInfo* objectItemInfo = (*objectInfo)[i];
    
            switch (objectItemInfo->getValue()->getType())
            {
                case PARSING_ELEMENT::ARRAY:
                    this->deleteArray(objectItemInfo->getValue());
                    break;
                case PARSING_ELEMENT::OBJECT:
                    this->deleteObject(objectItemInfo->getValue());
                    break;
                default:
                    delete objectItemInfo->getValue();
            }
    
            delete objectItemInfo;
        }
    
        delete objectInfo;
    }
    
    void JsonParser::deleteArray(MetaInfo* array)
    {
        ArrayInfo* arrayInfo = static_cast<ArrayInfo*>(array);
    
        for (int i = 0; i < arrayInfo->size(); ++i)
        {
            ArrayItemInfo* arrayItemInfo = (*arrayInfo)[i];
    
            switch (arrayItemInfo->getValue()->getType())
            {
                case PARSING_ELEMENT::ARRAY:
                    this->deleteArray(arrayItemInfo->getValue());
                    break;
                case PARSING_ELEMENT::OBJECT:
                    this->deleteObject(arrayItemInfo->getValue());
                    break;
                default:
                    delete arrayItemInfo->getValue();
            }
    
            delete arrayItemInfo;
        }
    
        delete arrayInfo;
    }
    
    bool JsonParser::isObject()
    {
        return this->topElement->getType() == PARSING_ELEMENT::OBJECT;
    }
    
    bool JsonParser::isArray()
    {
        return this->topElement->getType() == PARSING_ELEMENT::ARRAY;
    }
    
    ArrayItem* JsonParser::parseArray(MetaInfo* item)
    {
        ArrayItem* arrayItem = new ArrayItem;
        ArrayInfo* arrayInfo = static_cast<ArrayInfo*>(item);
    
        for (int i = 0; i < arrayInfo->size(); ++i)
        {
            ArrayItemInfo* arrayItemInfo = (*arrayInfo)[i];
            
            switch (arrayItemInfo->getValue()->getType())
            {
                case PARSING_ELEMENT::ARRAY:
                {
                    arrayItem->push_back<ArrayItem>(this->parseArray(arrayItemInfo->getValue()));
                    break;
                }
                case PARSING_ELEMENT::OBJECT:
                {
                    arrayItem->push_back<ObjectItem>(this->parseObject(arrayItemInfo->getValue()));
                    break;
                }
                case PARSING_ELEMENT::NUMBER:
                {
                    NumberInfo* numberInfo = static_cast<NumberInfo*>(arrayItemInfo->getValue());
                    
                    if (numberInfo->isFloat())
                        arrayItem->push_back<FloatItem>(new FloatItem(std::stof(numberInfo->getValue())));
                    else
                        arrayItem->push_back<IntItem>(new IntItem(std::stoi(numberInfo->getValue())));
    
                    break;
                }
                case PARSING_ELEMENT::BOOL:
                {
                    BoolInfo* boolInfo = static_cast<BoolInfo*>(arrayItemInfo->getValue());
                    arrayItem->push_back<BoolItem>(new BoolItem(boolInfo->getValue() == "true"));
                    break;
                }
                case PARSING_ELEMENT::STRING:
                {
                    StringInfo* stringInfo = static_cast<StringInfo*>(arrayItemInfo->getValue());
                    arrayItem->push_back<StringItem>(new StringItem(stringInfo->getValue()));
                    break;
                }
            }
        }
    
        return arrayItem;
    }
    
    ObjectItem* JsonParser::parseObject(MetaInfo* item)
    {
        ObjectItem* objectItem = new ObjectItem;
        ObjectInfo* objectInfo = static_cast<ObjectInfo*>(item);
    
        for (int i = 0; i < objectInfo->size(); ++i)
        {
            ObjectItemInfo* objectItemInfo = (*objectInfo)[i];
    
            switch (objectItemInfo->getValue()->getType())
            {
                case PARSING_ELEMENT::ARRAY:
                {
                    objectItem->push<ArrayItem>(objectItemInfo->getKey(), 
                    this->parseArray(objectItemInfo->getValue()));
                    break;
                }
                case PARSING_ELEMENT::OBJECT:
                {
                    objectItem->push<ObjectItem>(objectItemInfo->getKey(),
                                                 this->parseObject(objectItemInfo->getValue()));
                    break;
                }
                case PARSING_ELEMENT::NUMBER:
                {
                    NumberInfo* numberInfo = static_cast<NumberInfo*>(objectItemInfo->getValue());
    
                    if (numberInfo->isFloat())
                        objectItem->push<FloatItem>(objectItemInfo->getKey(), 
                                                    new FloatItem(std::stof(numberInfo->getValue())));
                    else
                    objectItem->push<IntItem>(objectItemInfo->getKey(),
                                              new IntItem(std::stoi(numberInfo->getValue())));
    
                    break;
                }
                case PARSING_ELEMENT::BOOL:
                {
                    BoolInfo* boolInfo = static_cast<BoolInfo*>(objectItemInfo->getValue());
                    objectItem->push<BoolItem>(objectItemInfo->getKey(), 
                                               new BoolItem(boolInfo->getValue() == "true"));
                    break;
                }
                case PARSING_ELEMENT::STRING:
                {
                    StringInfo* stringInfo = static_cast<StringInfo*>(objectItemInfo->getValue());
                    objectItem->push<StringItem>(objectItemInfo->getKey(), 
                                                 new StringItem(stringInfo->getValue()));
                    break;
                }
            }
        }
    
        return objectItem;
    }
    
    ArrayItem* JsonParser::getArray()
    {
        return this->parseArray(this->topElement);
    }
    
    ObjectItem* JsonParser::getObject()
    {
        return this->parseObject(this->topElement);
    }
}