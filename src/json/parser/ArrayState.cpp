#include "ArrayState.h"

namespace json
{
    ArrayState::ArrayState(std::stack<MetaInfo*>* stack):
        JsonParserState(stack)
        {}
    
    void ArrayState::mustNextElement()
    {
        this->isMustNextElement = true;
    }
    
    JsonParserState* ArrayState::next(char c)
    {
        if (std::isspace(c))
            return this;
    
        if (c == '[')
        {
            this->parsingElement->push(new ArrayItemInfo);
            this->parsingElement->push(new ArrayInfo);
            return new ArrayState(this->parsingElement);
        }
        else if (c == ']')
        {
            if (this->isMustNextElement)
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
            this->parsingElement->push(new ArrayItemInfo);
            this->parsingElement->push(new StringInfo(c));
            return new StringState(this->parsingElement);
        }
        else if (c == '{')
        {
            this->parsingElement->push(new ArrayItemInfo);
            this->parsingElement->push(new ObjectInfo);
            return new ObjectState(this->parsingElement);
        }
        else if (std::isdigit(c) || c == '-')
        {
            this->parsingElement->push(new ArrayItemInfo);
            this->parsingElement->push(new NumberInfo);
            NumberState* numberState = new NumberState(this->parsingElement);
            return numberState->next(c);
        }
        else if (c == 't' || c == 'f')
        {
            this->parsingElement->push(new ArrayItemInfo);
            this->parsingElement->push(new BoolInfo);
            BoolState* boolState = new BoolState(this->parsingElement);
            return boolState->next(c);
        }
        
        throw JsonParseException(c);
    }
}