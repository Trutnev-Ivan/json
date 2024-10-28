#include "ObjectState.h"

namespace json
{
    ObjectState::ObjectState(std::stack<MetaInfo*>* stack):
        JsonParserState(stack)
        {}
    
    void ObjectState::mustNextElem()
    {
        this->isMustNextElem = true;
    }
    
    JsonParserState* ObjectState::next(char c)
    {
        if (std::isspace(c))
            return this;
    
        if (c == '}')
        {
            if (this->isMustNextElem)
                throw JsonEmptyNextElementException();
    
            if (this->parsingElement->size() == 1)
                return new EndState(this->parsingElement);
            else
            {
                AppendState* appendState = new AppendState(this->parsingElement);
                return appendState->next(c);
            }
        }
        else if (c == '\'' || c == '"')
        {
            this->parsingElement->push(new ObjectItemInfo(c));
            return new ObjectItemState(this->parsingElement);
        }
        
        throw JsonParseException(c);
    }
}