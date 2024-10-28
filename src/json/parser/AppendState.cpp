#include "AppendState.h"

namespace json
{
    AppendState::AppendState(std::stack<MetaInfo*>* stack):
        JsonParserState(stack)
        {}
    
    JsonParserState* AppendState::next(char c)
    {
        MetaInfo* metaInfo = this->parsingElement->top();
        this->parsingElement->pop();
    
        switch (metaInfo->getType())
        {
            case PARSING_ELEMENT::OBJECT_ITEM:
                return this->appendToObject(metaInfo, c==',');
            case PARSING_ELEMENT::ARRAY_ITEM:
                return this->appendToArray(metaInfo, c==',');
            default:
                return this->append(metaInfo);
        }
    }
    
    JsonParserState* AppendState::appendToObject(MetaInfo* metaInfo, bool mustNextElem)
    {
        ObjectItemInfo* objectItemInfo = static_cast<ObjectItemInfo*>(metaInfo);
        ObjectInfo* objectInfo = static_cast<ObjectInfo*>(this->parsingElement->top());
    
        objectInfo->appendItem(objectItemInfo);
        ObjectState* objectState = new ObjectState(this->parsingElement);
        
        if (mustNextElem)
            objectState->mustNextElem();
    
        return objectState;
    }
    
    JsonParserState* AppendState::appendToObjectItem(MetaInfo* metaInfo)
    {
        ObjectItemInfo* objectItemInfo = static_cast<ObjectItemInfo*>(this->parsingElement->top());
        objectItemInfo->setValue(metaInfo);
    
        return new ObjectItemState(this->parsingElement);
    }
    
    JsonParserState* AppendState::appendToArrayItem(MetaInfo* metaInfo)
    {
        ArrayItemInfo* arrayItemInfo = static_cast<ArrayItemInfo*>(this->parsingElement->top());
        arrayItemInfo->setValue(metaInfo);
    
        return new ArrayItemState(this->parsingElement);
    }
    
    JsonParserState* AppendState::append(MetaInfo* metaInfo)
    {
        MetaInfo* top = this->parsingElement->top();
    
        switch (top->getType())
        {
            case PARSING_ELEMENT::OBJECT_ITEM:
                return this->appendToObjectItem(metaInfo);
            case PARSING_ELEMENT::ARRAY_ITEM:
                return this->appendToArrayItem(metaInfo);
        }
    
        throw JsonAppendStateException();
    }
    
    JsonParserState* AppendState::appendToArray(MetaInfo* metaInfo, bool mustNextElem)
    {
        ArrayItemInfo* arrayItemInfo = static_cast<ArrayItemInfo*>(metaInfo);
        ArrayInfo* arrayInfo = static_cast<ArrayInfo*>(this->parsingElement->top());
    
        arrayInfo->append(arrayItemInfo);
    
        ArrayState* arrayState = new ArrayState(this->parsingElement);
    
        if (mustNextElem)
            arrayState->mustNextElement();
    
        return arrayState;
    }
}