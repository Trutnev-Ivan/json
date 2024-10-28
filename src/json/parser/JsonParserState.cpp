#include "JsonParserState.h"

namespace json
{
    JsonParserState::JsonParserState(std::stack<MetaInfo*>* stack)
    {
        this->parsingElement = stack;
    }
    
    JsonParserState* JsonParserState::next(char c)
    {
        return nullptr;
    };
    
    MetaInfo* JsonParserState::getTopElement()
    {
        return this->topElement;
    }
}