#pragma once
#include "JsonParserState.h"
#include "AppendState.h"
#include "../meta/NumberInfo.h"

namespace json
{
    class NumberState: public JsonParserState
    {
    protected:
        bool hasPoint = false;
    public:
        NumberState(std::stack<MetaInfo*>* stack);
        virtual JsonParserState* next(char c) override;
    };
}