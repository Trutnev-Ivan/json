#include "EndState.h"

namespace json
{
    EndState::EndState(std::stack<MetaInfo*>* stack):
        JsonParserState(stack)
        {
            this->topElement = this->parsingElement->top();
            this->parsingElement->pop();
        }
    
    JsonParserState* EndState::next(char c)
    {
        if (std::isspace(c) || c == EOF)
            return this;
    
        throw JsonParseException(c);
    }
}