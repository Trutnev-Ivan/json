#include "BoolState.h"

namespace json
{
    BoolState::BoolState(std::stack<MetaInfo*>* state):
        JsonParserState(state)
        {}
    
    JsonParserState* BoolState::next(char c)
    {   
        BoolInfo* boolInfo = static_cast<BoolInfo*>(this->parsingElement->top());
    
        if (c == ',' || c == ']' || c == '}' || std::isspace(c))
        {
            if (boolInfo->getValue() != "true" && boolInfo->getValue() != "false")
                throw JsonParseException(c);
    
            AppendState* appendState = new AppendState(this->parsingElement);
            JsonParserState* next = appendState->next(c);
            delete appendState;
    
            return next->next(c);
        }
    
        boolInfo->appendChar(c); // throws error
        return this;
    }
}