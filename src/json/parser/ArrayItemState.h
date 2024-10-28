#pragma once
#include "JsonParserState.h"
#include "AppendState.h"

namespace json
{
    class ArrayItemState: public JsonParserState
    {
    public:
        ArrayItemState(std::stack<MetaInfo*>* stack);
        virtual JsonParserState* next(char c) override;
    };
}