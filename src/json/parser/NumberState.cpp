#include "NumberState.h"

namespace json
{
    NumberState::NumberState(std::stack<MetaInfo*>* stack):
        JsonParserState(stack)
        {}
    
    JsonParserState* NumberState::next(char c)
    {
        NumberInfo* numberInfo = static_cast<NumberInfo*>(this->parsingElement->top());
        
        if (std::isdigit(c))
        {
            numberInfo->appendChar(c);
            return this;
        }
        else if (c == '-' && numberInfo->getValue().size() == 0)
        {
            numberInfo->appendChar(c);
            return this;
        }
        else if (c == '.')
        {
            if (this->hasPoint)
                throw JsonNumberPointException();
    
            this->hasPoint = true;
            numberInfo->appendChar(c);
            return this;
        }
        else if (c == ',' || c == ']' || c == '}' || std::isspace(c))
        {
            AppendState* appendState = new AppendState(this->parsingElement);
            JsonParserState* next = appendState->next(c);
    
            delete appendState;
            return next->next(c);
        }
        
        throw JsonParseException(c);
    }
}