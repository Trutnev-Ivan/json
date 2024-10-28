#include "StringState.h"

namespace json
{
    StringState::StringState(std::stack<MetaInfo*>* stack):
        JsonParserState(stack)
        {}
    
    JsonParserState* StringState::next(char c)
    {
        StringInfo* stringInfo = static_cast<StringInfo*>(this->parsingElement->top());

        if (stringInfo->getQuoteType() == c)
        {
            if (stringInfo->isEscaped())
            {
                stringInfo->appendChar(c);
                return this;
            }
            else
            {
                AppendState* appendState = new AppendState(this->parsingElement);
                JsonParserState* next = appendState->next(c);
    
                delete appendState;
                return next;
            }
        }
        else
        {
            stringInfo->appendChar(c);
            return this;
        }
    }
}